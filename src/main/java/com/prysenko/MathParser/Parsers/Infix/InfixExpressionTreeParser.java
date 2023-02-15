package com.prysenko.MathParser.Parsers.Infix;


import com.prysenko.MathParser.Exception.ParserException;
import com.prysenko.MathParser.Expression;
import com.prysenko.MathParser.ExpressionTree;
import com.prysenko.MathParser.MathParser;
import com.prysenko.MathParser.Misc.FunctionManager;
import com.prysenko.MathParser.Misc.NestingLevelHelper;
import com.prysenko.MathParser.Misc.RegexManager;
import com.prysenko.MathParser.Misc.SymbolsManager;
import com.prysenko.MathParser.Parsers.Infix.Nodes.*;
import com.prysenko.MathParser.Parsers.Infix.Nodes.Function.FunctionFabric;
import com.prysenko.MathParser.Parsers.Infix.Nodes.Function.FunctionNode;
import com.prysenko.MathParser.Validators.InfixExpressionValidator;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.function.Predicate;

public class InfixExpressionTreeParser extends MathParser {
    protected Map<String, VariableValue> symbolTable;

    public InfixExpressionTreeParser() {
        // not the best way to pass dependency, i guess
        super(new InfixExpressionValidator());
    }

    @Override
    protected Expression _parse(String expression) throws ParserException {
        symbolTable = new HashMap<>();
        AbstractNode root = doParse(RegexManager.removeSpaces(expression));

        return new ExpressionTree(root, symbolTable);
    }

    private AbstractNode doParse(String expression) throws ParserException {
        AbstractNode node;
        expression = SymbolsManager.trimBrackets(expression);

        // binary +-
        node = getSignNode(expression, SymbolsManager::isPlusMinus);

        if (node != null) {
            return node;
        }

        // */
        node = getSignNode(expression, SymbolsManager::isMultDiv);

        if (node != null) {
            return node;
        }

        // %
        node = getSignNode(expression, SymbolsManager::isMod);

        if (node != null) {
            return node;
        }

        // ^
        node = getSignNode(expression, SymbolsManager::isPow);

        if (node != null) {
            return node;
        }

        // unary -
        if (expression.startsWith("-")) {
            return new SignNode('-', new ValueNode(0), doParse(expression.substring(1)));
        }

        // function
        node = getFunctionNode(expression);

        if (node != null) {
            return node;
        }

        // variable
        node = getVarNode(expression);

        if (node != null) {
            return node;
        }

        // raw value
        return new ValueNode(Double.parseDouble(expression));
    }

    private SignNode getSignNode(String expression, Predicate<Character> signPredicate) throws ParserException {
        NestingLevelHelper nestingHelper = new NestingLevelHelper();

        for (int i = 0; i < expression.length(); i++) {
            char c = expression.charAt(i);
            nestingHelper.updateNestingLevel(c);

            if (signPredicate.test(c) && nestingHelper.getNestingLevel() == 0 && i != 0) {
                // finally! we found sign specified by signPredicate

                String left = SymbolsManager.trimBrackets(expression.substring(0, i));
                String right = SymbolsManager.trimBrackets(expression.substring(i + 1));
                char sign = expression.charAt(i);

                return new SignNode(sign, doParse(left), doParse(right));
            }
        }

        return null;
    }

    private FunctionNode getFunctionNode(String expression) throws ParserException {
        int openingBracketPos = expression.indexOf("(");

        if (openingBracketPos == -1) {
            return null;
        }

        String functionName = expression.substring(0, openingBracketPos);
        String args = expression.substring(openingBracketPos + 1, expression.length() - 1);

        if (!functionValidator.validate(functionName, args)) {
            return null;
        }

        return FunctionFabric.create(functionName, splitAndParseArgs(args));
    }

    private List<AbstractNode> splitAndParseArgs(String args) throws ParserException {
        List<AbstractNode> res = new ArrayList<>();

        NestingLevelHelper nestingHelper = new NestingLevelHelper();
        int beginIndex = 0;

        for (int i = 0; i < args.length(); i++) {
            char c = args.charAt(i);
            nestingHelper.updateNestingLevel(c);

            if (nestingHelper.getNestingLevel() == 0 && c == ',') {
                res.add(doParse(args.substring(beginIndex, i)));

                beginIndex = i + 1;
            }
        }

        res.add(doParse(args.substring(beginIndex)));

        return res;
    }

    private VarNode getVarNode(String expression) throws ParserException {
        if (!Character.isLetter(expression.charAt(0))) {
            return null;
        }

        if (FunctionManager.INSTANCE.hasFunction(expression)) {
            throw new ParserException(expression + " is reserved name of a function. Use another name for variable.");
        }

        VariableValue var = addVarToSymbolTable(expression);

        return new VarNode(var);
    }

    private VariableValue addVarToSymbolTable(String expression) {
        VariableValue var = new VariableValue(expression);

        if (!symbolTable.containsKey(expression)) {
            symbolTable.put(expression, var);
        } else {
            var = symbolTable.get(expression);
        }

        return var;
    }

}