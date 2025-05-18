# 语法分析

## Introduction

### 功能与作用
- **功能**：从左至右扫描Token流，按语法规则识别语句结构，输出语法树或错误信息。
- **阶段**：
  - **分析阶段**：词法分析 $\rightarrow$ 语法分析 $\rightarrow$ 中间代码生成  
  - **综合阶段**：中间代码优化 $\rightarrow$ 目标代码生成  
- **构造要素**：源程序串、源语言文法、语法范畴表示。

### 语法分析器工具
- 自动生成工具：Bison/Yacc、ANTLR、JavaCC等。
- 对应自动机：**确定性下推自动机**。



## 前置概念

### 文法形式化定义

文法 $G$ 是四元组：  
$$
G = (V_N, V_T, S, P)
$$

- $V_N$：非终结符集合（如 $\langle NUMBER \rangle$）  
- $V_T$：终结符集合（如 `0、1、2、3 ...`）  
- $S$：开始符号（$S \in V_N$）  
- $P$：产生式集合（如 $\langle 句子 \rangle \rightarrow \langle 主语 \rangle \langle 谓语 \rangle$）

### BNF表示法
- **元符号**：$\langle \rangle$（语法成分）、$\rightarrow$（定义为）、$|$（或）。
- **示例**：  
  $$
  \langle 句子 \rangle \rightarrow \langle 主语 \rangle \langle 谓语 \rangle \\  
  \langle 主语 \rangle \rightarrow \langle 形容词 \rangle \langle 名词 \rangle \\  
  \langle 形容词 \rangle \rightarrow 小 \mid 大
  $$

### 推导与归约

- **直接推导**：若存在产生式 $A \rightarrow \gamma$，则 $\alpha A \beta \Rightarrow \alpha \gamma \beta$。  
- **最左/最右推导**：总是替换最左（右）非终结符。  
- **规范推导**：最右推导，其逆为规范归约。

### 语法树与二义性
- **语法树**：句子结构的层次化图形表示。  

- **二义文法**：存在至少一个句子对应多棵语法树。  
  
  **示例**：  
  $$
  E \rightarrow E + E \mid E \times E \mid i  
  $$
  句子 $i + i \times i$ 有两棵语法树，需通过**优先级**和**结合性**消除二义。

### 文法的递归性

- **左递归**：产生式形如 $A \rightarrow A \alpha$。  
- **右递归**：产生式形如 $A \rightarrow \alpha A$。  



### 乔姆斯基文法分类

| 类型 | 别名               | 产生式形式                     | 自动机               | 示例语言              |
|------|--------------------|-------------------------------|----------------------|-----------------------|
| 0型  | 短语文法           | $\alpha \rightarrow \beta$（无限制） | 图灵机        | 任意可计算语言        |
| 1型  | 上下文有关文法     | $\alpha A \beta \rightarrow \alpha \gamma \beta$ | 线性有界自动机 |      |
| 2型  | 上下文无关文法     | $A \rightarrow \gamma$        | 非确定下推自动机     |          |
| 3型  | 正则文法（线性）   | 右线性：$A \rightarrow a B$；左线性：$A \rightarrow B a$ | 有限状态自动机 |          |



###  例题精选

#### 例题1：构造文法

**需求**：设计文法生成语言 $L = \{a^n b^n \mid n \geq 1\}$。 
**解答**：  
$$
S \rightarrow aSb \mid ab
$$

#### 例题2：消除二义性

**原文法**：  
$$
E \rightarrow E + E \mid E \times E \mid (E) \mid i
$$
**二义性**：$i + i \times i$ 的运算顺序不明确。 
**改进文法**（引入优先级）：  
$$
E \rightarrow E + T \mid T \\  
T \rightarrow T \times F \mid F \\  
F \rightarrow (E) \mid i  
$$

#### 例题3：符号串运算

**符号串集合乘积**：  
- $A = \{ab, c\}$，$B = \{d, ef\}$  
- $AB = \{abd, abef, cd, cef\}$  

**闭包运算**：  
- $A = \{0, 1\}$，则 $A^* = \{\epsilon, 0, 1, 00, 01, 10, 11, \dots\}$  





## 自上而下分析法

给定文法 G 和源程序串 \$ 。从 G 的开始符号 S 出发，通过反复使用产生式对句型中的非终结符进行替换（**推导**），逐步推导出 \$ 

- 使用**最左推导**

- 是一种产生的方法，面向目标的方法
- 自上而下分析是以**文法 G 的开始符号**为树的根结点，从根结点出发，对任何输入的字符串 \$，试图用尽一切可能的方法，**自上而下地为其建立一棵语法树**



### 不确定的自上而下分析法

不确定的原因：

- **假匹配**  -- 回溯（效率低，开销大）  <-- 解决方案：提取左公因子
- **G 的左递归** -- 无止境的匹配（死循环） <-- 解决方案： 消除G的左递归



### 消除文法的左递归

#### 消除直接左递归

假定关于非终结符 P 的规则为：
$$
P \rightarrow P\alpha | \beta  \qquad \alpha,\beta \in (V_T \cup V_N)^* 
$$
其中，$\beta$ 不以 P 开头。则可以将 P 改写为等价的**非直接左递归形式**：
$$
P \rightarrow \beta P'  \\
P' \rightarrow \alpha P' | \epsilon
$$
<img src="Syntactic Analysis.assets/image-20250422144223171.png" alt="image-20250422144223171" style="zoom:33%;" />

