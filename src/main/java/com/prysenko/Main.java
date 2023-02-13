package com.prysenko;

import com.prysenko.MathParser.Exception.ParserException;
import com.prysenko.MathParser.MathParser;
import com.prysenko.MathParser.Parsers.Infix.InfixExpressionTreeParser;

public class Main {
    public static void main(String[] args) {
        MathParser infixParser = new InfixExpressionTreeParser();
        String expr = "5 + 4 * abs(-3 - 2)^3";
        try {
            double res = infixParser.eval(expr);
            System.out.println(expr  + " = " + res);
        } catch (ParserException e) {
            System.err.println("Parsing error: " + e.getMessage());
        }
    }
}
