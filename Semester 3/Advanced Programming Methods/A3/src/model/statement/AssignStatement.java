package model.statement;

import exception.ADTException;
import exception.ExpressionException;
import exception.StatementException;
import model.expressions.MyIExpression;
import model.state.PrgState;
import model.value.MyIValue;

public class AssignStatement implements MyIStatement {

    private String variableName;
    private MyIExpression expression;

    public AssignStatement(String variableName, MyIExpression expression) {
        this.variableName = variableName;
        this.expression = expression;
    }

    @Override
    public MyIStatement deepCopy() {
        return new AssignStatement(new String(this.variableName), this.expression.deepCopy());
    }

    @Override
    public PrgState execute(PrgState prgState) throws StatementException, ADTException, ExpressionException {
        if (!prgState.getSymTable().contains(this.variableName)) {
            throw new StatementException("Variable was not found");
        }
        MyIValue value = prgState.getSymTable().getValue(this.variableName);
        MyIValue evalValue = this.expression.eval(prgState.getSymTable());
        if (!value.getType().equals(evalValue.getType())) {
            throw new StatementException("Value type mismatch");
        }
        prgState.getSymTable().insert(this.variableName, evalValue);
        return prgState;

    }

    @Override
    public String toString() {
        return this.variableName + " = " + this.expression.toString();
    }

}
