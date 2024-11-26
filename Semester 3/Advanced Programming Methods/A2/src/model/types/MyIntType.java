package model.types;

import model.value.MyIValue;
import model.value.MyIntValue;

public class MyIntType implements MyIType {
    @Override
    public boolean equals(MyIType object) {
        return object instanceof MyIntType;
    }

    @Override
    public String toString() {
        return "int";
    }

    @Override
    public MyIValue getDefaultValue() {
        return new MyIntValue(0);
    }
}
