package model.expressions;

import exception.ADTException;
import exception.ExpressionException;
import model.adt.MyIDictionary;
import model.adt.MyIHeap;
import model.value.MyIValue;

public class VariableExpression implements MyIExpression {
    private String variable;

    public VariableExpression(String variable) {
        this.variable = variable;
    }

    @Override
    public MyIValue eval(MyIDictionary<String, MyIValue> sym_table, MyIHeap heap) throws ADTException {
        return sym_table.getValue(variable);
    }

    @Override
    public String toString() {
        return variable;
    }

    @Override
    public MyIExpression deepCopy() {
        return new VariableExpression(new String(this.variable));
    }
}
