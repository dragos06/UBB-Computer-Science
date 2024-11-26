package view;
import model.IVehicles;

public interface IView {
    void displayMenu();

    void addCar();

    void addMotorcycle();

    void addBicycle();

    void deleteCar();

    void deleteMotorcycle();

    void deleteBicycle();

    void filterByColor();

    void displayAll();

    void run();
}
