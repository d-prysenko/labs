package com.prysenko.MathParser.Parsers.Infix.Nodes.Function;

import com.prysenko.MathParser.Exception.ExpressionEvalException;
import com.prysenko.MathParser.Parsers.Infix.Nodes.AbstractNode;

import java.util.List;

public abstract class FunctionNode extends AbstractNode {
    protected List<AbstractNode> args;
    public FunctionNode() {}
    public FunctionNode(List<AbstractNode> args) {
        this.args = args;
    }

    public abstract String getName();

    public abstract int getArgsCount();

    protected abstract double _eval() throws ExpressionEvalException;

    @Override
    public final double eval() throws ExpressionEvalException {
        if (_isArgsCountInvalid()) {
            _throwInvalidArgsCountException();
        }

        return _eval();
    }

    public FunctionNode setArgs(List<AbstractNode> args) {
        this.args = args;

        return this;
    }

    public List<AbstractNode> getArgs() {
        return args;
    }

    protected boolean _isArgsCountInvalid() {
        return args.size() != getArgsCount();
    }

    protected void _throwInvalidArgsCountException() throws ExpressionEvalException {
        throw new ExpressionEvalException("Function '" + getName() + "' expects " + getArgsCount() + " argument(s), given " + args.size());
    }
}
