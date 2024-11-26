package model.state;

import model.adt.*;
import model.statement.MyIStatement;
import model.value.MyIValue;
import model.value.StringValue;

import java.io.BufferedReader;

public class PrgState {
    private MyIDictionary<String, MyIValue> symTable;
    private MyIStack<MyIStatement> exeStack;
    private MyIList<String> output;
    private MyIStatement initialState;
    private IFileTable<StringValue, BufferedReader> fileTable;
    private MyIHeap heapTable;

    public PrgState(MyIDictionary<String, MyIValue> symTable, MyIStack<MyIStatement> exeStack, MyIList<String> output, MyIStatement initialState, FileTable<StringValue, BufferedReader> fileTable, MyIHeap heapTable) {
        this.symTable = symTable;
        this.exeStack = exeStack;
        this.output = output;
        this.fileTable = fileTable;
        this.heapTable = heapTable;
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

    public IFileTable<StringValue, BufferedReader> getFileTable() {
        return fileTable;
    }

    public MyIHeap getHeapTable() {
        return heapTable;
    }

    @Override
    public String toString() {
        return symTable.toString() + "\n" + exeStack.toString() + "\n" + output.toString() + "\n" + fileTable.toString() + "\n" + heapTable.toString() + "\n-----------------------------\n";
    }
}
