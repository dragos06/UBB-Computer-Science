package model.types;

import model.value.MyIValue;
import model.value.RefValue;

public class RefType implements MyIType {
    MyIType inner;

    public RefType(MyIType inner) {
        this.inner = inner;
    }

    MyIType getInner() {
        return this.inner;
    }

    @Override
    public boolean equals(MyIType object) {
        return object instanceof RefType && this.inner.equals(((RefType) object).getInner());
    }

    @Override
    public MyIValue getDefaultValue() {
        return new RefValue(0, this.inner);
    }

    @Override
    public MyIType deepCopy() {
        return new RefType(this.inner.deepCopy());
    }

    @Override
    public String toString() {
        return "Ref(" + this.inner.toString() + ")";
    }
}
