package controller;

import exception.RepositoryException;
import model.IVehicles;
import repository.IRepository;
import repository.Repository;

public class Controller implements IController {
    private IRepository repository;

    public Controller(IRepository repository) {
        this.repository = repository;
    }

    @Override
    public void add(IVehicles vehicle) throws RepositoryException {
        this.repository.add(vehicle);
    }

    @Override
    public void delete(IVehicles vehicle) throws RepositoryException {
        this.repository.delete(vehicle);
    }

    @Override
    public IVehicles[] filterByColor(String color) {
        IVehicles[] vehicles = this.repository.getAll();
        IVehicles[] filtered = new IVehicles[Repository.SIZE];
        int currentPos = 0;

        for (int i = 0; i < this.repository.getLength(); i++) {
            if (vehicles[i].getColor().equals(color)) {
                filtered[currentPos++] = vehicles[i];
            }
        }
        return filtered;
    }

    @Override
    public int filterByColorLength(String color) {
        IVehicles[] vehicles = this.repository.getAll();
        int length = 0;

        for (int i = 0; i < this.repository.getLength(); i++) {
            if (vehicles[i].getColor().equals(color)) {
                length++;
            }
        }
        return length;
    }

    @Override
    public IVehicles[] getAll(){
        return this.repository.getAll();
    }

    @Override
    public int getLength(){
        return this.repository.getLength();
    }
}
