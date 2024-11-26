package model.statement;

import exception.ADTException;
import exception.ExpressionException;
import exception.StatementException;
import model.expressions.MyIExpression;
import model.state.PrgState;
import model.types.StringType;
import model.value.MyIValue;
import model.value.StringValue;

import java.io.BufferedReader;
import java.io.IOException;

public class CloseRFileStatement implements MyIStatement {
    private MyIExpression exp;

    public CloseRFileStatement(MyIExpression exp) {
        this.exp = exp;
    }

    @Override
    public PrgState execute(PrgState prgState) throws StatementException, ADTException, ExpressionException {
        MyIValue evalValue = exp.eval(prgState.getSymTable(), prgState.getHeapTable());
        if (!evalValue.getType().equals(new StringType())) {
            throw new StatementException("Value type is not string");
        }
        if (!prgState.getFileTable().contains((StringValue) evalValue)) {
            throw new StatementException("File not opened");
        }
        BufferedReader bufferedReader = prgState.getFileTable().getValue((StringValue) evalValue);
        try {
            bufferedReader.close();
        } catch (IOException e) {
            throw new StatementException("Couldn't close buffer");
        }
        prgState.getFileTable().remove((StringValue) evalValue);
        return prgState;
    }

    @Override
    public MyIStatement deepCopy() {
        return new CloseRFileStatement(this.exp.deepCopy());
    }

    @Override
    public String toString() {
        return "File closed: " + this.exp.toString();
    }
}
