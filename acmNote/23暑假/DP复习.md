# DP复习

## 题目

### A

转移方程：$f_{i,j}$表示选出的物品a属性不超过i，c属性的和恰好为j时，b[i]最小值的最大值。

$$
f_{i,j} = max\{f_{i-1,j},min\{f_{i-1,j-a_{i}},b_{i}\}\}
$$

$a_i$ 数据较大，但是 N 较小，可以离散化

查询太多，排序，然后离线算法

### B

### T

$ v_i 为村庄在数轴的坐标，按照升序排列$

$dis(i,j)表示村庄i到村庄j，插入一个邮局，其最小距离的之和的最小值$

## 状态压缩

典例：TSP问题

```cpp
lowbit(x):  x&(-x);
while(x): x&(x-1) , cnt++;
```

## 决策单调DP

解决方程1：

$$
f_{i,k} = min_{1\leq j < i}\{f_{j,k-1}+g(j,i)\}  \\
或  \qquad  f'_i = min_{1\leq j<i}\{f_j+g(j,i)\}
$$

***静态转移***，即当前一轮的DP值不会立刻转移

**在已知决策单调的情况下**，可以使用：二分栈  或   分治法（推荐）    时间复杂度$O(n\log n)$

```cpp
// 分治法 示例代码 //
int s[N];
void solve(int l,int r,int L,int R)   // [l,r]是待测区间 , [L,R]是搜索区间
{
    if(l>r) return;
    int mid = l +(r-l>>1);
    int id = -1;
    for(int i=L;i<=min(R,mid-1);i++)
        if(id==-1||(double)a[i]+sqr[mid-i]<(double)a[id]+sqr[mid-id])  id=i;   // 找到mid的最佳决策点
    s[mid] = id;
    solve(l,mid-1,L,id);
    solve(mid+1,r,id,R);
}
```

解决方程2：

$$
f_{i,k} =min_{1\leq j<i}\{f_{j,k}+g(j,i)\})
$$

***动态转移***

可以使用 二分栈 ， 但是无法使用分治法了

单调决策DP下的 二分栈 算法流程：

首先，将 i 与队尾的决策点比较转移到左端点谁更优，即fi + g(i, Lj) 与 fj + g(j, Lj) 谁更优。若 i 更优，那么由决策单调性
知，[Lj, Rj] 中都是 i 更优，直接删去队尾即可！
反之，如果 j 更优，那么，这说明，在 [Lj, Rj] 中有一个点开始，i 将比 j 更优，这可以用 **二分法** 找到。

wqs二分

## 斜率DP

- 动态维护凸包
- 李超线段树（推荐)

### 李超线段树


***1. 例题：APOI2014 序列分割***

注意每个数的贡献

设状态：f[i][j] 表示前 i 个数分成 j+1 段的费用最小值， f[n][k] 即为题目所求

转移方程：

$$
f_{i,j} = min_{1\leq t \leq i-1}(f_{t,j-1}+S_t(S_i-S_t))  \quad 其中，S_i = \sum_{j=1}^ia_j 
$$






## 前缀和优化

例题：

**基站选址**

$$
f_{i,j} = min\{f_{k,j-1}+cost\}
$$
