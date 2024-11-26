package model;

public class Bicycle implements IVehicles {
    protected String color;
    protected String type;

    public Bicycle(String color) {
        this.color = color;
        this.type = "Bicycle";
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
        return "Bicycle " + this.color;
    }
}
