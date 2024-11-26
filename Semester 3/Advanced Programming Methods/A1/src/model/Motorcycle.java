package model;

public class Motorcycle implements IVehicles {
    protected String color;
    protected String type;

    public Motorcycle(String color) {
        this.color = color;
        this.type = "Motorcycle";
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
        return "Motorcycle " + this.color;
    }


}
