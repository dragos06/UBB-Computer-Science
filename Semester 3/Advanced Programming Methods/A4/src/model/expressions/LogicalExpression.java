package model.expressions;

import exception.ADTException;
import exception.ExpressionException;
import model.adt.MyIDictionary;
import model.adt.MyIHeap;
import model.types.MyBoolType;
import model.value.MyBoolValue;
import model.value.MyIValue;

public class LogicalExpression implements MyIExpression {
    private MyIExpression left;
    private MyIExpression right;
    private LogicalOperator operator;

    public LogicalExpression(MyIExpression left, MyIExpression right, LogicalOperator operator) {
        this.left = left;
        this.right = right;
        this.operator = operator;
    }

    @Override
    public MyIValue eval(MyIDictionary<String, MyIValue> sym_table, MyIHeap heap) throws ADTException, ExpressionException {
        MyIValue evaluatedExpressionLeft = this.left.eval(sym_table, heap);
        MyIValue evaluatedExpressionRight = this.right.eval(sym_table, heap);
        if (!evaluatedExpressionLeft.getType().equals(new MyBoolType())) {
            throw new ExpressionException("Left expression is not of type BoolType");
        }
        if (!evaluatedExpressionRight.getType().equals(new MyBoolType())) {
            throw new ExpressionException("Right expression is not of type BoolType");
        }
        MyBoolValue bool1 = (MyBoolValue) evaluatedExpressionLeft;
        MyBoolValue bool2 = (MyBoolValue) evaluatedExpressionRight;
        switch (operator) {
            case AND:
                return new MyBoolValue(bool1.getValue() && bool2.getValue());
            case OR:
                return new MyBoolValue(bool1.getValue() || bool2.getValue());
            default:
                throw new ExpressionException("Unknown operator");
        }
    }

    @Override
    public MyIExpression deepCopy() {
        return new LogicalExpression(this.left.deepCopy(),  this.right.deepCopy(), this.operator);
    }

    @Override
    public String toString() {
        return left.toString() + " " + operator + " " + right.toString();
    }
}
