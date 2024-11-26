package controller;

import exception.ADTException;
import exception.ExpressionException;
import exception.RepoException;
import exception.StatementException;
import model.adt.*;
import model.state.PrgState;
import model.statement.CompStatement;
import model.statement.MyIStatement;
import model.value.MyIValue;
import model.value.StringValue;
import repository.IRepository;

import java.io.BufferedReader;

public class Controller {
    private IRepository repository;

    public Controller(IRepository repository) {
        this.repository = repository;
    }

    public void add(MyIStatement statement) {
        PrgState my_state = new PrgState(new MyDictionary<String, MyIValue>(), new MyStack<MyIStatement>(), new MyList<String>(), statement, new MyDictionary<StringValue, BufferedReader>());
        this.repository.add(my_state);
    }

    public PrgState oneStep(PrgState prgState) throws StatementException, ADTException, ExpressionException {
        MyIStack<MyIStatement> exeStack = prgState.getExeStack();
        MyIStatement crtStatement = exeStack.pop();
        return crtStatement.execute(prgState);
    }

    public void allStep() throws StatementException, ADTException, ExpressionException, RepoException {
        PrgState prgState = this.repository.getCrtPrg();
        this.repository.logPrgStateExec();
        while (!prgState.getExeStack().isEmpty()) {
            this.oneStep(prgState);
            this.repository.logPrgStateExec();
        }
    }

}
