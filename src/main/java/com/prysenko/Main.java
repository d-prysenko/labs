package com.prysenko;

import com.prysenko.Example.SomeBean;
import com.prysenko.Services.Injector;

public class Main {
    public static void main(String[] args) {
        SomeBean sb = (new Injector()).inject(new SomeBean());
        sb.foo();
    }
}
