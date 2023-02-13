package com.prysenko.MathParser.Parsers.Infix.Nodes;

public class TokenNode extends AbstractNode {
    private final String name;
    private double value;

    public TokenNode(String name) {
        this.name = name;
    }

    @Override
    public double eval() {
        return value;
    }
}
