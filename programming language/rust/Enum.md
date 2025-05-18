# Enum  && pattern matching

> **枚举命名采用 PacscalCase**



##  枚举的使用实例

### 例子 1 -- 最基本的枚举

```rust
enum IpAddrKind {
    V4,
    V6,
}
struct IpAddr {
    kind: IpAddrKind,
    address: String,
}
let home = IpAddr {
    kind: IpAddrKind::V4,
    address: String::from("127.0.0.1"),
};
let loopback = IpAddr {
    kind: IpAddrKind::V6,
    address: String::from("::1"),
};
```



基本的枚举：

- 有多个枚举变体
- 使用 `EnumName::VariantName` 来访问枚举变体



### 例子 2 -- enum variants 拥有 struct 类型数据

```rust
struct Ipv4Addr {
    // --snip--
}

struct Ipv6Addr {
    // --snip--
}

enum IpAddr {
    V4(Ipv4Addr),
    V6(Ipv6Addr),
}
```



可以将任何类型的数据放入枚举变体中：例如 字符串、数字类型或结构，**甚至可以包含另一个枚举**。



### 例子 3 -- enum variants 拥有 其他几种类型的数据

```rust
enum Message {
    Quit,
    Move { x: i32, y: i32 },
    Write(String),
    ChangeColor(i32, i32, i32),
}
```


此枚举有四种不同类型的变体：

- `Quit` has no data associated with it at all.
- `Move` has named fields(命名字段), like a struct does.
- `Write` includes a single `String`.
- `ChangeColor` includes three `i32` values



### 例子 4 -- 实现枚举的方法

和实现结构体方法类似，使用 `impl` 关键字

```rust
impl Message {
    fn call(&self) {
        // method body would be defined here
    }
}

let m = Message::Write(String::from("hello"));
m.call();
```







## 标准库常用枚举



### Option 枚举

```rust
enum Option<T> {
    None,
    Some(T),
}
```



- 表示某个值可能存在或不存在
- 来自标准库， **Option** 和 **None** 和 **Some** 都在 preclude 中
- **Option \< T \>**  和 **T** 并不同类，强制要求你处理数值为 **None** 的情况









## Match Control Flow



### 关于 `match`

`match` 表达式可以有**返回值**：

- 但是*每个分支的返回值类型必须一致*，除了会直接退出程序的分支（如 panic! 等）

- 如何让返回值类型一致 ？—— **使用枚举类型** 





### 例子 1 -- `_` 匹配符

 

使用 `_`  匹配除了列出的模式的其他所有的模式：

- 把 `_` 改成其他变量名也可以： 如 `other` 等，但是一般使用 `_` 来匹配不使用的值

- 必须每个模式都可以得到匹配
- 有哪些模式要匹配？ 取决于 **待匹配变量的类型**，此处 `ip1` 的类型是 `IpAddr`

```rust
fn main(){
    let mut ip1 = IpAddr::V4(127, 0, 0, 1);
    match ip1{
        IpAddr::V4(a, b, c,d ) => {
            println!("ipv4地址是: {a}.{b}.{c}.{d}");
        }
        _ => {}   
    }
}
enum IpAddr{
    V4(u8, u8, u8, u8),
    V6(String),
}
```





```rust
fn main(){
    let mut ip1 = IpAddr::V4(127, 0, 0, 1);
    match ip1{
        IpAddr::V4(a, b, c,d ) => {
            println!("ipv4地址是: {a}.{b}.{c}.{d}");
        }
        IpAddr::V6(_) => {}   
    }
}
enum IpAddr{
    V4(u8, u8, u8, u8),
    V6(String),
}
```



```rust
fn main(){
    let x: i32 = 10;
    match x{
        3 => {},
        7 => {},
        _ => {println!("无效数值")},
    }
}
```





### 例子 2 -- Option \< i32 \> 已经实现 copy trait

- 调用 `plus_one(five)` 的时候，会复制 `five` 并且传递给形参 `x`，故不会发生所有权的转移

```rust
fn main(){ 
    fn plus_one(x: Option<i32>) -> Option<i32>{
        match x {
            None => None,
            Some(i) => Some(i+1),
        }
    }
    let five:Option<i32> = Some(5);
    let none:Option<i32> = None;   // 必须写上类型，否则 rust 编译器无法推断类型
    let six = plus_one(five);

    println!("{five:?}");
    println!("{six:?}");
}
```





### 例子 3 -- 匹配时也建议使用引用

```rust
fn main(){
    let opt = Some(String::from("hello world"));
    match opt{
        Some(_) => {println!("Some!")},
        None => {println!("None!")},
    }
    println!("{:?}", opt);
}
```



可以正常输出，可是在改变一点后会报错（如下）：

```rust
fn main(){
    let opt = Some(String::from("hello world"));
    match opt{
        Some(s) => {println!("Some! {s}")},
        None => {println!("None!")},
    }
    println!("{:?}", opt);    // 报错： borrow of patially moved value: 'opt'
}
```



- 因为在匹配的时候 `Some(s) => {println!("Some! {s}")},`  会将 **Option** 中的 **String** 变量赋值给变量 `s`
- 赋值之后， String 数据的使用权被移动到变量 `s`, 并且在 match 语句结束后销毁



可以按照如下的方式更改： **使用引用匹配！**

- 对 `&opt` 进行匹配
- 匹配 `&opt` 时，`match` 表达式会自动解引用（deref）一层，因此 `Some(s)` 中的 `s` 实际上是对 `opt` 中 `String` 的引用
- 具体来说，`Some(s)` 中的 `s` 的类型是 `&String`，而不是 `String` 

```rust
fn main(){
    let opt = Some(String::from("hello world"));
    match &opt{
        Some(s) => {println!("Some! {s}")},
        None => {println!("None!")},
    }
    println!("{:?}", opt);
}
```



### `if let` 匹配一种情况

`if let <pattern> = <expression> {}` 进行匹配，后也可以加上 `else{}` 表示没有匹配的剩余情况

```rust
fn main(){
    let config_max = Some(3u8);
    if let Some(max) = config_max {    // if let 匹配表达式
        println!("the maximum number is {max}");
    } else {
        println!("None: no maximum number");
    }
}
```























