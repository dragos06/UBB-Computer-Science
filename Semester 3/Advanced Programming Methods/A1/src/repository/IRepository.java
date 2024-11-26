package repository;

import model.IVehicles;
import exception.RepositoryException;

public interface IRepository {
    void add(IVehicles vehicle) throws RepositoryException;
    void delete(IVehicles vehicle) throws RepositoryException;
    IVehicles[] getAll();
    int getLength();
}
