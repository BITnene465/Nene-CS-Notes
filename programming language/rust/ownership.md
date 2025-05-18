#  ownership && borrowing

## 引入

### 栈上变量实现复制

```rust
fn main() {
    let arr1 = [3; 5];
    let arr2 = arr1;
    println!("{:?}", arr1);
    println!("{:?}", arr2);
}
```



以上代码，不会发生所有权的转移，执行 `let arr2=arr1` 时发生的是复制 （栈上内存直接复制）



### 栈(stack)内存管理

**stack frame:**

- 指函数在**调用期间**存储**这个函数和其局部变量以及返回值**的内存空间
- 或者一个变量存储时，包含变量值的一整块内存空间



**Rust 不允许手动管理内存**： Stack Frame 由 Rust 自动管理

- 当调用一个函数时， Rust 为被调用的函数分配一个 Stack Frame，当调用结束之后，Rust释放该函数的 Stack Frame
- 对于变量而言， .....



## Box 智能指针



使用 `Box::new()` 在堆上分配内存：

```rust
let a = Box::new([0; 1_000_000]);  # 堆上分配数组数据
let b = a;
```





**Box 内存释放原则：**

- 如果一个变量**拥有**一个 box, 当 Rust 释放变量的 frame 时， Rust 也会释放该 box 的堆（heap）内存



**移动堆（heap） 数据原则：**

- 如果变量 x 将堆数据的所有权移动给另一个变量 y, 那么在移动之后，x 不能再使用





## 引用 和 借用

### 概念区别

- C++ 中的指针的本质是 "别名"， `int* arr = new int[3]; int* &ref = arr;`  ref指向arr指向的数据，并且ref可以改变arr的指向 （所以说 ref 和 arr 可以当做一个东西使用  --> **会有一些安全隐患**）
- rust 中的引用本质上是指针，指向被应用对象 （乍一看和 C/C++ 中的指针概念类似）
- rust 引用是没有**"所有权"**的指针
- 创建引用的这种行为称之为**借用**

<img src="G:\softwares\typora\typora 图片\ownership\image-20250207194813812-17389874087743.png" alt="image-20250207194813812" style="zoom:80%;" />



### 解引用（dereference） 与 引用（reference）

显式解引用 / 引用：

- 解引用 `*`
- 引用 `&`



隐式解引用 / 引用：

- 在使用`.` 运算符调用方法时触发: `x.len()`
- 可以触发多层



### 引用规则

**The Rules of References** 

- At any given time, you can have *either* one mutable reference *or* any number of immutable references.
  在任何给定时刻，都可以有一个可变引用*或*任意数量的不可变引用
- References must always be valid.
  引用必须始终有效

为什么？ 为了满足后面的原则，实现了rust权限管理



## 指针安全原则

**指针安全原则：**

- 数据不应该同时 "被别名引用" 和 "具有可变性"

------> 

**别名和可变性不可同时存在（Rust Avoids Simultaneous Ailasing and Mutation）**

- 别名： 通过不同的变量访问同一数据
- 别名数据：可被多个变量访问的一块数据





## rust 变量权限管理

### 为什么需要权限

前面的**指针安全原则**，Rust的实现方式是：

- Box （有 “所有权”的指针）：
  - 不能别名
  - 将一个 Box 变量赋值给另一个变量  --->  移动了所有权
  - **被所有的数据只能通过其所有者来访问，不能通过别名访问**
- 引用 （无“所有权”的指针）：
  - 旨在临时创建别名



Rust 通过**“借用检查器”**确保引用的安全性，变量对数据有三种权限：

- 读（R）
- 写 （W）
- 拥有（O）：数据可以被**移动**或**释放**

**这些权限运行时并不存在，仅存在于编译器内部**



tips：

- 默认情况下，变量对其数据具有 RO 权限
- 如果一个变量被声明为 `let mut`,则还拥有 W 权限
- 关键：**引用可以临时移除这些权限**

```rust
// 引用与Box
let x = Box::new(1);
let y = x;
// println!("{}", x);  //Box 不能有别名，所有权已经被移交到 y 变量上
println!("{}", y);

// let x0 = *&y;         // 引用 &y 不能传递值
let x1 = &y;
// *x1 = Box::new(-1);   // 引用 x1 只有读的权限
let x2 = &*y;
let x3 = &&&&&&&&y;
println!("{x1} {x2} {x3}");

// 输出: 1 1 1
```



![image-20250208002751699](G:\softwares\typora\typora 图片\ownership\image-20250208002751699-17389873993071.png)

- 第三行处，num使用完毕（被回收）
- 第四行，v使用完毕（被回收）



![image-20250208003238039](G:\softwares\typora\typora 图片\ownership\image-20250208003238039-17389874038692.png)

- x_ref 的 W 权限  -->   x_ref 可以指向另一个变量







### 权限管理 II

权限是定义在 **places** 上的 （不仅仅是变量），places 是任何可以放在赋值语句左侧的东西：

- 变量，例如 `a`
- places 的解引用，例如 `*a`
- places 的数组访问, 例如`a[0]`
- places 的子段访问，例如`a.0  a.field`
- 上述四种的任何组合





变量必须在其所有的引用存在的期间存活 （借用检查器检查）



**流动（flow）权限** F：

- 在表达式使用输入引用或返回输出引用时需要
- F权限在函数体内不会发生变化
- 如果一个引用被允许在特定表达式中使用（即流动）：，那么它就具有F权限







##  Slice 切片

### string slice



![image-20250211121638788](G:\softwares\typora\typora 图片\ownership\image-20250211121638788-17392474048991.png)



![image-20250211122015050](G:\softwares\typora\typora 图片\ownership\image-20250211122015050.png)





### range 语法

```rust
let s: String = String::from("hello world!");

// 切片语法
let slice: &str = &s[0..]  // 全部
let len = s.len();
let slice: &str = &s[0..len] // 全部
let slice: &str = &s[..]   // 全部
let slice: &str = &s[..len] // 全部

let slice: &str = &s[1..3]  // 左闭右开区间
let slice: &str = &s[1..=3] // 闭区间
```





###  其他数据类型的 slice

