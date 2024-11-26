package model.expressions;

import exception.ADTException;
import exception.ExpressionException;
import model.adt.MyIHeap;
import model.value.MyIValue;
import model.state.PrgState;
import model.adt.MyIDictionary;


public interface MyIExpression {
    MyIValue eval(MyIDictionary<String, MyIValue> sym_table, MyIHeap heap) throws ADTException, ExpressionException;

    MyIExpression deepCopy();

    String toString();
}
