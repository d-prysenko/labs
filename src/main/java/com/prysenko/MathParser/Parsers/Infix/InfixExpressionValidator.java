package com.prysenko.MathParser.Parsers.Infix;

import java.util.Stack;

import com.prysenko.MathParser.Exception.ParserValidationException;
import com.prysenko.MathParser.ExpressionValidator;
import com.prysenko.MathParser.Misc.RegexManager;

public class InfixExpressionValidator implements ExpressionValidator {
    protected final String notAllowedSymbolsPattern = "[^a-zA-Z0-9-+*/%^()\\[\\]\\s]|[*/+-][/*+]|--|\\+-";
    protected final String spacesWithinTokensPattern = "\\w+(\\s+\\w+)+";

    @Override
    public void validate(String expression) throws ParserValidationException {
        RegexManager regex = new RegexManager();
        String occurrences;

        // GOOD: 1 + name % 2
        // BAD: 1 + ~name % 2
        occurrences = regex.find(expression, notAllowedSymbolsPattern);
        if (regex.isFound()) {
            throw new ParserValidationException("There are not allowed symbols. Allowed symbols: [a-z] [A-Z] [0-9] + - * / % ^ ( ) [ ]\n" + occurrences);
        }

        // GOOD: 8 + var_name_1 ^ 2
        // BAD: 8 + var name 1 ^ 2
        occurrences = regex.find(expression, spacesWithinTokensPattern);
        if (regex.isFound()) {
            throw new ParserValidationException("There are unexpected spaces within tokens:\n" + occurrences);
        }

        // GOOD: (13 * [3 + 5])
        // BAD: (13 * [3 + 5)], etc..
        checkForUnexpectedBrackets(expression);
    }

    private void checkForUnexpectedBrackets(String expression) throws ParserValidationException {
        Stack<Character> brackets = new Stack<>();

        for (int pos = 0; pos < expression.length(); pos++) {
            char c = expression.charAt(pos);

            if (c == '(' || c == '[') {
                brackets.push(c);
            }

            if (c == ')' || c == ']') {
                char openBracket = c == ')' ? '(' : '[';
                char secondTypeOpenBracket = c == ')' ? '[' : '(';
                char secondTypeCloseBracket = c == ')' ? ']' : ')';

                if (brackets.size() == 0) {
                    throw new ParserValidationException("Missing '" + openBracket + "' but found '" + c + "' at pos " + pos);
                }

                if (brackets.peek() == secondTypeOpenBracket) {
                    throw new ParserValidationException("Expected '" + secondTypeCloseBracket + "', actual '" + c + "' at pos " + pos);
                }

                brackets.pop();
            }
        }

        if (brackets.size() != 0) {
            throw new ParserValidationException("There are unclosed parenthesis");
        }
    }
}
