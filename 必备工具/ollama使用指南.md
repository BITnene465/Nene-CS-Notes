# OLLAMA

## 传统命令行

系统环境变量内 `OLLAMA_MODELS` 为 OLLAMA 存储模型文件的地方，建议改到 C 盘以外的位置



常用命令

```powershell
ollama serve       启动ollama
ollama create      从模型文件创建模型
ollama show        显示模型信息
ollama run         运行模型
ollama pull        从注册表中拉取模型
ollama push        将模型推送到注册表
ollama list        列出模型
ollama cp          复制模型
ollama rm          删除模型
ollama help        获取有关任何命令的帮助信息
```



## open-webui

本地的大模型 webui， 支持 openai 的各个模型和 ollama 



### 安装

#### python

python 安装可以直接 新建一个 conda 环境， 然后 `pip install open-webui`

安装完毕后 `open-webui serve` 启动应用，在 `localhost:8080` 访问即可



#### docker

**使用 docker 部署才是重点**





### 面板管理





### 对话记录清理

[docker 部署的 openwebui 怎么查看清理聊天记录呢 - 搞七捻三 - LINUX DO](https://linux.do/t/topic/292088)
