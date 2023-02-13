package com.prysenko.MathParser;

import com.prysenko.MathParser.Exception.ParserEvalException;
import com.prysenko.MathParser.Exception.ParserException;
import com.prysenko.MathParser.Exception.ParserValidationException;
import com.prysenko.MathParser.Validators.ExpressionValidator;

import java.util.HashMap;
import java.util.Map;

public abstract class MathParser {
    protected ExpressionValidator validator;
    protected Map<String, Integer> symbolTable;

    public MathParser(ExpressionValidator validator) {
        // you must pass different validators for infix, prefix (and etc.) expressions
        this.validator = validator;
        this.symbolTable = new HashMap<>();
    }

    public void validate(String expression) throws ParserValidationException
    {
        validator.validate(expression);
    }

    public void parse(String expression) throws ParserException {
        validate(expression);

        _parse(expression);
    }

    protected abstract void _parse(String expression) throws ParserException;
    public abstract double eval() throws ParserEvalException;
    public abstract double eval(String expression) throws ParserException;
}