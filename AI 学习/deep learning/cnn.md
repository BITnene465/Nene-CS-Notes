# CNN中的常用计算公式

## 1. 卷积层计算公式

卷积层的输出大小可以通过以下公式计算：

$$
H_{out} = \frac{H_{in} + 2P - K}{S} + 1
$$

$$
W_{out} = \frac{W_{in} + 2P - K}{S} + 1
$$

其中：
- $H_{out}, W_{out}$ 是输出的高度和宽度
- $H_{in}, W_{in}$ 是输入的高度和宽度
- $P$ 是填充（Padding）的大小
- $K$ 是卷积核的大小
- $S$ 是步长（Stride）

## 2. 池化层计算公式

池化层的输出大小与卷积层类似，计算公式为：

$$
H_{out} = \frac{H_{in} + 2P - K}{S} + 1
$$

$$
W_{out} = \frac{W_{in} + 2P - K}{S} + 1
$$

其中参数含义与卷积层相同。

## 3. 参数数量计算公式

卷积层参数数量的计算公式为：

$$
\text{Params} = (K_H \times K_W \times C_{in} + 1) \times C_{out}
$$

其中：
- $K_H, K_W$ 是卷积核的高度和宽度
- $C_{in}$ 是输入通道数
- $C_{out}$ 是输出通道数
- $1$ 代表偏置项

## 4. 全连接层的参数数量

全连接层的参数数量可以通过以下公式计算：

$$
\text{Params} = (n_{in} + 1) \times n_{out}
$$

其中：
- $n_{in}$ 是输入的节点数
- $n_{out}$ 是输出的节点数
- $1$ 代表偏置项

## 5. 激活函数

常见的激活函数包括：
- **ReLU**：$f(x) = \max(0, x)$
- **Sigmoid**：$f(x) = \frac{1}{1 + e^{-x}}$
- **Tanh**：$f(x) = \frac{e^x - e^{-x}}{e^x + e^{-x}}$

激活函数决定了神经元的输出如何被传递到下一层。

## 6. 批归一化 (Batch Normalization)

批归一化层的公式为：

$$
\hat{x}^{(k)} = \frac{x^{(k)} - \mu_B}{\sqrt{\sigma_B^2 + \epsilon}}
$$

$$
y^{(k)} = \gamma \hat{x}^{(k)} + \beta
$$

其中：
- $\mu_B$ 和 $\sigma_B^2$ 是小批量数据的均值和方差
- $\epsilon$ 是防止除零的小常数
- $\gamma, \beta$ 是可学习的缩放和平移参数