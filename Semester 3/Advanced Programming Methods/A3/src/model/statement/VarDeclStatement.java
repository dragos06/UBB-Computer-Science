package model.statement;

import exception.ADTException;
import exception.ExpressionException;
import exception.StatementException;
import model.state.PrgState;
import model.types.MyIType;

public class VarDeclStatement implements MyIStatement {
    private String name;
    private MyIType type;

    public VarDeclStatement(String name, MyIType type) {
        this.name = name;
        this.type = type;
    }

    @Override
    public PrgState execute(PrgState prgState) throws StatementException, ADTException, ExpressionException {
        // TO CHECK IF VARIABLE ALREADY EXISTS
        prgState.getSymTable().insert(this.name, this.type.getDefaultValue());
        return prgState;
    }

    @Override
    public MyIStatement deepCopy() {
        return new VarDeclStatement(new String(this.name), this.type.deepCopy());
    }

    @Override
    public String toString() {
        return this.type + " " + this.name;
    }
}