#### 消除间接左递归

有些文法表面上不具有左递归性，但是却隐含左递归:

<img src="Syntactic Analysis.assets/image-20250422150122891.png" alt="image-20250422150122891" style="zoom: 50%;" />

**方法论**：

1. 将间接左递归文法改写成直接左递归文法
2. 使用**消除直接左递归文法**的方法改写文法



#### 消除左递归算法

**输入**: 含左递归的文法 G 
**输出**: 等价的无左递归文法 G'

---
1. 将 G 的非终结符按固定顺序排列为 $A_1, A_2, ..., A_n$  
2. **for** 每个非终结符 $A_i$ (从 $A_1$ 到 $A_n$) **do**: 
   a. **for** 每个非终结符 $A_j$ (从 $A_1$ 到 $A_{i-1}$) **do**: 
      i. **if** 存在产生式 $A_i → A_j \gamma$ **then**: 
         - 将 $A_j$ 的所有产生式  $A_j → δ_1 | δ_2 | ... | δ_k $ 代入 
               - 替换原产生式为 $A_i → \delta_1 \gamma | δ_2 \gamma | ... | δ_k \gamma $
             b. 消除 $A_i$ 的直接左递归: 
         i. 将其产生式分为两类: 
               - 左递归形式: $A_i → A_i \alpha_1 | ... | A_i \alpha_m $
                     - 非左递归形式: $A_i → \beta_1 | ... | \beta_p $
            ii. **if** 存在左递归 **then**: 
                     - 引入新非终结符 $A_i' $
                           - 重写为: 
             $A_i  → \beta_1 A_i' | ... | \beta_p A_i' $
             $A_i' → \alpha_1A_i' | ... | \alpha_mA_i' | ε  $
3. 删除不可达产生式和冗余规则  
4. **return** 更新后的文法 G'  

----



**一个实例：**

<img src="Syntactic Analysis.assets/image-20250422153241069.png" alt="image-20250422153241069" style="zoom: 33%;" />

<img src="Syntactic Analysis.assets/image-20250422153331776.png" alt="image-20250422153331776" style="zoom: 33%;" />



### 消除回溯（FIRST集）

 设**文法G是二型文法且不含左递归**，则G中的非终结符的每个候选式 $\alpha $的终结首符集 $FIRST(\alpha)$ 为
$$
FIRST(\alpha) = \{ a | \alpha \Rightarrow^* a...... , \ a\in V_T\}
$$
若 $\alpha \Rightarrow^* \epsilon$ , 则 $\epsilon \in FIRST(\alpha)$ 

<img src="Syntactic Analysis.assets/image-20250422155832360.png" alt="image-20250422155832360" style="zoom:50%;" />

> **如果满足不带回溯的条件：**当前扫描的字符为 $a$ ,若有 $a∈FIRST(\alpha_i)$ ,则可唯一选取 $A \rightarrow \alpha_i$ 进行推导。

#### 提取左公因子

如果候选式的 FIRST集 彼此之间有交集，则是因为候选式有**左公因子**，可以提取后再作处理

<img src="Syntactic Analysis.assets/image-20250422163525012.png" alt="image-20250422163525012" style="zoom: 50%;" />

<img src="Syntactic Analysis.assets/image-20250422163430861.png" alt="image-20250422163430861" style="zoom: 50%;" />

#### 计算 FIRST 集的算法

<img src="Syntactic Analysis.assets/image-20250422161746198.png" alt="image-20250422161746198" style="zoom: 50%;" />

<img src="Syntactic Analysis.assets/image-20250422161042563.png" alt="image-20250422161042563" style="zoom: 50%;" />



### LL(1) 分析器

LL(1):

- L : 扫描模式为**从左到右**
- L : 分析模式为**最左推导**
- 1 : 在分析中**最多向前看 1 个输入字符**

**LL(1) 分析器结构图：**

<img src="Syntactic Analysis.assets/image-20250422170130914.png" alt="image-20250422170130914" style="zoom:50%;" />



#### FOLLOW 集

 设**文法G是二型文法**，S是开始符号，对于文法G的任何非终结符A
$$
FOLLOW(A) = \{ a | S \Rightarrow^* ...Aa... , \ a\in V_T\}
$$

- 若 $S \Rightarrow^* ...A$ , 则 $ \#\in FOLLOW(A)$ 
- FOLLOW(A) 的含义为在文法G的一切句型中，能够紧跟在非终结符A后面的一切终结符或 “#”
- **"#" 是句子的右结束符**



**如何构造？**

1. **构造算法1（迭代法）：**

<img src="Syntactic Analysis.assets/image-20250422202818265.png" alt="image-20250422202818265" style="zoom:50%;" />



2. **构造算法2（关系图法）：**





#### 构造 LL(1) 分析表

<img src="Syntactic Analysis.assets/image-20250422210624893.png" alt="image-20250422210624893" style="zoom:50%;" />





### LL(1) 文法

一部文法 G，若它的LL(1)分析表M不含**多重定义入口**，则称它是一个LL(1)文法。由LL(1)文法产生的语言成为LL(1)语言。

**如何判断？**



**如何改写成 LL(1) 文法？**





## 自下而上分析法



































