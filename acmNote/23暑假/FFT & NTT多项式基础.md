# FFT

## ��������

$����n�εĶ���ʽA(x)=\sum_{k=0}^{n}a_k,B(x)=\sum_{k=0}^{n}b_k,��Ҫ������(A*B)(x)$
$������O(n^2)�������㷨:$

$$
(A*B)(x)=\sum_{k=0}^{2n}x^k\sum_{i+j=k}a_i+b_j \\
$$

## ����ǰ��֪ʶ

$��ȥ: w^n_{dn}=w_d$
$�۰룺\{w_{2n}^{2k}|k \in [2n]\}=\{w_{n}^{k}|k \in [n]\}$
$��ͻ���ʽ��$

$$
\frac{1}{n}\sum_{k=1}^{n-1}w_n^{tk}=
\begin{cases}
    1 & if \ n \ | \ t \\
    0 & if \ otherwise \\
\end{cases}
\qquad tΪһ������
$$

## DFT ��ɢ����Ҷ�任

**��ɢ����Ҷ�任**(Discrete Fourier transform��DFT)

������ʽ������ϵ����ʽת��Ϊ��ֵ��ʽ

### ����˷���ʾ

$$
�Ǹ���Ҷ���� \ F=
\begin{pmatrix}
1&1&{\cdots}&1\\
1&{w_n}&{\cdots}&{w_n^{n-1}}\\
{\vdots}&{\vdots}&{\ddots}&{\vdots}\\
1&{w_n^{n-1}}&{\cdots}&{w_n^{(n-1)(n-1)}}\\
\end{pmatrix}
\qquad w_nΪn�α�ԭ��λ��  \\
���� \ \mathbf{x}=
\begin{pmatrix}
x_1\\
x_2\\
{\vdots}\\
x_n\\
\end{pmatrix}
��ʾһ������  \\
�Ը�����DFT�ı���Ϊ
\mathbf{X}=
\begin{pmatrix}
    X_1\\
    X_2\\
    {\vdots}\\
    X_n\\
\end{pmatrix}
=F\mathbf{x} \quad �õ�������\mathbf{X} \\
$$

## IDFT

$$
����Ҷ���������� \ F^{-1}=\frac{1}{n}
\begin{pmatrix}
1&1&{\cdots}&1\\
1&{w_n^{-1}}&{\cdots}&{w_n^{-(n-1)}}\\
{\vdots}&{\vdots}&{\ddots}&{\vdots}\\
1&{w_n^{-(n-1)}}&{\cdots}&{w_n^{-(n-1)(n-1)}}\\
\end{pmatrix}
\qquad w_nΪn�α�ԭ��λ�� \\
$$

������ͬ����DFT����任������Ϊ��$\mathbf{x}=F^{-1}\mathbf{X}$

���Խ�����ʽ�����ĵ�ֵ��ʽת��Ϊϵ����ʽ

## FFT ��Чʵ��DFT��IDFT

---

### �㷨����

**����˼�룺���η�**

$����һ��deg(f)\leq 2n-1, ��f(x)=\sum_{k=0}^{2n-1}a_kx^k$
$��f(x)=f_0(x^2)+x*f_1(x^2),����f_0(x)=\sum_{k=0}^{n-1}a_{2k}x^k,f_1(x)=\sum_{k=0}^{n-1}a_{2k+1}x^k$
�Ƶ���

$$
f(w_{2n}^k)=f_0(w_{2n}^{2k})+w_{2n}^{k}*f_1(w_{2n}^{2k})=f_0(w_{n}^{k})+w_{2n}^{k}*f_1(w_{n}^{k})\quad k \in [2n]\\
���w_{2n}^n=-1 \\
�У�\begin{cases}
    f(w_{2n}^k)=f_0(w_n^k)+w_{2n}^k*f_1(w_n^k) \\
    f(w_{2n}^{n+k})=f_0(w_n^k)-w_{2n}^k*f_1(w_n^k) \\
\end{cases}
\qquad k \in [n] \\
$$

�������·���,���յõ� 2n ����ֵ

### �ݹ�ʵ��FFT(�����ϴ�)

