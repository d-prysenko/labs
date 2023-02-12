package com.prysenko.MathParser.Validators;

import com.prysenko.MathParser.Misc.FunctionManager;
import com.prysenko.MathParser.Misc.NestingLevelHelper;

public class FunctionValidator {

    protected FunctionManager functionManager;

    public FunctionValidator() {
        functionManager = FunctionManager.INSTANCE;
    }

    public boolean validate(String functionName, String args) {
        if (!functionManager.hasFunction(functionName)) {
            return false;
        }

        int argsCount = functionManager.getFunctionArgsCount(functionName);

        if (argsCount != getNotNestedCommasCount(args) + 1) {
            return false;
        }

        return true;
    }

    private int getNotNestedCommasCount(String args) {
        NestingLevelHelper nestingHelper = new NestingLevelHelper();

        int commasCount = 0;

        for (int i = 0; i < args.length(); i++) {
            char c = args.charAt(i);
            nestingHelper.updateNestingLevel(c);

            if (nestingHelper.getNestingLevel() == 0 && c == ',') {
                commasCount++;
            }

        }

        return commasCount;
    }
}
