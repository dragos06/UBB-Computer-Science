package model.adt;
import exception.EmptyStackException;

public interface MyIStack<T> {
    public void push(T element);
    public T pop() throws EmptyStackException;
    public int size();
    public boolean isEmpty();
}
