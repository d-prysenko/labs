package com.prysenko.MathParser.Parsers.Infix.Nodes.Function;

import java.util.List;

import com.prysenko.MathParser.Exception.ParserEvalException;
import com.prysenko.MathParser.Parsers.Infix.Nodes.AbstractNode;

public class FunctionFabric {
    public static FunctionNode create(String name, List<AbstractNode> args) throws ParserEvalException {
        switch (name) {
            case "abs" -> {
                return new AbsFunctionNode(args);
            }
            case "sin" -> {
                return new SinFunctionNode(args);
            }
        }

        throw new ParserEvalException("Undefined function: " + name);
    }
}
