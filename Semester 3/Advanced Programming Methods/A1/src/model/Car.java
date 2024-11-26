package model;

public class Car implements IVehicles {
    protected String color;
    protected String type;

    public Car(String color){
        this.color = color;
        this.type = "Car";
    }

    @Override
    public String getColor() {
        return this.color;
    }

    @Override
    public String getType() {
        return this.type;
    }

    @Override
    public String toString() {
        return "Car " + this.color;
    }
}
