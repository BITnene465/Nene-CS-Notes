# Linux基础

## 目录结构

`/` 表示根目录

`~` 表示当前所在用户的主目录



>  没有磁盘的概念，只有一个根目录，所有文件系统都作为一个子目录挂在根目录下的某一个子目录下



## 基本命令

### 文件与目录

#### ls

> list,  类似win下的 dir 命令

实例：

```bash
ls -l -a   # -a 表示显示隐藏文件， -l表示详细显示
ls -dl /bin   # 仅查看目录属性
ls -R      # 递归显示子目录的文件
ls directory # 查看指定目录下的文件信息
```



#### cd

>  change directory



#### pwd

> print working directory



#### touch

>用于创建一个空白文件

```bash
touch a.txt
```



#### mv

> 移动文件（目录）， 修改文件名（目录名）

```bash
mv a.txt aa.txt    # 改名

mv /usr/cbu/*  ./  # /usr/cbu中的所有文件移动到当前目录

```



#### mkdir

> make directory

- 要求创建目录的用户在当前目录中（dirname的父目录中）具有写权限，并且dirname不能是当前目录中已有的目录或 文件名称。
- -m 对新建目录设置存取权限。也可以用chmod命令设置。
- -p 可以是一个路径名称。此时若路径中的某些目录尚不存在， 加上此选项后， 系统将自动建立好那些尚不存在的目录，即一次可以建立多个目录。 



#### rm

> remove, 删除一个文件或者目录

-d 删除目录

-i 删除文件

-f 不询问直接删除

-r 递归删除，通常和d结合，删除一个完整目录及其子目录



#### rmdir

> 删除**空目录**

- 注意，一个目录被删除之前必须是空的。rm - r命令可代替 rmdir。
- -p 递归删除目录dirname，当子目录删除后其父目录为空时，也一同被删除。



#### file

> 确定文件类型



#### cat/tac

> 连接并显示指定的一个和多个文件的有关信息

```bash
cat hello.txt  # 显示hello.txt内容

cat hello1.txt hello2.txt > hello3.txt  # 将1，2的内容合并到3中
```



#### more/less



#### head/tail

> 显示文件的头几行/尾几行

`head -num filename`

`tail -num filename`



#### nl

> 以输出行号的方式显示文件



#### ln

> 链接文件





#### echo

`echo`命令用于将文本输出到终端或文件中。

可以将 `echo` 命令的输出重定向到文件，从而创建一个带有内容的文件。

```bash
echo "这是一个文本文件的内容" > message.txt    # 写入（覆盖）
echo "这是一段文本" >> message.txt    # 追加
```



### 字符查找和统计相关

#### grep

> 定位字符信息

`grep keyword filename`



#### wc

> 统计字符信息



#### sort

> 排序字符信息



### 进程操作

#### ps

> 显示当前系统中由该用户运行的进程列表

- -a  显示终端所有进程，包括其他用户的进程 
- -u  查看进程所有者及详细信息
- -x  显示没有控制终端的进程
- -e  显示所有进程
- -l  PPID、PID等详细显示格式





#### kill

> 杀死进程

```bash
kill PID   # 终止进程

kill -9 PID  # 强制终止进程 
```



#### top

> 动态显示当前系统重由该用户运行的进程列表
>
> p.s.  可以下载 htop 命令， 有更加完善的界面显示

```bash
# 使用 top
top 

# 下载并使用 htop
sudo apt-get install htop
htop
```





###  打包/压缩命令





### 网络基础



#### ip

> 主要用于查询主机ip

```bash
# 几个效果一致的ip查询命令
ip addr
ip address
ip address show
```



#### nc

> 用于监听主机端口

```bash
nc -lp portnum   # 最多请求一次
nc -lkp portnum   # 一直请求
```







