package com.prysenko.MathParser.Parsers.Infix.Nodes.Function;

import com.prysenko.MathParser.Exception.ExpressionEvalException;
import com.prysenko.MathParser.Parsers.Infix.Nodes.AbstractNode;

import java.util.List;

public class AbsFunctionNode extends FunctionNode {

    public AbsFunctionNode() {
        super();
    }

    public AbsFunctionNode(List<AbstractNode> args) {
        super(args);
    }

    @Override
    public String getName() {
        return "abs";
    }

    @Override
    public int getArgsCount() {
        return 1;
    }

    @Override
    protected double _eval() throws ExpressionEvalException {
        return Math.abs(args.get(0).eval());
    }
}
