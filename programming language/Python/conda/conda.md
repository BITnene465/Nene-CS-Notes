# conda

## 安装

### windows

安装 anaconda 的同时会自动安装 conda，安装完成需要配置**环境变量**

```bash
G:\Anaconda3 

G:\Anaconda3\Scripts 

G:\Anaconda3\Library\mingw-w64\bin

G:\Anaconda3\Library\usr\bin 

G:\Anaconda3\Library\bin
```

再运行 `conda init`  初始化conda命令在各个终端的使用

> 参考 [Windows下的Anaconda详细安装教程_windows安装anaconda-CSDN博客](https://blog.csdn.net/weixin_52677672/article/details/133632708)



### ubuntu

wget 下载安装脚本（**各个版本可以到官网上查到**）

`wget -c 'https://repo.anaconda.com/archive/Anaconda3-2024.10-1-Linux-x86_64.sh' -P ~/Downloads`

然后按照指示运行脚本即可



> 参考 [超详细Ubuntu安装Anaconda步骤+Anconda常用命令_ubuntu 安装anaconda-CSDN博客](https://blog.csdn.net/KRISNAT/article/details/124041869)



## 常规

### 配置指令

也可以直接修改 `~/.bashrc`

```bash
# 更换conda源: 在Anaconda Prompt中先后执行下面三个命令即可
conda config --add channels https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/free/
conda config --add channels https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/main/
conda config --set show_channel_urls yes
```

`conda info`  可以展示当前conda的各种信息，可以找到对应路径去更改和手动管理



### 环境（env）操作

