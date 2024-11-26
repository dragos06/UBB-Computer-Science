package repository;

import exception.RepoException;
import model.state.PrgState;

import java.util.List;

public interface IRepository {
    void add(PrgState prgState);
    PrgState getCrtPrg();
    List<PrgState> getAllPrg();
    void next();
    void logPrgStateExec() throws RepoException;
    void clearFile() throws RepoException;
}
