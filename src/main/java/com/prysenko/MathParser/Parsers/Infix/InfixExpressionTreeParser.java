package com.prysenko.MathParser.Parsers.Infix;

import com.prysenko.MathParser.Exception.ParserEvalException;
import com.prysenko.MathParser.Exception.ParserValidationException;
import com.prysenko.MathParser.MathParser;
import com.prysenko.MathParser.Misc.RegexManager;
import com.prysenko.MathParser.Parsers.Infix.Nodes.AbstractNode;
import com.prysenko.MathParser.Parsers.Infix.Nodes.TokenNode;

public class InfixExpressionTreeParser extends MathParser {
    protected AbstractNode root;

    public InfixExpressionTreeParser() {
        // not the best way to pass dependency, i guess
        super(new InfixExpressionValidator());
    }

    @Override
    public void parse(String expression) throws ParserValidationException {
        validate(expression);

        root = _parse(RegexManager.removeSpaces(expression));
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

    private AbstractNode _parse(String expression) {
        // Если очередной токен это одно из зарезервированных имен функций, тогда ожидаем,
        // что рядом с ним должны быть скобки
        // делаем split по запятой и инфикс валидатором проверяем все части
        // для каждой части запускаем _parse и кладем результат в спикок List<AbstractNode> parameters.
        // когда все готово создаем ноду с помощью фабрики и токена в качестве названия названия
        return new TokenNode();
    }
}
