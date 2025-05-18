# Physical Layer

##  Introduction

**物理层任务：实现相邻节点之间二进制传输**



## 《通信基础》前置知识

### 基本概念

<img src="Physical Layer.assets/image-20250406164710848.png" alt="image-20250406164710848" style="zoom:50%;" />



**码元（symbol）**：码元是数字通信中表示一个基本信号单元的最小单位，可以携带一个或多个比特的信息。

- 一个码元可以对应不同的比特数，具体取决于调制方式（调制就是将连续的模拟信号编码为离散的数字信号?）。
- **例子**：
  - 二进制调制（如 ASK、FSK）：1 个码元 = 1 比特（0 或 1）。
  - 四进制调制（如 QPSK）：1 个码元 = 2 比特（00、01、10、11）。
  - 16-QAM 调制：1 个码元 = 4 比特。



**波特率(baud rate)**: 每秒传输多少 **码元**，单位： **baud**





### 信道的极限容量

<img src="Physical Layer.assets/image-20250406171736509.png" alt="image-20250406171736509" style="zoom:50%;" />

#### Nyquist Theorem

对于一个 **理想低通信道**（没有噪声、带宽有限的信道），**极限波特率** 为 
$$
max\_baud\_rate = 2  W
$$

- W 为**信道的频率带宽**（单位 Hz）

- 单位为  **码元/s** **（baud）**

- 极限比特率：

  - $$
    max\_bit\_rate = max\_baud\_rate \cdot log_2 K 
    $$

  -  K 为每个码元携带的 bit 数



#### Shannon Theorem

对于一个 **有噪声的实际信道**（带宽有限且存在噪声），**极限比特率** 为  
$$
C = W \cdot \log_2 (1 + \text{SNR})
$$

- **W**：信道频率带宽（单位 Hz）  
- **SNR**：信噪比（线性值）  
- **单位**：**bit/s（bps）**  



####  信噪比（SNR）

- **定义**：信号功率与噪声功率的比值，即  
  $$
  \text{SNR (线性值)} = \frac{\text{信号功率}}{\text{噪声功率}}
  $$
  
- **分贝（dB）转换**：  
  $$
  \text{SNR (dB)} = 10 \cdot \log_{10} (\text{SNR (线性值)})
  $$

**tips:** 我们一般是用分贝值来描述信噪比，但是带入 Shannon 定理中需要转换为线性值



### 编码 & 调制

<img src="Physical Layer.assets/image-20250406172329954.png" alt="image-20250406172329954" style="zoom:50%;" />

#### 基本框架

<img src="Physical Layer.assets/image-20250406172853848.png" alt="image-20250406172853848" style="zoom:50%;" />

#### 常见编码方法 （考点）

编码： 将二进制数据变成数字信号

<img src="Physical Layer.assets/image-20250406174105488.png" alt="image-20250406174105488" style="zoom:50%;" />



#### 常见调制方式

调制：将二进制数据变成模拟信号

<img src="Physical Layer.assets/image-20250406174821568.png" alt="image-20250406174821568" style="zoom:50%;" />

以上展示的都是两种信号，实际上每种方式都可以用类似的方法表示更多的信号

常用的调制方式还有**正交幅度调制（QAM）**

<img src="Physical Layer.assets/image-20250406175241051.png" alt="image-20250406175241051" style="zoom:50%;" />



## 物理层传输

### 传输介质





### 物理层设备





## 例题

### 奈奎斯特定理

<img src="Physical Layer.assets/image-20250406174339783.png" alt="image-20250406174339783" style="zoom:50%;" />



### 香农定理

<img src="Physical Layer.assets/image-20250406170715532.png" alt="image-20250406170715532" style="zoom:50%;" />



### 编码

题设要求：NRZI和差分Manchester都从 -1 开始

<img src="Physical Layer.assets/image-20250406180338534.png" alt="image-20250406180338534"  />









