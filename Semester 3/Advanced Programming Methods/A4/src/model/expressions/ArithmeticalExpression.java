package model.expressions;

import exception.ADTException;
import exception.ExpressionException;
import model.adt.MyIDictionary;
import model.adt.MyIHeap;
import model.types.MyIntType;
import model.value.MyIValue;
import model.value.MyIntValue;

public class ArithmeticalExpression implements MyIExpression {
    private MyIExpression left;
    private MyIExpression right;
    private AritmeticalOperator operator;

    public ArithmeticalExpression(MyIExpression left, AritmeticalOperator operator, MyIExpression right) {
        this.left = left;
        this.right = right;
        this.operator = operator;
    }

    @Override
    public MyIExpression deepCopy() {
        return new ArithmeticalExpression(this.left.deepCopy(), this.operator, this.right.deepCopy());
    }

    @Override
    public MyIValue eval(MyIDictionary<String, MyIValue> sym_table, MyIHeap heap) throws ADTException, ExpressionException {
        MyIValue value1 = this.left.eval(sym_table, heap);
        MyIValue value2 = this.right.eval(sym_table, heap);
        if (!value1.getType().equals(new MyIntType())) {
            throw new ExpressionException("First value is not int");
        }
        if (!value2.getType().equals(new MyIntType())) {
            throw new ExpressionException("Second value is not int");
        }
        MyIntValue int1 = (MyIntValue) value1;
        MyIntValue int2 = (MyIntValue) value2;

        switch (operator) {
            case ADD:
                return new MyIntValue(int1.getValue() + int2.getValue());
            case SUBTRACT:
                return new MyIntValue(int1.getValue() - int2.getValue());
            case MULTIPLY:
                return new MyIntValue(int1.getValue() * int2.getValue());
            case DIVIDE: {
                if (int2.getValue() == 0) {
                    throw new ExpressionException("Division by zero");
                }
                return new MyIntValue(int1.getValue() / int2.getValue());
            }
            default:
                throw new ExpressionException("Unknown operator");
        }
    }

    @Override
    public String toString() {
        return this.left.toString() + " " + this.operator + " " + this.right.toString();
    }
}
