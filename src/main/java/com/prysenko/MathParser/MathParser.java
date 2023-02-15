package com.prysenko.MathParser;

import com.prysenko.MathParser.Exception.ParserException;
import com.prysenko.MathParser.Exception.ParserValidationException;
import com.prysenko.MathParser.Validators.ExpressionValidator;
import com.prysenko.MathParser.Validators.FunctionValidator;

public abstract class MathParser {
    protected ExpressionValidator expressionValidator;
    protected FunctionValidator functionValidator;

    public MathParser(ExpressionValidator validator) {
        // you must pass different validators for infix, prefix (and etc.) expressions
        this.expressionValidator = validator;
        this.functionValidator = new FunctionValidator();
    }

    public void validate(String expression) throws ParserValidationException
    {
        expressionValidator.validate(expression);
    }

    public Expression parse(String expression) throws ParserException {
        validate(expression);

        return _parse(expression);
    }

    protected abstract Expression _parse(String expression) throws ParserException;
    public double eval(String expression) throws ParserException {
        return parse(expression).eval();
    }
}