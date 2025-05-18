# 7 二元关系



## Part 7.1 有序对和笛卡尔积

定义 7.1  有序对的定义



定义 7.2  笛卡尔积的定义



补充 7.2 笛卡尔积的运算性质：







## Part 7.2 二元关系

定义 7.3：二元关系的定义（二元关系R是一个**特化的集合**）



定义 7.4：

$A \times B$ 的所有子集所确定的二元关系称为**从A到B的二元关系**，特别地，$A=B$ 时，称为A上的二元关系



定义 7.5:

对于一个非空集合A,定义：
$$
\begin{align}
	& E_A = \{<x,y>|x\in A\wedge y\in A\} = A \times A \\
	& I_A = \{<x,x>|x\in A \}  \\
\end{align}
$$


## Part 7.3 关系的运算

定义 7.6：









## Part 7.4 关系的性质

定义 7.11：

(1) 若 $\forall x(x\in A \rightarrow <x,x>\in R)$ ,则称关系R在A上是自反的。

(2) 若 $\forall x(x\in A \rightarrow <x,x>\not \in R )$ ,则称关系R在A上是反自反的。



定义 7.12：

(1) 若 $\forall x\forall y(x,y\in A\wedge <x,y>\in R \rightarrow <y,x> \in R)$ ，则称关系R在A上是对称的。

(2) 若 $\forall x\forall y(x,y\in A\wedge <x,y>\in R\wedge<y,x>\in R \rightarrow x=y)$ ,则称关系R在A上是反对称的。

​           

定义 7.13:

若 $\forall x\forall y \forall z(x,y,z\in A \wedge <x,y>\in R \wedge <y,z> \in R\rightarrow <x,z>\in R)$ ,则称关系R在A上有传递性。



定理 7.10:

关系R是定义在非空集合A上的关系

1. $R是自反的 \Leftrightarrow I_{A} \subseteq R$
2. $R是反自反的 \Leftrightarrow I_{A} \cap R = \emptyset$
3. $R是对称的 \Leftrightarrow R = R^{-1}$
4. $R是反对称的 \Leftrightarrow R \cap R^{-1} \subseteq I_{A}$
5. $R是传递的 \Leftrightarrow R^{2} \subseteq R$



 



## Part 7.5 闭包

定义 7.14: 

设$R$是非空集合$A$上的关系，$R$的自反（或对称、传递）闭包是$A$上的关系$R’$,使得$R’$满足以下条件：

1. $R’$ 是自反的（对称的或传递的）
2. $R \subseteq R'$
3. 对$A$上任何**包含**$R$的自反（对称或传递）关系 $R’’$ 有 $R' \subseteq R''$

>  tips: **某种条件下极小的关系**



定理 7.10:

设$R$是$A$上的关系，则有：

1. $r(R) = R\cup R^0$
2. $s(R) = R\cup R^{-1}$
3. $r(R) = \bigcup_{i=1}^{\infty} R^i$

> tips: 对于有限集A上的关系，3中的式子项数也是有限的，**R的幂次有阶**

**定理7.10的关系矩阵形式和图语言的描述：**



定理 7.11:

R是非空集合A上的关系，则有

1. $R 是自反的 \Leftrightarrow R = r(R)$
2. $R 是对称的 \Leftrightarrow R = t(R)$
3. $R 是传递的 \Leftrightarrow R = s(R)$



定理 7.12：

1. $R \subseteq r(R)$
2. $R \subseteq s(R)$
3. $R \subseteq t(R)$



定理 7.13:

R是非空集合A上的关系

1. 如果R是自反的，则 $s(R),t(R)$ 也是自反的
2. 如果R是对称的，则 $r(R),t(R)$ 也是对称的
3. 如果R是传递的，则 $r(R)$ 也是传递的

> tips: 如果需要进行多个闭包运算，$tsr(R) = rts(R) = trs(R)$ ,需要按照一定顺序





## Part 7.6 等价关系与划分

**符号**

>  $\sim $  `\sim`    $\simeq$  `\simeq`

