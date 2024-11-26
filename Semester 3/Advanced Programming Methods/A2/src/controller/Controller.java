package controller;

import exception.ADTException;
import exception.ExpressionException;
import exception.StatementException;
import model.adt.*;
import model.state.PrgState;
import model.statement.CompStatement;
import model.statement.MyIStatement;
import model.value.MyIValue;
import repository.IRepository;

public class Controller {
    private IRepository repository;

    public Controller(IRepository repository) {
        this.repository = repository;
    }

    public void add(MyIStatement statement) {
        PrgState my_state = new PrgState(new MyDictionary<String, MyIValue>(), new MyStack<MyIStatement>(), new MyList<String>(), statement);
        this.repository.add(my_state);
    }

    public PrgState oneStep(PrgState prgState) throws StatementException, ADTException, ExpressionException {
        MyIStack<MyIStatement> exeStack = prgState.getExeStack();
        MyIStatement crtStatement = exeStack.pop();
        return crtStatement.execute(prgState);
    }

    public void allStep() throws StatementException, ADTException, ExpressionException {
        PrgState prgState = this.repository.getCrtPrg();
        while (!prgState.getExeStack().isEmpty()) {
            this.oneStep(prgState);
            System.out.println(prgState);
            System.out.println("_______________________________________\n");
        }
        this.repository.next();
    }

}
