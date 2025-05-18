# 再探 Java

## Java 变量的作用域

在Java中，作用域（Scope）是指变量或标识符的可见性和访问范围，它决定了在程序的哪些部分可以引用和访问某个变量或标识符。Java具有以下几种主要的作用域类型：

1. **局部作用域（Local Scope）**：局部作用域指的是变量在定义它们的**方法**、**代码块**或语句中的可见性范围。变量在局部作用域内声明，只能在这个局部作用域内使用，超出这个范围就无法访问。例如，方法中的参数和局部变量就处于局部作用域。

```java
public void exampleMethod() {
    int localVar = 42; // localVar在exampleMethod的局部作用域内可见
}

// 或者
public static void main(String[] args) {
        {
            int i=1;
            System.out.println(i);
        }
        for(int i = 1;i<=10;++i){
            System.out.println(i);
        }
    }
```

2. **实例作用域（Instance Scope）**：实例作用域指的是在类的实例（对象）内部的成员变量的可见性范围。实例作用域的变量是在类中声明的，每个类的实例都有一份独立的拷贝，可以通过实例来访问。

```java
public class MyClass {
    int instanceVar; // 实例作用域的成员变量

    public void setInstanceVar(int value) {
        instanceVar = value; // 在实例方法中访问实例作用域的变量
    }
}
```

3. **类作用域（Class Scope）**：类作用域指的是在类中使用`static`关键字声明的静态成员变量（类变量）的可见性范围。类作用域的变量在整个类的生命周期内都存在，可以通过类名来访问，无需创建类的实例。

```java
public class MyClass {
    static int classVar; // 类作用域的静态成员变量

    public static void setClassVar(int value) {
        classVar = value; // 在静态方法中访问类作用域的变量
    }
}
```

总之，作用域规定了变量的可见性和访问权限，而合理使用作用域可以帮助控制变量的生命周期，提高代码的可维护性和安全性。不同作用域内的同名变量不会相互干扰，从而避免了命名冲突问题。



**tips:**

- java 中没有作用域的覆写

