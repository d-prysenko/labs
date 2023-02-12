package com.prysenko.MathParser.Parsers.Infix;


import java.util.ArrayList;
import java.util.List;
import java.util.function.Predicate;

import com.prysenko.MathParser.Exception.ParserEvalException;
import com.prysenko.MathParser.Exception.ParserValidationException;
import com.prysenko.MathParser.MathParser;
import com.prysenko.MathParser.Misc.NestingLevelHelper;
import com.prysenko.MathParser.Misc.RegexManager;
import com.prysenko.MathParser.Misc.SymbolsManager;
import com.prysenko.MathParser.Parsers.Infix.Nodes.AbstractNode;
import com.prysenko.MathParser.Parsers.Infix.Nodes.Function.FunctionFabric;
import com.prysenko.MathParser.Parsers.Infix.Nodes.Function.FunctionNode;
import com.prysenko.MathParser.Parsers.Infix.Nodes.SignNode;
import com.prysenko.MathParser.Parsers.Infix.Nodes.ValueNode;
import com.prysenko.MathParser.Validators.FunctionValidator;
import com.prysenko.MathParser.Validators.InfixExpressionValidator;

public class InfixExpressionTreeParser extends MathParser {
    protected AbstractNode root;
    protected FunctionValidator functionValidator;

    public InfixExpressionTreeParser() {
        // not the best way to pass dependency, i guess
        super(new InfixExpressionValidator());
        functionValidator = new FunctionValidator();
    }

    @Override
    protected void _parse(String expression) throws ParserValidationException, ParserEvalException {
        root = _doParse(RegexManager.removeSpaces(expression));
    }

    @Override
    public void eval() throws ParserEvalException {
        if (root == null) {
            throw new ParserEvalException("Root node is null");
        }

        // есть 3 идеи:
        // 1) в AbstractNode добавить метод eval.
        //    в TokenNode добавить статический метод получения symbolTable.
        //    таким образом в TokenNode через статику получать symbolTable и значение соответствующего токена.
        //    с потенциальным FunctionNode сделать так же.
        //    !!! тогда получается очень плохо и неправильно при создании двух экземпляров парсера !!!
        // 2) предпринимать действия в соответствии с типами нод тут
        //    возможно добавить какой-то NodeManager и сделать как в предыдущей версии
        // 3) в AbstractNode добавить метод eval.
        //    перед вычислением пройтись по дереву и проставить все значения для переменных
        //    в FunctionNode добавить List<AbstractNode> parameters.
        //    !!! если встречаем FunctionNode, тогда заменять переменные нужно не только в left,right но и в parameters

    }

    @Override
    public void eval(String expression) throws ParserValidationException {

    }

    private AbstractNode _doParse(String expression) throws ParserEvalException {
        // Если очередной токен это одно из зарезервированных имен функций, тогда ожидаем,
        // что рядом с ним должны быть скобки
        // делаем split по запятой и инфикс валидатором проверяем все части
        // для каждой части запускаем _parse и кладем результат в спикок List<AbstractNode> parameters.
        // когда все готово создаем ноду с помощью фабрики и токена в качестве названия названия

        AbstractNode node;
        expression = SymbolsManager.trimBrackets(expression);

        // 5+4*func(3 + 2)^3

        //         +
        //       5   2

        //         +
        //       +   2
        //     5   *
        //       4   3

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

        // value /

        return new ValueNode(Integer.parseInt(expression));
    }

    private SignNode _getNodeForSigns(String expression, Predicate<Character> signPredicate) throws ParserEvalException {
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

    private FunctionNode _getFunctionNode(String expression) throws ParserEvalException {
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

    private List<AbstractNode> splitAndParseArgs(String args) throws ParserEvalException {

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
