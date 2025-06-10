# WSL

## 介绍





## 安装 Linux 子系统

### 命令行安装（便捷）

`wsl --list --online`  或 `wsl -l -o`     看看有哪些可以下载分发包

`wsl --install <Distro_name>`     用于下载并安装对应分发包



### MIcrosoft store

从微软商店下载 Linux 发行版即可自动安装





### 利用 docker 安装

比如以上的方法就没有办法安装 centos 版 linux，但是可以利用 docker 和导入导出进行安装





## 给 WSL 配置美化终端 （optional）

> 参考 [Ubuntu美化过程中zsh和oh-my-zsh的安装与配置（步骤和小白注意项）_zsh美化-CSDN博客](https://blog.csdn.net/zcllwxl/article/details/130538974)





## 操作

### 常用指令

`wsl`  直接输入 wsl 会启动默认的子系统

`wsl -d <distro_name>` 启动对应的 Linux 子系统

`wsl --set-default <distro_name>` 设置默认子系统

`wsl -l -v`   列出所有已安装的子系统

`wsl --shutdown` 终止所有正在运行 Linux 子系统

`wsl --terminate <distro_name>`  终止特定的 Linux 子系统

 

### wsl 和 windows 的命令相互调用

#### 在 windows 中调用 wsl 命令

`wsl -d <distro_name> <Linux command>` 或 `wsl <Linux command>`

绝大部分 linux 命令都可以用， 也可以调用该子系统中自己写的命令







#### 在 wsl 中调用 windows 命令

只能使用少数命令

`explorer.exe . `  用资源管理器打开当前目录

`code .`  (**需要 Vscode 安装 wsl 插件**) 使用 Vscode 打开当前目录

 



### wsl 与 windows 的互相访问

> 参考： [WSL 与 Windows 互相访问教程_wsl 访问 windows 本地文件-CSDN 博客](https://blog.csdn.net/djh3200/article/details/144693143#:~:text=方法 1：通过网络路径访问 1 打开文件资源管理器或命令行： 在地址栏或命令行输入以下路径： \\wsl%24\<发行版名称>\ 1 例如：,\\wsl%24\Ubuntu\home\<用户名> dir 1 2 3 优点： 直接访问，无需额外配置。 文件路径自动挂载，无权限问题。)

#### windows 中访问 wsl 文件

1. 直接在 **资源管理器** 中的 Linux 部分访问每个子系统的文件系统
2. **通过网络路径访问**：
    -  在 **资源管理器** 的路径栏中输入 `\\wsl$`
    -  在 **终端** 中 `cd \\wsl$\<distro_name>` 到对应子系统的文件系统中



#### wsl 中访问 windows 文件系统

直接 `cd \mnt` 即可， 每个子系统中的 **mnt** 文件夹就是对应主机的文件系统



#### 共享文件 & 传输文件







### 导入导出备份还原

`wsl --export <distro_name> <target_path>`  将系统备份导出成 tar 包

`wsl --import <DistributionName> <安装位置> <tar文件名>`  将 tar 包导入安装到具体为止





### 修改子系统的存储位置

> 参考： [Windows 11：如何移动 WSL Linux 发行版存储位置 - 系统极客](https://www.sysgeek.cn/move-wsl-distros-windows/) 的 **方法 2**

`wsl --manage <distro_name> --move <new_path>`  **一步到位**，没有其他遗留问题

当然也可以采用导入导出的方法，不过会有一些细节难处理，所以就不使用了





## wsl 配置文件

文件为 `/etc/wsl.conf`

更换为以下内容：

```json
[boot]    # 开机配置
systemd=true    # 启动systemd支持
```







## 杂项： 一些报错

**网络问题**

如果有以下报错，表示wsl无法使用系统代理（如 clash），可以按照下面博客的操作进行修复

[wsl: 检测到 localhost 代理配置，但未镜像到 WSL。NAT 模式下的 WSL 不支持 localhost 代理。_wsl: 检测到 localhost 代理配置, 但未镜像到 wsl。nat 模式下的 wsl 不支持-CSDN 博客](https://blog.csdn.net/weixin_50925658/article/details/135111897)
