# std::string



## 1. `std::string` 的基本操作

### 初始化

```cpp
#include <string>
using namespace std;

string s1 = "Hello"; // 直接初始化
string s2("World");  // 构造函数初始化
string s3(5, 'a');   // 初始化 5 个 'a'，结果为 "aaaaa"
```

### 访问字符
```cpp
string s = "Hello";
char c = s[0];       // 访问第一个字符 'H'
char c2 = s.at(1);   // 访问第二个字符 'e'（带边界检查）
```

### 获取字符串长度
```cpp
int len = s.length(); // 或者 s.size()
```

### 字符串拼接
```cpp
string s1 = "Hello";
string s2 = "World";
string s3 = s1 + " " + s2; // "Hello World"
s1.append(s2);             // s1 变为 "HelloWorld"
```

### 子字符串
```cpp
string s = "Hello World";
string sub = s.substr(6, 5); // 从索引 6 开始，取 5 个字符，结果为 "World"
```

### 查找子字符串
```cpp
string s = "Hello World";
size_t pos = s.find("World"); // 返回子字符串的起始位置，结果为 6
if (pos != string::npos) {
    cout << "Found at position: " << pos << endl;
}
```

### 替换子字符串
```cpp
string s = "Hello World";
s.replace(6, 5, "C++"); // 从索引 6 开始，替换 5 个字符，结果为 "Hello C++"
```

### 插入字符串
```cpp
string s = "Hello World";
s.insert(5, " Beautiful"); // 在索引 5 处插入，结果为 "Hello Beautiful World"
```

### 删除字符
```cpp
string s = "Hello World";
s.erase(5, 6); // 从索引 5 开始，删除 6 个字符，结果为 "Hello"
```

### 比较字符串
```cpp
string s1 = "Hello";
string s2 = "World";
if (s1 == s2) {
    cout << "Strings are equal" << endl;
} else {
    cout << "Strings are not equal" << endl;
}
```





## 2. `std::string` 的常用算法

### 排序字符串
```cpp
#include <algorithm>
#include <string>

string s = "hello";
sort(s.begin(), s.end()); // 升序排序，结果为 "ehllo"
sort(s.begin(), s.end(), greater<char>()); // 降序排序，结果为 "ollhe"
```

### 反转字符串
```cpp
#include <algorithm>
#include <string>

string s = "hello";
reverse(s.begin(), s.end()); // 结果为 "olleh"
```

### 查找字符
```cpp
#include <algorithm>
#include <string>

string s = "hello";
auto it = find(s.begin(), s.end(), 'e'); // 查找字符 'e'
if (it != s.end()) {
    cout << "Found at position: " << (it - s.begin()) << endl;
}
```

### 统计字符出现次数
```cpp
#include <algorithm>
#include <string>

string s = "hello";
int count = count(s.begin(), s.end(), 'l'); // 统计 'l' 出现的次数，结果为 2
```

### 删除特定字符
```cpp
#include <algorithm>
#include <string>

string s = "hello";
s.erase(remove(s.begin(), s.end(), 'l'), s.end()); // 删除所有 'l'，结果为 "heo"
```

### 转换大小写
```cpp
#include <algorithm>
#include <string>

string s = "Hello";
transform(s.begin(), s.end(), s.begin(), ::toupper); // 转换为大写，结果为 "HELLO"
transform(s.begin(), s.end(), s.begin(), ::tolower); // 转换为小写，结果为 "hello"
```





## 3. 字符串与数值的转换

### 字符串转整数
```cpp
#include <string>

string s = "123";
int num = stoi(s); // 字符串转整数
long long big_num = stoll(s); // 字符串转长整数
```

### 字符串转浮点数
```cpp
#include <string>

string s = "3.14";
float f = stof(s); // 字符串转浮点数
double d = stod(s); // 字符串转双精度浮点数
```

### 数值转字符串
```cpp
#include <string>

int num = 123;
string s = to_string(num); // 整数转字符串
double d = 3.14;
string s2 = to_string(d); // 浮点数转字符串
```





## 4. 字符串分割

C++ 标准库没有直接提供字符串分割函数，但可以通过以下方法实现：

### 使用 `std::stringstream`
```cpp
#include <sstream>
#include <vector>
#include <string>

vector<string> split(const string& s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

int main() {
    string s = "Hello,World,C++";
    vector<string> tokens = split(s, ',');
    for (const string& t : tokens) {
        cout << t << endl;
    }
    return 0;
}
```





## 5. 字符串匹配算法

### KMP 算法
KMP 算法用于高效查找子字符串。

```cpp
#include <vector>
#include <string>

vector<int> computeLPS(const string& pattern) {
    int n = pattern.length();
    vector<int> lps(n, 0);
    for (int i = 1, len = 0; i < n; ) {
        if (pattern[i] == pattern[len]) {
            lps[i++] = ++len;
        } else if (len) {
            len = lps[len - 1];
        } else {
            lps[i++] = 0;
        }
    }
    return lps;
}

int KMP(const string& text, const string& pattern) {
    int m = text.length(), n = pattern.length();
    vector<int> lps = computeLPS(pattern);
    for (int i = 0, j = 0; i < m; ) {
        if (text[i] == pattern[j]) {
            i++, j++;
            if (j == n) {
                return i - j; // 匹配成功，返回起始位置
            }
        } else if (j) {
            j = lps[j - 1];
        } else {
            i++;
        }
    }
    return -1; // 未找到
}

int main() {
    string text = "ABABDABACDABABCABAB";
    string pattern = "ABABCABAB";
    int pos = KMP(text, pattern);
    if (pos != -1) {
        cout << "Pattern found at position: " << pos << endl;
    } else {
        cout << "Pattern not found" << endl;
    }
    return 0;
}
```





## 6. 总结

| 操作             | 方法或函数                      | 示例                                                   |
| ---------------- | ------------------------------- | ------------------------------------------------------ |
| 初始化           | `string s = "Hello";`           | `string s("World");`                                   |
| 访问字符         | `s[index]` 或 `s.at(index)`     | `char c = s[0];`                                       |
| 获取长度         | `s.length()` 或 `s.size()`      | `int len = s.length();`                                |
| 拼接字符串       | `+` 或 `append`                 | `string s3 = s1 + s2;`                                 |
| 子字符串         | `substr(pos, len)`              | `string sub = s.substr(6, 5);`                         |
| 查找子字符串     | `find(sub)`                     | `size_t pos = s.find("World");`                        |
| 替换子字符串     | `replace(pos, len, new_str)`    | `s.replace(6, 5, "C++");`                              |
| 插入字符串       | `insert(pos, str)`              | `s.insert(5, " Beautiful");`                           |
| 删除字符         | `erase(pos, len)`               | `s.erase(5, 6);`                                       |
| 比较字符串       | `==`, `!=`, `compare`           | `if (s1 == s2) { ... }`                                |
| 排序字符串       | `sort(s.begin(), s.end())`      | `sort(s.begin(), s.end());`                            |
| 反转字符串       | `reverse(s.begin(), s.end())`   | `reverse(s.begin(), s.end());`                         |
| 统计字符出现次数 | `count(s.begin(), s.end(), ch)` | `int cnt = count(s.begin(), s.end(), 'l');`            |
| 转换大小写       | `transform` + `toupper/tolower` | `transform(s.begin(), s.end(), s.begin(), ::toupper);` |
| 字符串分割       | `stringstream` + `getline`      | `vector<string> tokens = split(s, ',');`               |
