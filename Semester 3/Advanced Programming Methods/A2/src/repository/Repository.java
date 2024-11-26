package repository;

import model.state.PrgState;

import java.util.ArrayList;
import java.util.List;

public class Repository implements IRepository {
    private List<PrgState> prgStateList;
    private int index;

    public Repository() {
        this.prgStateList = new ArrayList<>();
        this.index = 0;
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
}
