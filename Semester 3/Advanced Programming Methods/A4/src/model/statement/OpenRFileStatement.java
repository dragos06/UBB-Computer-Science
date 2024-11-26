package model.statement;

import exception.ADTException;
import exception.ExpressionException;
import exception.StatementException;
import model.expressions.MyIExpression;
import model.state.PrgState;
import model.types.MyIntType;
import model.types.StringType;
import model.value.MyIValue;
import model.value.StringValue;

import java.io.*;

public class OpenRFileStatement implements MyIStatement {
    private MyIExpression exp;

    public OpenRFileStatement(MyIExpression exp) {
        this.exp = exp;
    }

    @Override
    public PrgState execute(PrgState prgState) throws StatementException, ADTException, ExpressionException {
        MyIValue evalValue = this.exp.eval(prgState.getSymTable(), prgState.getHeapTable());
        if (!evalValue.getType().equals(new StringType())) {
            throw new StatementException("Value type is not String");
        }
        if (prgState.getSymTable().contains(evalValue.toString())) {
            throw new StatementException("Key already exists");
        }
        try {
            BufferedReader bufferedReader = new BufferedReader(new FileReader(((StringValue) evalValue).toString()));
            prgState.getFileTable().insert((StringValue) evalValue, bufferedReader);
        } catch (IOException | IOError e) {
            throw new StatementException("File does not exist");
        }
        return prgState;
    }

    @Override
    public MyIStatement deepCopy() {
        return new OpenRFileStatement(this.exp.deepCopy());
    }

    @Override
    public String toString() {
        return "File opened: " + this.exp.toString();
    }
}
