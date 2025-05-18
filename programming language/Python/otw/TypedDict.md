# TypedDict 类型

## 简介

`TypedDict` 是 Python 的 `typing` 模块中用于定义具有严格键和值类型约束的字典类型的工具。它最初在 **PEP 589** 中引入，从 Python 3.8 开始可用，并在 3.9 及更高版本中有了进一步增强。

与普通的 `dict` 不同，`TypedDict` 提供了一种方法来明确指定字典的结构，包括键和值的类型，从而**增强类型检查和代码的可读性**。



## TypedDict 特点

1. **键和值的类型约束**：
   - 使用 `TypedDict` 定义的字典，其键是预定义的，并且每个键的值类型需要明确声明。
   - 在使用时，如果键或值的类型不符合定义，静态类型检查工具（如 `mypy`）会提示错误。
2. **运行时仍是普通字典**：
   - 在运行时，`TypedDict` 本质上还是普通的 Python 字典，因此可以像普通字典一样操作。
3. **支持必选和可选字段**：
   - 可以区分字段是必须存在的还是可以省略的。



## TypedDict 基本使用

```python
from typing import TypedDict

class User(TypedDict):
    name: str
    age: int
    is_active: bool

user: User = {
    "name": "John Doe",
    "age": 30,
    "is_active": True
}
```

也可以使用 `total = False` +  Optional 来添加可选键:

```python
from typing import TypedDict, Optional

class User(TypedDict, total=False):
    name: str
    age: int
    email: Optional[str]

user: User = {
    "name": "Jane Doe",
    "age": 28
    # email 是可选的
}
```



## TypedDict 高级用法

### 可嵌套





### 可继承



