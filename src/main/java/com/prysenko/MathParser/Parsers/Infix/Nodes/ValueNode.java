package com.prysenko.MathParser.Parsers.Infix.Nodes;

public class ValueNode extends AbstractNode {
    private final double value;

    public ValueNode(double value) {
        this.value = value;
    }

    @Override
    public double eval() {
        return value;
    }
}
