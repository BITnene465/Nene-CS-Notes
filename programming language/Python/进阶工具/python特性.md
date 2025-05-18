# python 特性

## 变量作用域与 global nonlocal



### 变量作用域

- **局部作用域（Local）**：在函数内部定义的变量，仅在该函数内有效。
- **外层作用域（Enclosing）**：在嵌套函数中，外层函数的变量对内层函数可见。
- **全局作用域（Global）**：在模块级别定义的变量，整个模块内有效。
- **内置作用域（Built-in）**：Python 内置的变量（如 `print`、`len` 等）。





### `global` 关键字

- **作用**：在函数内部修改全局变量。

- **用法**：

  ```python
  x = 10  # 全局变量
  def func():
      global x
      x = 20  # 修改全局变量
  func()
  print(x)  # 输出 20
  ```





### `nonlocal` 关键字

- **作用**：在嵌套函数中修改外层函数的变量（非全局）。

- **用法**：

  ```python
  def outer():
      x = 10  # 外层变量
      def inner():
          nonlocal x
          x = 20  # 修改外层变量
      inner()
      print(x)  # 输出 20
  outer()
  ```





### 作用域优先级

- **查找顺序**：局部 → 外层 → 全局 → 内置。
- 如果变量在局部作用域中未找到，Python 会依次向外层、全局和内置作用域查找。



### 对比 `nonlocal` 和 `global`

| 关键字     | 作用范围                 | 适用场景                     |
| :--------- | :----------------------- | :--------------------------- |
| `global`   | 全局作用域               | 修改模块级别的变量           |
| `nonlocal` | 外层函数作用域（非全局） | 修改嵌套函数中外层函数的变量 |



### 示例对比

```python
x = 10  # 全局变量

def outer():
    x = 20  # 外层变量
    def inner():
        nonlocal x  # 修改外层变量
        x = 30
    inner()
    print("Outer x:", x)  # 输出 30

outer()
print("Global x:", x)  # 输出 10（全局变量未变）
```





## 生成器 yield

### 基本介绍

`yeild` 关键字将函数变成一个生成器（生成器其实是一种特殊的函数，每次运行到 `yield` 就会返回并且停止在**下一行的入口**）

```python
def Fibonacci(limit):
    a = 0
    b = 1
    for _ in range(limit):
        b, a = a+b, b
        yield a
```



### 生成器的特点

1. **惰性求值**：生成器不会一次性生成所有值，而是按需生成，节省内存。
2. **可迭代**：生成器是一个迭代器，可以使用 `for` 循环或 `next()` 函数逐个获取值。
3. **状态保存**：每次 `yield` 后，生成器会保存当前的状态，下次继续执行。



### 如何使用生成器？

```python
iterable = Fibonacci(10)    # 这返回了一个 迭代器对象的引用
funcObj = Fibonacci       # 这返回了一个 生成器对象引用（和函数引用一样）

# 使用(这下知道 range(10) 怎么来的了)
for x, fx in enumerate(iterable):
    print(f"F({x}) = {fx}")

# 使用 next() 手动获取值
gen = Fibonacci(5)
print(next(gen))  # 输出: 1
print(next(gen))  # 输出: 1
print(next(gen))  # 输出: 2

# 转换为列表
fib_list = list(Fibonacci(5))
print(fib_list)  # 输出: [1, 1, 2, 3, 5]
```





### 生成器表达式（Generator expression）

- **作用**：惰性生成数据，节省内存。

- **语法**：`(表达式 for 变量 in 可迭代对象 if 条件)`

- **示例**：

  ```python
  gen = (x**2 for x in range(10))  # 生成器对象
  for num in gen:
      print(num)
  ```





## 装饰器

### 什么是装饰器？

装饰器是一种用于修改或扩展函数行为的工具。它本质上是一个**高阶函数**，接受一个函数作为参数，并返回一个新的函数。



### 装饰器的特点

1. **不修改原函数**：装饰器在不改变原函数代码的情况下，为其添加新功能。
2. **语法糖**：使用 `@decorator_name` 的语法可以方便地应用装饰器。
3. **链式调用**：可以同时使用多个装饰器。



### 如何定义装饰器？

1. 定义一个高阶函数，接受一个函数作为参数。
2. 在内部定义一个包装函数，用于扩展原函数的行为。
3. 返回包装函数。

#### 示例：定义一个简单的装饰器

```python
def my_decorator(func):
    def wrapper(*args, **kwargs):
        print("函数执行前")
        result = func(*args, **kwargs)  # 调用原函数
        print("函数执行后")
        return result
    return wrapper

# 使用装饰器
@my_decorator
def say_hello(name):
    print(f"Hello, {name}!")

say_hello("Alice")
# 输出:
# 函数执行前
# Hello, Alice!
# 函数执行后
```



### 带参数的装饰器

如果需要为装饰器传递参数，可以再嵌套一层函数。

#### 示例：带参数的装饰器

```python
def repeat(num_times):
    def decorator(func):
        def wrapper(*args, **kwargs):
            for _ in range(num_times):
                result = func(*args, **kwargs)
            return result
        return wrapper
    return decorator

# 使用带参数的装饰器
@repeat(3)
def greet(name):
    print(f"Hello, {name}!")

greet("Bob")
# 输出:
# Hello, Bob!
# Hello, Bob!
# Hello, Bob!
```



