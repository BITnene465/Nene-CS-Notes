# common collections

## foreword

### 集合类型中的元素所有权不能随便移动

**一个错误案例:**

```rust
fn main(){
    let mut v = vec![String::from("hello ")];
    let mut s = v[0];     // 集合元素不能移动所有权
    s.push_str("world");
    println!("{s}");
}
```



**正确的写法如下：**

```rust
fn main(){
    let mut v = vec![String::from("hello ")];
    let mut s = v.remove(0);   // 第 0 号元素会被移出 vec，并且把所有权交给 s
    s.push_str("world");
    println!("{s}");
    println!("{}", v.len())
}
```



```rust
fn main(){
    let mut v = vec![String::from("hello ")];
    let mut s = v[0].clone();
    s.push_str("world");
    println!("{s}");
    println!("{}", v.len())
}
```





### 几种迭代方式解析

```rust
let mut v: Vec<i32> = vec![1, 2, 3];

// 几种迭代方式
for item in v {}    // 会获取所有权，之后 v 就不可用了 
for item in v.into_iter()  {}   // 效果同上
for item in v.iter() {}   // iter方法会得到一个迭代器，每次返回元素的不可变引用
for item in &v {}      // &v 会调用其 into_iter() 方法，效果和 v.iter() 一致
for item in v.iter_mut()  {}    // 得到一个迭代器，每次返回元素的可变引用, 需要 v 是 mutable 	
for item in &mut v {}       // 效果同上
for item in (&v).iter() {}  // 通过 . 调用方法的时候， rust 会自动进行 deref， 效果与 v.iter() 一致

// for 语句会自动进行 模式匹配 ， 此时 item的类型是 i32
for &item in &v {}  
for &mut item in &mut v{}    // 无法这样使用，想想为什么？
```









## Vec













## String

### 简介

**Rust 的核心语言: str (&str)**



**String 类型：**

- 来自标准库
- 可变、可增长 、拥有所有权
- UTF-8 编码
- 是对 `Vec<u8>` 的一个包装，是存储 **字节** 的向量



**三种与 String 相关的视角：**

1. 字节 (u8)
2. Unicode 标量值 (Rust 中的 char)
3. 字形簇 -- 有些文字的字母需要多个 unicode 标量组合起来

<img src="G:\softwares\typora\typora 图片\collections\image-20250212143454890.png" alt="image-20250212143454890" style="zoom:67%;" />





### 创建 String

所有实现了 **Display trait** 的类型都有 `to_string()` 方法

```rust
let s = "hello world".to_string();
let s = String::from("hello world");
```



### 更新 String



**使用 `push_str()` 方法：**

- 需要原字符串 `s` 有 W 权限 (mutable)
- 输入参数 `ap` 的类型为 `&str`  (字符串切片类型)
- 方法调用结束后， `ap` 仍然可以使用 （并没有移动所有权）

```rust
let mut s = String::from("foo");
let ap = "bar";
s.push_str(ap);    // 添加到字符串s的末尾
println!("{s}");
println!("{ap}");

// 也可以是 String， 因为 &String 会隐式地转换为 &str
let mut s1 = String::from("hello");
let s2 = String::from("world");
s1.push_str(&s2);

```





**使用 `push()` 方法：**

- 需要原字符串 `s` 有 W 权限 
- 输入参数 `ap` 的类型是 `char`
- 由于 `char` 类型实现了 **copy trait**, 所以不会发生所有权的移动

```rust
fn main(){
    let mut s = "foot".to_string();
    let ch = 'a';
    s.push(ch);
    println!("{ch}");
}
```







### 连接 String



**使用  `+`:**

- 调用了 String 中的一个私有方法 `fn add(self, s: &str) -> String`
-  需要 `&ap` 有 R 权限， `s` 有 O 权限

<img src="G:\softwares\typora\typora 图片\collections\image-20250212134427065.png" alt="image-20250212134427065" style="zoom:80%;" />

```rust
fn main(){
    let s = "foot".to_string();
    let ap: String = String::from("ball");
    
    // 单个字符串拼接
    let new_s = s + &ap;
           // println!("{s}");  // 报错： s所有权已经被移动，已经不能再使用 s
    println!("{new_s}");
    
    // 多个字符串拼接
    let mut s1 = String::from("tic");
    let s2 = String::from("toc");
    let s3 = String::from("toe");
    s1 = s1 + "-" + &s2 + "-" + &s3;
    println!("{s1}"); 
}
```





**使用 `format!` 宏：**

- 更加常用

- 更适合在多字符串拼接的时候使用
- 不会夺走使用权，而是 **重新分配内存并创建变量**

```rust
fn main(){
    let s1 = String::from("tic");
    let s2 = String::from("toc");
    let s3 = String::from("toe");
    let new_s1 = format!("{}-{}-{}", s1, s2 ,s3);
    println!("{s1}"); 
    println!("{s2}");
    println!("{s3}");
    println!("{new_s1}");
}
```







