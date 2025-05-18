# rust 代码组织形式

## crate

**crate 是组织和共享代码的基本构建块**

- binary crate：可执行的，需要 main 函数
- library crate：没有 main 函数，无法执行。定义了一些功能，可以共享使用



**crate root 是编译 crate 的入口（源代码文件）**

- binary crate: src/main.rs
- library crate: src/lib.rs





## package

**package 由 1 个或多个 crates 组成**, package 的规则：

- 包含 Cargo.toml 文件 （描述了如何构建这些 crates）
- 可有多个 binary crates
- 最多只能有一个 library crate
- 但是至少得有一个 crate



使用 `cargo new` 创建 package:

- `cargo new project_name` 创建一个 package，包含一个 binary crate
- `cargo new project_name --lib` 创建一个 package，包含一个 lib crate







## Module 模块

### 简介

>  module 将代码组织成更小、更容易管理单元的方法

- 使用 `mod` 关键字声明
- 可以有子模块
- 路径 （path）
- public v.s. private
- 引用 (use)



**在哪里声明 module？**

在 src 目录下新建一个 `lib.rs` 文件，在这个文件里面声明模块

```rust
```







**rust 编译器如何寻找 module 定义？** 假如现在`lib.rs`声明了一个`<models_name>`的模块：

1. 内联（inline）： 在当前文件内寻找，直接在当前文件内定义即可
2. 在同级目录中寻找是否存在 `<models_name>.rs ` !!!!，在该文件内定义
3. 在同级目录中寻找是否存在 `< models_name >/mod.rs`，在这个 `mod.rs` 文件中定义



我们一般使用第二种方法构建模块，假如在同级目录下的 `<models_name>.rs` 文件中构建模块，如何构建其子模块？

- 在同级下创建 `<models_name>` 目录
- 在 `<models_name>` 目录下创建 `<子模块名称>.rs`, 并且在该文件下构建子模块



### 路径（path）

**绝对路径调用**：

- binary crate 的顶级模块可以使用 `crate` 
- 在 binary crate 中调用 lib crate 的模块，需要使用 `<package_name>` 定位到 src 目录(此处可能表述不准确)，再进一步访问下面的模块



**相对路径调用**：

- `super` 当前模块的上一级模块
- `self` 当前模块



### 可见性



**模块的可见性：**

- 所有的东西 **(functions, methods, structs, enums, modules, and constants)** 默认对父模块是 **private** (私有的)
- 父模块中的项不能使用子模块中的私有项
- 但子模块中的项可以使用其祖先模块中的项
- 使用 `pub` 关键字让其变为 **public**





**Struct 和 Enum 属性的可见性**

<img src="G:\softwares\typora\typora 图片\rust代码的组织形式\image-20250211213236261.png" alt="image-20250211213236261" style="zoom:70%;" />







### use 引用

**引用规则：**

- function: 引用到父模块
- struct、enum ... : 引用完整路径



**如果引用的项目同名？**

1. 方法一：只引用到父模块

   <img src="G:\softwares\typora\typora 图片\rust代码的组织形式\image-20250211213914005.png" alt="image-20250211213914005" style="zoom:100%;" />

2. 方法二：使用 `as` 关键字声明别名

   <img src="G:\softwares\typora\typora 图片\rust代码的组织形式\image-20250211213958122.png" alt="image-20250211213958122" style="zoom:80%;" />





### 为 package 添加依赖项

- 直接在 `cargo.toml` 中加，IDE会自动下载
- 使用 `cargo add <crate_name>` 来给项目添加 crate