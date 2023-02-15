package com.prysenko.MathParser.Parsers.Infix.Nodes;

public class VarNode extends AbstractNode {
    private final VariableValue var;

    public VarNode(VariableValue var) {
        this.var = var;
    }

    @Override
    public double eval() {
        return var.value;
    }
}
