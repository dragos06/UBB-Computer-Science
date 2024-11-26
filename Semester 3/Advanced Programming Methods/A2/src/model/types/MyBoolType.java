package model.types;

import model.value.MyBoolValue;
import model.value.MyIValue;

public class MyBoolType implements MyIType{
    @Override
    public boolean equals(MyIType object) {
        return object instanceof MyBoolType;
    }

    @Override
    public String toString(){
        return "bool";
    }

    @Override
    public MyIValue getDefaultValue() {
        return new MyBoolValue(false);
    }
}
