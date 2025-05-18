# structure 结构体

## 类型

> **结构体命名采用 PacscalCase**

### 普通 struct



```rust
fn main() {
    let mut user1 = User { // 结构体创建语法
        email: String::from("bitnene@gmail.com"),
        sign_in_count: 1,
        username: String::from("nene"),
        password: String::from("jkl123"),
        active: true,
    };
    println!("{:}", user1.email); // . 运算符访问属性
    user1.email = String::from("nene@gmail.com");  // mutable， 可以改变属性的值

    let mut user2 = User{  // 语法糖：其余字段与 user1 相同
        email: String::from("shinku@gmail.com"),
        ..user1
    };
    user2.username = String::from("shinku");  // user2 的子段的可变性与 user1 无关
}
struct User{
    active: bool,
    username: String,
    email: String,
    sign_in_count: u64,
    password: String,
}
```



![image-20250211131047362](G:\softwares\typora\typora 图片\struct\image-20250211131047362.png)







### tuple struct

特点：

- 使用struct 声明
- 但是字段没有名字

```rust
// tuple struct
struct Point3d(i32, i32, i32);   // 声明完最后要有 分号 ;
struct Color(i32, i32, i32);

fn main() {
    let point1 = Point3d(1, 1, 1);  // 构建语法
    let color = Color(1, 1, 1);
}
```



虽然 point1 和 color 形式一样，但是含义不同，也不相等









###  unique struct

特点：

- 没有字段
- 可以用于实现一些行为（Trait等）

```rust
struct AlwaysEqual;
```





## 操作



### 借用结构体的字段（属性）

```rust
fn main(){
// test struct attribute reference
    let mut point2 = Point{x: 1, y: 2};
    let x = &mut point2.x;
    let y = &mut point2.y;   // 还可以借 --> 和元组类似；与数组不同
    println!("{}", x);
}
struct Point{x: i32, y: i32}
```



结构体借用字段和元组借用字段类似：

- 如果字段 x 有可变引用，仍然可以改变字段 y 的值 （**互相独立**）



### Derived Trait

**结构体在执行某些操作之前需要实现某些特性 （Trait）**

下面是一个快速实现 Debug 特性的语法糖：

```rust
fn main(){
    let rect1 = Rect{
        width: 10,
        height: 100,
    };
    println!("{:?}", rect1);     // 不实现debug 特性则会报错
    println!("{:#?}", rect1);    // 加一个 # 可以让打印内容更加美观
}
#[derive(Debug)]   // 快速实现 Debug 特性 (也可以用于实现别的特性)
struct Rect{
    width: u32,
    height: u32,
}
```



**输出如下：**

```shell
Rect { width: 10, height: 100 }
Rect {
    width: 10,
    height: 100,
}
```









### `impl` 实现方法

```rust
impl Rect {
    fn area(&self) -> u32{
       self.height * self.width 
    }
    fn can_hold(&self, rect: &Rect) -> bool{
        if self.width > rect.width && self.height > rect.height{
            return true;
        }
        return false;
    }
    fn create_square(size: u32) -> Self{
        Self {
            height: size,
            width: size,
        }
    }
}
```



- `&self` 是一个语法糖:  等价于普通函数的 `self: &Self`  (此处的 `Self` 就是 `Rect` 的一个别名)，表示是原实例的**不可变引用**

- `&mut self` 表示是原实例的一个可变引用
- `self` 表示是原实例，会直接拿到所有权 (**所以一般不这么使用**)





```rust
fn main(){
    let rect1 = Rect{
        width: 10,
        height: 100,
    };
    let sq1 = Rect::create_square(9);
    println!("{sq1:#?}");
    println!("rect1 can hold sq1? {}", rect1.can_hold(&sq1));
    println!("rect1 can hold sq1? {}", Rect::can_hold(&rect1, &sq1));  // 这种调用方式也可以
}
```



-  其中的 `create_square` 第一个参数不是 `self` 相关的，那么这就是结构体的**关联函数(Associated Functions)（理解成类函数）**
- 调用方式为 `let sq1 = Rect::create_square(10);`
- 对于**实例方法**，也可以采用类似 `Rect::can_hold(&rect1, &sq1)` 的方法调用











