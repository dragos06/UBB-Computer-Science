package model.adt;

import exception.KeyNotFoundException;

import java.util.Map;
import java.util.Set;

public interface MyIDictionary<K, V> {
    public Map<K, V> getMap();

    void insert(K key, V value);

    V getValue(K key) throws KeyNotFoundException;

    void remove(K key) throws KeyNotFoundException;

    boolean contains(K key);

    String toString();

    Set<K> getKeys();
}
