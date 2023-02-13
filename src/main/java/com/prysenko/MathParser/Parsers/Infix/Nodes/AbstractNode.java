package com.prysenko.MathParser.Parsers.Infix.Nodes;

import com.prysenko.MathParser.Exception.ParserEvalException;

abstract public class AbstractNode {
    protected AbstractNode left;
    protected AbstractNode right;

    public abstract double eval() throws ParserEvalException;
}
