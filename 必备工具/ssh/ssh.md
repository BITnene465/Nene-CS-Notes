# SSH

## SSH的安装与配置

### 安装

Linux系统自带ssh，如果没有可以自行安装openssh

```bash
# 安装OpenSSH服务器
sudo apt-get install openssh-server    # Ubuntu/Debian
sudo yum install openssh-server        # CentOS/RHEL
```



### 配置SSH服务

```bash
# 编辑sshd_config文件
sudo nano /etc/ssh/sshd_config
```



### 允许SSH通过防火墙

大部分时候都是允许的，如果不允许就使用以下命令:(以Ubuntu举例，其防火墙为 ufw, Uncomplicated firewall)

```bash
sudo ufw status   # 检查防火墙状态
sudo ufw allow OpenSSH  # 允许SSH通过防火墙
sudo ufw enable  # 启用防火墙（如果没有）
sudo ufw status # 用于验证SSH是否可以通过防火墙
```



### 测试并连接ssh

```bash
ip addr show | grep inet  # 这将会获取所有网络接口的IP地址，用于找到服务器地址

ssh username@addr    # 在客户机上使用该命令连接Linux服务机
```

如果是第一次连接，会需要**输入密码**



## 一些常用命令

服务器

```bash
sudo systemctl status ssh   # 检查SSH服务器状态

# 启动ssh(任选一个)
sudo service ssh start  
sudo systemctl start sshd
sudo systemctl start ssh  # 安装 openssh服务器的情况下

# windows下启动关闭ssh服务
net start sshd
net stop sshd

```



客户机

```bash
# 1. 密码连接
ssh username@addr   # 连接，然后输密码
# 2. 首次连接后会得到秘钥，之后可以使用秘钥进行连接（ ###存疑 ）
ssh-keygen -t rsa   # -t表示类型选项，此处使用rsa加密算法
ssh-copy-id username@addr  # 将公钥复制到远程主机，从此不再需要登录密码


exit  # 用于退出ssh连接的linux服务器
```



[OpenSSH for Windows 中基于密钥的身份验证 | Microsoft Learn](https://learn.microsoft.com/zh-cn/windows-server/administration/openssh/openssh_keymanagement)





## windows下使用ssh

[如何在Windows电脑上启动并配置SSH服务_windows开启ssh服务-CSDN博客](https://blog.csdn.net/qq_44154915/article/details/139297015)



## 一些报错的解决

1. **connect： network is unreachable**

    [史上最详细的linux关于connect: network is unreachable 问题的解决方案 - 星朝 - 博客园 (cnblogs.com)](https://www.cnblogs.com/jpfss/p/10918110.html)

2. 




