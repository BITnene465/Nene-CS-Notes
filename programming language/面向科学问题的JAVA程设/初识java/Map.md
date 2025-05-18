# Java的`Map`类型

-----

## 前言

Java的`java.util`包中包含多种不同类型的`Map`，每种类型都有不同的特性和用途。以下是一些常见的`Map`实现：

1. **HashMap**：
    - 基于哈希表实现，具有快速的查找性能。
    - 不保证元素的顺序，不支持有序遍历。
    - 允许使用`null`作为键和值。
2. **LinkedHashMap**：
    - 继承自`HashMap`，在`HashMap`的基础上添加了维护插入顺序或访问顺序的功能。
    - 保留元素的插入顺序或访问顺序，可以实现有序遍历。
    - 允许使用`null`作为键和值。
3. **TreeMap**：
    - 基于红黑树实现，具有按键的自然顺序或自定义顺序进行排序的能力。
    - 保持键的有序性，支持按键的范围查找。
    - 不允许使用`null`作为键，但可以使用`null`作为值。
4. **Hashtable**：
    - 早期的哈希表实现，线程安全。
    - 不保证元素的顺序。
    - 不允许使用`null`作为键或值。
5. **ConcurrentHashMap**：
    - 线程安全的哈希表实现，用于高并发环境。
    - 分段锁机制，支持多个线程同时读取和写入，提供高性能。
    - 不保证元素的顺序。
    - 不允许使用`null`作为键或值。
6. **WeakHashMap**：
    - 允许使用弱引用作为键，当没有强引用指向键时，键可以被垃圾回收。
    - 主要用于实现缓存和关联对象的场景。
7. **IdentityHashMap**：
    - 使用引用相等（而不是`equals`方法）来比较键。
    - 主要用于需要考虑对象引用完全相等的情况。

这些`Map`实现都实现了`java.util.Map`接口，因此它们具有相似的方法，如`put`、`get`、`remove`等。你可以根据具体的需求选择适合的`Map`类型来存储和操作键值对数据。



## HashMap 类

### 特点和特性

1. **基于哈希表**：`HashMap`内部使用哈希表来存储键值对。哈希表允许快速的插入、查找和删除操作，因此`HashMap`具有高效的性能。
2. **无序性**：`HashMap`不保证元素的顺序。插入顺序和访问顺序都不被保留。
3. **键唯一性**：`HashMap`中的键是唯一的。如果尝试使用已经存在的键来存储新的值，旧的值将被覆盖。
4. **允许null键和null值**：`HashMap`**允许使用**`null`作为键和值。
5. **非线程安全**：`HashMap`不是线程安全的，如果在多线程环境中使用，需要进行额外的同步操作或者考虑使用`ConcurrentHashMap`。

### 常用方法

下面是`HashMap`类中一些常用的方法：

- `put(key, value)`：将键值对添加到`HashMap`中，如果键已经存在，则替换对应的值。
- `get(key)`：根据键获取对应的值，如果键不存在，则返回`null`。
- `remove(key)`：根据键删除键值对，如果键不存在，则不执行任何操作。
- `containsKey(key)`：检查`HashMap`中是否包含指定的键。
- `containsValue(value)`：检查`HashMap`中是否包含指定的值。
- `size()`：返回`HashMap`中键值对的数量。
- `isEmpty()`：检查`HashMap`是否为空。
- `keySet()`：返回包含所有键的集合。
- `values()`：返回包含所有值的集合。
- `entrySet()`：返回包含所有键值对的集合。

### 使用示例

```java
javaCopy codeimport java.util.HashMap;
import java.util.Map;

public class HashMapExample {
    public static void main(String[] args) {
        // 创建一个HashMap对象
        Map<String, Integer> hashMap = new HashMap<>();

        // 添加键值对
        hashMap.put("Alice", 25);
        hashMap.put("Bob", 30);
        hashMap.put("Charlie", 28);

        // 获取值
        int aliceAge = hashMap.get("Alice"); // 25

        // 检查是否包含键
        boolean containsKey = hashMap.containsKey("David"); // false

        // 遍历键值对
        for (Map.Entry<String, Integer> entry : hashMap.entrySet()) {
            String name = entry.getKey();
            int age = entry.getValue();
            System.out.println(name + ": " + age);
        }
    }
}
```

