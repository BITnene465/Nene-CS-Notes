# Pytest

## 1. 安装 `pytest`

在使用 `pytest`之前，需要确保已经安装了它。可以使用以下命令进行安装：

```bash
pip install pytest
```

## 2. 项目结构

为了更好地组织测试代码，建议采用以下项目结构：

```
project-root/
├── src/  # 源代码目录
│   ├── __init__.py
│   └── my_module.py
├── tests/  # 测试代码目录
│   ├── __init__.py
│   ├── test_my_module.py
│   └── conftest.py  # 用于定义测试夹具和其他配置
├── pytest.ini  # pytest 配置文件
└── README.md
```

### 2.1 关键目录说明

- **`src/`**：项目中的源代码文件。
- **`tests/`**：项目中的测试代码文件。
- **`pytest.ini`**：pytest 的配置文件，用于定义测试路径、标记等。

## 3. 编写测试代码

### 3.1 测试文件命名规范

- 测试文件的命名应以 `test_` 开头或结尾，例如 `test_my_module.py`。
- 测试函数的命名应以 `test_` 开头，例如 `test_addition`。

### 3.2 示例测试代码

```python
# tests/test_my_module.py

def add(a, b):
    return a + b

def test_addition():
    assert add(2, 3) == 5
```

## 4. 运行测试

### 4.1 运行所有测试

在项目根目录下运行以下命令，`pytest` 会自动发现并运行所有符合命名约定的测试文件和测试函数：

```bash
pytest
```

### 4.2 运行特定的测试文件

如果你想运行特定的测试文件，可以指定文件路径，例如：

```bash
pytest tests/test_my_module.py
```

### 4.3 显示标准输出信息

要在运行 `pytest` 时显示标准输出信息，可以使用 `-s` 选项：

```bash
pytest -s
```

例如，运行你的测试文件并显示标准输出信息：

```bash
pytest -s tests/test_alexnet.py
```

## 5. 使用 `pytest` 标记

### 5.1 定义标记

可以在 `pytest.ini` 文件中定义标记，例如：

```ini
[pytest]
markers =
    smoke: mark test as smoke test
    regression: mark test as regression test
    slow: mark test as slow
```

### 5.2 使用标记

在测试函数或测试类中使用标记，例如：

```python
# tests/test_my_module.py

import pytest

@pytest.mark.smoke
def test_addition():
    assert add(2, 3) == 5

@pytest.mark.regression
def test_subtraction():
    assert subtract(5, 3) == 2
```

### 5.3 运行带有特定标记的测试

使用 `-m` 参数运行带有特定标记的测试，例如运行标记为 `smoke` 的测试：

```bash
pytest -m smoke
```

## 6. 处理导入错误

如果在运行测试时遇到导入错误，可以在测试文件的顶部添加以下代码，以确保包可以被正确导入：

```python
import sys
import os
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), '..')))
```

例如，在 `tests/test_alexnet.py` 文件中：

```python
import sys
import os

sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), '..')))
from nenets.models import AlexNet
```

## 7. 组织测试

### 7.1 测试模块

将相关的测试函数组织在一个测试模块中，例如 `test_alexnet.py`，专门用于测试 `AlexNet` 模型。

### 7.2 测试夹具

使用 `pytest` 的测试夹具（fixtures）可以更好地组织测试代码。测试夹具可以用于初始化测试数据、清理测试环境等。

以下是一个示例测试夹具：

```python
# tests/conftest.py

import pytest

@pytest.fixture
def sample_data():
    return {
        'input': torch.randn(1, 3, 224, 224),
        'expected_output': (1, 1000)
    }
```

### 7.3 参数化测试

使用 `pytest` 的参数化功能可以更高效地测试多种输入情况。以下是一个示例：

```python
# tests/test_my_module.py

import pytest

@pytest.mark.parametrize("a, b, expected", [
    (2, 3, 5),
    (5, 7, 12),
    (-1, 1, 0)
])
def test_addition(a, b, expected):
    assert add(a, b) == expected
```

## 8. 调试测试

如果测试失败，可以使用 `pytest` 的调试功能来定位问题。例如，在测试函数中设置断点，或使用 `print` 语句输出调试信息。

在 `pytest` 中，可以使用 `-s` 选项来显示 `print` 语句的输出：

```bash
pytest -s
```

## 9. 自动生成测试报告

`pytest` 可以与多种测试报告插件配合使用，例如 `pytest-html`，以生成 HTML 格式的测试报告。

安装 `pytest-html`：

```bash
pip install pytest-html
```

生成测试报告：

```bash
pytest --html=report.html
```

