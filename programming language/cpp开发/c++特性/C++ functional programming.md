# C++ functional programming



## Lambda Expression

### C++ lambda basic use

---

#### 基本语法

Lambda 表达式的基本语法如下：
```cpp
[capture-list](parameters) -> return-type { body }
```


- **`[capture-list]`**：捕获列表，用于指定如何捕获外部变量。
- **`(parameters)`**：参数列表，与普通函数的参数列表类似。
- **`-> return-type`**：返回类型（可选）。如果省略，编译器会自动推导返回类型。
- **`{ body }`**：函数体，包含 Lambda 表达式的逻辑。

---

#### 捕获列表 `[capture-list]`
捕获列表用于指定 Lambda 表达式如何访问外部作用域的变量。

- **值捕获 `[=]`**：以值的方式捕获外部变量，捕获的变量在 Lambda 表达式内部是只读的（除非使用 `mutable` 关键字）。
  ```cpp
  int x = 10;
  auto lambda = [=]() { return x + 1; };
  cout << lambda(); // 输出 11
  ```

- **引用捕获 `[&]`**：以引用的方式捕获外部变量，捕获的变量在 Lambda 表达式内部可以修改。
  ```cpp
  int x = 10;
  auto lambda = [&]() { x += 1; };
  lambda();
  cout << x; // 输出 11
  ```

- **混合捕获**：可以同时使用值捕获和引用捕获。
  ```cpp
  int x = 10, y = 20;
  auto lambda = [&x, y]() { x += y; };
  lambda();
  cout << x; // 输出 30
  ```

- **显式捕获**：可以显式指定捕获的变量。
  ```cpp
  int x = 10, y = 20;
  auto lambda = [x, &y]() { y += x; };
  lambda();
  cout << y; // 输出 30
  ```

- **默认捕获 + 显式捕获**：可以结合默认捕获和显式捕获。
  ```cpp
  int x = 10, y = 20;
  auto lambda = [=, &y]() { y += x; }; // 默认值捕获，显式引用捕获 y
  lambda();
  cout << y; // 输出 30
  ```

---

#### 参数列表 `(parameters)`
Lambda 表达式的参数列表与普通函数的参数列表类似。如果没有参数，可以省略 `()`。
```cpp
auto lambda = []() { cout << "Hello, World!"; };
lambda(); // 输出 Hello, World!
```

带参数的 Lambda：
```cpp
auto add = [](int a, int b) { return a + b; };
cout << add(3, 4); // 输出 7
```

---

#### 返回类型 `-> return-type`
返回类型可以显式指定，也可以由编译器自动推导。如果函数体只有一条 `return` 语句，编译器可以自动推导返回类型。
```cpp
auto square = [](int x) -> int { return x * x; };
cout << square(5); // 输出 25
```

如果省略返回类型：
```cpp
auto square = [](int x) { return x * x; };
cout << square(5); // 输出 25
```

---

#### 函数体 `{ body }`
函数体是 Lambda 表达式的逻辑部分，与普通函数的函数体相同。
```cpp
auto print = [](const string& msg) { cout << msg << endl; };
print("Hello, Lambda!"); // 输出 Hello, Lambda!
```

---

#### `mutable` 关键字
默认情况下，值捕获的变量在 Lambda 表达式内部是只读的。如果需要在 Lambda 内部修改值捕获的变量，可以使用 `mutable` 关键字。
```cpp
int x = 10;
auto lambda = [x]() mutable { x += 1; return x; };
cout << lambda(); // 输出 11
cout << x;       // 输出 10（外部变量未被修改）
```

---

#### Lambda 表达式的类型
Lambda 表达式的类型是一个唯一的、匿名的函数对象类型。通常使用 `auto` 来声明 Lambda 表达式。
```cpp
auto lambda = []() { cout << "Hello, Lambda!"; };
```

如果需要显式指定类型，可以使用 `std::function`：
```cpp
#include <functional>
std::function<void()> lambda = []() { cout << "Hello, Lambda!"; };
lambda();
```

---

#### Lambda 表达式的用途
Lambda 表达式在 C++ 中非常灵活，常见的用途包括：

- **作为函数参数**：Lambda 表达式可以传递给算法函数，例如 `std::sort`、`std::for_each` 等。
  ```cpp
  #include <algorithm>
  #include <vector>
  vector<int> nums = {3, 1, 4, 1, 5, 9};
  sort(nums.begin(), nums.end(), [](int a, int b) { return a > b; });
  // nums = {9, 5, 4, 3, 1, 1}
  ```

- **作为局部函数**：Lambda 表达式可以在函数内部定义，作为局部函数使用。
  ```cpp
  void foo() {
      auto print = []() { cout << "Inside foo()"; };
      print();
  }
  ```