总之，`HashMap`是一个常用的、高性能的键值对存储容器，适用于许多场景。但需要注意的是，由于它不是线程安全的，因此在多线程环境中使用时需要额外的注意和同步措施。如果需要线程安全的哈希表，可以考虑使用`ConcurrentHashMap`。



## LinkedHashMap 类

`LinkedHashMap`是Java中的一个`Map`实现，它**继承**自`HashMap`，在`HashMap`的基础上添加了维护插入顺序或访问顺序的功能。以下是对`LinkedHashMap`的详细介绍：

### 特点和特性：

1. **保持插入顺序或访问顺序**：`LinkedHashMap`具有一个特性，可以根据元素的插入顺序或访问顺序（最近访问的元素排在前面）来保持元素的顺序。这使得你可以按照元素被插入或访问的顺序来遍历`LinkedHashMap`。

2. **基于哈希表和双向链表**：`LinkedHashMap`内部使用哈希表来存储键值对，并使用双向链表来维护元素的顺序。这意味着元素的插入和删除操作是高效的，同时可以按照顺序遍历元素。

3. **无序性**：虽然`LinkedHashMap`可以保持插入顺序或访问顺序，但它本身并不保证元素的全局有序性。即使使用插入顺序或访问顺序遍历，元素之间的相对顺序也不会改变。

4. **键唯一性**：`LinkedHashMap`中的键仍然是唯一的。如果尝试使用已经存在的键来存储新的值，旧的值将被覆盖。

5. **允许null键和null值**：与`HashMap`一样，`LinkedHashMap`也允许使用`null`作为键和值。

6. **非线程安全**：`LinkedHashMap`不是线程安全的，如果在多线程环境中使用，需要进行额外的同步操作或者考虑使用`ConcurrentHashMap`。

### 常用方法：

`LinkedHashMap`继承了`HashMap`的方法，因此它具有与`HashMap`相似的方法，如`put`、`get`、`remove`等。此外，它还有一些与顺序有关的方法：

- `put(key, value)`：将键值对添加到`LinkedHashMap`中，如果键已经存在，则替换对应的值。
- `get(key)`：根据键获取对应的值，如果键不存在，则返回`null`。
- `remove(key)`：根据键删除键值对，如果键不存在，则不执行任何操作。
- `containsKey(key)`：检查`LinkedHashMap`中是否包含指定的键。
- `containsValue(value)`：检查`LinkedHashMap`中是否包含指定的值。
- `size()`：返回`LinkedHashMap`中键值对的数量。
- `isEmpty()`：检查`LinkedHashMap`是否为空。
- `keySet()`：返回包含所有键的集合。
- `values()`：返回包含所有值的集合。
- `entrySet()`：返回包含所有键值对的集合。

### 使用示例：

```java
import java.util.LinkedHashMap;
import java.util.Map;

public class LinkedHashMapExample {
    public static void main(String[] args) {
        // 创建一个LinkedHashMap对象，保持插入顺序
        Map<String, Integer> linkedHashMap = new LinkedHashMap<>();

        // 添加键值对
        linkedHashMap.put("Alice", 25);
        linkedHashMap.put("Bob", 30);
        linkedHashMap.put("Charlie", 28);

        // 遍历按插入顺序保持的键值对
        for (Map.Entry<String, Integer> entry : linkedHashMap.entrySet()) {
            String name = entry.getKey();
            int age = entry.getValue();
            System.out.println(name + ": " + age);
        }

        // 访问顺序保持（最近访问的元素排在前面）
        linkedHashMap.get("Bob"); // Bob的键值对被移到最后

        // 再次遍历按访问顺序保持的键值对
        for (Map.Entry<String, Integer> entry : linkedHashMap.entrySet()) {
            String name = entry.getKey();
            int age = entry.getValue();
            System.out.println(name + ": " + age);
        }
    }
}
```

