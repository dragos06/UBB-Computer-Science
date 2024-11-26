package model.expressions;

import exception.ADTException;
import exception.ExpressionException;
import model.value.MyIValue;
import model.state.PrgState;
import model.adt.MyIDictionary;


public interface MyIExpression {
    MyIValue eval(MyIDictionary<String, MyIValue> sym_table) throws ADTException, ExpressionException;
    MyIExpression deepCopy();
    String toString();
}
