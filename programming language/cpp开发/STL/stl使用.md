# STL 使用



## STL 容器 -- 算法题要求

### 1. `map` 和 `unordered_map`

#### 特点

- **`map`**：基于红黑树，键值对有序，查找、插入、删除时间复杂度为 **O(log n)**。
- **`unordered_map`**：基于哈希表，键值对无序，查找、插入、删除时间复杂度为 **O(1)**。

#### 常用操作

```cpp
#include <map>
#include <unordered_map>

// 初始化
std::map<std::string, std::string> m1 = {
    {"key1", "value1"},
    {"key2", "value2"}
};
std::unordered_map<std::string, std::string> m2 = {
    {"key1", "value1"},
    {"key2", "value2"}
};

// 插入元素
m1["key3"] = "value3"; // map
m2.insert({"key3", "value3"}); // unordered_map

// 访问元素
std::cout << m1.at("key1") << std::endl; // 如果键不存在，抛出异常
std::cout << m2["key2"] << std::endl; // 如果键不存在，会插入默认值

// 检查元素是否存在
if (m1.find("key1") != m1.end()) {
    std::cout << "key1 exists" << std::endl;
}

// 删除元素
m1.erase("key1"); // map
m2.erase("key2"); // unordered_map

// 遍历
for (const auto& kv : m1) {
    std::cout << kv.first << ": " << kv.second << std::endl;
}
```



### 2. `vector`

#### 特点
- 动态数组，支持随机访问，尾部插入和删除的时间复杂度为 **O(1)**。

#### 常用操作
```cpp
#include <vector>

// 初始化
std::vector<int> v = {1, 2, 3, 4, 5};

// 访问元素
std::cout << v[0] << std::endl; // 1
std::cout << v.at(1) << std::endl; // 2

// 添加元素
v.push_back(6); // {1, 2, 3, 4, 5, 6}

// 删除元素
v.pop_back(); // {1, 2, 3, 4, 5}

// 插入元素
v.insert(v.begin() + 2, 10); // {1, 2, 10, 3, 4, 5}

// 删除元素
v.erase(v.begin() + 2); // {1, 2, 3, 4, 5}

// 遍历
for (int i : v) {
    std::cout << i << " ";
}

// 大小
std::cout << "Size: " << v.size() << std::endl;

// 清空
v.clear();
```



### 3. `set` 和 `unordered_set`

#### 特点

- **`set`**：基于红黑树，元素有序，查找、插入、删除时间复杂度为 **O(log n)**。
- **`unordered_set`**：基于哈希表，元素无序，查找、插入、删除时间复杂度为 **O(1)**。

#### 常用操作
```cpp
#include <set>
#include <unordered_set>

// 初始化
std::set<int> s1 = {1, 2, 3};
std::unordered_set<int> s2 = {1, 2, 3};

// 插入元素
s1.insert(4); // set
s2.insert(4); // unordered_set

// 查找元素
if (s1.find(2) != s1.end()) {
    std::cout << "2 exists" << std::endl;
}

// 删除元素
s1.erase(2); // set
s2.erase(2); // unordered_set

// 遍历
for (int i : s1) {
    std::cout << i << " ";
}
```



### 4. `queue`

#### 特点
- 先进先出（FIFO）的数据结构。

#### 常用操作
```cpp
#include <queue>

// 初始化
std::queue<int> q;

// 添加元素
q.push(1);
q.push(2);
q.push(3);

// 访问队首元素
std::cout << q.front() << std::endl; // 1

// 删除队首元素
q.pop(); // {2, 3}

// 检查是否为空
if (!q.empty()) {
    std::cout << "Queue is not empty" << std::endl;
}
```



### 5. `stack`

#### 特点
- 后进先出（LIFO）的数据结构。

#### 常用操作
```cpp
#include <stack>

// 初始化
std::stack<int> s;

// 添加元素
s.push(1);
s.push(2);
s.push(3);

// 访问栈顶元素
std::cout << s.top() << std::endl; // 3

// 删除栈顶元素
s.pop(); // {1, 2}

// 检查是否为空
if (!s.empty()) {
    std::cout << "Stack is not empty" << std::endl;
}
```



### 6. `priority_queue`

#### 特点

- 优先队列（堆），默认是大顶堆。

#### 常用操作

#### 默认大顶堆

```cpp
#include <queue>

// 初始化（默认大顶堆）
std::priority_queue<int> pq;

// 添加元素
pq.push(3);
pq.push(1);
pq.push(4);

// 访问堆顶元素
std::cout << pq.top() << std::endl; // 4

// 删除堆顶元素
pq.pop(); // {3, 1}
```



#### 自定义小顶堆

通过传递比较函数 `std::greater<T>` 来实现小顶堆。

```cpp
#include <queue>

// 小顶堆
std::priority_queue<int, std::vector<int>, std::greater<int>> min_pq;

// 添加元素
min_pq.push(3);
min_pq.push(1);
min_pq.push(4);

// 访问堆顶元素
std::cout << min_pq.top() << std::endl; // 1

// 删除堆顶元素
min_pq.pop(); // {3, 4}
```



#### 自定义比较函数

如果需要更复杂的比较逻辑，可以自定义比较函数。

```cpp
#include <queue>

// 自定义比较函数（按元素的绝对值从小到大排序）
struct Compare {
    bool operator()(int a, int b) {
        return abs(a) > abs(b); // 小顶堆
    }
};

// 使用自定义比较函数
std::priority_queue<int, std::vector<int>, Compare> custom_pq;

// 添加元素
custom_pq.push(-3);
custom_pq.push(1);
custom_pq.push(-4);

// 访问堆顶元素
std::cout << custom_pq.top() << std::endl; // 1（绝对值最小）

// 删除堆顶元素
custom_pq.pop(); // {-3, -4}
```









