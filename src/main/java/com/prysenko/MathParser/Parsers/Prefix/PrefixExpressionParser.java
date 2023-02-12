package com.prysenko.MathParser.Parsers.Prefix;

import com.prysenko.MathParser.Exception.ParserEvalException;
import com.prysenko.MathParser.Exception.ParserValidationException;
import com.prysenko.MathParser.MathParser;
import com.prysenko.MathParser.Validators.PrefixExpressionValidator;

// Example of parser for prefix(Polish) notation

public class PrefixExpressionParser extends MathParser {

    // TODO: implement all logic

    public PrefixExpressionParser() {
        super(new PrefixExpressionValidator());
    }

    @Override
    public void parse(String expression) throws ParserValidationException {

    }

    @Override
    protected void _parse(String expression) throws ParserValidationException {

    }

    @Override
    public void eval() throws ParserEvalException {

    }

    @Override
    public void eval(String expression) throws ParserValidationException {

    }
}
