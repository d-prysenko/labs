package com.prysenko.MathParser.Parsers.Infix.Nodes.Function;

import java.util.List;

import com.prysenko.MathParser.Parsers.Infix.Nodes.AbstractNode;

public abstract class FunctionNode extends AbstractNode {
    protected List<AbstractNode> args;

    public abstract String getName();
    public abstract int getArgsCount();
    public abstract int eval();

    public FunctionNode(List<AbstractNode> args) {
        this.args = args;
    }
}
