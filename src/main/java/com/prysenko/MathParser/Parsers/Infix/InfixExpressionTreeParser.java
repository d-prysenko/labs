package com.prysenko.MathParser.Parsers.Infix;


import com.prysenko.MathParser.Exception.ParserEvalException;
import com.prysenko.MathParser.Exception.ParserException;
import com.prysenko.MathParser.MathParser;
import com.prysenko.MathParser.Misc.NestingLevelHelper;
import com.prysenko.MathParser.Misc.RegexManager;
import com.prysenko.MathParser.Misc.SymbolsManager;
import com.prysenko.MathParser.Parsers.Infix.Nodes.AbstractNode;
import com.prysenko.MathParser.Parsers.Infix.Nodes.Function.FunctionFabric;
import com.prysenko.MathParser.Parsers.Infix.Nodes.Function.FunctionNode;
import com.prysenko.MathParser.Parsers.Infix.Nodes.SignNode;
import com.prysenko.MathParser.Parsers.Infix.Nodes.TokenNode;
import com.prysenko.MathParser.Parsers.Infix.Nodes.ValueNode;
import com.prysenko.MathParser.Validators.FunctionValidator;
import com.prysenko.MathParser.Validators.InfixExpressionValidator;

import java.util.ArrayList;
import java.util.List;
import java.util.function.Predicate;

public class InfixExpressionTreeParser extends MathParser {
    protected AbstractNode root;
    protected FunctionValidator functionValidator;

    public InfixExpressionTreeParser() {
        // not the best way to pass dependency, i guess
        super(new InfixExpressionValidator());
        functionValidator = new FunctionValidator();
    }

    @Override
    public double eval() throws ParserEvalException {
        if (root == null) {
            throw new ParserEvalException("Root node is null");
        }

        // TODO: check that symbolTable is filled and set all values in tree

        return root.eval();
    }

    @Override
    public double eval(String expression) throws ParserException {
        parse(expression);
        return eval();
    }

    @Override
    protected void _parse(String expression) throws ParserException {
        root = _doParse(RegexManager.removeSpaces(expression));
    }

    private AbstractNode _doParse(String expression) throws ParserException {
        AbstractNode node;
        expression = SymbolsManager.trimBrackets(expression);

        // binary +-
        node = _getNodeForSigns(expression, SymbolsManager::isPlusMinus);

        if (node != null) {
            return node;
        }

        // */
        node = _getNodeForSigns(expression, SymbolsManager::isMultDiv);

        if (node != null) {
            return node;
        }

        // %
        node = _getNodeForSigns(expression, SymbolsManager::isMod);

        if (node != null) {
            return node;
        }

        // ^
        node = _getNodeForSigns(expression, SymbolsManager::isPow);

        if (node != null) {
            return node;
        }

        // unary -
        if (expression.startsWith("-")) {
            return new SignNode('-', new ValueNode(0), _doParse(expression.substring(1)));
        }

        // function
        // is it a function?
        node = _getFunctionNode(expression);

        if (node != null) {
            return node;
        }

        // variable
        // starts with letter
        if (Character.isLetter(expression.charAt(0))) {
            if (!symbolTable.containsKey(expression)) {
                symbolTable.put(expression, null);
            }

            return new TokenNode(expression);
        }

        // value
        return new ValueNode(Double.parseDouble(expression));
    }

    private SignNode _getNodeForSigns(String expression, Predicate<Character> signPredicate) throws ParserException {
        NestingLevelHelper nestingHelper = new NestingLevelHelper();

        for (int i = 0; i < expression.length(); i++) {
            char c = expression.charAt(i);
            nestingHelper.updateNestingLevel(c);

            if (signPredicate.test(c) && nestingHelper.getNestingLevel() == 0 && i != 0) {
                // finally! we found +-*/^%

                String left = SymbolsManager.trimBrackets(expression.substring(0, i));
                String right = SymbolsManager.trimBrackets(expression.substring(i + 1));
                char sign = expression.charAt(i);

                return new SignNode(sign, _doParse(left), _doParse(right));
            }
        }

        return null;
    }

    private FunctionNode _getFunctionNode(String expression) throws ParserException {
        int openingBracketPos = expression.indexOf("(");

        if (openingBracketPos == -1) {
            return null;
        }

        String functionName = expression.substring(0, openingBracketPos);
        String args = expression.substring(openingBracketPos + 1, expression.length() - 1);

        if (!functionValidator.validate(functionName, args)) {
            return null;
        }

        return FunctionFabric.create(functionName, _splitAndParseArgs(args));
    }

    private List<AbstractNode> _splitAndParseArgs(String args) throws ParserException {
        List<AbstractNode> res = new ArrayList<>();

        NestingLevelHelper nestingHelper = new NestingLevelHelper();
        int beginIndex = 0;

        for (int i = 0; i < args.length(); i++) {
            char c = args.charAt(i);
            nestingHelper.updateNestingLevel(c);

            if (nestingHelper.getNestingLevel() == 0 && c == ',') {
                res.add(_doParse(args.substring(beginIndex, i)));

                beginIndex = i + 1;
            }
        }

        res.add(_doParse(args.substring(beginIndex)));

        return res;
    }

}
