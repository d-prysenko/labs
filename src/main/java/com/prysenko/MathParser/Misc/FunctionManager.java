package com.prysenko.MathParser.Misc;

import java.util.HashMap;

public final class FunctionManager {

    public static final FunctionManager INSTANCE = new FunctionManager();

    private static HashMap<String, Integer> funcTable;

    private FunctionManager() {
        // TODO: find inheritors of abstract function class
        funcTable = new HashMap<>();
        funcTable.put("abs", 1);
        funcTable.put("sin", 1);
    }

    public boolean hasFunction(String functionName) {
        return funcTable.containsKey(functionName);
    }

    public int getFunctionArgsCount(String functionName) {
        return funcTable.get(functionName);
    }
}
