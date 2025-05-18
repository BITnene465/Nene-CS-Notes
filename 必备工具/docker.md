# docker

## 安装 docker desktop

### 安装流程

官网下载安装器

安装完手动打开 docker desktop

注册/登录 （可跳过）

终端中测试 `docker --version` 查看是否安装成功 （可能要加 环境变量）





### 一些安装报错

> [Windows10安装Docker Desktop - WSL update failed](https://blog.csdn.net/wochunyang/article/details/138225109)



### images 的存储位置

docker 在 windows 上运行也是建立在 wsl 之上

> [Docker-Docker镜像存储位置(Windows/Mac/Linux)_win11中docker仓库的保存地址-CSDN博客](https://blog.csdn.net/qq_24256877/article/details/123033703)

**`host.docker.internal`** 来表示宿主机；   `localhost` 或 `127.0.0.1` 表示本容器



## docker 容器

### 容器与主机的互相访问

> 待学习： [【docker知识】从容器中如何访问到宿主机_docker容器访问宿主机-CSDN博客](https://blog.csdn.net/gongdiwudu/article/details/128888497)



### docker 容器之间互相访问

> 待学习:  [Docker容器互访三种方式 - 三只松鼠 - 博客园](https://www.cnblogs.com/shenh/p/9714547.html)







## 使用

### 查看容器的启动参数

`docker ps -a --no-truc`



`docker inspect`



## 指令： 容器控制

> 一般而言， 可以用 container name 的地方都可以使用 container ID

**启动容器：**







`docker stats <container_name>`   监测container的资源使用情况，如果没有 container_name 则监视所有 container 的资源使用情况

列举所有的容器： `docker ps -a`  没有 -a 只会输出正在运行的容器

停止容器： `docker stop <容器 ID>` 

重启容器： `docker restart <容器 ID>` 

删除容器： `docker rm <容器 ID>` 

启动容器内控制台: `docker exec -it <容器 ID> /bin/bash`





