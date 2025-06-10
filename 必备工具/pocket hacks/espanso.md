# Espanso

## introduction

跨平台的文本 snippets 软件：

- 代码片段、固定邮件片段
- 快速输入 llm prompt （亮点）
- 释放双手，拒绝无意义重复打字
- 配置即服务，需要的片段直接配置在 yaml 文件中即可，可以使用 github 进行多设备的同步



## quick guide

可以直接参考官方文档 [Getting Started | Espanso](https://espanso.org/docs/get-started/)

### Configuration

Espanso 使用基于**文件配置**的方法，遵循Unix哲学。所有配置文件都位于`espanso`目录中，其位置取决于当前操作系统：

- Linux：`$XDG_CONFIG_HOME/espanso`（例如：`/home/user/.config/espanso`）

- Windows：`{FOLDERID_RoamingAppData}\espanso`（例如：`C:\Users\user\AppData\Roaming\espanso`）

- macOS：`$HOME/Library/Application Support/espanso`（例如：`/Users/user/Library/Application Support/espanso`）。您也可以使用`$HOME/.config/espanso`，但需要在Espanso停止时自己移动文件夹。

> **特别的**，macos 下推荐使用 brew 下载和管理 espanso (而不是直接使用互联网下载，再放到 application 中)，虽然也会把相关软件移动到 applications 文件夹中，但是会 `Linking Binary 'espanso' to '/opt/homebrew/bin/espanso'` ，这样就可以更加方面使用相关的 CLI .
>
> 下载命令如下：
>
> ```bash
> brew install espanso
> ```
>
> - 配置文件在：`~/Application Support/espanso`
> - 相关 cli 工具(软链接)在：`/opt/homebrew/bin/espanso` 



快速找到配置文件夹路径的方法可以使用以下命令：

```bash
espanso path
```

有必要设置一下用户级别的环境变量（Macos）：

```bash
# 在 ~/.zshrc 中加入以下环境变量
export ESPANSO_CONFIG=$HOME/Library/Application Support/espanso
```





### CLI

```bash
espanso 2.2.1
Federico Terzi
A Privacy-first, Cross-platform Text Expander

USAGE:
    espanso [FLAGS] [SUBCOMMAND]

FLAGS:
    -h, --help       Prints help information
    -v               Sets the level of verbosity
    -V, --version    Prints version information

OPTIONS:


SUBCOMMANDS:
    cmd           Send a command to the espanso daemon.
    edit          Shortcut to open the default text editor to edit config files
    env-path      Add or remove the 'espanso' command from the PATH
    help          Prints this message or the help of the given subcommand(s)
    install       Install a package
    log           Print the daemon logs.
    match         List and execute matches from the CLI
    migrate       Automatically migrate legacy config files to the new v2 format.
    package       package-management commands
    path          Prints all the espanso directory paths to easily locate configuration and matches.
    restart       Restart the espanso service
    service       A collection of commands to manage the Espanso service (for example, enabling auto-start on 		                   system boot).
    start         Start espanso as a service
    status        Check if the espanso daemon is running or not.
    stop          Stop espanso service
    uninstall     Remove a package
    workaround    A collection of workarounds to solve some common problems.

```



Espanso 的命令行工具用于管理其后台服务、配置和包。

1. **服务管理**

- `espanso start | stop | restart` - 分别用于启动、停止和重启后台服务。`restart` 可强制重载配置。
- `espanso status` - 检查服务的当前运行状态。
- `espanso service` - 服务配置相关命令。 

2. **配置与路径**

- `espanso edit` - **(最常用)** 在文件管理器中快速打开整个配置文件夹。
- `espanso path` - 在终端显示配置目录或其特定子目录（如 `match`, `packages`）的绝对路径。

3. **调试与包管理**

- `espanso log` - **(排错关键)** 实时查看日志流，用于分析触发器不生效等问题。
- `espanso install | uninstall <包名>` - 安装或卸载来自社区的片段包。
- `espanso package list | install | uninstall | update` - 包管理。
- `espanso --version`  - 查看当前版本号。



### how to make our own sni