### 类装饰器

装饰器也可以是一个类，通过实现 `__call__` 方法来定义行为。

#### 示例：类装饰器

```python
class MyDecorator:
    def __init__(self, func):
        self.func = func

    def __call__(self, *args, **kwargs):
        print("函数执行前")
        result = self.func(*args, **kwargs)
        print("函数执行后")
        return result

# 使用类装饰器
@MyDecorator
def say_goodbye(name):
    print(f"Goodbye, {name}!")

say_goodbye("Charlie")
# 输出:
# 函数执行前
# Goodbye, Charlie!
# 函数执行后
```









## `functools` 模块

### 作用

`functools` 是 Python 的标准库模块，提供了一些高阶函数工具，用于函数操作和装饰器。

### 常用功能

1. **`functools.reduce`**

   - **作用**：对可迭代对象中的元素进行累积计算。

   - **语法结构：**  `reduce(function, iterable[, initializer])`

   - **示例**：

     ```python
     from functools import reduce
     result = reduce(lambda x, y: x + y, [1, 2, 3, 4])  # 输出 10
     ```

   

2. **`functools.lru_cache`**

   - **作用**：为函数添加缓存，避免重复计算。

   - **示例**：

     - `max_size` 的单位是函数调用结果， 这里缓存的是 `fib(0), ..., fib(127)`
     
     ```python
     from functools import lru_cache
     
     @lru_cache(maxsize=128)
     def fib(n):
         if n < 2:
             return n
         return fib(n - 1) + fib(n - 2)
     
     print(fib(50))  # 快速计算斐波那契数
     ```

   

3. **`functools.partial`**

   - **作用**：固定函数的部分参数，生成一个新函数。

   - **示例**：

     ```python
     from functools import partial
     
     def power(base, exponent):
         return base ** exponent
     
     square = partial(power, exponent=2)
     print(square(3))  # 输出 9
     ```

4. **`functools.wraps`**

   - **作用**：保留被装饰函数的元信息（如 `__name__`）。

   - **示例**：

     ```python
     from functools import wraps
     
     def my_decorator(func):
         @wraps(func)
         def wrapper(*args, **kwargs):
             return func(*args, **kwargs)
         return wrapper
     ```





## 2. **`collections` 模块**

### 作用

`collections` 是 Python 的标准库模块，提供了高效的数据结构，扩展了内置数据类型的功能。

### 常用数据结构

1. **`defaultdict`**

   - **作用**：为字典提供默认值，避免键不存在时的 `KeyError`。

   - **示例**：

     ```python
     from collections import defaultdict
     d = defaultdict(int)  # 默认值为 0
     d["a"] += 1
     print(d["a"])  # 输出 1
     ```

2. **`Counter`**

   - **作用**：统计可迭代对象中元素的频率。

   - **示例**：

     ```python
     from collections import Counter
     
     count = Counter("hello")  # Counter({'h': 1, 'e': 1, 'l': 2, 'o': 1})
     print(count.most_common(1))  # 输出 [('l', 2)]
     ```
   
3. **`deque`**

   - **作用**：双端队列，支持高效的头尾插入和删除。

   - **示例**：

     ```python
     from collections import deque
     
     d = deque([1, 2, 3])
     d.appendleft(0)  # 添加到左侧
     d.pop()  # 删除右侧元素
     print(d)  # 输出 deque([0, 1, 2])
     ```

4. **`namedtuple`**

   - **作用**：创建具有字段名的元组。

   - **示例**：

     ```python
     from collections import namedtuple
     
     Point = namedtuple("Point", ["x", "y"])
     p = Point(1, 2)
     print(p.x, p.y)  # 输出 1 2
     ```
   
5. **`ChainMap`**

   - **作用**：将多个字典合并为一个逻辑字典。

   - **示例**：

     ```python
     from collections import ChainMap
     
     dict1 = {"a": 1, "b": 2}
     dict2 = {"b": 3, "c": 4}
     chain = ChainMap(dict1, dict2)
     print(chain["b"])  # 输出 2（优先使用 dict1 的值）
     ```





## 3. **`__slots__`**

### 作用

`__slots__` 是类的一个特殊属性，用于限制类的实例可以拥有的属性，从而减少内存占用。

### 使用场景

- 当类的实例数量非常多时，使用 `__slots__` 可以显著减少内存消耗。
- 适用于需要高性能和低内存占用的场景。

### 示例

```python
class Point:
    __slots__ = ("x", "y")  # 限制实例只能有 x 和 y 两个属性

    def __init__(self, x, y):
        self.x = x
        self.y = y

p = Point(1, 2)
print(p.x, p.y)  # 输出 1 2

# p.z = 3  # 报错：AttributeError，因为 z 不在 __slots__ 中
```

### 注意事项

1. **内存优化**：使用 `__slots__` 后，实例不再使用 `__dict__` 存储属性，从而节省内存。
2. **灵活性降低**：无法动态添加未在 `__slots__` 中定义的属性。
3. **继承问题**：如果子类没有定义 `__slots__`，则会使用父类的 `__slots__`；如果子类定义了 `__slots__`，则父类的 `__slots__` 不会生效。