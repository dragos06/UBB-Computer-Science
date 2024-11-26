package view;

import controller.IController;
import exception.RepositoryException;
import model.*;

import java.util.InputMismatchException;
import java.util.Scanner;

public class View implements IView {
    private IController controller;

    public View(IController controller) {
        this.controller = controller;
    }

    @Override
    public void displayMenu() {
        System.out.println("\n\nVehicles Garage\n\n");
        System.out.println("1. Add Car");
        System.out.println("2. Add Motorcycle");
        System.out.println("3. Add Bicycle");
        System.out.println("4. Delete Car");
        System.out.println("5. Delete Motorcycle");
        System.out.println("6. Delete Bicycle");
        System.out.println("7. Filter Vehicles by Color");
        System.out.println("8. Display all vehicles");
        System.out.println("0. Exit\n");
    }

    @Override
    public void addCar() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Please enter the color of the car: ");
        String color = scanner.nextLine();

        Car car = new Car(color);
        try {
            this.controller.add(car);
        } catch (RepositoryException e) {
            System.out.println("Repository Exception: " + e.getMessage());
        }
    }

    @Override
    public void addMotorcycle() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Please enter the color of the motorcycle: ");
        String color = scanner.nextLine();

        Motorcycle motorcycle = new Motorcycle(color);
        try {
            this.controller.add(motorcycle);
        } catch (RepositoryException e) {
            System.out.println("Repository Exception: " + e.getMessage());
        }
    }

    @Override
    public void addBicycle() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Please enter the color of the bicycle: ");
        String color = scanner.nextLine();

        Bicycle bicycle = new Bicycle(color);
        try {
            this.controller.add(bicycle);
        } catch (RepositoryException e) {
            System.out.println("Repository Exception: " + e.getMessage());
        }
    }

    @Override
    public void deleteCar() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Please enter the color of the car: ");
        String color = scanner.nextLine();

        Car car = new Car(color);
        try {
            this.controller.delete(car);
        } catch (RepositoryException e) {
            System.out.println("Repository Exception: " + e.getMessage());
        }
    }

    @Override
    public void deleteMotorcycle() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Please enter the color of the motorcycle: ");
        String color = scanner.nextLine();

        Motorcycle motorcycle = new Motorcycle(color);
        try {
            this.controller.delete(motorcycle);
        } catch (RepositoryException e) {
            System.out.println("Repository Exception: " + e.getMessage());
        }
    }

    @Override
    public void deleteBicycle() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Please enter the color of the bicycle: ");
        String color = scanner.nextLine();

        Bicycle bicycle = new Bicycle(color);
        try {
            this.controller.delete(bicycle);
        } catch (RepositoryException e) {
            System.out.println("Repository Exception: " + e.getMessage());
        }
    }

    @Override
    public void filterByColor() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Please enter the color to filter by: ");
        String color = scanner.nextLine();

        IVehicles[] vehicles = this.controller.filterByColor(color);
        int length = this.controller.filterByColorLength(color);
        for (int i = 0; i < length; i++) {
            System.out.println(vehicles[i]);
        }
    }

    @Override
    public void displayAll() {
        IVehicles[] vehicles = this.controller.getAll();
        int length = this.controller.getLength();
        for (int i = 0; i < length; i++) {
            System.out.println(vehicles[i]);
        }
    }

    @Override
    public void run() {
        Scanner scanner = new Scanner(System.in);
        while (true) {
            this.displayMenu();
            System.out.println("Please choose an option: ");
            try {
                int user_option = scanner.nextInt();
                switch (user_option) {
                    case 1: // add_car
                        this.addCar();
                        break;
                    case 2: // add_motorcycle
                        this.addMotorcycle();
                        break;
                    case 3: // add_bicycle
                        this.addBicycle();
                        break;
                    case 4: // delete_car
                        this.deleteCar();
                        break;
                    case 5: // delete_motorcycle
                        this.deleteMotorcycle();
                        break;
                    case 6: // delete_bicycle
                        this.deleteBicycle();
                        break;
                    case 7:
                        this.filterByColor();
                        break;
                    case 8:
                        this.displayAll();
                        break;
                    case 0:
                        System.out.println("Exiting...");
                        System.exit(0);
                    default:
                        System.out.println("Please choose an option from the list");
                        break;
                }
            }
            catch (InputMismatchException e){
                System.out.println("Invalid input");
                scanner.next();
            }
        }
    }
}

