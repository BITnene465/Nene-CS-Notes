# docker

## Introduction

### 应用的集装箱

Docker 是一个**开放平台，用于开发、交付和运行应用程序**。它的核心设计哲学是实现**“构建一次，到处运行”（Build, Ship, Run Any App, Anywhere）**。

其设计思路源于对传统软件部署痛点的深刻理解：

1. **环境一致性困境**: 软件在开发、测试和生产环境中经常因为环境差异（操作系统版本、库文件等）而出现“在我机器上能跑，到你那儿就崩了”的问题。Docker 的目标是彻底解决这个问题。
2. **资源利用率低下**: 传统虚拟机 (VM) 虽然提供了隔离，但每个 VM 都需要完整的操作系统，导致资源消耗大、启动慢。

为了解决这些问题，Docker 引入了**容器化**的概念。

**设计哲学和思路：**

- **封装与隔离：** Docker 借鉴了**集装箱**的理念。它将应用程序及其所有依赖（代码、运行时环境、系统工具、库等）打包成一个**独立的、可移植的“容器”**。这个容器与底层操作系统隔离，与其他容器也相互隔离。
- **轻量与高效：** 与虚拟机不同，Docker 容器不包含完整的操作系统。它们**共享宿主机的操作系统内核**，这使得容器非常轻量级，启动速度极快，并能显著提高服务器的资源利用率。
- **一致性与可重复性：** 一旦应用程序被打包成 Docker 镜像，无论在开发者的本地机器、测试服务器还是生产环境，这个镜像都能以完全相同的方式运行。这极大地简化了部署流程，消除了“环境差异”带来的问题。
- **标准化与自动化：** Docker 提供了一套标准化的工具和流程（如 Dockerfile），使得应用程序的构建、打包、分发和运行变得简单、可自动化，促进了持续集成/持续部署 (CI/CD) 的实践。



### Inspects

#### developer

对于**工程师**而言，Docker 是实现软件开发、交付和运维一致性的强大工具。它通过将应用程序及其所有依赖打包成独立的、可移植的“容器”，彻底解决了“在我机器上能跑，到你那儿就崩了”的环境一致性问题。无论是本地开发环境隔离，还是在持续集成/持续部署 (CI/CD) 流程中确保生产环境的可靠部署，亦或是复杂微服务架构中的独立部署与管理，Docker 都极大地简化了工作流程，提高了开发效率和部署可靠性，让工程师能专注于代码本身而非环境配置的烦恼。

#### ai scientist

对**AI 科学家**来说，Docker 解决了深度学习和机器学习领域最头疼的环境复现性问题。复杂的模型训练和推理往往依赖于特定的 CUDA 版本、AI 框架和各种科学计算库，手动配置极易出错且难以复现。Docker 允许科学家将模型代码、所有依赖以及特定的驱动版本封装成一个自包含的镜像，确保无论在任何支持 Docker 和 GPU 的机器上，实验环境都能完美复现，从而大大提高了研究结果的透明度和可信度。同时，它也便于在共享计算资源的环境中进行有效的资源隔离与调度，并简化了训练好模型的生产部署过程。



## quick guide

> more guidance in ‘CLI’ section 😁

### Installation

#### windows

官网下载安装器

安装完手动打开 docker desktop

注册/登录 （可跳过）

终端中测试 `docker --version` 查看是否安装成功 （可能要加 环境变量）



#### macos

类似 windows ，直接下载 docker desktop 即可。





#### 一些安装报错

