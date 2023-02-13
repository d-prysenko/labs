package com.prysenko.MathParser.Parsers.Infix.Nodes.Function;

import com.prysenko.MathParser.Exception.ParserException;
import com.prysenko.MathParser.Parsers.Infix.Nodes.AbstractNode;

import java.util.List;

public class FunctionFabric {
    public static FunctionNode create(String name, List<AbstractNode> args) throws ParserException {
        switch (name) {
            case "abs" -> {
                return new AbsFunctionNode(args);
            }
            case "sin" -> {
                return new SinFunctionNode(args);
            }
            case "cos" -> {
                return new CosFunctionNode(args);
            }
            case "tg" -> {
                return new TgFunctionNode(args);
            }
            case "ctg" -> {
                return new CtgFunctionNode(args);
            }
            case "pow" -> {
                return new PowFunctionNode(args);
            }
            case "exp" -> {
                return new ExpFunctionNode(args);
            }
        }

        throw new ParserException("Undefined function: " + name);
    }
}
