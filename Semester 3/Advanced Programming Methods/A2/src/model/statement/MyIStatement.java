package model.statement;

import exception.ADTException;
import exception.ExpressionException;
import exception.StatementException;
import model.state.PrgState;

public interface MyIStatement {
    PrgState execute(PrgState prgState) throws StatementException, ADTException, ExpressionException;

}
