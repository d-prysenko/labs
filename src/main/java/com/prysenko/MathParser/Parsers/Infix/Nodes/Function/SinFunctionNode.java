package com.prysenko.MathParser.Parsers.Infix.Nodes.Function;

import java.util.List;

import com.prysenko.MathParser.Parsers.Infix.Nodes.AbstractNode;

public class SinFunctionNode extends FunctionNode {

    public SinFunctionNode(List<AbstractNode> args) {
        super(args);
    }

    @Override
    public String getName() {
        return "sin";
    }

    @Override
    public int getArgsCount() {
        return 1;
    }

    @Override
    public int eval() {
        // assert that args is not empty

        return (int) Math.sin(args.get(0).eval());
    }
}
