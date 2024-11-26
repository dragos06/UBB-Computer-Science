package view;

import exception.ADTException;
import exception.ExpressionException;
import exception.RepoException;
import exception.StatementException;
import view.commands.Command;

import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class TextMenu {
    private Map<String, Command> map;

    public TextMenu() {
        this.map = new HashMap<>();
    }

    public void addCommand(Command command) {
        this.map.put(command.getKey(), command);
    }

    private void printMenu() {
        for (Command cm : this.map.values()) {
            String line = String.format("%4s: %s", cm.getKey(), cm.getDescription());
            System.out.println(line);
        }
    }

    public void show() {
        while (true) {
            Scanner sc = new Scanner(System.in);
            printMenu();
            System.out.println("Please choose an option: ");
            String line = sc.nextLine();
            Command cm = this.map.get(line);
            if (cm == null) {
                System.out.println("Invalid command");
                continue;
            }
            try{
            cm.execute();
            }
            catch (StatementException | ADTException | RepoException | ExpressionException e){
                System.out.println(e.getMessage());
            }

        }
    }
}
