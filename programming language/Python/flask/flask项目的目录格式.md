# Flask 项目结构

## 简单项目结构

适用于小型应用，所有代码集中在一个文件中：

```
my_flask_app/
│
├── app.py
└── requirements.txt
```

- `app.py`：主要的 Flask 应用文件
- `requirements.txt`：项目依赖库

示例 `app.py`：
```python
from flask import Flask

app = Flask(__name__)

@app.route('/')
def home():
    return 'Hello, World!'

if __name__ == '__main__':
    app.run(debug=True)
```

示例 `requirements.txt`：
```
Flask==2.2.3
```

## 中型项目结构

适用于稍复杂的应用：

```
my_flask_app/
│
├── app/
│   ├── __init__.py
│   ├── routes.py
│   └── models.py
│
├── config.py
├── requirements.txt
└── run.py
```

关键文件说明：
- `app/__init__.py`：初始化Flask应用
- `app/routes.py`：定义路由和视图函数
- `app/models.py`：定义数据模型
- `config.py`：配置文件
- `run.py`：启动文件

示例 `app/__init__.py`：
```python
from flask import Flask

def create_app():
    app = Flask(__name__)
    app.config.from_object('config.Config')
    
    from . import routes
    app.register_blueprint(routes.bp)
    
    return app
```

## 复杂项目结构
适用于大型应用：

```
my_flask_app/
│
├── app/
│   ├── __init__.py
│   ├── routes/
│   │   ├── __init__.py
│   │   ├── main.py
│   │   └── auth.py
│   ├── models/
│   │   ├── __init__.py
│   │   └── user.py
│   ├── templates/
│   │   ├── layout.html
│   │   └── home.html
│   └── static/
│       ├── css/
│       └── js/
│
├── config.py
├── requirements.txt
├── migrations/
│   └── ...
└── run.py
```

目录说明：
- `routes/`：按功能模块划分路由
- `models/`：数据模型
- `templates/`：HTML模板
- `static/`：静态资源
- `migrations/`：数据库迁移文件

示例 `app/routes/main.py`：
```python
from flask import Blueprint, render_template

bp = Blueprint('main', __name__)

@bp.route('/')
def home():
    return render_template('home.html')
```

示例 `app/models/user.py`：
```python
from app import db

class User(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(150), unique=True, nullable=False)
```
