## 支持向量机（SVM）

支持向量机（SVM）是一种强大的监督学习算法，广泛用于分类和回归任务。SVM 通过寻找一个最佳的超平面将数据分成不同的类别。

### 关键概念

1. **超平面**：
   - 在 SVM 中，分类问题的核心在于找到一个最佳的超平面，将数据点分开。

2. **支持向量**：
   - 支持向量是离超平面最近的数据点，这些点对确定超平面的位置和方向起关键作用。

3. **最大化间隔**：
   - SVM 通过最大化支持向量到超平面的间隔来找到最佳的超平面。

### SVM 的数学表示

对于一个二分类问题，假设我们有一个训练数据集 $(x_i, y_i)$，其中 $x_i$ 是输入特征向量， $y_i$ 是对应的标签（1 或 -1）。我们希望找到一个超平面 $w \cdot x + b = 0$，使得每个数据点满足：

$$ y_i (w \cdot x_i + b) \geq 1 $$

我们的目标是最小化目标函数：

$$ \frac{1}{2} \|w\|^2 $$

在约束条件下：

$$ y_i (w \cdot x_i + b) \geq 1 $$

### 转换为无约束优化问题

通过引入松弛变量和损失函数，我们将原始的有约束优化问题转化为一个无约束优化问题。目标是最小化以下损失函数：

$ \text{Loss}(w, b) = \frac{1}{2} \|w\|^2 + \dfrac{C}{n} \sum_{i=1}^{n} \max(0, 1 - y_i (w \cdot x_i + b)) $

这里，$C$ 是一个正则化参数，用来平衡间隔最大化和错误分类的权衡。

### 梯度下降法的使用

通过使用这个损失函数，我们可以用梯度下降法来优化权重和偏置。

### 手动实现 SVM（二分类软间隔）

#### 初始化参数

```python
def initialize_params(dim):
    w = np.zeros(dim)
    b = 0
    return w, b
```

#### 计算 SVM 损失

```python
def hinge_loss(w, b, X, y, C):
    n = X.shape[0]
    distances = 1 - y * (np.dot(X, w) + b)
    distances[distances < 0] = 0  # max(0, distance)
    hinge_loss = C * (np.sum(distances) / n)
    return 0.5 * np.dot(w, w) + hinge_loss
```

#### 梯度下降优化

```python
def sgd(X, y, learning_rate=0.001, C=1, epochs=1000):
    n_samples, n_features = X.shape
    w, b = initialize_params(n_features)
    for epoch in range(epochs):
        for i in range(n_samples):
            if y[i] * (np.dot(X[i], w) + b) < 1:
                w = w - learning_rate * (2 * w / n_samples - C * y[i] * X[i])
                b = b + learning_rate * C * y[i]
            else:
                w = w - learning_rate * (2 * w / n_samples)
    return w, b
```

#### 训练 SVM 模型

```python
w, b = sgd(X, y)
```

#### 预测函数

```python
def predict(X, w, b):
    return np.sign(np.dot(X, w) + b)
```

#### 计算准确率

```python
def accuracy(y_true, y_pred):
    return np.mean(y_true == y_pred)
```

#### 可视化结果

```python
import matplotlib.pyplot as plt

plt.scatter(X[:, 0], X[:, 1], c=y, s=50, cmap='autumn')
ax = plt.gca()
xlim = ax.get_xlim()
xx = np.linspace(xlim[0], xlim[1])
yy = - (w[0] * xx + b) / w[1]
plt.plot(xx, yy, 'k-')
plt.show()
```

### 伪代码

```shell
1. 初始化参数 w 和 b
2. 对于每个训练样本：
    1. 如果样本被错误分类（即 y_i (w . x_i + b) < 1）：
        1. 更新权重 w 和截距 b
3. 重复步骤2，直到收敛或达到最大迭代次数
4. 使用训练好的 w 和 b 进行预测
```
