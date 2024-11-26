package repository;

import exception.RepoException;
import model.state.PrgState;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;

public class Repository implements IRepository {
    private List<PrgState> prgStateList;
    private int index;
    private String filename;

    public Repository(String filename) {
        this.prgStateList = new ArrayList<>();
        this.index = 0;
        this.filename = filename;
    }

    @Override
    public void add(PrgState prgState) {
        this.prgStateList.add(prgState);
    }

    @Override
    public PrgState getCrtPrg() {
        return this.prgStateList.get(this.index);
    }

    @Override
    public void next() {
        this.index++;
    }

    @Override
    public List<PrgState> getAllPrg() {
        return this.prgStateList;
    }

    @Override
    public void logPrgStateExec() throws RepoException {
        try {
            PrintWriter logFile = new PrintWriter(new BufferedWriter(new FileWriter(this.filename, true)));
            logFile.println(this.getCrtPrg().toString());
            logFile.close();
        } catch (IOException err) {
            throw new RepoException("File does not exist");
        }
    }
}
