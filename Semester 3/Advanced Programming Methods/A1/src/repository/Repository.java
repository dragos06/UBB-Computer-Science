package repository;

import exception.RepositoryException;
import model.IVehicles;

public class Repository implements IRepository {
    private IVehicles[] vehicles;
    private int length;
    public final static int SIZE = 10;


    public Repository() {
        this.vehicles = new IVehicles[SIZE];
        this.length = 0;
    }

    @Override
    public void add(IVehicles vehicle) throws RepositoryException {
        if (this.length >= SIZE) {
            throw new RepositoryException("Array is full");
        }

        for (int i = 0; i < this.length; i++) {
            if (this.vehicles[i].getColor().equals(vehicle.getColor()) && this.vehicles[i].getType().equals(vehicle.getType())) {
                throw new RepositoryException("Vehicle already exists");
            }
        }
        this.vehicles[this.length++] = vehicle;

    }

    @Override
    public void delete(IVehicles vehicle) throws RepositoryException {
        if (this.length == 0) {
            throw new RepositoryException("Array is empty");
        }
        boolean found = false;
        for (int i = 0; i < this.length; i++) {
            if (this.vehicles[i].getColor().equals(vehicle.getColor()) && this.vehicles[i].getType().equals(vehicle.getType())) {
                found = true;
                if (i != this.length - 1) {
                    this.vehicles[i] = this.vehicles[this.length - 1];
                } else {
                    this.vehicles[i] = null;
                }
                this.length--;
            }
        }
        if (!found) {
            throw new RepositoryException("Couldn't find vehicle in repository");
        }
    }

    @Override
    public IVehicles[] getAll() {
        return this.vehicles;
    }

    @Override
    public int getLength() {
        return this.length;
    }
}
