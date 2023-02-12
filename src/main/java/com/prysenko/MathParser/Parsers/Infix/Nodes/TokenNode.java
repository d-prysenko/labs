package com.prysenko.MathParser.Parsers.Infix.Nodes;

public class TokenNode extends AbstractNode {
    private String token;
    private int value;

    @Override
    public int eval() {
        return value;
    }
}
