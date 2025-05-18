# FFT

## 问题引入

$至多n次的多项式A(x)=\sum_{k=0}^{n}a_k,B(x)=\sum_{k=0}^{n}b_k,需要计算卷积(A*B)(x)$
$首先是O(n^2)的朴素算法:$

$$
(A*B)(x)=\sum_{k=0}^{2n}x^k\sum_{i+j=k}a_i+b_j \\
$$

## 复数前置知识

$消去: w^n_{dn}=w_d$
$折半：\{w_{2n}^{2k}|k \in [2n]\}=\{w_{n}^{k}|k \in [n]\}$
$求和基本式：$

$$
\frac{1}{n}\sum_{k=1}^{n-1}w_n^{tk}=
\begin{cases}
    1 & if \ n \ | \ t \\
    0 & if \ otherwise \\
\end{cases}
\qquad t为一个参数
$$

## DFT 离散傅里叶变换

**离散傅里叶变换**(Discrete Fourier transform，DFT)

将多项式函数的系数形式转换为点值形式

### 矩阵乘法表示

$$
记傅里叶矩阵 \ F=
\begin{pmatrix}
1&1&{\cdots}&1\\
1&{w_n}&{\cdots}&{w_n^{n-1}}\\
{\vdots}&{\vdots}&{\ddots}&{\vdots}\\
1&{w_n^{n-1}}&{\cdots}&{w_n^{(n-1)(n-1)}}\\
\end{pmatrix}
\qquad w_n为n次本原单位根  \\
向量 \ \mathbf{x}=
\begin{pmatrix}
x_1\\
x_2\\
{\vdots}\\
x_n\\
\end{pmatrix}
表示一个序列  \\
对该序列DFT的本质为
\mathbf{X}=
\begin{pmatrix}
    X_1\\
    X_2\\
    {\vdots}\\
    X_n\\
\end{pmatrix}
=F\mathbf{x} \quad 得到新序列\mathbf{X} \\
$$

## IDFT

$$
傅里叶矩阵的逆矩阵 \ F^{-1}=\frac{1}{n}
\begin{pmatrix}
1&1&{\cdots}&1\\
1&{w_n^{-1}}&{\cdots}&{w_n^{-(n-1)}}\\
{\vdots}&{\vdots}&{\ddots}&{\vdots}\\
1&{w_n^{-(n-1)}}&{\cdots}&{w_n^{-(n-1)(n-1)}}\\
\end{pmatrix}
\qquad w_n为n次本原单位根 \\
$$

其余相同，即DFT的逆变换，本质为：$\mathbf{x}=F^{-1}\mathbf{X}$

可以将多项式函数的点值形式转换为系数形式

## FFT 高效实现DFT和IDFT

---

### 算法流程

**核心思想：分治法**

$对于一个deg(f)\leq 2n-1, 记f(x)=\sum_{k=0}^{2n-1}a_kx^k$
$令f(x)=f_0(x^2)+x*f_1(x^2),其中f_0(x)=\sum_{k=0}^{n-1}a_{2k}x^k,f_1(x)=\sum_{k=0}^{n-1}a_{2k+1}x^k$
推导：

$$
f(w_{2n}^k)=f_0(w_{2n}^{2k})+w_{2n}^{k}*f_1(w_{2n}^{2k})=f_0(w_{n}^{k})+w_{2n}^{k}*f_1(w_{n}^{k})\quad k \in [2n]\\
结合w_{2n}^n=-1 \\
有，\begin{cases}
    f(w_{2n}^k)=f_0(w_n^k)+w_{2n}^k*f_1(w_n^k) \\
    f(w_{2n}^{n+k})=f_0(w_n^k)-w_{2n}^k*f_1(w_n^k) \\
\end{cases}
\qquad k \in [n] \\
$$

继续向下分治,最终得到 2n 个点值

### 递归实现FFT(常数较大)

