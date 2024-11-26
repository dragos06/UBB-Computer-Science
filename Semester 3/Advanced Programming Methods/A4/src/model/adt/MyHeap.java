package model.adt;

import exception.KeyNotFoundException;
import model.value.MyIValue;

import java.util.HashMap;
import java.util.Map;
import java.util.Set;

public class MyHeap implements MyIHeap {
    private Map<Integer, MyIValue> heap;
    private Integer freeLocation = 1;

    @Override
    public Map<Integer, MyIValue> getHeap() {
        return heap;
    }

    @Override
    public void setHeap(Map<Integer, MyIValue> heap) {
        this.heap = heap;
    }

    public Integer getFreeLocation() {
        return freeLocation;
    }

    public void setFreeLocation(Integer freeLocation) {
        this.freeLocation = freeLocation;
    }

    public MyHeap() {
        this.heap = new HashMap<>();
    }

    public Map<Integer, MyIValue> getHeapTable() {
        return heap;
    }


    @Override
    public Integer insert(MyIValue value) {
        this.heap.put(freeLocation, value);
        this.freeLocation += 1;
        return this.freeLocation - 1;
    }

    @Override
    public void update(Integer key, MyIValue value) throws KeyNotFoundException {
        if (!this.heap.containsKey(key)) {
            throw new KeyNotFoundException("Address is not allocated in heap");
        }
        this.heap.put(key, value);
    }

    @Override
    public MyIValue getValue(Integer key) throws KeyNotFoundException {
        if (!this.heap.containsKey(key)) {
            throw new KeyNotFoundException("Address in heap was not found");
        }
        return this.heap.get(key);
    }

    @Override
    public void remove(Integer key) throws KeyNotFoundException {
        if (!this.heap.containsKey(key)) {
            throw new KeyNotFoundException("Address in heap was not found");
        }
        this.heap.remove(key);
    }

    @Override
    public boolean contains(Integer key) {
        return this.heap.containsKey(key);
    }

    @Override
    public Set<Integer> getKeys() {
        return this.heap.keySet();
    }

    @Override
    public String toString() {
        StringBuilder text = new StringBuilder();
        text.append("HeapTable: \n");
        for (Integer key : this.heap.keySet()) {
            text.append(key).append(" -> ").append(this.heap.get(key)).append("\n");
        }
        return text.toString();
    }
}
