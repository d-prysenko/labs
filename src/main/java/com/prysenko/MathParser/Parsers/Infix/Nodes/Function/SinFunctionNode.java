package com.prysenko.MathParser.Parsers.Infix.Nodes.Function;

import com.prysenko.MathParser.Exception.ParserEvalException;
import com.prysenko.MathParser.Parsers.Infix.Nodes.AbstractNode;

import java.util.List;

public class SinFunctionNode extends FunctionNode {
    public SinFunctionNode() {
        super();
    }

    public SinFunctionNode(List<AbstractNode> args) {
        super(args);
    }

    @Override
    public String getName() {
        return "sin";
    }

    public int getArgsCount() {
        return 1;
    }

    @Override
    protected double _eval() throws ParserEvalException {
        return Math.sin(args.get(0).eval());
    }
}