> [Windows10安装Docker Desktop - WSL update failed](https://blog.csdn.net/wochunyang/article/details/138225109)



### 容器的通信

#### docker 容器与主机的互相访问

> 待学习： [【docker知识】从容器中如何访问到宿主机_docker容器访问宿主机-CSDN博客](https://blog.csdn.net/gongdiwudu/article/details/128888497)

#### docker 容器之间互相访问

> 待学习:  [Docker容器互访三种方式 - 三只松鼠 - 博客园](https://www.cnblogs.com/shenh/p/9714547.html)



## docker Philosophy

### image



### container



### volume









## CLI

### how to download image？

`docker pull <image_name>:<tag>` Pull an image or a repository from a registry. 

The `<tag>` is optional; if omitted, Docker will pull the `latest` tag.



### start a container

```
docker run [OPTIONS] IMAGE [COMMAND] [ARG...]
```

这是 Docker 中最核心的命令之一，它基于一个镜像创建一个新的容器并运行它。它有很多可选参数（OPTIONS），可以精细地控制容器的行为。

**常用参数详解：**

- `-d, --detach` **后台运行容器**（分离模式）。加上这个参数后，容器会在后台启动并持续运行，命令行会立刻返回容器的 ID。如果不加，容器将在前台运行，当前终端会连接到容器的输入输出流，关闭终端会导致容器停止。
- `-p, --publish <主机端口>:<容器端口>` **端口映射**。将宿主机的指定端口映射到容器内的指定端口。这样，外部网络就可以通过访问 `宿主机IP:主机端口` 来访问容器内的服务。
- `-P, --publish-all` **随机端口映射**。将镜像中所有通过 `EXPOSE` 指令暴露的端口，自动映射到宿主机的一系列随机端口上。不常用，但对于快速测试很方便。
- `--name <容器名>` **指定容器名称**。为容器分配一个独一无二且易于记忆的名称，方便后续通过名字来管理（如 `docker stop my-container`）。若不指定，Docker 会随机生成一个（例如 `quirky_newton`）。
- `-it` **交互式操作**。这是 `-i` (`--interactive`) 和 `-t` (`--tty`) 两个参数的组合。`-i` 保持标准输入（STDIN）打开，`-t` 为容器分配一个伪终端。这个组合通常用于进入容器的命令行环境，例如 `docker run -it ubuntu /bin/bash`。
- `--rm` **自动删除容器**。当容器运行结束（无论是正常退出还是出现错误），自动将其文件系统和所有相关资源删除。这对于执行一次性任务或进行测试非常有用，可以避免系统中残留大量已停止的容器。
- `-v, --volume <宿主机路径>:<容器路径>` **挂载数据卷**。将宿主机上的一个目录或文件挂载到容器内的指定路径。这使得数据可以持久化存储在宿主机上，即使容器被删除，数据也不会丢失。这也是在宿主机和容器之间共享文件的主要方式。
- `-e, --env <键=值>` **设置环境变量**。向容器内部传递一个或多个环境变量。很多应用程序（特别是数据库、Web 服务等）通过读取环境变量来获取配置信息，如数据库密码、运行模式等。例如：`-e MYSQL_ROOT_PASSWORD=secret`。
- `--restart <策略>` **设置重启策略**。定义容器在退出时应采取的重启行为，这对于保证服务的持续可用性至关重要。常用策略包括：
  - `no`: 不自动重启（默认值）。
  - `on-failure`: 仅当容器以非零状态退出时才重启。
  - `unless-stopped`: 总是重启容器，除非它被手动停止 (`docker stop`)。
  - `always`: 无论退出状态码是什么，总是重启容器。
- `--network <网络模式>` **连接到指定网络**。默认情况下，容器会连接到 `bridge` 网络。此参数可以让你将容器连接到自定义的网络，以实现容器之间的隔离或便捷通信。
- `-m, --memory <内存限制>` 和 `--cpus <CPU数量>` **资源限制**。可以限制容器能使用的最大内存和 CPU 资源，防止单个容器耗尽系统资源。例如：`-m 512m` 限制最大内存为 512MB，`--cpus="1.5"` 表示容器最多可以使用 1.5 个 CPU 核心。

**示例：**

```bash
# 启动一个后台运行的 Redis 容器
# --name: 命名为 my-redis
# --restart: 除非手动停止，否则总是保持运行
# -p: 将主机的 6379 端口映射到容器的 6379 端口
# -v: 将主机当前目录下的 data 目录挂载到容器的 /data 目录，用于数据持久化
# redis: 使用的镜像
docker run -d --name my-redis --restart unless-stopped -p 6379:6379 -v $(pwd)/data:/data redis
```



### container operation

> 一般而言， 可以用 container name 的地方都可以使用 container ID

`docker stats <container_name>`   监测container的资源使用情况，如果没有 container_name 则监视所有 container 的资源使用情况

列举所有的容器： `docker ps -a`  没有 -a 则只会输出正在运行的容器

停止容器： `docker stop <容器 ID>` 

重启容器： `docker restart <容器 ID>` 

删除容器： `docker rm <容器 ID>` 

启动容器内控制台: `docker exec -it <容器 ID> /bin/bash`



### iamge operation

`docker images`：List all locally stored images.

`docker rmi <image_ID>`： Remove one or more images.

`docker build -t <image_name>:<tag> .` ： Build an image from a Dockerfile in the current directory.





### tips

#### 更新已有容器的重启策略

假设你有一个名为 `my-app` 的容器，之前没有设置重启策略，现在你想为它加上。

```bash
# 为名为 my-app 的容器更新重启策略为 unless-stopped
# 这个命令对正在运行或已停止的容器都有效
docker update --restart unless-stopped my-app
```

