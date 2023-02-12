package com.prysenko.MathParser.Parsers.Infix.Nodes;

abstract public class AbstractNode {
    protected AbstractNode left;
    protected AbstractNode right;

    public abstract int eval();
}
