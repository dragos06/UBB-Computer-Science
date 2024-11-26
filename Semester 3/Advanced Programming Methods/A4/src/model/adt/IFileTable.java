package model.adt;

import exception.KeyNotFoundException;

import java.util.Set;

public interface IFileTable <K, V> {
    void insert(K key, V value);
    V getValue(K key) throws KeyNotFoundException;
    void remove(K key) throws KeyNotFoundException;
    boolean contains(K key);
    String toString();
    public Set<K> getKeys();
}
