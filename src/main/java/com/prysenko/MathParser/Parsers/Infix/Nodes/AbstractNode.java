package com.prysenko.MathParser.Parsers.Infix.Nodes;

import com.prysenko.MathParser.Exception.ExpressionEvalException;

public abstract class AbstractNode {
    protected AbstractNode left;
    protected AbstractNode right;

    public abstract double eval() throws ExpressionEvalException;
}
