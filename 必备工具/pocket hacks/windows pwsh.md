# windows powershell



## 参考 

> [Windows Terminal/终端 Powershell 美化——oh my posh 教程（保姆级）_powershell 美化主题-CSDN 博客](https://blog.csdn.net/satangele/article/details/135785794)
>
> [Windows Terminal 完美配置 PowerShell 7.1 - 知乎](https://zhuanlan.zhihu.com/p/137595941)



## 配置步骤 （windows 下）

### 安装 pwsh 7



```powershell
winget search Microsoft.PowerShell  # 搜索


# 下面的安装命令二选一
winget install --id Microsoft.PowerShell --source winget
winget install --id Microsoft.PowerShell.Preview --source winget   # 安装预发布版本
```



### 下载 oh-my-posh

使用命令行下载（不推荐）

```powershell
Set-ExecutionPolicy Bypass -Scope Process -Force; Invoke-Expression ((New-Object System.Net.WebClient).DownloadString('https://ohmyposh.dev/install.ps1'))
```

建议在 github 上下载解压，然后安装到本地（可以自定义安装路径）





### 配置终端字体

安装并且在 windows terminal中使用一种  Nerd Font 保证后面的主题中可以显示特殊符号（更重要是好看）

本人喜欢用 **Jetbrain Mono Nerd font**





### 更换 powershell 的安全策略  *

```powershell
Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope LocalMachine
```





### 设置主题  && 安装插件

```powershell
notepad $PROFILE  # 编辑配置文件（一个启动时自动调用的 ps1 脚本）
```





**我目前的配置文件如下：**

```powershell
oh-my-posh init pwsh --config "$env:POSH_THEMES_PATH/atomic.omp.json" | Invoke-Expression

# 导入模块
# Import-Module Terminal-Icons
Import-Module PSReadLine
# Import-Module ZLocation
Import-Module posh-git;
# Import-Module DirColors;


Set-PSReadLineKeyHandler -Key Tab -Function MenuComplete # Tab键会出现自动补全菜单
# 上下方向键箭头，搜索历史中进行自动补全
Set-PSReadlineKeyHandler -Key UpArrow -Function HistorySearchBackward
Set-PSReadlineKeyHandler -Key DownArrow -Function HistorySearchForward 


# 让powershell里面也可以使用mklink命令（实际上就是封装了一下cmd命令）
function Make-Link {
      cmd /C mklink $args
} 

set-alias mklink Make-Link
```





