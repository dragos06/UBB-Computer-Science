package model.statement;

import model.state.PrgState;

public class NopStatement implements MyIStatement {
    @Override
    public PrgState execute(PrgState prgState) {
        return null;
    }

    @Override
    public String toString() {
        return "NopStatement";
    }
}
