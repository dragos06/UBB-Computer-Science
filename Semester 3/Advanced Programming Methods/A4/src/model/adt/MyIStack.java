package model.adt;
import exception.EmptyStackException;

public interface MyIStack<T> {
    void push(T element);
    T pop() throws EmptyStackException;
    int size();
    boolean isEmpty();
    String toString();
}
