# RUST

## Variables

### 变量可变性

rust的变量按照可变性分为： 

- **immutable variable**
  - 使用 `let` 声明
- **mutable variable**
  - 使用 `let` + `mut` 声明
  - 可以改变变量的值，但是类型不可改变
- **constant**
  - **命名规范：** 变量名全部使用大写字母，中间使用下划线`_`连接
  - 使用 `const` 声明，且不能使用 `mut`
  - 值的类型必须被注释
  - 常量可以在任何范围内声明，包括全局范围
  - 始终是不可变的
  - 常量只能设置为**常量表达式**，而不能设置为只能在运行时计算的值的结果



### shadowing 机制

声明一个与已有变量同名的新变量时，会掩盖已有变量（新变量可以原变量不同类型），并且将该**变量名**的任何使用都归自己所有，**直到本身被隐藏或范围结束**

```rust
fn main() {
    let x = 5;
    let x = x + 1;
    {
        let x = x * 2;
        println!("The value of x in the inner scope is: {x}");
    }
    println!("The value of x is: {x}");
}
```





## 变量类型



- scalar 标量
  - Interger 整数类型
  - Boolean 布尔类型
  - Float Point 浮点类型
  - Character 字符类型
- compound  组合类型
  - Tuple 元组
    - 固定长度
    - 可以包含不同类型的元素
  - Array 数组
    - 固定长度
    - 元素类型相同



### scalar

```rust
let num_a = 1;  // 默认 i32
let num_b:i64 = 2;
let num_c:u8 = 255;
let num_d:i128 = 111;
let num_e:usize = 46;  // 取决于机器字长

let float_a = 2.0; // 默认 f64
let float_b: f32 = 1.0;

let c = 'z';     // 默认char
let z: char = 'A';
let chinese_char = '我';

let t = true;
let f: bool = false;
```



**关于 Interger 字面量的进制表示:**

- `100_001` Decimal 十进制
- `0xff` Hex 十六进制
- `0o77` Octal 八进制
- `0b1111_0000` Binary 二进制
- `b'A'` Byte（u8 only） 字节 





### Compound

```rust
// 元组 tuple
let my_tuple = ('A', 1, 2, 3)
let tup: (i32, f64, u8) = (500, 16.4, 1);

let num = tup.0;   // 元组的访问
let (c, x, y, z) = my_tuple;

// 数组 Array
let my_arr = [1, 2, 3];
let my_arr_typed: [i32; 3] = [1, 2, 3];
let arr = [3; 5];    // 五个 3

a = my_arr[1];

```





## 函数 function

### 命名规范

函数 & 变量名的命名规范 **snake_case**：

- 所有字母都小写
- 单词之间使用 `_` 连接



### 函数参数

- 必须声明每个参数的类型  `参数名: 类型`
- 多个参数使用 `,` 隔开

```rust
fn myfunc(var1: i32, var2: f64, c: char):
{}
```





### 表达式(expression) vs 语句(statement)

**在 rust 中：**

- 表达式有返回值
- 语句没有返回值

**一个语法糖：**

```rust
{
    let y = 1;
    y + 1
}   // 这个在rust中是一个表达式，返回 2  （注意：最后一行没有分号）
```





### 函数返回值

- 使用 `->` 声明函数返回值的类型

- 返回值：
  - 可以使用 `return` 返回
  - 也可以是函数体中 **最后一个表达式的值**

```rust
fn five() -> i32 {
    5
}
fn main() {
    let x = five();
    println!("the value of x is: {x}");
}
```





### 匿名函数



## Control flow

### if 表达式

```rust
if condition{
} else if{
} else{
}
```



**一个语法糖实例:**

- `{}` 作为表达式 + `if` 控制流

```rust
let condition: bool = true;
let x: i32 = if condition {2} else {3};
```





### 循环

- `while`，`for`  循环和 python 中的循环使用方法类似

```rust
while condition{
    // while 循环
}
for x in xs{
    // for 循环
}
```



- 对于 `loop` 循环：
  - 死循环
  - 可以定义标签（`'label: loop{}`）
  - 使用break退出（并且也可以使用break返回值）

```rust
// break 返回值
let mut cnt = 1;
let mut remain = 32;
cnt = loop {
    if cnt == 10 {
        break remain*2;
    }
    remain -= 1;
    cnt += 1;
};
println!("{}", cnt);

// 带标签的loop循环
cnt = 1;
    remain = 10;
    'counting: loop {
        loop {
            if remain == 8{
                break;
            }
            if cnt == 2{
                break 'counting;
            }
            remain -= 1;
        }
        cnt += 1;
        remain = 10
    }
println!("end cnt = {}", cnt);

```








