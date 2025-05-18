# matplotlib
> [教程](https://www.runoob.com/matplotlib/matplotlib-tutorial.html)
>
> [【Python】解决使用 plt.savefig 保存图片时一片空白_spyder 保存图片空白_secsilm的博客-CSDN博客](https://blog.csdn.net/u010099080/article/details/52912439)
>
> [matplotlib 设置坐标轴位置/方向 y轴反向_ax.invert_yaxis()__沥川往事的博客-CSDN博客](https://blog.csdn.net/yuejisuo1948/article/details/81023125)

## pyplot子库

> [官网教程](https://matplotlib.org/stable/api/_as_gen/matplotlib.pyplot.plot.html)


`plt.plot` 画折线图或点阵图

### 绘图标记 & 绘图线

参数集合： `fmt` 参数
`fmt = '[marker][linestyle][color]'`
例如 `o:r` 表示实心圆标记，虚线，红色线

[对应表格](https://www.runoob.com/matplotlib/matplotlib-marker.html)

> `marker` 参数： 标记的样式
> `markersize` 简写为 `ms` : 定义标记的大小
> `markerfacecolor` 简写为 `mfc` : 定义标记内部的颜色
> `markeredgecolor` 简写为 `mec` : 定义标记边框的颜色

> `linestyle` 简写为 `ls` ： 线的样式
> `color` 简写为 `c` ：线的颜色
> `linewidth` 简写为 `lw` ：线的宽度

### 轴标签 & 标题

**三个函数**
`plt.title()`
`plt.xlabel()`
`plt.ylabel()`

**关于定位：**
`title()` 方法提供了 loc 参数来设置标题显示的位置，可以设置为: 'left', 'right', 和 'center'， 默认值为 'center'。

`xlabel()` 方法提供了 loc 参数来设置 x 轴显示的位置，可以设置为: 'left', 'right', 和 'center'， 默认值为 'center'。

`ylabel()` 方法提供了 loc 参数来设置 y 轴显示的位置，可以设置为: 'bottom', 'top', 和 'center'， 默认值为 'center'。


**如何使用中文字体？**

使用 `fontproperties` 参数 
使用 `fomtproperties = 'SimHei'` 即可使用微软黑体

*我们可以打印系统自带的字体*
```python
from matplotlib import pyplot as plt
import matplotlib
a=sorted([f.name for f in matplotlib.font_manager.fontManager.ttflist])

for i in a:
    print(i)
```

*更改全局字体：*
`plt.rcParams['font.family']=['SimHei']`

*设置自己的字体字典，并且在需要的时候调用*
```python
import numpy as np 
from matplotlib import pyplot as plt 
import matplotlib
 
# fname 为 你下载的字体库路径，注意 SourceHanSansSC-Bold.otf 字体的路径，size 参数设置字体大小
zhfont1 = matplotlib.font_manager.FontProperties(fname="SourceHanSansSC-Bold.otf", size=18) 
font1 = {'color':'blue','size':20}
font2 = {'color':'darkred','size':15}
x = np.arange(1,11) 
y =  2  * x +  5 

# fontdict 可以使用 css 来设置字体样式
plt.title("菜鸟教程 - 测试", fontproperties=zhfont1, fontdict = font1) 
 
# fontproperties 设置中文显示，fontsize 设置字体大小
plt.xlabel("x 轴", fontproperties=zhfont1)
plt.ylabel("y 轴", fontproperties=zhfont1)
plt.plot(x,y) 
plt.show()
```

### 曲线标签显示

[blog](https://juejin.cn/s/plt.plot%E5%8F%82%E6%95%B0label)

### 网格线

`matplotlib.pyplot.grid(visable=None, which='major', axis='both', )` 
参数说明：
- visable:可选参数，默认为None，true为显示网格线，false为不显示，如果设置 **kwargs 参数，则值为 true
- which:可选参数，可选值为'major','minor'和'both',默认为'major',表示应用更改的网格线
- axis:可选参数，设置哪个方向的网格线，可以是取'both'(默认),'x'或'y'
- **kwargs:可选参数，设置网格样式，color='r',linestyle='-',linewidth=2 等等一些参数

[plt网格线](https://www.runoob.com/matplotlib/matplotlib-grid.html)

### 多图绘制

#### GridSpec 类 + plt.subplot()绘图

```python
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec
def func1(x,alpha=-0.1,c1=1,c2=1):
    return np.exp(alpha*x)*(c1*x+c2)
def func2(x,alpha1=0.5,alpha2=-0.5,c1=1,c2=1):
    return c1*np.exp(alpha1*x)+c2*np.exp(alpha2*x)
def func3(x,alpha=1,beta=1,c1=1,c2=1):
    return np.exp(alpha*x)*(c1*np.sin(x)+c2*np.cos(x))
def func4(x,c1=1,c2=1):
    return c1*np.sin(x)+c2*np.cos(x)
def main():
    gs = gridspec.GridSpec(3,3)
    
    ax1 = plt.subplot(gs[0,:])
    ax2 = plt.subplot(gs[1,:])
    ax3 = plt.subplot(gs[2,:-1])
    ax4 = plt.subplot(gs[2,2])
    
    # 开始画图
    x = np.arange(0,4*np.pi,0.05)
    ax1.plot(x,func1(x))
    ax2.plot(x,func2(x))
    ax3.plot(x,func3(x))
    ax4.plot(x,func4(x))
   
    plt.title("多图绘制",fontproperties='SimHei')
    plt.show()
    return
main()
```



#### plt.subplot2grid()方法





#### plt.subplot() 方法

`plt.subplot` 用于创建单个子图，通常用于手动控制每个子图的位置。

**语法：**
`plt.subplot(nrows, ncols, index)`

- **nrows**：子图的行数
- **ncols**：子图的列数
- **index**：当前子图的编号，从 1 开始，从左到右、从上到下排列

**示例：**

```python
import matplotlib.pyplot as plt

# 创建2x2的子图布局
plt.subplot(2, 2, 1)  # 第1个子图
plt.plot([1, 2, 3], [1, 4, 9])
plt.title("Subplot 1")

plt.subplot(2, 2, 2)  # 第2个子图
plt.plot([1, 2, 3], [1, 2, 3])
plt.title("Subplot 2")

plt.subplot(2, 2, 3)  # 第3个子图
plt.plot([1, 2, 3], [3, 2, 1])
plt.title("Subplot 3")

plt.subplot(2, 2, 4)  # 第4个子图
plt.plot([1, 2, 3], [9, 4, 1])
plt.title("Subplot 4")

plt.tight_layout()  # 调整子图布局，避免重叠
plt.show()
```





#### subplots()方法



`plt.subplots` 更为灵活和常用。它一次性创建多个子图，并返回一个包含所有子图的 `Figure` 对象和 `Axes` 对象数组。

**语法：** `fig, axes = plt.subplots(nrows, ncols, figsize=(width, height))`

- **nrows**：子图的行数
- **ncols**：子图的列数
- **figsize**：控制整个绘图区域的宽度和高度

`subplots` 返回两个对象：

- **fig**：`Figure` 对象，代表整个图像
- **axes**：`Axes` 对象或数组，代表每个子图

**示例：**

```python
import matplotlib.pyplot as plt

# 创建2x2的子图布局
fig, axes = plt.subplots(2, 2, figsize=(10, 8))

# 绘制第1个子图
axes[0, 0].plot([1, 2, 3], [1, 4, 9])
axes[0, 0].set_title("Subplot 1")

# 绘制第2个子图
axes[0, 1].plot([1, 2, 3], [1, 2, 3])
axes[0, 1].set_title("Subplot 2")

# 绘制第3个子图
axes[1, 0].plot([1, 2, 3], [3, 2, 1])
axes[1, 0].set_title("Subplot 3")

# 绘制第4个子图
axes[1, 1].plot([1, 2, 3], [9, 4, 1])
axes[1, 1].set_title("Subplot 4")

plt.tight_layout()  # 自动调整子图的布局
plt.show()
```

#### `subplots` 的更多功能

- **共享轴**：可以使用 `sharex=True` 或 `sharey=True` 来共享子图的 X 或 Y 轴
- **单个子图**：对于 `1x1` 子图，`axes` 不再是数组，而是单个 `Axes` 对象

**示例（共享 X 轴）：**

```python
fig, axes = plt.subplots(2, 1, sharex=True, figsize=(8, 6))
axes[0].plot([1, 2, 3], [1, 4, 9])
axes[1].plot([1, 2, 3], [9, 4, 1])
plt.show()
```



>  注意下面这个示例中 `subplots` 方法的使用

```python
def act_fn_test():
    activate_fn_dict = {"ReLU": nn.ReLU, "LeakyReLU": nn.LeakyReLU, "Sigmoid": nn.Sigmoid, "Tanh": nn.Tanh}
    conv1_params = {'in_channels': 1, 'out_channels': 32, 'kernel_size': 5, 'stride': 1, 'padding': 2}
    conv2_params = {'in_channels': 32, 'out_channels': 64, 'kernel_size': 5, 'stride': 1, 'padding': 2}
    pool_params = {'kernel_size': 2, 'stride': 2}
    BATCH_SIZE = 100
    epochs=100
    
    # 准备绘制图像
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(14, 6))
    ax1.set_title('Training Loss for Different Activation Functions')
    ax1.set_xlabel('Epochs')
    ax1.set_ylabel('Loss')
    
    ax2.set_title('Test Accuracy for Different Activation Functions')
    ax2.set_xlabel('Epochs')
    ax2.set_ylabel('Accuracy')
    
    for fn_str, fn in activate_fn_dict.items():
        print("activate funtion: " + fn_str)
        # 加载数据
        x_train, y_train, x_test, y_test = load_data()  # 你需要定义数据加载函数
        # 设置模型、损失函数和优化器
        model = Cnn_net(activation_fn=fn, conv1_params=conv1_params, conv2_params=conv2_params, pool_params=pool_params).to(device)
        loss_function = nn.CrossEntropyLoss()
        optimizer = torch.optim.Adam(model.parameters(), lr=0.001)
        # 训练模型
        train_loss, test_acc = train(x_train, y_train, x_test, y_test, BATCH_SIZE, model, loss_function, 		optimizer, epochs=epochs)
        
        ax1.plot(range(1, epochs + 1), train_loss, label=fn_str)
        ax2.plot(range(1, epochs + 1), test_acc, label=fn_str)
    
    ax1.legend()
    ax2.legend()
    plt.tight_layout()
    plt.show()
```



### 绘制散点图

scatter
`matplotlib.pyplot.scatter(x, y, s=None, c=None, marker=None, cmap=None, norm=None, vmin=None, vmax=None, alpha=None, linewidths=None, *, edgecolors=None, plotnonfinite=False, data=None, **kwargs)`

示例：
```python
import matplotlib.pyplot as plt
import numpy as np

x = np.array([1, 2, 3, 4, 5, 6, 7, 8])
y = np.array([1, 4, 9, 16, 7, 11, 23, 18])

plt.scatter(x, y)
plt.show()
```

[绘制散点图](https://www.runoob.com/matplotlib/matplotlib-scatter.html)

### 绘制柱形图

`matplotlib.pyplot.bar(x, height, width=0.8, bottom=None, *, align='center', data=None, **kwargs)`

**水平柱形图**
```python
import matplotlib.pyplot as plt
import numpy as np

x = np.array(["Runoob-1", "Runoob-2", "Runoob-3", "C-RUNOOB"])
y = np.array([12, 22, 6, 18])

plt.barh(x,y)
plt.show()
```

`matplotlib.pyplot.barh(x, height, width, bottom=None, *, align='center', data=None, **kwargs)`

此处要设置每个条的宽度要设置 height 才行（

**垂直柱形图：**
```python
import matplotlib.pyplot as plt
import numpy as np

x = np.array(["Runoob-1", "Runoob-2", "Runoob-3", "C-RUNOOB"])
y = np.array([12, 22, 6, 18])

plt.barh(x,y)
plt.show()
```

### 绘制饼图

`matplotlib.pyplot.pie(x, explode=None, labels=None, colors=None, autopct=None, pctdistance=0.6, shadow=False, labeldistance=1.1, startangle=0, radius=1, counterclock=True, wedgeprops=None, textprops=None, center=0, 0, frame=False, rotatelabels=False, *, normalize=None, data=None)[source]`

[饼图](https://www.runoob.com/matplotlib/matplotlib-pie.html)

### 绘制直方图

[直方图](https://www.runoob.com/matplotlib/matplotlib-hist.html)

**概率统计中使用较多**
`matplotlib.pyplot.hist(x, bins=None, range=None, density=False, weights=None, cumulative=False, bottom=None, histtype='bar', align='mid', orientation='vertical', rwidth=None, log=False, color=None, label=None, stacked=False, **kwargs)`

|参数|说明|
|:---|:---|
|x|表示要绘制直方图的数据，可以是一个一维数组或列表|
|bins|可选，表示直方图的箱数。默认为10|
|range|可选，表示直方图的值域范围，可以是一个二元组或列表，默认为None，即使用数据中的最大之和最小值|
|density|可选，表示是否将直方图归一化。默认为false，即直方图的高度为每个箱子内的样本数，而不是频率或概率密度|
|weights|可选，表示每个数据点的权重，默认为None|
|cumulative|可选，表示是否绘制累积分布图，默认为false|
|bottom|可选，表示直方图的起始高度，默认为None|
|histtype|可选，表示直方图的类型，'bar','barstacked','step','stepfilled',默认为'bar'|
|align|可选，箱子的对齐方式，可选'left','mid','right',默认为'mid'|
|orientation|可选，表示直方图的方向，可以为'vertical','horizontal',默认为'vertical'|
|rwidth|可选，表示每个箱子的宽度，默认为None|
|log|可选，表示是否在y轴上使用对数刻度，默认为None|
|color|可选|
|label|可选|
|stacked|可选，表示是否堆叠不同的直方图，默认为false|
|**kwargs|可选参数，表示其他绘图参数|

示例：
```python
import matplotlib.pyplot as plt
import numpy as np

# 生成一组随机数据
data = np.random.randn(1000)

# 绘制直方图
plt.hist(data, bins=30, color='skyblue', alpha=0.8)

# 设置图表属性
plt.title('RUNOOB hist() Test')
plt.xlabel('Value')
plt.ylabel('Frequency')

# 显示图表
plt.show()
```

多个直方图一起绘制
```python
import matplotlib.pyplot as plt
import numpy as np

# 生成三组随机数据
data1 = np.random.normal(0, 1, 1000)
data2 = np.random.normal(2, 1, 1000)
data3 = np.random.normal(-2, 1, 1000)

# 绘制直方图
plt.hist(data1, bins=30, alpha=0.5, label='Data 1')
plt.hist(data2, bins=30, alpha=0.5, label='Data 2')
plt.hist(data3, bins=30, alpha=0.5, label='Data 3')

# 设置图表属性
plt.title('RUNOOB hist() TEST')
plt.xlabel('Value')
plt.ylabel('Frequency')
plt.legend()

# 显示图表
plt.show()
```

## 曲线拟合

[知乎文章](https://zhuanlan.zhihu.com/p/122702657)

polynomial fit 比较方便，直接使用numpy库的两个方法 **np.polyfit()** 和 **np.poly1d()** 即可

对于一般的光滑拟合:
