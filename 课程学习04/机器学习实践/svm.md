 

# 支持向量机 (SVM) 学习笔记

---

## 1. SVM 核心思想：最大间隔分类器

支持向量机（Support Vector Machine, SVM）是一种功能强大且用途广泛的监督学习模型，擅长处理分类和回归任务。其核心思想是找到一个能将不同类别的数据点**最好地**分开的决策边界。

### 1.1 什么是SVM？

对于一个二分类问题，数据点在特征空间中是可分的。SVM的目标是在两类数据点之间找到一个**最优的超平面（Hyperplane）**，这个超平面不仅能将两类数据正确分开，而且距离最近的数据点的**间隔（Margin）**最大。

这个最大化的间隔使得模型具有更好的泛化能力和鲁棒性。



### 1.2 目标：最大化间隔

* **超平面**：在二维空间中是一条直线，三维空间中是一个平面。其数学表达式为 $w^T x + b = 0$。
* **间隔 (Margin)**：超平面两侧各有一条“边界线”，它们与超平面的距离相等，并且线上或线外没有任何数据点。这两条边界线之间的距离就是间隔。
* **SVM的目标**：就是找到一个合适的参数 $w$ 和 $b$，使得这个间隔最大化。



### 1.3 支持向量 (Support Vectors)

那些**距离超平面最近**并且刚好落在间隔边界上的数据点，被称为**支持向量**。这些点是定义最优超平面的关键，移动或删除非支持向量的数据点对最终的模型没有任何影响。这也是SVM高效和鲁棒的原因之一。



---

## 2. SVM 的数学原理

### 2.1 硬间隔 SVM (Hard-Margin)

硬间隔SVM适用于**线性完全可分**的数据集，即不存在任何噪声或异常点。

其目标是最大化间隔，这等价于最小化 $\frac{1}{2}\|w\|^2$，同时要满足所有数据点都被正确分类的约束条件。

**优化目标**：
$$
\min_{w,b} \frac{1}{2}\|w\|^2 \\
\text{s.t.} \quad y_i(w^T x_i + b) \ge 1, \quad i=1, 2, ..., N
$$
其中 $y_i$ 是第 $i$ 个样本的标签（+1 或 -1），$x_i$ 是其特征向量。约束条件 $y_i(w^T x_i + b) \ge 1$ 确保了所有点不仅被正确分类，而且都位于间隔边界之外。

### 2.2 软间隔 SVM (Soft-Margin)

在现实世界的数据中，数据往往不是完全线性可分的，或者存在一些噪声。硬间隔SVM会因无法满足所有约束而失效。为此，软间隔SVM被提出。

软间隔SVM允许一些数据点**不满足约束**（即越过间隔边界，甚至被错误分类），但会对这些“违规”的点施加一个惩罚。

**优化目标**：
$$
\min_{w,b,\xi} \frac{1}{2}\|w\|^2 + C \sum_{i=1}^{N} \xi_i \\
\text{s.t.} \quad y_i(w^T x_i + b) \ge 1 - \xi_i, \quad \xi_i \ge 0, \quad i=1, 2, ..., N
$$
* **松弛变量 $\xi_i$**：表示第 $i$ 个样本被允许“犯规”的程度。
* **惩罚参数 C**：是一个超参数，用于权衡 **“最大化间隔”** 和 **“最小化分类错误”** 这两个目标。
    * **C值很大**：对误分类的惩罚极高，模型会尽量将所有点都正确分类，导致间隔变窄，可能**过拟合**（低偏差，高方差）。
    * **C值很小**：对误分类的容忍度高，模型会专注于寻找更宽的间隔，即使牺牲一些点的分类准确性，可能**欠拟合**（高偏差，低方差）。

### 2.3 Hinge Loss (合页损失函数)

从另一个角度看，软间隔SVM的优化目标可以被视为在最小化一个叫做“Hinge Loss”的损失函数。

**Hinge Loss 公式**:
$$ L(y_i, f(x_i)) = \max(0, 1 - y_i(w^T x_i + b)) $$
这个损失函数意味着：
* 如果一个样本被正确分类，并且其函数间隔 $y_i(w^T x_i + b)$ 大于等于1，那么它的损失为0。
* 否则，它的损失就是 $1 - y_i(w^T x_i + b)$，与“犯规”的程度成正比。





---

## 3. 核技巧 (The Kernel Trick)

### 3.1 解决线性不可分问题

当数据在原始空间中线性不可分时，一种有效的方法是将数据从原始空间映射到一个**更高维的特征空间**，并期望数据在这个高维空间中变得线性可分。




### 3.2 核函数是什么？

直接进行高维映射和计算会带来巨大的计算开销（维度灾难）。**核技巧（Kernel Trick）**是一个绝妙的解决方案。

