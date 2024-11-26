package model.expressions;

import exception.ADTException;
import exception.ExpressionException;
import model.adt.MyIDictionary;
import model.value.MyIValue;

public class VariableExpression implements MyIExpression{
    private String variable;

    public VariableExpression(String variable){
        this.variable = variable;
    }

    @Override
    public MyIValue eval(MyIDictionary<String, MyIValue> sym_table) throws ADTException{
        return sym_table.getValue(variable);
    }

    @Override
    public String toString(){
        return variable;
    }
}
