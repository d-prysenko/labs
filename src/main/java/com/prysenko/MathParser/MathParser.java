package com.prysenko.MathParser;

import java.util.HashMap;
import java.util.Map;

import com.prysenko.MathParser.Exception.ParserEvalException;
import com.prysenko.MathParser.Exception.ParserValidationException;

public abstract class MathParser {
    protected ExpressionValidator validator;
    protected Map<String, Integer> symbolTable;

    public MathParser(ExpressionValidator validator) {
        this.validator = validator;
        this.symbolTable = new HashMap<>();
    }

    public void validate(String expression) throws ParserValidationException
    {
        validator.validate(expression);
    }

    public abstract void parse(String expression) throws ParserValidationException;
    public abstract void eval() throws ParserEvalException;
    public abstract void eval(String expression) throws ParserValidationException;
}

// parse = [validate, _parse]
// eval() = [_eval]
// eval(str) = [parse, _eval]