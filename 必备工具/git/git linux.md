# linux Git

## 配置

### 安装

```bash
# 以Ubuntu举例
sudo apt-get install git

git --version    # 检查安装，查看版本
```





### 用户设置

```bash
git config --global user.name "your name"
git config --global user.email "your email"
git config --list   # 本机全部设置
```



### 设置https代理

> 用于clone，fork等操作

```bash
# 使用全局端口代理
git config --global http.proxy http://127.0.0.1:1080
git config --global https.proxy http://127.0.0.1:1080

# 去除代理
git config --global --unset http.proxy
git config --global --unset https.proxy

```



```bash
# 单次clone使用代理
git clone -c https.proxy="127.0.0.1:1081" https://github.com/jonny-xhl/FastReport.git
```

**注：clash的默认端口为7890**



> 参考资料： [为 git clone github 设置 HTTP 和 SSH 代理 (niluan304.github.io)](https://niluan304.github.io/p/为-git-clone-github-设置-http-和-ssh-代理/)



### 配置Github.ssh

```bash
# 以Ubuntu举例
ssh-keygen -C "your email" -t rsa   # 生成秘钥

cd ~/.ssh
cat id_rsa.pub
# 然后复制rsa秘钥到github即可
```

<img src="git linux.assets/image-20240820101047791.png" alt="image-20240820101047791" style="zoom: 33%;" />



**检查连接**

```bash
# 可以使用以下命令来检查连接状况
ssh -T git@github.com
```

![image-20240820101516204](git linux.assets/image-20240820101516204.png)





