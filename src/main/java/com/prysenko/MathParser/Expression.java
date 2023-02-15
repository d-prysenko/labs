package com.prysenko.MathParser;

import com.prysenko.MathParser.Exception.ExpressionEvalException;

public interface Expression {
    double eval() throws ExpressionEvalException;
    Expression set(String var, double value) throws ExpressionEvalException;
}
