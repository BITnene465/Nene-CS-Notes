# QQchatBot

> [五分钟构建go-cqhttp QQ对话机器人 - wxyww - 博客园](https://www.cnblogs.com/wxyww/p/16712598.html)
>
> [基于go-cqhttp搭建的qq机器人_你的账号被限制登录, 请配置 signserver 后重试-CSDN博客](https://blog.csdn.net/tttll3014/article/details/133317446)

## 实现方案







## 准备工作

### 测试本地 ollama

端口测试 (下面这个是 powershell 命令)

```powershell
 Test-NetConnection -Computername 127.0.0.1 -Port 11434
```



api 测试

> 参考： [handy-ollama/docs/C4/1. Ollama API 使用指南.md at main · datawhalechina/handy-ollama](https://github.com/datawhalechina/handy-ollama/blob/main/docs/C4/1. Ollama API 使用指南.md)

```powershell
# cmd
curl http://localhost:11434/api/generate -d "{\"model\": \"llama3.1\", \"prompt\": \"how are you？\"}"

# powershell
curl.exe http://localhost:11434/api/generate -d "{\`"model\`": \`"llama3.1\`", \`"prompt\`": \`"how are you?\`"}"
```



powershell 内

- 需要用 ` 来转义双引号保证双引号能够传给 curl 命令
- 需要显式调用 `curl.exe`





### 配置 config.yml 文件



### 配置本地签名服务器

> [最新版go-cqhttp的sign 签名服务器搭建教程_qsign签名服务器-CSDN博客](https://blog.csdn.net/qq_42123284/article/details/135375460)

`docker run -d --restart=always --name qsign -p 7778:8080 hansaes/unidbg-fetch-qsign:latest`
