package com.prysenko.MathParser.Parsers.Infix.Nodes.Function;

import com.prysenko.MathParser.Exception.ExpressionEvalException;
import com.prysenko.MathParser.Parsers.Infix.Nodes.AbstractNode;

import java.util.List;

public class DegFunctionNode extends FunctionNode {
    public DegFunctionNode() {
        super();
    }

    public DegFunctionNode(List<AbstractNode> args) {
        super(args);
    }

    @Override
    public String getName() {
        return "deg";
    }

    @Override
    public int getArgsCount() {
        return 1;
    }

    @Override
    protected double _eval() throws ExpressionEvalException {
        return Math.toDegrees(args.get(0).eval());
    }
}
