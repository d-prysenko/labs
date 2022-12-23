package com.prysenko.Example;

import com.prysenko.Annotations.AutoInjectable;

public class SomeBean {
    @AutoInjectable
    private SomeInterface field1;

    @AutoInjectable
    private SomeOtherInterface field2;

    public void foo(){
        field1.doSomething();
        field2.doSomeOther();
    }
}
