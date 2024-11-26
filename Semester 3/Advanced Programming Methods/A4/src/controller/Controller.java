package controller;

import exception.ADTException;
import exception.ExpressionException;
import exception.RepoException;
import exception.StatementException;
import model.adt.*;
import model.state.PrgState;
import model.statement.CompStatement;
import model.statement.MyIStatement;
import model.value.MyIValue;
import model.value.RefValue;
import model.value.StringValue;
import repository.IRepository;

import java.io.BufferedReader;
import java.util.Collection;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

public class Controller {
    private IRepository repository;

    public Controller(IRepository repository) {
        this.repository = repository;
    }

    public void add(MyIStatement statement) {
        PrgState my_state = new PrgState(new MyDictionary<String, MyIValue>(), new MyStack<MyIStatement>(), new MyList<String>(), statement, new FileTable<StringValue, BufferedReader>(), new MyHeap());
        this.repository.add(my_state);
    }

    public PrgState oneStep(PrgState prgState) throws StatementException, ADTException, ExpressionException {
        MyIStack<MyIStatement> exeStack = prgState.getExeStack();
        MyIStatement crtStatement = exeStack.pop();
        return crtStatement.execute(prgState);
    }

    public void allStep() throws StatementException, ADTException, ExpressionException, RepoException {
        PrgState prgState = this.repository.getCrtPrg();
        this.repository.clearFile();
        this.repository.logPrgStateExec();
        while (!prgState.getExeStack().isEmpty()) {
            this.oneStep(prgState);
            this.repository.logPrgStateExec();
            prgState.getHeapTable().setHeap(safeGarbageCollector(getAddrFromSymTable(prgState.getSymTable().getMap().values()), getAddrFromHeapTable(prgState.getHeapTable().getHeap().values()), prgState.getHeapTable().getHeap()));
            this.repository.logPrgStateExec();
        }
    }

    public Map<Integer, MyIValue> safeGarbageCollector(List<Integer> symTableAddr, List<Integer> heapTableAddr, Map<Integer, MyIValue> heapTable) {
        return heapTable.entrySet().stream()
                .filter(e -> symTableAddr.contains(e.getKey()) || heapTableAddr.contains(e.getKey()))
                .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));
    }

    public List<Integer> getAddrFromSymTable(Collection<MyIValue> symTableValues) {
        return symTableValues.stream()
                .filter(v -> v instanceof RefValue)
                .map(v -> {
                    RefValue v1 = (RefValue) v;
                    return v1.getAddress();
                })
                .collect(Collectors.toList());
    }

    public List<Integer> getAddrFromHeapTable(Collection<MyIValue> heapTableValues) {
        return heapTableValues.stream()
                .filter(v -> v instanceof RefValue)
                .map(v -> {
                    RefValue v1 = (RefValue) v;
                    return v1.getAddress();
                })
                .collect(Collectors.toList());
    }

}
