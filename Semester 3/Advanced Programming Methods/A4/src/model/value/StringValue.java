package model.value;

import model.types.MyIType;
import model.types.StringType;

public class StringValue implements MyIValue {
    private String value;

    public StringValue(String value) {
        this.value = value;
    }

    @Override
    public MyIType getType() {
        return new StringType();
    }

    public String getValue() {
        return value;
    }

    public void setValue(String value) {
        this.value = value;
    }

    @Override
    public boolean equals(MyIValue val) {
        return val.getType().equals(new StringType()) && ((StringValue) val).getValue().equals(this.value);
    }

    @Override
    public String toString() {
        return value;
    }
}
