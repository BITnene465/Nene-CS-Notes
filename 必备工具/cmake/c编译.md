## gcc, g++

```bash
# 产出连接文件
gcc -c demo.c -o demo.o
```

 

```bash
# 产出可执行文件
gcc demo.c -o demo
./demo   # 运行可执行文件
```





## makefile

> 解决多文件编译的 1. 多文件连接  2. 文件前后依赖



一个C/C++文件需要经过预处理(preprocessing),编译(compolation)，汇编(assembly)和链接(linking) 才可以变成可执行文件

![image-20240820195810360](G:/softwares/typora/typora%20%E5%9B%BE%E7%89%87/c%E7%BC%96%E8%AF%91/image-20240820195810360.png)



### 基本规则



**注意：Makefile文件有以下的书写规则：**

1. 如果这个工程没有编译过，那么我们的所有C文件都要编译并被链接。

2. 如果这个工程的某几个C文件被修改，那么我们只编译被修改的C文件，并链接目标程序。

3. 如果这个工程的头文件被改变了，那么我们需要编译引用了这几个头文件的C文件，并链接目标程序。



**makefile命令的基本规则**

```bash
目标： 依赖1  依赖2  ...
[TAB] 命令
```



> https://blog.csdn.net/XieHYBlog/article/details/127034105

















