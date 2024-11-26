package model.types;

import model.value.MyIValue;

public interface MyIType {
    boolean equals(MyIType object);
    MyIValue getDefaultValue();
    String toString();
    MyIType deepCopy();
}