- **作为回调函数**：Lambda 表达式可以作为回调函数传递给异步任务或事件处理器。
  ```cpp
  #include <thread>
  thread t([]() { cout << "Hello from thread!"; });
  t.join();
  ```

---

#### 递归 Lambda 表达式

Lambda 表达式可以通过将自身作为参数传递来实现递归调用。

> 在C++中，`auto&&`是一种通用引用，它可以绑定到左值（lvalue）或右值（rvalue）

```cpp
auto factorial = [](auto&& self, int n) -> int {
    return n <= 1 ? 1 : n * self(self, n - 1);
};
cout << factorial(factorial, 5); // 输出 120
```

---

#### Lambda 表达式的性能

Lambda 表达式通常会被编译器内联优化，因此性能与普通函数相当。捕获列表和 `std::function` 的使用可能会引入额外的开销，但在大多数情况下可以忽略。

---

### 总结

- Lambda 表达式是一种简洁的定义匿名函数的方式。
- 捕获列表 `[capture-list]` 用于指定如何捕获外部变量。
- 参数列表 `(parameters)` 和返回类型 `-> return-type` 与普通函数类似。
- `mutable` 关键字允许修改值捕获的变量。
- Lambda 表达式可以用于算法、回调函数、局部函数等场景。
- 递归 Lambda 表达式可以通过将自身作为参数传递来实现。





## in STL

###  `std::function`

`std::function` 是一个通用的函数包装器，可以存储、复制和调用任何可调用对象（如函数指针、Lambda 表达式、成员函数等）。它是实现高阶函数的重要工具。

```cpp
#include <functional>
#include <iostream>

void print(int x) {
    std::cout << x << std::endl;
}

int main() {
    std::function<void(int)> func = print;
    func(42); // 输出 42
    return 0;
}
```





###  `std::bind`

`std::bind` 用于将函数与参数绑定，生成一个新的可调用对象。它可以部分应用函数参数，或者重新排列参数顺序。

有点像 py 中的装饰器

```cpp
#include <iostream>
#include <functional>

int add(int a, int b) {
    return a + b;
}

int main() {
    auto add5 = std::bind(add, 5, std::placeholders::_1);
    std::cout << add5(10); // 输出 15
    return 0;
}
```





### 流式操作

#### `std::transform`

`std::transform` 是 STL 中的一个算法，用于对容器中的每个元素应用一个函数，并将结果存储到另一个容器中。它是函数式编程中 `map` 操作的实现。

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> nums = {1, 2, 3, 4, 5};
    std::vector<int> result(nums.size());

    std::transform(nums.begin(), nums.end(), result.begin(), [](int x) { return x * 2; });

    for (int x : result) {
        std::cout << x << " "; // 输出 2 4 6 8 10
    }
    return 0;
}
```



####  `std::for_each`

`std::for_each` 是 STL 中的一个算法，用于对容器中的每个元素应用一个函数。它是函数式编程中 `forEach` 操作的实现。

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> nums = {1, 2, 3, 4, 5};
    std::for_each(nums.begin(), nums.end(), [](int x) { std::cout << x << " "; }); // 输出 1 2 3 4 5
    return 0;
}
```









#### `std::accumulate`

`std::accumulate` 是 STL 中的一个算法，用于对容器中的元素进行累加或其他二元操作。它是函数式编程中 `reduce` 操作的实现。

```cpp
#include <iostream>
#include <vector>
#include <numeric>

int main() {
    std::vector<int> nums = {1, 2, 3, 4, 5};
    int sum = std::accumulate(nums.begin(), nums.end(), 0);
    std::cout << sum; // 输出 15
    return 0;
}
```







### 模式匹配(感觉不如 rust)

#### `std::optional`

`std::optional` 是 C++17 引入的特性，用于表示一个可能不存在的值。它是函数式编程中 `Maybe` 或 `Option` 类型的实现。

如果不存在需要使用 `std::nullopt`,

```cpp
#include <iostream>
#include <optional>

std::optional<int> divide(int a, int b) {
    if (b == 0) return std::nullopt;
    return a / b;
}

int main() {
    auto result = divide(10, 0);
    if (result) {
        std::cout << *result;
    } else {
        std::cout << "Division by zero!";
    }
    return 0;
}
```





#### `std::variant` 和 `std::visit`

`std::variant` 是 C++17 引入的特性，用于表示一个可以存储多种类型的值。`std::visit` 用于对 `std::variant` 进行模式匹配。

```cpp
#include <iostream>
#include <variant>
#include <string>

int main() {
    std::variant<int, std::string> v = "Hello";
    std::visit([](auto&& arg) { std::cout << arg; }, v); // 输出 Hello
    return 0;
}
```





