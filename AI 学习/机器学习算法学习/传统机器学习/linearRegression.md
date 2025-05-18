## 多元线性回归 - 梯度下降法

梯度下降法是一种迭代优化算法，用于通过不断调整参数来最小化损失函数。在多元线性回归中，我们通常最小化均方误差（MSE）。

### 梯度下降的步骤

1. 初始化回归系数（权重），通常设为零或小的随机数。
2. 计算预测值 y^\hat{y}y^。
3. 计算损失函数（均方误差）。
4. 计算损失函数对回归系数的梯度。
5. 更新回归系数。
6. 重复步骤2到5，直到损失函数收敛或达到最大迭代次数。

### 损失函数和梯度计算





### 伪代码

```shell
1. 初始化权重 beta 为零或随机数
2. 选择学习率 alpha 和迭代次数 max_iter
3. 对于每次迭代：
    a. 计算预测值 y_hat = X * beta
    b. 计算损失函数 L = (1/m) * sum((y - y_hat)^2)
    c. 计算梯度 gradient = -(2/m) * X.T * (y - y_hat)
    d. 更新权重 beta = beta - alpha * gradient
4. 返回权重 beta
```

### Python 实现

以下是使用梯度下降法实现多元线性回归的代码：

```python
import numpy as np

def gradient_descent(X, y, alpha=0.01, max_iter=1000):
    """
    多元线性回归的梯度下降法
    :param X: 特征矩阵，形状为 (m, n)
    :param y: 目标向量，形状为 (m, 1)
    :param alpha: 学习率
    :param max_iter: 最大迭代次数
    :return: 回归系数，形状为 (n, 1)
    """
    m, n = X.shape
    beta = np.zeros((n, 1))  # 初始化权重
    X = np.hstack((np.ones((m, 1)), X))  # 在 X 前加一列 1 以包含截距项 beta_0
    y = y.reshape(-1, 1)
    
    for _ in range(max_iter):
        y_hat = X.dot(beta)
        gradient = -(2/m) * X.T.dot(y - y_hat)
        beta -= alpha * gradient
        
    return beta

# 示例数据
X = np.array([[1, 2], [2, 4], [3, 6], [4, 8]])
y = np.array([3, 6, 9, 12])

# 计算回归系数
beta = gradient_descent(X, y, alpha=0.01, max_iter=1000)

print("回归系数:", beta)
```

### 解释

1. **`np.zeros((n, 1))`**：
    - 初始化回归系数（权重）为零。
2. **`X = np.hstack((np.ones((m, 1)), X))`**：
    - 在特征矩阵 XXX 前面加一列全为1的列，以包含截距项 β0\beta_0β0。
3. **`for _ in range(max_iter)`**：
    - 进行指定次数的迭代。
4. **`y_hat = X.dot(beta)`**：
    - 计算预测值 y^\hat{y}y^。
5. **`gradient = -(2/m) \* X.T.dot(y - y_hat)`**：
    - 计算梯度。
6. **`beta -= alpha \* gradient`**：
    - 更新回归系数。

### 可视化

我们可以使用生成的回归系数来预测并可视化结果：

```python
import matplotlib.pyplot as plt

# 生成示例数据
np.random.seed(0)
X = 2 * np.random.rand(100, 2)
y = 4 + 3 * X[:, 0] + 5 * X[:, 1] + np.random.randn(100)

# 计算回归系数
beta = gradient_descent(X, y, alpha=0.01, max_iter=1000)

# 打印回归系数
print("回归系数:", beta)

# 预测值
X_new = np.array([[0, 0], [2, 2]])
X_new_b = np.hstack((np.ones((X_new.shape[0], 1)), X_new))
y_predict = X_new_b.dot(beta)

# 绘制数据和回归直线
plt.scatter(X[:, 0], y, color='blue', label='Data')
plt.plot(X_new[:, 0], y_predict, color='red', label='Regression Line')
plt.xlabel('Feature 1')
plt.ylabel('Target')
plt.legend()
plt.show()
```

### 解释

1. **`X = 2 * np.random.rand(100, 2)`**：
    - 生成100个样本，每个样本有两个特征，特征值在0到2之间。
2. **`y = 4 + 3 * X[:, 0] + 5 * X[:, 1] + np.random.randn(100)`**：
    - 生成目标值，基于特征的线性组合加上一个随机噪声项。
3. **`X_new = np.array([[0, 0], [2, 2]])`**：
    - 新的特征数据，用于预测目标值。
4. **`plt.scatter(X[:, 0], y, color='blue', label='Data')`**：
    - 绘制原始数据点。
5. **`plt.plot(X_new[:, 0], y_predict, color='red', label='Regression Line')`**：
    - 绘制回归直线。