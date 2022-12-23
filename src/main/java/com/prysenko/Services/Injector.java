package com.prysenko.Services;

import java.io.FileInputStream;
import java.io.IOException;
import java.lang.annotation.Annotation;
import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;
import java.util.HashMap;
import java.util.Map.Entry;
import java.util.Properties;

import com.prysenko.Annotations.AutoInjectable;

public class Injector {
    private final HashMap<String, Object> DIContainer = new HashMap<>();

    public Injector() {
        FileInputStream fis;
        Properties property = new Properties();

        try {
            fis = new FileInputStream("src/main/resources/services.properties");
            property.load(fis);

            for (Entry<Object, Object> e : property.entrySet()) {
                String interfaceName = e.getKey().toString();
                String className = e.getValue().toString();

                Object classInstance = Class.forName(className).getDeclaredConstructor().newInstance();
                DIContainer.put(interfaceName, classInstance);

                System.out.println("Created instance " + className + " for " + interfaceName);
            }

        } catch (IOException e) {
            System.err.println("Error: 'services.properties' file not found");
        } catch (ClassNotFoundException e) {
            System.err.println("Error: class in 'services.properties' not found");
            System.err.println(e.getMessage());
        } catch (InstantiationException | InvocationTargetException | NoSuchMethodException | IllegalAccessException e) {
            System.err.println("Error: cannot create instance of class from 'services.properties'");
            e.printStackTrace();
        }
    }


    public <T> T inject(T obj) {
        Field[] fields = obj.getClass().getDeclaredFields();

        for (Field field : fields) {
            Annotation annotation = field.getAnnotation(AutoInjectable.class);
            if (annotation == null) {
                continue;
            }

            try {
                String fieldType = field.getType().getName();
                Object classInstance = DIContainer.get(fieldType);
                field.setAccessible(true);
                field.set(obj, classInstance);
            } catch (IllegalAccessException e) {
                System.err.println("Error: cannot inject dependency");
                System.err.println(e.getMessage());
            }
        }

        return obj;
    }
}
