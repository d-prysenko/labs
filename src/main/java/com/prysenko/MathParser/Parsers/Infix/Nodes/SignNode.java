package com.prysenko.MathParser.Parsers.Infix.Nodes;

import com.prysenko.MathParser.Exception.ExpressionEvalException;

public class SignNode extends AbstractNode {
    public Type signType;

    public SignNode() {
        this.signType = Type.Invalid;
    }

    public SignNode(char type) {
        setSign(type);
    }

    public SignNode(char type, AbstractNode left, AbstractNode right) {
        setSign(type);
        this.left = left;
        this.right = right;
    }

    public void setSign(char type) {
        switch (type) {
            case '+' -> this.signType = Type.Plus;
            case '-' -> this.signType = Type.Minus;
            case '*' -> this.signType = Type.Multiply;
            case '/' -> this.signType = Type.Divide;
            case '%' -> this.signType = Type.Mod;
            case '^' -> this.signType = Type.Pow;
            default -> this.signType = Type.Invalid;
        }
    }

    @Override
    public double eval() throws ExpressionEvalException {
        switch (signType) {
            case Plus -> {
                return left.eval() + right.eval();
            }
            case Minus -> {
                return left.eval() - right.eval();
            }
            case Multiply -> {
                return left.eval() * right.eval();
            }
            case Divide -> {
                return left.eval() / right.eval();
            }
            case Mod -> {
                return left.eval() % right.eval();
            }
            case Pow -> {
                return Math.pow(left.eval(), right.eval());
            }
            case Invalid -> {
                return 0;
            }
        }
        return 0;
    }

    public enum Type {
        Plus,
        Minus,
        Multiply,
        Divide,
        Mod,
        Pow,
        Invalid
    }
}
