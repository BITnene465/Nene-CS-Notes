

`http.server`

```python
python -m http.server 8000
```

以当前目录为根目录构建一个http服务器，访问端口号为 8000

`http://localhost:8000`来查看当前目录下的文件。





**`json.tool`**：用于验证JSON文件格式并美化输出。

```bash
python -m json.tool data.json
```

如果`data.json`文件格式正确，它会以格式化的方式输出JSON内容；如果格式有误，会报错提示具体问题。