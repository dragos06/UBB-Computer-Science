package model.value;

import model.types.MyIType;

public interface MyIValue {
    MyIType getType();
    boolean equals(MyIValue other);
    String toString();
}
