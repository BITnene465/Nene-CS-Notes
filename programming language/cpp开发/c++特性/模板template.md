# Template

> 

## 使用类模板和声明类型别名

### 类内声明类型别名

在类内声明类型别名，可以确保模板参数在正确的作用域内被解析。以下是如何在类内声明类型别名的步骤和示例。

#### 定义类模板

首先，在 `mytrees.h` 文件中定义类模板 `TreeNode`。

```cpp
#ifndef MYTREES_H
#define MYTREES_H

template<typename Value, typename Key = int>
class TreeNode {
private:
    Value value;   // 值
    Key key;       // 排序的依据

public:
    using TreeNodePtr = TreeNode<Value, Key>*;  // 在类内声明类型别名

    TreeNode(Value v, Key k) : value(v), key(k) {}

    TreeNodePtr createNode(Value v, Key k) {
        return new TreeNode(v, k);
    }

    Value getValue() const { return value; }
    Key getKey() const { return key; }
};

#endif // MYTREES_H
```

#### 使用类型别名

在代码中使用 `TreeNodePtr` 类型别名。

```cpp
#include <iostream>
#include "mytrees.h"

int main() {
    using IntTreeNode = TreeNode<int>;  // 实例化类模板
    IntTreeNode::TreeNodePtr node = new IntTreeNode(10, 1);  // 使用类型别名创建指针

    std::cout << "Value: " << node->getValue() << ", Key: " << node->getKey() << std::endl;

    delete node;  // 别忘了释放内存
    return 0;
}
```

### 类外声明类型别名

在类外声明类型别名，使用模板别名 `using TreeNodePtr = TreeNode<Value, Key>*;`。

#### 定义类模板

首先，在 `mytrees.h` 文件中定义类模板 `TreeNode`。

```cpp
#ifndef MYTREES_H
#define MYTREES_H

template<typename Value, typename Key = int>
class TreeNode {
private:
    Value value;   // 值
    Key key;       // 排序的依据

public:
    TreeNode(Value v, Key k) : value(v), key(k) {}

    Value getValue() const { return value; }
    Key getKey() const { return key; }
};

#endif // MYTREES_H
```

#### 在类外声明类型别名

在 `main.cpp` 文件中使用模板别名 `using TreeNodePtr = TreeNode<Value, Key>*;` 在类外声明类型别名。

```cpp
#include "mytrees.h"

// 在类外声明类型别名
template<typename Value, typename Key = int>
using TreeNodePtr = TreeNode<Value, Key>*;
```

#### 使用类型别名

在代码中使用 `TreeNodePtr` 创建指向 `TreeNode` 的指针，并访问其成员变量。

```cpp
#include <iostream>
#include "mytrees.h"

// 在类外声明类型别名
template<typename Value, typename Key = int>
using TreeNodePtr = TreeNode<Value, Key>*;

int main() {
    // 使用类型别名创建指针
    TreeNodePtr<int> node = new TreeNode<int>(10, 1);

    // 使用添加的函数来访问 value 和 key
    std::cout << "Value: " << node->getValue() << ", Key: " << node->getKey() << std::endl;

    delete node;  // 别忘了释放内存
    return 0;
}
```

### 详细步骤总结

#### 类内声明类型别名

1. **定义类模板**：在 `mytrees.h` 文件中定义类模板 `TreeNode`。
2. **类内声明类型别名**：在类内使用 `using TreeNodePtr = TreeNode<Value, Key>*;` 声明类型别名。
3. **使用类型别名**：在代码中通过实例化后的类引用 `TreeNodePtr`。

#### 类外声明类型别名

1. **定义类模板**：在 `mytrees.h` 文件中定义类模板 `TreeNode`。
2. **类外声明类型别名**：在 `main.cpp` 文件中使用模板别名 `using TreeNodePtr = TreeNode<Value, Key>*;` 在类外声明类型别名。
3. **使用类型别名**：在代码中通过实例化后的类引用 `TreeNodePtr`，并访问其成员变量。





## 模板 + 多文件

涉及到模板类的代码全部放到**头文件**中，如果分为**头文件(.h)**和**源文件(.cpp)**，可能导致编译上的一些链接错误。







