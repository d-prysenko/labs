package com.prysenko;

import com.prysenko.MathParser.Exception.ParserException;
import com.prysenko.MathParser.Expression;
import com.prysenko.MathParser.MathParser;
import com.prysenko.MathParser.Parsers.Infix.InfixExpressionTreeParser;

public class Main {
    public static void main(String[] args) {
        MathParser infixParser = new InfixExpressionTreeParser();
        String source = "a + b * abs(-3 - a)";
        try {
            Expression expr = infixParser.parse(source);
            expr.set("a", 5);
            expr.set("b", 1);
            double res = expr.eval();
            System.out.println(expr  + " = " + res);
        } catch (ParserException e) {
            System.err.println("Parsing error: " + e.getMessage());
        }
    }
}
