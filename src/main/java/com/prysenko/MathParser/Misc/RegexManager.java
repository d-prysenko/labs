package com.prysenko.MathParser.Misc;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class RegexManager {
    protected int matchesCount;

    public static String removeSpaces(String expression) {
        return Pattern.compile("\\s").matcher(expression).replaceAll("");
    }

    public String find(String source, String regex) {
        Pattern pattern = Pattern.compile(regex);
        Matcher matcher = pattern.matcher(source);
        matchesCount = 0;

        StringBuilder result = new StringBuilder();

        while (matcher.find()) {

            matchesCount++;
            result
                .append("'")
                .append(matcher.group())
                .append("' at ")
                .append(matcher.start())
                .append("\n")
            ;

        }

        return result.toString();
    }

    public int getMatchesCount() {
        return matchesCount;
    }

    public boolean isFound() {
        return matchesCount > 0;
    }
}
