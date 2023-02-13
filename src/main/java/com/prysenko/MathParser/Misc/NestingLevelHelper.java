package com.prysenko.MathParser.Misc;

/**
 * Used in places where we are iterating through string with expression
 * and looking for a signs with the lowest priority outside of parentheses
 */
public class NestingLevelHelper {
    private int bracketsNestingLevel = 0;

    public void updateNestingLevel(char symbol) {
        if (SymbolsManager.isOpeningBracket(symbol)) {
            bracketsNestingLevel++;
        } else if (SymbolsManager.isClosingBracket(symbol)) {
            bracketsNestingLevel--;
        }
    }

    public int getNestingLevel() {
        return bracketsNestingLevel;
    }
}
