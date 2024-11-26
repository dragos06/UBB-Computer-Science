package controller;

import exception.RepositoryException;
import model.IVehicles;
import repository.IRepository;

public interface IController {
    void add(IVehicles vehicle) throws RepositoryException;
    void delete(IVehicles vehicle) throws RepositoryException;
    IVehicles[] filterByColor(String color);
    int filterByColorLength(String color);
    IVehicles[] getAll();
    int getLength();
}
