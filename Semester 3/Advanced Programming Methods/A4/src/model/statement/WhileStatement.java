package model.statement;

import exception.ADTException;
import exception.ExpressionException;
import exception.StatementException;
import model.expressions.MyIExpression;
import model.state.PrgState;
import model.types.MyBoolType;
import model.value.MyBoolValue;
import model.value.MyIValue;

public class WhileStatement implements MyIStatement {
    MyIExpression expression;
    MyIStatement statement;

    public WhileStatement(MyIExpression expression, MyIStatement statement) {
        this.expression = expression;
        this.statement = statement;
    }

    @Override
    public PrgState execute(PrgState prgState) throws StatementException, ADTException, ExpressionException {
        MyIValue value = this.expression.eval(prgState.getSymTable(), prgState.getHeapTable());
        if (!value.getType().equals(new MyBoolType())) {
            throw new StatementException("Condition expression is not a boolean");
        }
        MyBoolValue boolValue = (MyBoolValue) value;
        if (boolValue.getValue()) {
            prgState.getExeStack().push(this);
            prgState.getExeStack().push(statement);
        }
        return prgState;
    }

    @Override
    public MyIStatement deepCopy() {
        return new WhileStatement(this.expression.deepCopy(), this.statement.deepCopy());
    }

    @Override
    public String toString() {
        return "While(" + this.expression + "){" + this.statement + "}";
    }
}
