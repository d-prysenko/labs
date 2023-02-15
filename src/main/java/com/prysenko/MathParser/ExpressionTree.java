package com.prysenko.MathParser;

import com.prysenko.MathParser.Exception.ExpressionEvalException;
import com.prysenko.MathParser.Parsers.Infix.Nodes.AbstractNode;
import com.prysenko.MathParser.Parsers.Infix.Nodes.VariableValue;

import java.util.Map;

public class ExpressionTree implements Expression {
    protected AbstractNode root;
    protected Map<String, VariableValue> symbolTable;

    public ExpressionTree() {
        super();
    }

    public ExpressionTree(AbstractNode root, Map<String, VariableValue> symbolTable) {
        this.root = root;
        this.symbolTable = symbolTable;
    }

    @Override
    public double eval() throws ExpressionEvalException {
        if (root == null) {
            throw new ExpressionEvalException("Root node is null");
        }

        // TODO: check that symbolTable is filled and set constants

        return root.eval();
    }

    @Override
    public Expression set(String var, double value) throws ExpressionEvalException {
        if (!symbolTable.containsKey(var)) {
            throw new ExpressionEvalException("Unknown variable '" + var + "'");
        }

        symbolTable.get(var).value = value;

        return this;
    }
}
