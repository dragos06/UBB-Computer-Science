package view.commands;

import controller.Controller;
import exception.ADTException;
import exception.ExpressionException;
import exception.RepoException;
import exception.StatementException;

public class RunExampleCommand extends Command {
    private Controller controller;

    public RunExampleCommand(String key, String description, Controller controller) {
        super(key, description);
        this.controller = controller;
    }

    @Override
    public void execute(){
        try {
            controller.allStep();
        }
        catch (StatementException | ADTException | ExpressionException | RepoException e){
            System.out.println(e.getMessage());
        }
    }

}
