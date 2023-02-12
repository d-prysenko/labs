package com.prysenko.MathParser.Misc;

// Assume that 'parenthesis' = 'brackets'

public class SymbolsManager {
    public static String trimBrackets(String expression) {
        // ensure that it works correctly at this example: (5 + 4) - (4 / 6)

        while (isSideBracketsComplement(expression)) {
            expression = expression.substring(1, expression.length() - 1);
        }

        return expression;
    }

    /***
     * (5 + 4) - (4 / 6)   - false
     * ((5 + 4) - (4 / 6)) - true
     */
    public static boolean isSideBracketsComplement(String expression) {
        NestingLevelHelper nestingHelper = new NestingLevelHelper();

        if (expression.length() < 2) {
            return false;
        }

        for (int i = 0; i < expression.length(); i++) {
            char c = expression.charAt(i);

            nestingHelper.updateNestingLevel(c);

            if (nestingHelper.getNestingLevel() == 0 && i != expression.length() - 1) {
                return false;
            }
        }

        return true;
    }

    public static boolean isOpeningBracket(char symbol) {
        return symbol == '(' || symbol == '[';
    }

    public static boolean isClosingBracket(char symbol) {
        return symbol == ')' || symbol == ']';
    }

    public static boolean isPlusMinus(char symbol) {
        return symbol == '+' || symbol == '-';
    }

    public static boolean isMultDiv(char symbol) {
        return symbol == '*' || symbol == '/';
    }

    public static boolean isPow(char symbol) {
        return symbol == '^';
    }

    public static boolean isMod(char symbol) {
        return symbol == '%';
    }
}