总之，`LinkedHashMap`是一个常用的`Map`实现，它在**保持插入顺序或访问顺序方面提供了更多的控制**。这对于某些特定的应用场景非常有用，如LRU（最近最少使用）缓存。但需要注意的是，它仍然**不是线程安全**的，如果需要线程安全的哈希表，可以考虑使用`ConcurrentHashMap`。



## TreeMap 类

`TreeMap` 是 Java 中的一个有序映射（Map）实现，它基于**红黑树（Red-Black Tree）**数据结构来存储键值对。`TreeMap` 具有以下特性和特点：

### 有序性：

1. **按键的自然顺序或自定义顺序排序**：`TreeMap`会根据键的自然顺序（如果键实现了`Comparable`接口）或者根据自定义的`Comparator`来对键进行排序。这使得在`TreeMap`中的键值对能够按照特定顺序进行存储和遍历。

2. **有序遍历**：通过`TreeMap`的迭代器，你可以按照键的顺序遍历键值对。这对于需要按照键的顺序进行操作的场景非常有用。

### 数据结构：

3. **基于红黑树**：`TreeMap`内部使用红黑树来存储键值对。红黑树是一种自平衡的二叉查找树，保证了对树的操作的平均时间复杂度为O(log N)。这使得`TreeMap`在插入、删除和查找操作上有较好的性能表现。

4. **键唯一性**：`TreeMap`中的键是唯一的，如果尝试使用已经存在的键来存储新的值，旧的值将被替换。

### 其他特点：

5. **不允许null键（但允许null值）**：`TreeMap`不允许使用null作为键，因为红黑树的特性要求键不能为null。但它允许使用null作为值。

6. **非线程安全**：`TreeMap`不是线程安全的，如果在多线程环境中使用，需要进行额外的同步操作或者考虑使用`ConcurrentSkipListMap`。

### 常用方法：

`TreeMap`继承了`SortedMap`接口和`NavigableMap`接口的方法，除此之外，它还有一些自己的方法。以下是一些常用方法：

- `put(key, value)`：将键值对添加到`TreeMap`中，如果键已经存在，则替换对应的值。
- `get(key)`：根据键获取对应的值，如果键不存在，则返回`null`。
- `remove(key)`：根据键删除键值对，如果键不存在，则不执行任何操作。
- `containsKey(key)`：检查`TreeMap`中是否包含指定的键。
- `containsValue(value)`：检查`TreeMap`中是否包含指定的值。
- `size()`：返回`TreeMap`中键值对的数量。
- `isEmpty()`：检查`TreeMap`是否为空。
- `firstKey()`：返回第一个（最小的）键。
- `lastKey()`：返回最后一个（最大的）键。
- `lowerKey(key)`：返回严格小于给定键的最大键。
- `higherKey(key)`：返回严格大于给定键的最小键。



### 使用示例：

以下是一个使用`TreeMap`的简单示例：

```java
import java.util.TreeMap;
import java.util.Map;

public class TreeMapExample {
    public static void main(String[] args) {
        // 创建一个TreeMap对象，按键的自然顺序排序
        TreeMap<Integer, String> treeMap = new TreeMap<>();

        // 添加键值对
        treeMap.put(3, "Alice");
        treeMap.put(1, "Bob");
        treeMap.put(2, "Charlie");

        // 遍历按键的顺序保持的键值对
        for (Map.Entry<Integer, String> entry : treeMap.entrySet()) {
            int key = entry.getKey();
            String name = entry.getValue();
            System.out.println(key + ": " + name);
        }

        // 获取最小的键
        int minKey = treeMap.firstKey(); // 1
        // 获取最大的键
        int maxKey = treeMap.lastKey(); // 3
    }
}
```

总之，`TreeMap`是一个有序的`Map`实现，**适用于需要按照键的顺序进行操作的场景**。它的性能在大多数情况下非常好，但需要注意，由于不是线程安全的，如果需要线程安全的有序映射，可以考虑使用`ConcurrentSkipListMap`。