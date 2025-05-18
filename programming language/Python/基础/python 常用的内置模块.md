# 常用内置模块

| module     | description                                                  |
| ---------- | ------------------------------------------------------------ |
| `sys`      | python 解释器、环境相关                                      |
| `urllib`   | 用于读取来自网上（服务器）的数据标准库                       |
| `os`       | 提供了访问操作系统和系统服务功能的标准库                     |
| `re`       | 正则库                                                       |
| `decimal`  | 用于进行精确控制运算精度、有效数位和四舍五入操作的十进制运算 |
| `json`     | 用于使用 JSON 序列化和反序列化对象                           |
| `logging`  | 提供了灵活记录事件、错误、警告和调试信息等日志信息的功能     |
| `calendar` | 提供与日期相关的各种函数的标准库                             |
| `time`     | 提供与时间相关的各种函数                                     |





## py OS & file & IO & sys

[OS 参考资料](https://www.runoob.com/python3/python3-os-file-methods.html)

[py file](https://www.runoob.com/python3/python3-file-methods.html)

### 文件操作（虽然放在这不太合适）

**with 上下文管理器** ： 可以自动释放资源，永远保证退出该语句块后，一定可以保证资源文件的关闭

```python
with open(...) as src_file:
    ...
    ...
    ...
```

file类的常用方法：

|      |      |
| ---- | ---- |
|      |      |
|      |      |
|      |      |
|      |      |
|      |      |
|      |      |



### os 模块

python 内置的模块，但是**不同的操作系统的结果不一定相同**

`os.system()` 相当于直接输入命令

- 调用命令或可执行文件

    - `os.system("calc.exe")`
    - `os.system("notepad.exe")`
    - `os.system("1.exe")`

- 操作目录和文件

    | 函数(常用)                           | 功能                       |
    | ------------------------------------ | -------------------------- |
    | `os.getcwd()`                        | 获得当前工作目录           |
    | `os.listdir(path)`                   | 列举目录下的文件和目录     |
    | `os.mkdir(path)`                     | 创建目录                   |
    | `os.mkdirs(path1/path2/.../[,mode])` | 创建多级目录               |
    | `os.rmdir(path)`                     | 删除目录或文件             |
    | `os.removedirs(path1/path2,....)`    | 删除多级目录               |
    | `os.chdir(path)`                     | 将 path 设置为当前工作目录 |

    

### os.path 子库