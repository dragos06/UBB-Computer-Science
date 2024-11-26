package model.statement;

import exception.ADTException;
import exception.ExpressionException;
import exception.StatementException;
import model.expressions.MyIExpression;
import model.state.PrgState;
import model.types.RefType;
import model.value.MyIValue;
import model.value.RefValue;

public class HeapAllocationStatement implements MyIStatement {
    private String variableName;
    private MyIExpression expression;

    public HeapAllocationStatement(String variableName, MyIExpression expression) {
        this.variableName = variableName;
        this.expression = expression;
    }

    @Override
    public PrgState execute(PrgState prgState) throws StatementException, ADTException, ExpressionException {
        if (!prgState.getSymTable().contains(this.variableName)) {
            throw new StatementException("Variable is not in the SymTable, cannot allocate");
        }
        MyIValue varValue = prgState.getSymTable().getValue(this.variableName);
        if (!(varValue.getType() instanceof RefType)) {
            throw new StatementException("Variable in SymTable is not of RefType");
        }
        MyIValue evalValue = this.expression.eval(prgState.getSymTable(), prgState.getHeapTable());
        RefValue refValue = (RefValue) varValue;
        if (!evalValue.getType().equals(refValue.getLocationType())) {
            throw new StatementException("The type of the variable does not match the type of the allocated value");
        }
        Integer adr = prgState.getHeapTable().insert(evalValue);
        prgState.getSymTable().insert(this.variableName, new RefValue(adr, evalValue.getType()));
        return prgState;
    }

    @Override
    public MyIStatement deepCopy() {
        return new HeapAllocationStatement(new String(this.variableName), this.expression.deepCopy());
    }

    @Override
    public String toString() {
        return this.variableName + "=new(" + this.expression + ")";
    }
}
