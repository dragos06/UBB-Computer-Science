package model.expressions;

import exception.ADTException;
import exception.ExpressionException;
import model.adt.MyIDictionary;
import model.adt.MyIHeap;
import model.value.MyIValue;

public class ValueExpression implements MyIExpression {
    private MyIValue value;

    public ValueExpression(MyIValue value) {
        this.value = value;
    }

    @Override
    public MyIValue eval(MyIDictionary<String, MyIValue> sym_table, MyIHeap heap) {
        return value;
    }

    @Override
    public MyIExpression deepCopy() {
        return new ValueExpression(this.value);
    }

    @Override
    public String toString() {
        return this.value.toString();
    }
}