```cpp
typedef long long ll;
typedef complex<double> CP;
const ll maxn=1<<20;
const CP I(0,1);     // ������λ
const double PI=acos(-1);   // ����PI
// FFT //
// ʱ�临�Ӷ�O(nlogn) //
// n=2^k ,���������룬������㷨������ //
CP tmp[maxn];
void _FFT(CP* f,ll n,ll rev)
{
    if(n==1)  return;   // ����Ϊ1�����������ֱ�ӷ���
    for(ll i=0;i<n;++i) tmp[i]=f[i];
    // ż������ߣ��������ұ� //
    for(ll i=0;i<n;++i)
    {
        if(i&1) f[n/2+i/2]=tmp[i];
        else    f[i/2]=tmp[i];
    }
    // �ݹ�DFT
    _FFT(f,n/2,rev);_FFT(f+n/2,n/2,rev);
    // cur��ǰ�ĳ������� , stepΪ��ԭ��λ��
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
// n=2^k ,���������룬������㷨������ //
void FFT(CP* f,ll n,ll rev)
{
    _FFT(f,n,rev);
    if(rev==-1) for(ll i=0;i<n;i++) f[i]*=(CP)(1.0/n);
    return;
}
// ���㷨�ĸ������� 2^k�ϸ����n��nΪf����ߴ��� //
ll log2ceil(ll n){ll cnt=0;for(ll i=1;i<=n;i=i<<1)++cnt;return cnt;}

// ���÷�ʽ ,��g*h���浽f�� //
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


### ѭ��ʵ��FFT

```cpp
// O(nlogn) ����������Ż���//
/*
 * ���� FFT �� IFFT ǰ�ķ��ñ任
 * λ�� i �� i �Ķ����Ʒ�ת���λ�û���
 * len ����Ϊ 2 ����
 */
void change_l(Complex y[], int len) {
  // һ��ʼ i �� 0...01���� j �� 10...0���ڶ��������෴�Գơ�
  // ֮�� i �𽥼�һ���� j ��Ȼά���ź� i �෴�Գƣ�һֱ�� i = 1...11��
  for (int i = 1, j = len / 2, k; i < len - 1; i++) {
    // ������ΪС�귴ת��Ԫ�أ�i < j ��֤����һ��
    if (i < j) swap(y[i], y[j]);
    // i �������� + 1��j ����ת���͵� + 1��ʼ�ձ��� i �� j �Ƿ�ת�ġ�
    // ���� k ������ 0 ���ֵ����λ��j �ȼ�ȥ��λ��ȫΪ 1 �����֣�֪��������
    // 0��֮���ټ��ϼ��ɡ�
    k = len / 2;
    while (j >= k) {
      j = j - k;
      k = k / 2;
    }
    if (j < k) j += k;
  }
}

// O(n)
// ͬ����Ҫ��֤ len �� 2 ����
// �� rev[i] Ϊ i ��ת���ֵ
void change(Complex y[], int len) {
  for (int i = 0; i < len; ++i) {
    rev[i] = rev[i >> 1] >> 1;
    if (i & 1) {  // ������һλ�� 1����ת�� len/2
      rev[i] |= len >> 1;
    }
  }
  for (int i = 0; i < len; ++i) {
    if (i < rev[i]) {  // ��֤ÿ����ֻ��תһ��
      swap(y[i], y[rev[i]]);
    }
  }
  return;
}

/*
 * �� FFT
 * len ������ 2^k ��ʽ
 * on == 1 ʱ�� DFT��on == -1 ʱ�� IDFT
 */
void fft(Complex y[], int len, int on) {
  change(y, len);
  for (int h = 2; h <= len; h <<= 1) {             // ģ��ϲ�����
    Complex wn(cos(2 * PI / h), sin(2 * PI / h));  // ���㵱ǰ��λ����
    for (int j = 0; j < len; j += h) {
      Complex w(1, 0);  // ���㵱ǰ��λ����
      for (int k = j; k < j + h / 2; k++) {
        Complex u = y[k];
        Complex t = w * y[k + h / 2];
        y[k] = u + t;  // ����ǰ������ַ��εĽ��������
        y[k + h / 2] = u - t;
        // ���� ��step�� �еĦ�һ���� ��ǰ����� �еĳ��෴��
        // ����Ȧ���ϵĵ�תһ��Ȧ��ת��������ת��Ȧ����ת���෴��
        // һ�����෴����ƽ��������������ƽ�����
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

## NTT �Ľ�FFT

---

**���ڽ��FFTʹ�ø������Ĵ����͸��������㾫������**

### ǰ��֪ʶ

$p=998244353 = 2^{23}*7*17+1 \ ��һ��������$

$��������n \ | \ p-1 ��n,�ɼ� g=3^{\frac{p-1}{n}},3��p��Բ��$

---

## ����Ӧ��

---

- �������˷�ʮ���������Բ��ɶ���ʽ���������þ�������λ����
- ��������
  ���������ĺϲ��Ƕ���ʽ���
- �˲�����ת����ʽϵ������������������Կ��ٵõ���������ʽ��������ʽ���ڻ�
- λ������Щλ�������д�ɾ����ʽmod 2 ������ ^ Ϊ�ӷ��� & Ϊ�˷��� | ����ȡ��ת��Ϊ &
- ����FFT
  ���ڶ��������ͬ�Ķ���ʽ��������εؾ��������Խ���ʱ�临�Ӷȡ�
  ���Ȳ�һ��ʱ���Ⱦ�С�ģ��ö�ά����

---
