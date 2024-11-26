package view;

import controller.Controller;
import exception.ADTException;
import exception.ExpressionException;
import exception.RepoException;
import exception.StatementException;
import model.adt.MyIStack;
import model.expressions.ArithmeticalExpression;
import model.expressions.AritmeticalOperator;
import model.expressions.ValueExpression;
import model.expressions.VariableExpression;
import model.statement.*;
import model.types.MyBoolType;
import model.types.MyIntType;
import model.value.MyBoolValue;
import model.value.MyIntValue;

import java.util.Scanner;

public class View {
    private Controller controller;

    public View(Controller controller) {
        this.controller = controller;
    }

    private void displayMenu() {
        System.out.println("1. int v; v = 2; Print(v)");
        System.out.println("2. int a; int b; a = 2 + 3 * 5; b = a + 1; Print(b)");
        System.out.println("3. bool a; int v; a = true; (If a Then v = 2 Else v = 3); Print(v)");
        System.out.println("4. Exit\n");
    }

    public void run() {
        while (true) {
            System.out.println("Toy Language\n");
            displayMenu();

            Scanner scanner = new Scanner(System.in);
            System.out.println("Please choose an option: ");
            int user_option = scanner.nextInt();

            switch (user_option) {
                case 1: {
                    MyIStatement statement = new CompStatement(new VarDeclStatement("v", new MyIntType()), new CompStatement(new AssignStatement("v", new ValueExpression(new MyIntValue(2))), new PrintStatement(new VariableExpression("v"))));
                    this.controller.add(statement);
                    try {
                        this.controller.allStep();
                    } catch (StatementException | ADTException | ExpressionException | RepoException e) {
                        System.out.println(e.getMessage());
                    }
                    break;
                }
                case 2: {
                    MyIStatement statement = new CompStatement(new VarDeclStatement("a", new MyIntType()), new CompStatement(new VarDeclStatement("b", new MyIntType()), new CompStatement(new AssignStatement("a", new ArithmeticalExpression(new ValueExpression(new MyIntValue(2)), AritmeticalOperator.ADD, new ArithmeticalExpression(new ValueExpression(new MyIntValue(3)), AritmeticalOperator.MULTIPLY, new ValueExpression(new MyIntValue(5))))), new CompStatement(new AssignStatement("b", new ArithmeticalExpression(new VariableExpression("a"), AritmeticalOperator.ADD, new ValueExpression(new MyIntValue(1)))), new PrintStatement(new VariableExpression("b"))))));
                    this.controller.add(statement);
                    try {
                        this.controller.allStep();
                    } catch (StatementException | ADTException | ExpressionException | RepoException e) {
                        System.out.println(e.getMessage());
                    }
                    break;
                }
                case 3: {
                    MyIStatement statement = new CompStatement(new VarDeclStatement("a", new MyBoolType()), new CompStatement(new VarDeclStatement("v", new MyIntType()), new CompStatement(new AssignStatement("a", new ValueExpression(new MyBoolValue(true))), new CompStatement(new IfStatement(new AssignStatement("v", new ValueExpression(new MyIntValue(2))), new AssignStatement("v", new ValueExpression(new MyIntValue(3))), new VariableExpression("a")), new PrintStatement(new VariableExpression("v"))))));
                    this.controller.add(statement);
                    try {
                        this.controller.allStep();
                    } catch (StatementException | ADTException | ExpressionException |RepoException e) {
                        System.out.println(e.getMessage());
                    }
                    break;
                }
                case 4: {
                    System.out.println("Exiting...");
                    System.exit(0);
                }
                default:
                    System.out.println("Please choose an option from the list!");
                    break;
            }
        }
    }
}
