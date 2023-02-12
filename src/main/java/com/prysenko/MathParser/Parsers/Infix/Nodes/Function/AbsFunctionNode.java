package com.prysenko.MathParser.Parsers.Infix.Nodes.Function;

import java.util.List;

import com.prysenko.MathParser.Parsers.Infix.Nodes.AbstractNode;

public class AbsFunctionNode extends FunctionNode {

    public AbsFunctionNode(List<AbstractNode> args) {
        super(args);
    }

    @Override
    public String getName() {
        return "abs";
    }

    @Override
    public int getArgsCount() {
        return 2;
    }

    @Override
    public int eval() {
        // assert that args is not empty

        return Math.abs(args.get(0).eval());
    }
}
