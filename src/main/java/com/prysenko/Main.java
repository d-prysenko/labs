package com.prysenko;

import com.prysenko.MathParser.Exception.ParserValidationException;
import com.prysenko.MathParser.MathParser;
import com.prysenko.MathParser.Parsers.Infix.InfixExpressionTreeParser;

public class Main {
    public static void main(String[] args) {
        MathParser infixParser = new InfixExpressionTreeParser();

        try {
            infixParser.parse("5f df * 2");
        } catch (ParserValidationException e) {
            System.err.println("Parsing error: " + e.getMessage());
        }
    }
}
