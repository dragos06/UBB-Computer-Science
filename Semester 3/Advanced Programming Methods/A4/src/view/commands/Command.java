package view.commands;

import exception.ADTException;
import exception.ExpressionException;
import exception.RepoException;
import exception.StatementException;

public abstract class Command {
    private String key;
    private String description;

    public Command(String key, String description) {
        this.key = key;
        this.description = description;
    }

    public abstract void execute() throws StatementException, ADTException, RepoException, ExpressionException;

    public String getKey() {
        return this.key;
    }
    public String getDescription(){
        return this.description;
    }
}
