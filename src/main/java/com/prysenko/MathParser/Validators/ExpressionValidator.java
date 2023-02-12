package com.prysenko.MathParser.Validators;

import com.prysenko.MathParser.Exception.ParserValidationException;

public interface ExpressionValidator {
    void validate(String expression) throws ParserValidationException;
}
