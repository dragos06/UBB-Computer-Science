package model.adt;

import exception.KeyNotFoundException;

import java.util.HashMap;
import java.util.Map;
import java.util.Set;

public class FileTable<K, V> implements IFileTable<K, V> {
    private Map<K, V> fileTable;

    public FileTable() {
        this.fileTable = new HashMap<>();
    }

    public Map<K, V> getFileTable() {
        return fileTable;
    }

    public void setFileTable(Map<K, V> fileTable) {
        this.fileTable = fileTable;
    }

    @Override
    public void insert(K key, V value) {
        this.fileTable.put(key, value);
    }

    @Override
    public V getValue(K key) throws KeyNotFoundException {
        if (!this.fileTable.containsKey(key)) {
            throw new KeyNotFoundException("Key not found");
        }
        return this.fileTable.get(key);
    }

    @Override
    public void remove(K key) throws KeyNotFoundException {
        if (!this.fileTable.containsKey(key)) {
            throw new KeyNotFoundException("Key not found");
        }
        this.fileTable.remove(key);
    }

    @Override
    public boolean contains(K key) {
        return this.fileTable.containsKey(key);
    }

    @Override
    public Set<K> getKeys() {
        return this.fileTable.keySet();
    }

    @Override
    public String toString() {
        StringBuilder text = new StringBuilder();
        text.append("FileTable: \n");
        for (K key : this.fileTable.keySet()) {
            text.append(key).append("\n");
        }
        return text.toString();
    }
}