```cpp
typedef long long ll;
typedef complex<double> CP;
const ll maxn=1<<20;
const CP I(0,1);     // 虚数单位
const double PI=acos(-1);   // 常数PI
// FFT //
// 时间复杂度O(nlogn) //
// n=2^k ,若不足则补齐，否则该算法不成立 //
CP tmp[maxn];
void _FFT(CP* f,ll n,ll rev)
{
    if(n==1)  return;   // 长度为1，无需操作，直接返回
    for(ll i=0;i<n;++i) tmp[i]=f[i];
    // 偶数放左边，奇数放右边 //
    for(ll i=0;i<n;++i)
    {
        if(i&1) f[n/2+i/2]=tmp[i];
        else    f[i/2]=tmp[i];
    }
    // 递归DFT
    _FFT(f,n/2,rev);_FFT(f+n/2,n/2,rev);
    // cur当前的乘数因子 , step为本原单位根
    CP cur(1,0),step(cos(2*PI/n),rev*sin(2*PI/n));
    for(ll k=0;k<n/2;++k)
    {
        tmp[k]=f[k]+f[n/2+k]*cur;
        tmp[k+n/2]=f[k]-f[n/2+k]*cur;
        cur*=step;
    }
    for(ll i=0;i<n;i++)    f[i]=tmp[i];  
    return;
}
// rev=1;DFT & rev=-1;IDFT//
// n=2^k ,若不足则补齐，否则该算法不成立 //
void FFT(CP* f,ll n,ll rev)
{
    _FFT(f,n,rev);
    if(rev==-1) for(ll i=0;i<n;i++) f[i]*=(CP)(1.0/n);
    return;
}
// 该算法的辅助函数 2^k严格大于n，n为f的最高次数 //
ll log2ceil(ll n){ll cnt=0;for(ll i=1;i<=n;i=i<<1)++cnt;return cnt;}

// 调用方式 ,求g*h并存到f中 //
CP f[maxn],g[maxn],h[maxn];
ll dg,dh;
void mul(CP *f,CP* g,CP* h,ll dg,ll dh)
{
    ll n=1<<log2ceil(dg+dh);
    FFT(g,n,1);FFT(h,n,1);
    for(ll i=0;i<n;i++) f[i]=g[i]*h[i];
    FFT(f,n,-1);
}
mul(f,g,h,dg,dh);
```


### 循环实现FFT

```cpp
// O(nlogn) 不如下面的优化版//
/*
 * 进行 FFT 和 IFFT 前的反置变换
 * 位置 i 和 i 的二进制反转后的位置互换
 * len 必须为 2 的幂
 */
void change_l(Complex y[], int len) {
  // 一开始 i 是 0...01，而 j 是 10...0，在二进制下相反对称。
  // 之后 i 逐渐加一，而 j 依然维持着和 i 相反对称，一直到 i = 1...11。
  for (int i = 1, j = len / 2, k; i < len - 1; i++) {
    // 交换互为小标反转的元素，i < j 保证交换一次
    if (i < j) swap(y[i], y[j]);
    // i 做正常的 + 1，j 做反转类型的 + 1，始终保持 i 和 j 是反转的。
    // 这里 k 代表了 0 出现的最高位。j 先减去高位的全为 1 的数字，知道遇到了
    // 0，之后再加上即可。
    k = len / 2;
    while (j >= k) {
      j = j - k;
      k = k / 2;
    }
    if (j < k) j += k;
  }
}

// O(n)
// 同样需要保证 len 是 2 的幂
// 记 rev[i] 为 i 翻转后的值
void change(Complex y[], int len) {
  for (int i = 0; i < len; ++i) {
    rev[i] = rev[i >> 1] >> 1;
    if (i & 1) {  // 如果最后一位是 1，则翻转成 len/2
      rev[i] |= len >> 1;
    }
  }
  for (int i = 0; i < len; ++i) {
    if (i < rev[i]) {  // 保证每对数只翻转一次
      swap(y[i], y[rev[i]]);
    }
  }
  return;
}

/*
 * 做 FFT
 * len 必须是 2^k 形式
 * on == 1 时是 DFT，on == -1 时是 IDFT
 */
void fft(Complex y[], int len, int on) {
  change(y, len);
  for (int h = 2; h <= len; h <<= 1) {             // 模拟合并过程
    Complex wn(cos(2 * PI / h), sin(2 * PI / h));  // 计算当前单位复根
    for (int j = 0; j < len; j += h) {
      Complex w(1, 0);  // 计算当前单位复根
      for (int k = j; k < j + h / 2; k++) {
        Complex u = y[k];
        Complex t = w * y[k + h / 2];
        y[k] = u + t;  // 这就是把两部分分治的结果加起来
        y[k + h / 2] = u - t;
        // 后半个 「step」 中的ω一定和 「前半个」 中的成相反数
        // 「红圈」上的点转一整圈「转回来」，转半圈正好转成相反数
        // 一个数相反数的平方与这个数自身的平方相等
        w = w * wn;
      }
    }
  }
  if (on == -1) {
    reverse(y + 1, y + len);
    for (int i = 0; i < len; i++) {
      y[i].x /= len;
    }
  }
}

```

## NTT 改进FFT

---

**用于解决FFT使用浮点数的大常数和浮点数运算精度问题**

### 前置知识

$p=998244353 = 2^{23}*7*17+1 \ 是一个大质数$

$对于满足n \ | \ p-1 的n,可记 g=3^{\frac{p-1}{n}},3是p的圆根$

---

## 基本应用

---

- 大整数乘法十进制数可以拆解成多项式表述，利用卷积处理进位问题
- 背包计数
  两个背包的合并是多项式卷积
- 滤波器翻转多项式系数数组再做卷积，可以快速得到两个多项式滑动窗口式的内积
- 位运算有些位运算可以写成卷积形式mod 2 意义下 ^ 为加法， & 为乘法， | 可以取反转换为 &
- 分治FFT
  对于多个长度相同的多项式卷积，分治地卷起来可以降低时间复杂度。
  长度不一样时，先卷小的，用堆维护。

---