我们发现，在SVM的对偶问题求解过程中，所有计算都只涉及数据点之间的**点积**（$x_i^T x_j$）。核技巧的核心思想是：
> 定义一个**核函数 $K(x_i, x_j)$**，它能够直接计算出数据点在**高维空间中的点积**，而**无需真正执行高维映射**。
> $$ K(x_i, x_j) = \phi(x_i)^T \phi(x_j) $$

这样，我们就可以在原始低维空间中进行计算，却能达到在高维空间中寻找最优超平面的效果，极大地提高了计算效率。

### 3.3 常见核函数

* **线性核 (Linear Kernel)**：$K(x_i, x_j) = x_i^T x_j$
  * 实际上没有进行映射，主要用于线性可分的数据。

* **多项式核 (Polynomial Kernel)**：$K(x_i, x_j) = (\gamma x_i^T x_j + r)^d$
  * `d (degree)`：多项式的次数。
  * `r (coef0)`：常数项，影响高阶项与低阶项的权重。

* **高斯径向基函数核 (RBF Kernel)**：$K(x_i, x_j) = \exp(-\gamma \|x_i - x_j\|^2)$
  * 这是最常用、最强大的核函数之一，能映射到无限维空间。
  * gamma ($\gamma$)：控制了单个训练样本的影响范围。
    * **gamma值很小**：高斯核的“钟形”曲线很宽，单个样本的影响范围大，决策边界会更平滑（可能欠拟合）。
    * **gamma值很大**：高斯核的曲线很窄，单个样本的影响范围小，决策边界会更复杂、更不规则（可能过拟合）。

---

## 4. SVM 的优缺点总结

| 优点 | 缺点 |
| :--- | :--- |
| • 最终决策函数仅由少数支持向量确定，计算复杂性与支持向量数量有关，而非数据维度，避免了“维度灾难”。 | • 对大规模训练样本难以实施，因为求解过程涉及复杂的二次规划问题。 |
| • 基于结构风险最小化原则，泛化能力强，不易过拟合。 | • 解决多分类问题存在困难，通常需要采用“一对一”或“一对多”的组合策略。 |
| • 优化目标是凸优化问题，保证了局部最优解就是全局最优解。 | • 核函数的选择和参数的确定非常困难，这通常需要大量的实验和调参。 |
| • 模型具有较好的鲁棒性，增删非支持向量的样本对模型无影响。 | |

---

## 5. 在 Scikit-learn 中使用 SVM

`scikit-learn` 中主要有两个SVM分类器：`LinearSVC` 和 `SVC`。

* **`LinearSVC`**: 专门用于线性分类，基于`liblinear`库。它在处理大规模数据集时速度更快，但不支持核技巧。
* **`SVC`**: 功能更全面的分类器，基于`libsvm`库。它支持核技巧，可以处理线性和非线性问题。

### 5.1 实验代码示例

#### 实验一：线性SVM (Iris 数据集)

```python
import numpy as np
import matplotlib.pyplot as plt
from sklearn import datasets
from sklearn.preprocessing import StandardScaler
from sklearn.svm import LinearSVC

# 1. 导入数据并预处理
iris = datasets.load_iris()
X = iris.data
y = iris.target

# 为了可视化，仅选择前两个特征，并只对前两类进行分类
X = X[y<2, :2]
y = y[y<2]

# 2. 数据标准化
scaler = StandardScaler()
scaler.fit(X)
X_standard = scaler.transform(X)

# 3. 训练线性SVM模型
# C值设得非常大，趋近于硬间隔SVM
svc = LinearSVC(C=1e9, loss="hinge")
svc.fit(X_standard, y)

# 4. 可视化决策边界 (此部分代码省略）
```

#### 实验二：非线性SVM (Moons 数据集)

```python
from sklearn.datasets import make_moons
from sklearn.pipeline import Pipeline
from sklearn.preprocessing import PolynomialFeatures
from sklearn.svm import SVC

# 1. 生成非线性数据集
X, y = make_moons(n_samples=100, noise=0.2, random_state=42)

# 2. 使用多项式核的SVC进行训练
# Pipeline将数据标准化和SVC模型构建整合在一起
poly_kernel_svm_clf = Pipeline([
    ("scaler", StandardScaler()),
    ("svm_clf", SVC(kernel="poly", degree=3, coef0=1, C=5))
])
poly_kernel_svm_clf.fit(X, y)

# 3. 使用高斯RBF核的SVC进行训练
rbf_kernel_svm_clf = Pipeline([
    ("scaler", StandardScaler()),
    ("svm_clf", SVC(kernel="rbf", gamma=5, C=0.1))
])
rbf_kernel_svm_clf.fit(X, y)

# 4. 可视化结果 (此部分代码省略)
```