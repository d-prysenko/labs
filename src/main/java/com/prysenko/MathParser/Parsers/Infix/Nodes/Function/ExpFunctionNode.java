package com.prysenko.MathParser.Parsers.Infix.Nodes.Function;

import com.prysenko.MathParser.Exception.ExpressionEvalException;
import com.prysenko.MathParser.Parsers.Infix.Nodes.AbstractNode;

import java.util.List;

public class ExpFunctionNode extends FunctionNode {
    public ExpFunctionNode() {
        super();
    }

    public ExpFunctionNode(List<AbstractNode> args) {
        super(args);
    }

    @Override
    public String getName() {
        return "exp";
    }

    @Override
    public int getArgsCount() {
        return 1;
    }

    @Override
    protected double _eval() throws ExpressionEvalException {
        return Math.exp(args.get(0).eval());
    }
}