定义 7.15：

一个关系满足**自反、对称和传递**，那么称为**等价关系**

例如: $I_A$ 



定义 7.16:

设R是A上的等价关系，$\forall x \in A$,令
$$
{[x]}_R = \{y \ | y \in A \wedge y \mathit{R} x \}
$$
或者也可以记作 $[x]$ 或 $\overline{x}_R$ , 被称为**x关于关系R的等价类**





定理 7.14：

> **集合元素关于一个关系的所有等价类是该集合的一个划分**

关系R定义在非空集合A上

1. $x \in A \Rightarrow [x] \neq \empty$
2. $x \in A \wedge y\in A \wedge xRy \Rightarrow [x] = [y] $
3. $x \in A \wedge y\in A \wedge x\not Ry \Rightarrow [x] \cap[y] = \empty $
4. $\bigcup\{[x] \ | \ x \in A \} = A$



定义 7.17： 商集

R是定义在非空集合A上的关系，集合A上所有关于R的等价类组成的集合称为A对关系R的商集
$$
\mathit{A/R} = \{[x]_{\mathit{R}} \ | \ x \in A \}
$$
例子：

设$A = \{1,2,3,\dots, 8\}$,则A对于模3等价关系R的商集为  $\mathit{A/R} = \{ \{1,4,7\}, \{2,5,8\}, \{3,6\} \}$







定义 7.18： 划分

A是非空集合，$\pi$ 是A的子集镞（$\pi \subseteq P(A)$），如果满足：

- $\empty \not \in \pi$
- $\forall x,y \in \pi, x\cap y = \empty$
- $\bigcup_{x \in \pi}x = A$

则称$\pi$ 是集合A的一个**划分**，$\pi$ 中的元素被称为集合A的**划分块**





定理 7.15:

集合A上的一个**等价关系**R确定A的一个划分，该划分即为商集$\mathit{A/R}$



定理 7.16:

集合A上的一个划分$\pi$ ,可以唯一确定集合A上的一个**等价关系**R



定理 7.17:

由定理7.15 和 定理7.16,可知**集合划分和定义在集合上的等价关系一一映射**

> 对于集合A，A有n个元素，则A的**子集镞个数** 为 $2^{2^n}$，**划分个数**，**A上的等价关系**个数为 $$ 





## Part 7.7 偏序关系

**符号**

> $\succ$  `\succ`   $\prec$  `\prec`   $\preccurlyeq$  `\preccurlyeq`  $\preceq$  `\preceq`

 定义 7.19：

非空集合A上满足**自反、反对称和传递**的关系，称为**偏序关系**，记作 $\preccurlyeq$

例子： $I_A$ , 小于等于关系，包含关系， 整除关系 等



定义 7.20：





定义 7.21：



定义 7.22:

集合A和A上的偏序关系R一起叫做**偏序集**，记作 $<A,R>$

例子：$<\Z, \leq>, <P(A),R_{\subseteq}>$



`哈斯图` ： 利用偏序关系的自反、反对称和传递性进行简化的关系图 

哈斯图实例：





定义 7.23：

设$<A, \preccurlyeq>$ 是一个偏序集,$\forall x,y \in A$ ,如果 $x\prec y$ 且不存在 $z \in A$,使得 $x\prec z \prec y$ ，则称 y 覆盖 x

例子：整除关系下，易知一个素数 p 覆盖自己



定义 7.24：

设$<A,\preccurlyeq>$ 为偏序集，$B \subseteq A$,$y \in B$

1. 如果$\forall x(x\in B \rightarrow y\preccurlyeq x)$,则称 y 为 B中的**最小元**
2. 如果$\forall x(x\in B \wedge x \preccurlyeq y \rightarrow x = y )$,则称 y 为 A中的**极小元**
3. **最大元**和**极大元**的定义同理

一些性质列举：

- 最小元一定是极小元
- 最小元最多一个，可能不存在
- 极小元一定存在（？），可能存在多个

> 因为偏序集中不一定任意两个元素都可以比较，二者定义的区别就在于此

