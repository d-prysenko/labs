package com.prysenko.MathParser.Parsers.Infix.Nodes.Function;

import com.prysenko.MathParser.Exception.ParserEvalException;
import com.prysenko.MathParser.Parsers.Infix.Nodes.AbstractNode;

import java.util.List;

public class PowFunctionNode extends FunctionNode {
    public PowFunctionNode() {
        super();
    }

    public PowFunctionNode(List<AbstractNode> args) {
        super(args);
    }

    @Override
    public String getName() {
        return "pow";
    }

    @Override
    public int getArgsCount() {
        return 2;
    }

    @Override
    protected double _eval() throws ParserEvalException {
        return Math.pow(args.get(0).eval(), args.get(1).eval());
    }
}
