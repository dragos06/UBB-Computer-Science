package model.statement;

import exception.ADTException;
import exception.StatementException;
import model.state.PrgState;

public class CompStatement implements MyIStatement{
    private MyIStatement statement1;
    private MyIStatement statement2;

    public CompStatement(MyIStatement statement1, MyIStatement statement2){
        this.statement1 = statement1;
        this.statement2 = statement2;
    }

    @Override
    public PrgState execute(PrgState prgState) {
        prgState.getExeStack().push(statement2);
        prgState.getExeStack().push(statement1);

        return prgState;
    }

    @Override
    public MyIStatement deepCopy() {
        return new CompStatement(this.statement1.deepCopy(), this.statement2.deepCopy());
    }

    @Override
    public String toString(){
        return statement1.toString() + ";" + statement2.toString();
    }
}
