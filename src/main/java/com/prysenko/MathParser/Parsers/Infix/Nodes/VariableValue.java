package com.prysenko.MathParser.Parsers.Infix.Nodes;

public class VariableValue {
    public Double value;

    public VariableValue(String name) {
        this.value = null;
    }

    public boolean isInitialized() {
        return value != null;
    }
}