### 访问 String

**rust 中无法使用整数索引访问 String**：

- 前面提到 String 是 Vec \< u8 \> 的包装，由于使用的 UTF-8 编码（变长编码），如果直接使用整数访问字节，不一定能得到有含义的字符，**所以 Rust 直接断绝了这种访问方式**
- 就算 Rust 准备按照 UTF-8 的标准识别字符，由于 UTF-8 变长编码的特性，Rust 必须从头开始遍历内容直到指定索引，已确定有多少个有效字符，无法达到固定的 $O(1)$ 搜索时间

```rust
let hello = String::from("hello");
let h = hello[0];    // 报错！！！
```





**rust 可以通过切片访问 String 和 &str：**

- 单位是 **字节**

```rust
let s = String::from("你是hello");
let slice = &s[0..3];
println!("{slice}");    // 打印 "你"

let s = "hello";
let slice = &s[0..3];
println!("{slice}");   // 打印 "hel"
```





### String 遍历



**使用 `chars()` 和 `bytes()` 方法：**

- `chars()` 的单位是 Unicode 标量值
- `bytes()` 的单位是 u8 字节

```rust
for c in "你好".chars(){
    println!("{c}");
}
for c in "你好".bytes(){
    println!("{c}");
}
```



*输出结果为：*

```shell
你
好
228
189
160
229
165
189
```







**对比 `bytes()` 和 `as_bytes()` 两个方法 **

- `bytes()` 返回一个迭代器，每次得到一个 类型为 `u8` 的值
- `as_bytes()` 返回一个类型为  `&[u8]` (而不是 **&mut [u8]**) 的值，即 u8 字符数组的 **不可变切片** 
- 当然也还有返回 **可变切片** 的方法 `as_bytes_mut()` 不过这个方法是 **unsafe!!!!**



```rust
let s = String::from("你好hello");
println!("String: {s}");
let bytes = s.as_bytes();
println!("&[u8]: {bytes:?}");
```



*输出为：*

```shell
String: 你好hello
&[u8]: [228, 189, 160, 229, 165, 189, 104, 101, 108, 108, 111]
```











## HashMap



### 简介

需要引用模块 `use std::collections::HashMap`



**设计哲学：**

- 键不可变，值可变
- 删除旧键，插入新键



### @ownership

`map.insert(k, v)` ：

- 如果 k, v 实现了 copy trait, 则会复制一份放入 map
- 否则会夺走 k, v 的 ownership， 可以使用 `map.insert(k.clone(), v.clone())` 来避免所有权移动



### 创建 HashMap

1.  使用 `HashMap::new()` 创建空的 HashMap

```rust
fn main() {
    let mut map: HashMap<String, i32> = HashMap::new();
    // 添加元素
    map.insert("a", 10);
    map.insert("b", 20);
    println!("{:?}", map);
}
```



2. 使用 `HashMap::with_capacity()` 创建一个有初始容量的 `HashMap`
   - 规定初始容量，可以避免因为 **初始容量过小** 导致中途重新进行内存分配

```rust
fn main() {
    let mut map = HashMap::with_capacity(10); // 初始容量为10
    map.insert("a", 10);
    map.insert("b", 20);
    println!("{:?}", map);
}
```



3. 使用 `HashMap::from()` 从 `[(_,_); _]` 类型创建

```rust
fn main() {
    let map: HashMap<&str, i32> = HashMap::from([("a", 10), ("b", 20)]);
    println!("{:?}", map);
}
```





### 更新 HashMap

```rust
let mut map1: HashMap<String, i32> = HashMap::new();
map1.insert(String::from("has"), 1);

// 更新HashMap
map1.insert(String::from("hello"), 10);   // insert 插入, 如果键已经存在，则会使用薪值覆盖原值
map1.entry(String::from("halo")).or_insert(100);   // 如果已经存在就不改，如果不存在就插入值
	// 在值的基础上更新 1
let val_ref = map1.entry(String::from("sOx")).or_insert(1000);  // 会返回 值的可变引用
*val_ref += 10;
	// 在值的基础上更新 2
match map1.get_mut(&String::from("hello")) {
    None => {println!("不存在键");}
    Some(val_ref) => {
        *val_ref += 1;
    }
}
println!("upd map1 {map1:?}");
```





- `insert` 更新直接可能直接覆盖原值
- `entry + or_insert` 的方式可以来插入新值，并且不覆盖原值， 并且会返回值的可变引用，用于进一步 **更新**
- 使用 `get_mut()` 方法获取可变引用进行更新





### 遍历 HashMap

```rust
// 遍历键值对
for (key, value) in &map {}    
for (key, value) in map.iter() {}   // 同上
for (key, value) in &mut map {}   // 只有 value 是可变引用
for (key, value) in map.iter_mut() {}  // 同上
// 遍历键
for key in map.keys() {}  
// 遍历值
for value in map.values() {}
for value in map.values_mut() {}
```



分别是遍历 *键值对、键、值* 的方法











