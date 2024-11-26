package model.state;

import model.adt.MyIDictionary;
import model.adt.MyIStack;
import model.adt.MyIList;
import model.statement.MyIStatement;
import model.value.MyIValue;
import model.value.StringValue;

import java.io.BufferedReader;

public class PrgState {
    private MyIDictionary<String, MyIValue> symTable;
    private MyIStack<MyIStatement> exeStack;
    private MyIList<String> output;
    private MyIStatement initialState;
    private MyIDictionary<StringValue, BufferedReader> fileTable;

    public PrgState(MyIDictionary<String, MyIValue> symTable, MyIStack<MyIStatement> exeStack, MyIList<String> output, MyIStatement initialState, MyIDictionary<StringValue, BufferedReader> fileTable) {
        this.symTable = symTable;
        this.exeStack = exeStack;
        this.output = output;
        this.fileTable = fileTable;
        this.initialState = initialState.deepCopy();
        this.exeStack.push(this.initialState);
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

    public MyIStatement getInitialState() {
        return initialState;
    }

    public void setInitialState(MyIStatement initialState) {
        this.initialState = initialState;
    }

    public MyIDictionary<StringValue, BufferedReader> getFileTable() {
        return fileTable;
    }

    public void setFileTable(MyIDictionary<StringValue, BufferedReader> fileTable) {
        this.fileTable = fileTable;
    }

    public String fileTableToString() {
        StringBuilder text = new StringBuilder();
        text.append("FileTable: \n");
        for (StringValue key : this.fileTable.getKeys()) {
            text.append(key).append("\n");
        }
        return text.toString();
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
        return symTable.toString() + "\n" + exeStack.toString() + "\n" + output.toString() + "\n" + this.fileTableToString() + "\n-----------------------------\n";
    }
}
