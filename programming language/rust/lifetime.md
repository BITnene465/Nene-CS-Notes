# lifetime

## Introduction

使用 **生命周期**：

- 防止悬垂引用 **dangling references**:  导致程序引用到它不该引用的数据



rust 的 **Borrow Checker**

- 确保数据存活时间长于（Outlive）其引用
- 比较生命周期，以确定所有的借用是否有效



**生命周期注解：**

- 生命周期注解不会改变引用存活的时间，而是 **描述** 多个引用之间的生命周期 **关系**
- **生命周期参数语法**：
  - 必须以 `'` 开头
  - 通常是小写，且非常短



- **输入生命周期**：在函数、方法的参数上的生命周期
- **输出生命周期**：在返回值上的生命周期





**一个 泛型参数、Trait Bound 和 生命周期一起使用的例子：**

<img src="G:\softwares\typora\typora 图片\lifetime\image-20250214120547185.png" alt="image-20250214120547185" style="zoom:80%;" />





 ## 生命周期注解

### 函数内



###　struct 内







## 生命周期省略规则



**三条规则**（在没有显式生命周期注解时）：

1. 编译器为每个输入类型终端每个生命周期分配不同的生命周期参数

   ![image-20250214113816492](G:\softwares\typora\typora 图片\lifetime\image-20250214113816492.png)

2. 如果**只有一个**输入生命周期参数，该生命周期将被分配给所有的输出生命周期参数

   <img src="G:\softwares\typora\typora 图片\lifetime\image-20250214114027612.png" alt="image-20250214114027612" style="zoom:80%;" />

3. 如果有多个生命周期参数，但是其中一个是 `&self` 或 `&mut self` (因为这是一个方法)，那么 `self` 的生命周期会被分配给所有的输出生命周期参数







## 静态生命周期

`'static`  : 表示该引用可以在整个程序的持续时间内存活

- 所有的字符串字面量都具有 `'static ` 生命周期！

  <img src="G:\softwares\typora\typora 图片\lifetime\image-20250214115219180.png" alt="image-20250214115219180" style="zoom:80%;" />









