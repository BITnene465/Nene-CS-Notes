# Basic Use

## git workflow

> [Git之GitFlow工作流 | Gitflow Workflow（万字整理，已是最详）-CSDN博客](https://blog.csdn.net/sunyctf/article/details/130587970)

git flow 是一种git工作流的范式



> [Git工作流指南 - 不挑食的程序员 - SegmentFault 思否](https://segmentfault.com/a/1190000008880416)

这是另外几种范式，分别适用于几种开发情况



## Basic

> 使用git的大部分场景都是IDE自带的可视化git工具，  **但是也要熟悉git的终端操作**

### 常用命令流程

<img src="https://ts1.cn.mm.bing.net/th/id/R-C.5b340749640a829f4aff204e33d6cabf?rik=EYKZ5TnK0%2buvrQ&riu=http%3a%2f%2fwww.uml.org.cn%2fpzgl%2fimages%2f2017041302.png&ehk=RNQXQSY4hwra6cf5SuQmCAa6yStdjRprNOpxkUZ%2bvIY%3d&risl=&pid=ImgRaw&r=0" alt="Git 常用命令 - 知乎" style="zoom: 67%;" />





### 分支类命令

```bash
# 查看所有本地分支
git branch

# 查看代码仓库的所有远程分支
git branch -r

# 所有分支
git branch -a

# 切换分支
git checkout <branch_name>

# 合并分支  假设当前是 sp3, 要将 sp2的代码合并到sp3
git merge SP2
```



### 查看信息类命令

```bash
// 展示各个文件的状态和对比
git status  

// 提交日志, hash id 可查
git log 

```





### git提交步骤

```bash
git pull  # 先拉远程仓库代码
git status  # 查看状态
git add ...  # 将文件添加到缓存区
git commit -m ...  # 先提交到本地
git push    # 将本地提交推送到远程仓库 (如果没有追踪则需要指定远程仓库名)
```





### Git 提交格式

- 摘要（Summary）和详细描述（Description）
- 示例：`feat: Add new feature for user authentication`



### 在本地操作

#### 本地提交

一些**IDE**的可视化git工具在提交时会自动将文件加到**暂存区**

以下的本地提交都会在**当前分支**中操作

```bash
# 添加文件到暂存区
git add <filename>

# 提交文件并输入提交消息
git commit -m "Commit message" filename

# 直接 commit会将所有暂存区的修改文件全部提交
git commit -m ""
```

可以有多个 `-m` ， 例如：

```bash
git commit -m "命令行参数系统构建" main.py -m "main.py 修改"
```



#### 本地撤销

**reset 加提交ID回溯(rollback)到本地提交的指定分支**



### 远程仓库操作

#### 推送到远程仓库

```bash
# 查看远程仓库的状态
git remote -v

# 将本地提交推送到远程仓库（已追踪）
git push

# 如果需要指定分支，使用以下格式 : 会将当前本地的代码修改提交到远程仓库
git push origin <branch-name>
```



#### 推送指定版本的提交

```bash
# 使用 git log 查找提交的哈希值或者标签
# 使用 git push 推送特定版本的提交
git push origin <commit-hash>:<remote-branch>
git push origin <tag-name>:<remote-branch>
```

确保在提交和推送之前，你的代码处于一个良好的状态，并且你明确了你想要的更改。



#### 远程回溯

**只能先将本地代码回溯到指定版本再次push**





## 关于代理

### 设置https代理

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



### 终端代理脚本（快速停启代理）







## 通过开发场景学习

### 一些零碎场景

#### 一直在本地开发的项目第一次上传到 github

1. **创建新的 GitHub 仓库**：

   - 在 GitHub 网站上创建新仓库
   - 创建时不初始化仓库（不添加 README、.gitignore 或 license）

2. **连接本地仓库与远程仓库**：这一步是把远程仓库的镜像添加到本地 git

   `git remote add origin https://github.com/用户名/仓库名.git`

3. **推送本地分支到远程仓库**：

   `git push -u origin main`

   `-u` 参数会设置上游(upstream)跟踪，本地 main 分支会自动跟踪远程的 main 分支



**特殊情况：**

- **如果希望本地 A 分支对应远程 B 分支**：

  `git push -u origin A:B`

  这会将本地 A 分支推送到**远程 B 分支**，并设置跟踪

- **较低版本的 git 会在本地创建 master 默认分支，一般先改名：**

  `git branch -m master main`

  `git push -u origin main`



#### 将本地 A 分支强制推送到 远程 B 分支，并且建立追踪

1. **如果本地没有包含远程分支的镜像**

   `git remote add https://github.com/用户名/仓库名.git`

2. 强制推送

   `git push --force origin A:B`

3. 建立追踪

   `git branch --set-upstream-to=origin/B A ` 

   简化写法： `git branch -u origin/B` (目前 checkout 本地分支 A)

当然，我们一般会把本地分支 A 重命名为本地分支 B



### 单人开发场景

####   基于 `main` 分支创建并切换到本地 `dev` 分支

```bash
# 确保当前在 main 分支
git checkout main

# 创建并切换到新分支 dev（基于 main）
git checkout -b dev
# 或使用更直观的 git switch（Git 2.23+）
git switch -c dev main
```



####  推送 `dev` 分支到远程仓库

```bash
# 将本地 dev 分支推送到远程仓库，并设置跟踪（-u 表示 upstream）
git push -u origin dev
```
- 远程仓库会自动创建 `dev` 分支。
- `-u` 参数将本地 `dev` 与远程 `dev` 关联，后续可直接用 `git push` 或 `git pull`。



#### 合并 `dev` 到 `main` 分支

```bash
# 切换回 main 分支
git switch main
# 拉取远程 main 分支最新代码（先拉取后合并）
git pull origin main
# 合并 dev 分支到 main
git merge dev
# 推送更新后的 main 到远程
git push origin main
```



#### 删除本地和远程的 `dev` 分支 （如果需要）

```bash
# 删除本地 dev 分支
git branch -d dev
# 删除远程 dev 分支
git push origin --delete dev
```



#### 注意事项

1. **合并冲突**： 
   如果 `dev` 和 `main` 分支有冲突，需先解决冲突后再提交（`git add/commit`）。
2. **强制删除分支**：  
   - 若本地分支未合并，用 `git branch -D dev`（大写 `D` 强制删除）。  
   - 远程分支也可用 `git push origin :dev` 删除（冒号语法）。
3. **恢复误删分支**：  
   - 本地分支：通过提交哈希重新创建（`git checkout -b dev <commit-hash>`）。  
   - 远程分支：重新推送本地 `dev` 分支即可（`git push origin dev`）。





### 多人项目开发场景







## github workflow



