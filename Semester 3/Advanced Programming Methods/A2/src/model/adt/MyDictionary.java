package model.adt;

import exception.KeyNotFoundException;

import java.util.Map;
import java.util.HashMap;

public class MyDictionary<K, V> implements MyIDictionary<K, V> {
    private Map<K, V> map;

    public MyDictionary() {
        this.map = new HashMap<>();
    }

    public Map<K, V> getMap() {
        return map;
    }

    @Override
    public void insert(K key, V value) {
        this.map.put(key, value);
    }

    @Override
    public V getValue(K key) throws KeyNotFoundException {
        if (!this.map.containsKey(key)) {
            throw new KeyNotFoundException("Key not found");
        }
        return this.map.get(key);
    }

    @Override
    public void remove(K key) throws KeyNotFoundException {
        if (!this.map.containsKey(key)) {
            throw new KeyNotFoundException("Key not found");
        }
        this.map.remove(key);
    }

    @Override
    public boolean contains(K key) {
        return this.map.containsKey(key);
    }

    @Override
    public String toString() {
        StringBuilder str = new StringBuilder();
        for (K key : this.map.keySet()) {
            str.append(key).append(" -> ").append(this.map.get(key)).append("\n");
        }
        return "MyDictionary contains " + str + "\n";
    }
}
