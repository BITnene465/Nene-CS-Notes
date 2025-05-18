# rust 构建测试

## rust 中如何测试？

执行 `cargo test`

----> rust 编译生成一个 test runner(二进制文件)

--------> 运行带有 `#[test]` 的函数，并且报告结果



更多的方式 -->  `cargo test --help`



## 什么是测试？



### basic

**Test** 测试就是一些函数：

1. 设置所需的数据或者状态
2. 运行需要被测试的代码
3. 断言（assert）其结果是你想要



**最简单的情况下：**

Tests(测试) 就是带有 `#[test]` 的函数

```rust
[#test]
fn it_works() {
    let result = add(2, 2);
    assert_eq!(result, 4);
} 
```



### 测试宏

**测试常用宏**：

1. `assert!` 宏：
   - 接受一个 boolean 值
   - 如果为 true, 就通过测试
   - 否则引发 panic
2. `assert_eq` 宏 和 `assert_ne!` 宏：
   - 测试相等性
   - **断言失败时**：会打印出失败的值
   - 使用的值就是 `==` 和 `!=` ， 所以被比较的值需要实现 PartialEq 和 Debug trait





`#[should_panic]` , 如果函数引发了 panic 则通过测试，否则失败

- 如果测试函数返回 `Result<T, E>`, 则不能使用 `#[should_panic]`
- 断言某操作 **返回 Err**, 应该使用 `assert!(value.is_err())` 





### 测试类型

- **单元测试( Unit tests )**：小而集中的测试，每次只测试一个模块，并且可以测试私有接口
- **集成测试( Integration tests)**: 完全依靠外部的测试，仅仅使用公共接口，并且可能一个测试覆盖多个模块  







## 单元测试

单元测试代码通常和被测试代码放在同一个文件中，并且放在 `#[cfg(test)]` 注解的 **tests 模块**中

`#[cfg(test)]` 注解的模块只会在测试用被编译！而不会影响 `cargo build` 的编译速度





## 集成测试

集成测试需要再项目中创建 **tests 目录**来编写集成测试：

- 该目录下每个文件都是一个**单独的 crate （单独的测试）**

<img src="G:\softwares\typora\typora 图片\rust的测试\image-20250214184047914.png" alt="image-20250214184047914" style="zoom:80%;" />