###  7. 常用算法

STL 提供了丰富的算法函数。

#### 1. 排序 (`std::sort`)

- 对容器中的元素进行排序
- 默认是升序排序，可以通过自定义比较函数实现降序或其他排序规则

```cpp
#include <algorithm>
#include <vector>

std::vector<int> v = {5, 3, 1, 4, 2};

// 默认升序排序
std::sort(v.begin(), v.end()); // {1, 2, 3, 4, 5}

// 降序排序
std::sort(v.begin(), v.end(), std::greater<int>()); // {5, 4, 3, 2, 1}

// 自定义排序规则（按绝对值从小到大排序）
std::sort(v.begin(), v.end(), [](int a, int b) {
    return abs(a) < abs(b);
});
```

#### 2. 查找 (`std::find`)

- 在容器中查找指定元素，返回指向该元素的迭代器
- 如果未找到，返回 `end()` 迭代器

```cpp
#include <algorithm>
#include <vector>

std::vector<int> v = {1, 2, 3, 4, 5};

auto it = std::find(v.begin(), v.end(), 3);
if (it != v.end()) {
    std::cout << "Found: " << *it << std::endl; // 输出: Found: 3
} else {
    std::cout << "Not found" << std::endl;
}
```



#### 3. 反转 (`std::reverse`)

- 反转容器中的元素顺序。

```cpp
#include <algorithm>
#include <vector>

std::vector<int> v = {1, 2, 3, 4, 5};

std::reverse(v.begin(), v.end()); // {5, 4, 3, 2, 1}
```



#### 4. 去重 (`std::unique`)

- 去除容器中相邻的重复元素。
- 需要先对容器排序。

```cpp
#include <algorithm>
#include <vector>

std::vector<int> v = {1, 2, 2, 3, 3, 4, 5};

// 先排序
std::sort(v.begin(), v.end()); // {1, 2, 2, 3, 3, 4, 5}

// 去重
auto last = std::unique(v.begin(), v.end()); // {1, 2, 3, 4, 5, x, x}

// 删除多余元素
v.erase(last, v.end()); // {1, 2, 3, 4, 5}
```



#### 5. 累加 (`std::accumulate`)

- 计算容器中元素的累加和。
- 可以指定初始值。

```cpp
#include <numeric>
#include <vector>

std::vector<int> v = {1, 2, 3, 4, 5};

int sum = std::accumulate(v.begin(), v.end(), 0); // 0 是初始值
std::cout << "Sum: " << sum << std::endl; // 输出: Sum: 15
```





#### 6. 查找最大/最小元素 (`std::max_element`, `std::min_element`)

- 返回指向容器中最大或最小元素的迭代器。

```cpp
#include <algorithm>
#include <vector>

std::vector<int> v = {1, 2, 3, 4, 5};

auto max_it = std::max_element(v.begin(), v.end());
auto min_it = std::min_element(v.begin(), v.end());

std::cout << "Max: " << *max_it << std::endl; // 输出: Max: 5
std::cout << "Min: " << *min_it << std::endl; // 输出: Min: 1
```



#### 7. 填充 (`std::fill`)

- 将容器中的元素填充为指定值。

```cpp
#include <algorithm>
#include <vector>

std::vector<int> v(5); // {0, 0, 0, 0, 0}

std::fill(v.begin(), v.end(), 10); // {10, 10, 10, 10, 10}
```



#### 8. 二分查找 (`std::binary_search`)

- 在已排序的容器中进行二分查找。
- 返回布尔值，表示是否找到目标元素。

```cpp
#include <algorithm>
#include <vector>

std::vector<int> v = {1, 2, 3, 4, 5};

bool found = std::binary_search(v.begin(), v.end(), 3);
if (found) {
    std::cout << "Found" << std::endl;
} else {
    std::cout << "Not found" << std::endl;
}
```



#### 算法模板总结

| 算法                 | 功能描述     | 示例                                                      |
| -------------------- | ------------ | --------------------------------------------------------- |
| `std::sort`          | 排序         | `std::sort(v.begin(), v.end(), std::greater<int>());`     |
| `std::find`          | 查找元素     | `auto it = std::find(v.begin(), v.end(), 3);`             |
| `std::reverse`       | 反转容器     | `std::reverse(v.begin(), v.end());`                       |
| `std::unique`        | 去重         | `auto last = std::unique(v.begin(), v.end());`            |
| `std::accumulate`    | 累加         | `int sum = std::accumulate(v.begin(), v.end(), 0);`       |
| `std::max_element`   | 查找最大元素 | `auto max_it = std::max_element(v.begin(), v.end());`     |
| `std::fill`          | 填充容器     | `std::fill(v.begin(), v.end(), 10);`                      |
| `std::binary_search` | 二分查找     | `bool found = std::binary_search(v.begin(), v.end(), 3);` |



### 总结

| 容器             | 特点                   | 常用操作                          |
| ---------------- | ---------------------- | --------------------------------- |
| `map`            | 有序键值对，红黑树实现 | `insert`, `find`, `erase`, `at`   |
| `unordered_map`  | 无序键值对，哈希表实现 | `insert`, `find`, `erase`, `[]`   |
| `vector`         | 动态数组，支持随机访问 | `push_back`, `pop_back`, `insert` |
| `set`            | 有序集合，红黑树实现   | `insert`, `find`, `erase`         |
| `unordered_set`  | 无序集合，哈希表实现   | `insert`, `find`, `erase`         |
| `queue`          | 先进先出（FIFO）       | `push`, `pop`, `front`            |
| `stack`          | 后进先出（LIFO）       | `push`, `pop`, `top`              |
| `priority_queue` | 优先队列（堆）         | `push`, `pop`, `top`              |
