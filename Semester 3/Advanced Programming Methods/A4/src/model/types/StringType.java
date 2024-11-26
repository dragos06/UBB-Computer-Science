package model.types;

import model.value.MyIValue;
import model.value.StringValue;

public class StringType implements MyIType {
    public StringType() {
    }

    @Override
    public boolean equals(MyIType object) {
        return object instanceof StringType;
    }

    @Override
    public MyIValue getDefaultValue() {
        return new StringValue("");
    }

    @Override
    public String toString() {
        return "String";
    }

    @Override
    public MyIType deepCopy() {
        return new StringType();
    }
}
