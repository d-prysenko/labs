package com.prysenko.MathParser.Misc;

import com.prysenko.MathParser.Parsers.Infix.Nodes.Function.FunctionNode;
import org.reflections.Reflections;

import java.lang.reflect.InvocationTargetException;
import java.util.HashMap;
import java.util.Set;

public final class FunctionManager {

    public static final FunctionManager INSTANCE;

    static {
        try {
            INSTANCE = new FunctionManager();
        } catch (NoSuchMethodException | InvocationTargetException | IllegalAccessException | InstantiationException e) {
            throw new ExceptionInInitializerError(e);
        }
    }

    private static HashMap<String, Integer> funcTable;

    private FunctionManager() throws NoSuchMethodException, InvocationTargetException, IllegalAccessException, InstantiationException {
        funcTable = new HashMap<>();

        Reflections reflections = new Reflections("com.prysenko.MathParser.Parsers.Infix.Nodes.Function");
        Set<Class<? extends FunctionNode>> functionClasses = reflections.getSubTypesOf(FunctionNode.class);

        for (Class<? extends FunctionNode> functionClass : functionClasses) {
            // It's look like an anti-pattern, because all instances of for example CosFunctionClass
            // has func name 'cos' and this information should refer to the class,
            // but we're creating here new instance 'cause it's java...
            FunctionNode node = functionClass.getDeclaredConstructor().newInstance();
            String functionName = (String) functionClass.getMethod("getName").invoke(node);
            int argsCount = (int) functionClass.getMethod("getArgsCount").invoke(node);

            funcTable.put(functionName, argsCount);
        }
    }

    public boolean hasFunction(String functionName) {
        return funcTable.containsKey(functionName);
    }

    public int getFunctionArgsCount(String functionName) {
        return funcTable.get(functionName);
    }
}
