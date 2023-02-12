package com.prysenko.MathParser.Misc;

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
