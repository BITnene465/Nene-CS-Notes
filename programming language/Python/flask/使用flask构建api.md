# 使用 flask 构建 api

## Flask route -- 后端 api 核心

### 核心功能

将 URL 映射到 Python 函数，处理不同 URL 请求的机制

### 路由定义

使用 `@app.route('/path')` 装饰器，对应的 python 函数为视图函数
```python
@app.route('/')
def home():
    return 'Welcome to the Home Page!'
```

### 路由参数

#### 动态参数传递

```python
@app.route('/greet/<name>')
def greet(name):
    return f'Hello, {name}!'
```

#### 类型转换器
| 转换器类型 | 说明               | 示例                     |
| ---------- | ------------------ | ------------------------ |
| int        | 匹配整数           | `/user/<int:user_id>`    |
| float      | 匹配浮点数         | `/value/<float:num>`     |
| path       | 匹配包含斜杠的路径 | `/files/<path:filename>` |

示例：
```python
@app.route('/user/<int:user_id>')
def user_profile(user_id):
    return f'User ID: {user_id}'
```

### 请求方法处理
指定允许的 HTTP 方法： `GET, POST, PUT, DELETE` 等 
```python
@app.route('/submit', methods=['POST'])
def submit():
    return 'Form submitted!'
```

### 响应类型

视图函数可以返回多种类型的响应：

- **字符串**：返回纯文本响应
- **HTML**：返回 HTML 页面
- **JSON**：返回 JSON 数据
- **Response 对象**：自定义响应

```python
from flask import jsonify, Response

# JSON 响应
@app.route('/json')
def json_response():
    return jsonify({'key': 'value'})

# 自定义响应对象
@app.route('/custom')
def custom_response():
    res = Response('Custom response', status=200)
    res.headers['X-Custom-Header'] = 'Value'
    return res
```

### 静态文件与模板
#### 静态文件引用
```html
<link rel="stylesheet" href="{{ url_for('static', filename='style.css') }}">
```

#### 模板渲染
视图函数：
```python
@app.route('/hello/<name>')
def hello(name):
    return render_template('hello.html', name=name)
```

模板文件 (templates/hello.html)：
```html
<!DOCTYPE html>
<html>
<head>
    <title>Hello</title>
</head>
<body>
    <h1>Hello, {{ name }}!</h1>
</body>
</html>
```

### 路由优先级规则
1. 按定义顺序匹配
2. **更具体的路由应定义在前**
3. 避免模糊匹配冲突

正确顺序示例：

```python
@app.route('/user/<int:user_id>')  # 先定义具体路由
def user_profile(user_id): pass

@app.route('/user')  # 后定义通用路由
def user_list(): 
    pass
```





## Flask blueprints -- 模块化 api 构建

### 什么是Flask蓝图

Flask的蓝图（Blueprints）是一种组织代码的机制，允许你将Flask应用分解成多个模块。这样可以更好地组织应用逻辑，使得应用更具可维护性和可扩展性。每个蓝图可以有自己的路由、视图函数、模板和静态文件，这样可以将相关的功能分组。

通过使用蓝图，你可以将Flask应用拆分成多个模块，每个模块处理相关的功能，使得代码更加清晰和易于管理。

### 创建蓝图
创建蓝图涉及到以下几个步骤：

1. **定义蓝图**：在一个独立的模块（文件）中定义蓝图。
2. **注册蓝图**：在主应用中注册蓝图，使其生效。

#### 示例：创建一个博客应用
假设我们要创建一个博客应用，其中包含**用户管理**和**博客功能**，我们可以将这些功能分成两个蓝图：`auth` 和 `blog`。

**项目结构**：
```
yourapp/
│
├── app.py
├── auth/
│   ├── __init__.py
│   └── routes.py
│
└── blog/
    ├── __init__.py
    └── routes.py
```

#### 定义蓝图

**auth/routes.py 文件代码**：

```python
from flask import Blueprint, render_template, request, redirect, url_for

auth = Blueprint('auth', __name__)

@auth.route('/login')
def login():
    return render_template('login.html')

@auth.route('/logout')
def logout():
    return redirect(url_for('auth.login'))

@auth.route('/register')
def register():
    return render_template('register.html')
```

**blog/routes.py 文件代码**：
```python
from flask import Blueprint, render_template

blog = Blueprint('blog', __name__)

@blog.route('/')
def index():
    return render_template('index.html')

@blog.route('/post/<int:post_id>')
def post(post_id):
    return f'Post ID: {post_id}'
```

### 注册蓝图
在主应用中注册蓝图，使其生效。

**app.py 文件代码**：
```python
from flask import Flask

app = Flask(__name__)

# 导入蓝图
from auth.routes import auth
from blog.routes import blog

# 注册蓝图
app.register_blueprint(auth, url_prefix='/auth')
app.register_blueprint(blog, url_prefix='/blog')

if __name__ == '__main__':
    app.run(debug=True)
```

### 使用蓝图中的模板和静态文件
蓝图中的模板和静态文件应放在蓝图的文件夹下的 `templates` 和 `static` 子文件夹中。

**项目结构**：
```
yourapp/
│
├── app.py
├── auth/
│   ├── __init__.py
│   ├── routes.py
│   └── templates/
│       ├── login.html
│       └── register.html
│
└── blog/
    ├── __init__.py
    ├── routes.py
    └── templates/
        ├── index.html
        └── post.html
```

### 在蓝图中使用请求钩子
蓝图支持请求钩子，例如 `before_request` 和 `after_request`，可以在蓝图中定义这些钩子来处理请求和响应。

**auth/routes.py 文件代码**：
```python
@auth.before_app_request
def before_request():
    # 执行在每个请求之前的操作
    pass

@auth.after_app_request
def after_request(response):
    # 执行在每个请求之后的操作
    return response
```

### 在蓝图中定义错误处理
蓝图也可以定义自己的错误处理函数。

**blog/routes.py 文件代码**：
```python
@blog.errorhandler(404)
def page_not_found(error):
    return 'Page not found', 404
```





## Flask CLI

> 参考资料：[命令行界面 — Flask 文档 (3.1.x) - Flask 框架](https://flask.org.cn/en/stable/cli/)



