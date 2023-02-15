package com.prysenko.MathParser.Parsers.Prefix;

import com.prysenko.MathParser.Exception.ParserException;
import com.prysenko.MathParser.Expression;
import com.prysenko.MathParser.MathParser;
import com.prysenko.MathParser.Validators.ExpressionValidator;

// Example of parser for prefix(Polish) notation

public class PrefixExpressionParser extends MathParser {
    public PrefixExpressionParser(ExpressionValidator validator) {
        super(validator);
    }

    @Override
    protected Expression _parse(String expression) throws ParserException {
        return null;
    }

    // TODO: implement all logic

}
