package com.prysenko.MathParser.Parsers.Infix.Nodes.Function;

import com.prysenko.MathParser.Exception.ExpressionEvalException;
import com.prysenko.MathParser.Parsers.Infix.Nodes.AbstractNode;

import java.util.List;

public class TgFunctionNode extends FunctionNode {
    public TgFunctionNode() {
        super();
    }

    public TgFunctionNode(List<AbstractNode> args) {
        super(args);
    }

    @Override
    public String getName() {
        return "tg";
    }

    @Override
    public int getArgsCount() {
        return 1;
    }

    @Override
    protected double _eval() throws ExpressionEvalException {
        return Math.tan(args.get(0).eval());
    }
}
