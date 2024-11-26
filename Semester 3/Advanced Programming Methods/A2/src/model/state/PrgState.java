package model.state;

import model.adt.MyIDictionary;
import model.adt.MyIStack;
import model.adt.MyIList;
import model.statement.MyIStatement;
import model.value.MyIValue;

public class PrgState {
    private MyIDictionary<String, MyIValue> symTable;
    private MyIStack<MyIStatement> exeStack;
    private MyIList<String> output;

    public PrgState(MyIDictionary<String, MyIValue> symTable, MyIStack<MyIStatement> exeStack, MyIList<String> output, MyIStatement initialState) {
        this.symTable = symTable;
        this.exeStack = exeStack;
        this.output = output;
        this.exeStack.push(initialState);
    }

    public MyIStack<MyIStatement> getExeStack() {
        return exeStack;
    }

    public MyIDictionary<String, MyIValue> getSymTable() {
        return symTable;
    }

    public MyIList<String> getOutput() {
        return output;
    }

    public void setSymTable(MyIDictionary<String, MyIValue> symTable) {
        this.symTable = symTable;
    }

    public void setExeStack(MyIStack<MyIStatement> exeStack) {
        this.exeStack = exeStack;
    }

    public void setOutput(MyIList<String> output) {
        this.output = output;
    }

    @Override
    public String toString() {
        return symTable.toString() + " " + exeStack.toString() + " " + output.toString();
    }
}
