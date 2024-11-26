import model.expressions.ArithmeticalExpression;
import model.expressions.AritmeticalOperator;
import model.expressions.ValueExpression;
import model.expressions.VariableExpression;
import model.statement.*;
import model.types.MyBoolType;
import model.types.MyIntType;
import model.types.StringType;
import model.value.MyBoolValue;
import model.value.MyIntValue;
import model.value.StringValue;
import org.w3c.dom.Text;
import repository.Repository;
import repository.IRepository;
import controller.Controller;
import view.Interpreter;
import view.TextMenu;
import view.View;
import view.commands.ExitCommand;
import view.commands.RunExampleCommand;

public class Main {
    public static void main(String[] args) {
        Interpreter.main();
    }
}