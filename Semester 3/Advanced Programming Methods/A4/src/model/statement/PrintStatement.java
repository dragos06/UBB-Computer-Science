package model.statement;

import exception.ADTException;
import exception.ExpressionException;
import exception.StatementException;
import model.state.PrgState;
import model.expressions.MyIExpression;
import model.value.MyIValue;

import javax.naming.ldap.ExtendedRequest;


public class PrintStatement implements MyIStatement {
    private MyIExpression expression;

    public PrintStatement(MyIExpression expression) {
        this.expression = expression;
    }

    @Override
    public PrgState execute(PrgState prgState) throws ADTException, ExpressionException {
        MyIValue result = this.expression.eval(prgState.getSymTable(), prgState.getHeapTable());
        prgState.getOutput().add(result.toString());
        return prgState;
    }

    @Override
    public MyIStatement deepCopy() {
        return new PrintStatement(this.expression.deepCopy());
    }

    @Override
    public String toString() {
        return "print(" + expression.toString() + ")";
    }
}
