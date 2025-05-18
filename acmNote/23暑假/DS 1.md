# 复杂数据结构

## ST (Segment Tree)

### 简介

- 线段树可以在 $O(\log n)$ 的时间复杂度内实现单点修改、区间修改、区间查询（区间求和，求区间最大值，求区间最小值）等操作
- 如果只查询不更新，还有很多空间换时间的方法实现快速查询

### 数组实现

#### 数组实现的空间：

$2p 是 p 的左儿子 ，2p+1 是 p 的右儿子 $

$d数组最长为2^{[\log n]+1}-1 \leq 4n-5,一般开4n长度即可$

#### 建树(tree_build)（通用模板）：

**这是普通的线段树模板**

```cpp
void tree_build(int l,int r,int root)
{
    if(l==r)
    {
        tree[root].sum = a[l];
        return; 
    }
    int mid=l+((r-l)>>1);
    tree_build(l,mid,root*2);   // 左子树
    tree_build(mid+1,r,root*2+1);  // 右子树
    tree[root].sum = tree[root*2].sum + tree[root*2+1].sum;
    return;
}

```

#### 区间查询(tree_query)

区间最大值，最小值，区间和等

时间复杂度$O(\log n)$

```cpp
// [cl,cr]为当前区间 , [vl,vr]为目标区间 , cur 为当前节点号
int tree_query(int cl,int cr,int vl,int vr,int cur)
{
    // 如果无交集
    if(vr<cl||vl>cr)  return 0;     // 这个值视情况而定（用一个无效值）
    // 当前区间被目标区间包含
    else if(vl<=cl&&cr<=vr) return tree[cur];
    // 如果不完全包含而只是有交集
    else
    {
        int mid = cl+((cr-cl)>>1);
        int sum = 0;
        if(vl<=mid) sum+=tree_query(cl,mid,vl,vr,2*cur);  
        // 代表左儿子[cl,mid]与目标区间有交集，向左儿子递归查询
        if(mid<vr) sum+=tree_query(mid+1,cr,vl,vr,2*cur+1);
        // 代表右儿子[mid+1,cr]与目标区间有交集，向右儿子递归查询
        return sum;
    }
}

```

#### 单点修改(update)

我们显然需要更新所有包含目标点的区间，与建树类似，直到区间缩小至只剩目标点时停下，然后往上更新。

时间复杂度 $O(\log n)$

```cpp
// 单点更新类似于建树
// [cl,cr]是当前区间，cur为当前节点，pos为a数组要更新的位置，x为更新的值
void update(int cl,int cr,int cur,int pos,int x)
{
    if(cl>pos||cr<pos)  return;      // pos不在区间内，不搜索
    if(cl==cr)                       // 找到pos ,此时 cl=cr=pos
    {
        tree[cur] = x;
        return;
    }
    int mid = cl+((cr-cl)>>1);
    update(cl,mid,cur,pos,x);
    update(mid+1,cr,cur,pos,x);
    tree[cur] = tree[cur*2]+tree[cur*2+1];     // 将儿子节点更新完了，可以更新本节点
    return;
}
```

#### lazy tag & 区间修改

懒惰标记，简单来说，就是通过延迟对节点信息的更改，从而减少可能不必要的操作次数。每次执行修改时，我们通过打标记的方法表明该节点对应的区间在某一次操作中被更改，但不更新该节点的子节点的信息。实质性的修改则在下一次访问带有标记的节点时才进行。

使用 **pushdown** 函数下放 lazy tag    ->   减少代码的复杂度，减少出错

```cpp
// 下放lazy tag给子节点
void pushdown(int cur,int cl,int cr,int mid)
{
    tree[2*cur].tag += tree[cur].tag;     // 左子树更新
    tree[2*cur].sum += (mid-cl+1)*tree[cur].tag;
    tree[2*cur+1].tag += tree[cur].tag;   // 右子树更新
    tree[2*cur+1].sum += (cr-mid)*tree[cur].tag;
    tree[cur].tag = 0;       // cur标签更新
    return;
}
// 区间更新(对区间进行同一种操作)  ->  类似于区间查询
// 此处以 全部加k 举例
void update(int cl,int cr,int cur,int vl,int vr,int k)
{
    if(cr<vl||cl>vr)    return;   // 区间无交集，直接返回
    if(vl<=cl&&cr<=vr)   // 如果当前区间被包含在修改区间，进行修改
    {
        tree[cur].sum += (cr-cl+1)*k;
        tree[cur].tag += k;
        return;
    }
    // 如果当前区间与修改区间有交集且不被包含于修改区间内
    int mid = ((cr-cl)>>1)+cr;
    if(tree[cur].tag && cl!=cr) pushdown(cur);    // 如果当前节点 懒标签不为空 且 不是树叶 -> 下放懒节点
  
    if(vl<=mid) update(cl,mid,2*cur,vl,vr,k);
    if(vr>mid) update(mid+1,cr,2*cur+1,vl,vr,k);
    tree[cur].sum = tree[2*cur].sum + tree[2*cur+1].sum;   // 懒节点不在这一层，这一层的更新必不可少
    return;
}
// 带pushdown的查询
int query(int cur,int cl,int cr,int vl,int vr)
{
    if(vl>cr||vr<cl)    return 0;
    if(vl<=cl&&cr<=vr)  return tree[cur].sum;
    int mid = cl + ((cr-cl)>>1);
    if(tree[cur].tag && cl!=cr) pushdown(cur,cl,cr,mid);
    return query(2*cur,cl,mid,vl,vr)+query(2*cur+1,mid+1,cr,vl,vr);
}
```

#### 动态开点 & 可持久化数组

```cpp
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 1e5;  // 数据范围
int tot, n, m;
int sum[(maxn << 5) + 10], rt[maxn + 10], ls[(maxn << 5) + 10],
    rs[(maxn << 5) + 10];
int a[maxn + 10], ind[maxn + 10], len;

int getid(const int &val) {  // 离散化
  return lower_bound(ind + 1, ind + len + 1, val) - ind;
}

int build(int l, int r) {  // 建树
  int root = ++tot;
  if (l == r) return root;
  int mid = l + r >> 1;
  ls[root] = build(l, mid);
  rs[root] = build(mid + 1, r);
  return root;  // 返回该子树的根节点
}

int update(int k, int l, int r, int root) {  // 插入操作
  int dir = ++tot;
  ls[dir] = ls[root], rs[dir] = rs[root], sum[dir] = sum[root] + 1;
  if (l == r) return dir;
  int mid = l + r >> 1;
  if (k <= mid)
    ls[dir] = update(k, l, mid, ls[dir]);
  else
    rs[dir] = update(k, mid + 1, r, rs[dir]);
  return dir;
}

int query(int u, int v, int l, int r, int k) {  // 查询操作
  int mid = l + r >> 1,
      x = sum[ls[v]] - sum[ls[u]];  // 通过区间减法得到左儿子中所存储的数值个数
  if (l == r) return l;
  if (k <= x)  // 若 k 小于等于 x ，则说明第 k 小的数字存储在在左儿子中
    return query(ls[u], ls[v], l, mid, k);
  else  // 否则说明在右儿子中
    return query(rs[u], rs[v], mid + 1, r, k - x);
}

void init() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i) scanf("%d", a + i);
  memcpy(ind, a, sizeof ind);
  sort(ind + 1, ind + n + 1);
  len = unique(ind + 1, ind + n + 1) - ind - 1;
  rt[0] = build(1, len);
  for (int i = 1; i <= n; ++i) rt[i] = update(getid(a[i]), 1, len, rt[i - 1]);
}

int l, r, k;

void work() {
  while (m--) {
    scanf("%d%d%d", &l, &r, &k);
    printf("%d\n", ind[query(rt[l - 1], rt[r], 1, len, k)]);  // 回答询问
  }
}

int main() {
  init();
  work();
  return 0;
}
拓展：基于主席树的可持久化并查集
主席树是实现可持久化并查集的便捷方式，在此也提供一个基于主席树的可持久化并查集实现示例。


#include <bits/stdc++.h>
using namespace std;

struct SegmentTree {
  int lc, rc, val, rnk;
};

const int MAXN = 100000 + 5;
const int MAXM = 200000 + 5;

SegmentTree
    t[MAXN * 2 +
      MAXM * 40];  //每次操作1会修改两次，一次修改父节点，一次修改父节点的秩
int rt[MAXM];
int n, m, tot;

int build(int l, int r) {
  int p = ++tot;
  if (l == r) {
    t[p].val = l;
    t[p].rnk = 1;
    return p;
  }
  int mid = (l + r) / 2;
  t[p].lc = build(l, mid);
  t[p].rc = build(mid + 1, r);
  return p;
}

int getRnk(int p, int l, int r, int pos) {  //查询秩
  if (l == r) {
    return t[p].rnk;
  }
  int mid = (l + r) / 2;
  if (pos <= mid) {
    return getRnk(t[p].lc, l, mid, pos);
  } else {
    return getRnk(t[p].rc, mid + 1, r, pos);
  }
}

int modifyRnk(int now, int l, int r, int pos, int val) {  //修改秩（高度）
  int p = ++tot;
  t[p] = t[now];
  if (l == r) {
    t[p].rnk = max(t[p].rnk, val);
    return p;
  }
  int mid = (l + r) / 2;
  if (pos <= mid) {
    t[p].lc = modifyRnk(t[now].lc, l, mid, pos, val);
  } else {
    t[p].rc = modifyRnk(t[now].rc, mid + 1, r, pos, val);
  }
  return p;
}

int query(int p, int l, int r, int pos) {  //查询父节点（序列中的值）
  if (l == r) {
    return t[p].val;
  }
  int mid = (l + r) / 2;
  if (pos <= mid) {
    return query(t[p].lc, l, mid, pos);
  } else {
    return query(t[p].rc, mid + 1, r, pos);
  }
}

int findRoot(int p, int pos) {  //查询根节点
  int f = query(p, 1, n, pos);
  if (pos == f) {
    return pos;
  }
  return findRoot(p, f);
}

int modify(int now, int l, int r, int pos, int fa) {  //修改父节点（合并）
  int p = ++tot;
  t[p] = t[now];
  if (l == r) {
    t[p].val = fa;
    return p;
  }
  int mid = (l + r) / 2;
  if (pos <= mid) {
    t[p].lc = modify(t[now].lc, l, mid, pos, fa);
  } else {
    t[p].rc = modify(t[now].rc, mid + 1, r, pos, fa);
  }
  return p;
}

int main() {
  scanf("%d%d", &n, &m);
  rt[0] = build(1, n);
  for (int i = 1; i <= m; i++) {
    int op, a, b;

    scanf("%d", &op);
    if (op == 1) {
      scanf("%d%d", &a, &b);
      int fa = findRoot(rt[i - 1], a), fb = findRoot(rt[i - 1], b);
      if (fa != fb) {
        if (getRnk(rt[i - 1], 1, n, fa) >
            getRnk(rt[i - 1], 1, n, fb)) {  //按秩合并
          swap(fa, fb);
        }
        int tmp = modify(rt[i - 1], 1, n, fa, fb);
        rt[i] = modifyRnk(tmp, 1, n, fb, getRnk(rt[i - 1], 1, n, fa) + 1);
      } else {
        rt[i] = rt[i - 1];
      }
    } else if (op == 2) {
      scanf("%d", &a);
      rt[i] = rt[a];
    } else {
      scanf("%d%d", &a, &b);
      rt[i] = rt[i - 1];
      if (findRoot(rt[i], a) == findRoot(rt[i], b)) {
        printf("1\n");
      } else {
        printf("0\n");
      }
    }
  }

  return 0;
}
```

## BIT (Binary Indexed Tree)

### 简介

代码量少，可实现 **区间查询** 和 **单点修改**。

**普通树状数组** 可以维护的数据 ：

- 运算满足结合律 -> (x op y) op z = x op (y op z)
  例如：区间和，最值，最大公约数等
- 可差分，即运算具有逆运算

### 实现

#### lowbit

```cpp
int lowbit(int x)
{
    return x & (-x);
}
// lowbit返回x的最末位的1和后面的0组成的数
// lowbit(0b01011000) == 0b00001000
//          ~~~~^~~~
// lowbit(0b01110010) == 0b00000010
//          ~~~~~~^~
```

#### 建立树状数组

#### 单点修改

```cpp
ll bit_query(int x)
{
  
}
```

#### 区间查询

#### 一个简单拓展

如果想做到单点查询和区间修改：

## 单调队列

### 相关概念

使用普通的双端队列 STL deque ， 维护权值单调

可以维护一个区间的**最大/最小值**

### 模板题

**滑动区间问题**

```cpp
#include<bits/stdc++.h>
using namespace std;
deque<int> q1;   // 用来存编号,维护最大值
deque<int> q2;   // 维护最小值
int n,k;
int arr[1000005];
int mi[1000005],ma[1000005];
int main(void)
{
    cin>>n>>k;
    for(int i=1;i<=n;i++)
        scanf("%d",arr+i);
    // 单调队列
    for(int cur=1;cur<=n;cur++)
    {
        if(!q1.empty())
        {
            if(q1.front()<=cur-k)  q1.pop_front();   // 编号在区间之外，队首出，该操作优先级高
            while(!q1.empty()&&arr[q1.back()]<arr[cur])    q1.pop_back();   // 维护队列单调
        }
        q1.push_back(cur);
        if(cur>=k) ma[cur-k+1] = arr[q1.front()];   // 更新最大值
        // 下面的最小值同理
        if(!q2.empty())
        {
            if(q2.front()<=cur-k)  q2.pop_front();
            while(!q2.empty()&&arr[q2.back()]>arr[cur])   q2.pop_back();
        }
        q2.push_back(cur);
        if(cur>=k) mi[cur-k+1] = arr[q2.front()];
    }
    // print
    for(int i=1;i<=n-k+1;i++)
        printf("%d%c",mi[i],(i==n-k+1)?'\n':' ');
    for(int i=1;i<=n-k+1;i++)
        printf("%d%c",ma[i],(i==n-k+1)?'\n':' ');
    return 0;
}
```

**给定一个数列，求数列中长度$\in [S,T]$的连续子列的最大值**

分析：使用前缀和优化,$sum[k]=\sum_{i=1}^ka_i$
枚举每个结尾点$i$，那么就是求$sum_{i-T+1},...,sum_{i-S+1}$中的最小值,这个可以用单调队列来维护。
**参考题目**： POJ 2823




## 单调栈

### 相关概念

使用的数据结构就是普通的栈，一般选择 手写栈(数组实现，用top标记栈顶) 或使用 STL stack

### 模板题

NGE问题（next greater element）

```cpp
#include<bits/stdc++.h>
using namespace std;
stack<int> s;   // 存编号
int f[3000005];
int arr[3000005];
int n;
int main(void)
{
    cin>>n;
    for(int i=1;i<=n;i++)
        scanf("%d",arr+i);
    // 单调栈
    for(int cur=1;cur<=n;cur++)  // 每次都维护单调
    {
        while(!s.empty()&&arr[cur]>arr[s.top()])   f[s.top()]=cur,s.pop();  // 把非空判断写在前面
        s.push(cur);
    }
    //  单调栈结束
    for(int i=1;i<=n;i++)
        printf("%d ",f[i]);
    printf("\n");
    return 0;
}
```

一道多次套用模板解决的问题 -> feel good

```cpp
/*
我们假设某个点为某个区间最小值，那当区间从该点往左右延拓的时候，
由于区间和在变大，最小值又不变，则所求的值是单调递增的，
那么只需求出每个点最远能向左和向右延拓到的最远的点即可，
即是求每个点左边和右边的第一个小于自身的点的位置

解决上述问题就是单调栈的模板问题，
求出来左右端点后枚举一遍取最小值即可。
*/
// 数组实现栈 //
#include<iostream>
#include<cstdio>
using namespace std;
int arr[100005];
int f1[100005],f2[100005];  // 分别记录NLE 和 PLE
int s[100005];   // 实现栈
int top;
int n;
int sum[100005];  // 储存前缀和
int main(void)
{
    cin>>n;
    sum[0] = 0;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",arr+i);
        sum[i] = sum[i-1] + arr[i];
    }
    // init
    for(int i=1;i<=n;i++)
        f1[i]=n+1,f2[i]=0;
    // NLE
    top = -1;
    for(int cur=1;cur<=n;cur++)
    {
        while(top!=-1&&arr[cur]<arr[s[top]])    f1[s[top--]]=cur;
        s[++top] = cur;  
    }
    // PLE
    top = -1;                  // 清空栈
    for(int cur=n;cur>=1;cur--)
    {
        while(top!=-1&&arr[cur]<arr[s[top]])    f2[s[top--]]=cur;
        s[++top] = cur;
    }
    // 枚举
    int ans = -1e10;
    int r=0,l=0;
    for(int i=1;i<=n;i++)
        if(ans<arr[i]*(sum[f1[i]-1]-sum[f2[i]+1]))
            ans=arr[i]*(sum[f1[i]-1]-sum[f2[i]]),l=f2[i]+1,r=f1[i]-1;
    // print
    printf("%d\n",ans);
    printf("%d %d\n",l,r);
    return 0;
}
```

### 优化DP

1D1D 优化DP

## 利用数据结构优化DP

### 单调队列优化 & 单调栈优化

一维DP的优化：

$$
f_i = max_{i-R\leq j \leq i-L} f_j+B_j +A_i
$$

要求维护固定长度区间的最大值，可以用单调队列

更进一步，**只要保证区间两端点是同方向单调**，均可以用单调队列维护

题目：琪露诺

```cpp
//  1D 但是 单调队列优化 //
// f[i] = max(f[j]) + a[i] , 其中 i-R<=j<=i-L //
#include<bits/stdc++.h>
using namespace std;
int a[200005];
int f[200005];   // f[i] 表示以i为终点，能得到的最大冰冻能量
deque<int> q;
int n,l,r;
int main(void)
{
    cin>>n>>l>>r;
    for(int i=0;i<=n;i++)
        scanf("%d",a+i);
    f[0] = a[0];  // 初始化
    for(int i=1;i<=n;i++)
    {
        int cur=i-l;
        // 单调队列
        if(cur>=0)    // 如果cur>=0 则要维护单调队列
        {
            while(!q.empty()&&cur-q.front()>r-l)    q.pop_front();
            if(f[cur]!=INT_MIN)     // 没有这个判断将收获惨痛的教训
            {
                while(!q.empty()&&f[cur]>=f[q.back()]) q.pop_back();
                q.push_back(cur);
            }
        }
        if(!q.empty())  f[i]=f[q.front()]+a[i];
        else    f[i]=INT_MIN; //表示跳不到这个点
    }
    int ans = INT_MIN;
    for(int i=n+1-r;i<=n;i++)
        ans = max(ans,f[i]);
    cout<<ans<<endl;
    return 0;
}

/*
Hack:
5 3 4
0 1 2 3 4 5
ans = 4
已解决
*/
```

题目：跳房子

```cpp
// 跳房子 //
// DP + 单调队列优化 //
// 答案单调性 -> 可以二分搜索 //
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = LONG_LONG_MIN;
deque<ll> q;
ll n,d,k,Max,sum;
ll value[1000005];  // 机器人从 0 出发
ll dis[1000005];
ll dp[1000005];   // 到第 n 个格子的最大分数
bool check(ll g)
{
    ll l = max((ll)1,d-g);
    ll r = d+g;
    // init
    q.clear();
    for(ll i=1;i<=n;i++)
        dp[i] = INF;
    dp[0] = 0;
    //
    ll cur = 0;  // 当前要入队列的格子的下标
    for(ll i=0;i<=n;i++)
    {
        while(dis[cur]+r<dis[i])    cur++;   // cur太靠后了，要加回来
        while(dis[cur]+l<=dis[i])   // 由定义 必有 cur<=i<=n ,不会越界
        {
            while(!q.empty()&&dp[q.back()]<=dp[cur])    q.pop_back();
            q.push_back(cur);
            cur++;
        }
        while(!q.empty()&&dis[q.front()]+r<dis[i])  q.pop_front();
        if(!q.empty()&&dp[q.front()]!=INF)   
        {
            dp[i] = dp[q.front()]+value[i];
            if(dp[i]>=k)    return true;
        }
    }
    //
    return false;
}
int main(void)
{
    cin>>n>>d>>k;
    dis[0] = 0;
    for(ll i=1;i<=n;++i)
    {
        scanf("%lld %lld",dis+i,value+i);
        if(value[i]>0) sum+=value[i];
    }
    // 判断是否可一到达分数k
    if(sum<k){
        printf("-1\n");
        return 0;
    }
    ll mid; 
    ll r = 1010;   // 挑一个大一点点的数
    ll l = 1;
    while(r!=l)
    {
        mid = (r+l)/2;
        if(check(mid))  r = mid;
        else    l = mid+1; 
    }
    printf("%lld\n",l);
    return 0;
}
```

题目：Golden Sword

```cpp
// Golden Sword //
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 0x3f3f3f3f3f3f3f3f;
ll n,w,s;
ll f[5005][5005],a[5005];   // 空间够，就不用滚动数组优化了
deque<ll> q;
int main(void)
{
    cin>>n>>w>>s;
    for(ll i=1;i<=n;i++)
        scanf("%lld",a+i);
    // init_start
    for(ll i=1;i<=n;i++)
        for(ll j=0;j<=w;j++)
            f[i][j] = -INF;
    f[1][1] = a[1];
    // init_end
    for(ll i=2;i<=n;i++)
    {
        q.clear();   // 清空队列
        for(ll j=0;j<=min(w-1,s-1);j++)  // 初始化队列
        {
            while(!q.empty()&&f[i-1][q.back()]<=f[i-1][j])  q.pop_back();
            q.push_back(j);
        }
        for(ll j=1;j<=min(i,w);j++)
        {
            while(!q.empty()&&q.front()<j-1)    q.pop_front();
            if(j+s-1<=w)    //右侧区间改变，需要维护
            {
                while(!q.empty()&&f[i-1][q.back()]<=f[i-1][j+s-1])  q.pop_back();
                q.push_back(j+s-1);
            }
            if(f[i-1][q.front()]!=-INF) f[i][j] = f[i-1][q.front()]+j*a[i];
        }
    }
    ll ans = -INF;
    for(ll i=1;i<=w;i++)
        if(ans<f[n][i]) ans = f[n][i];
    cout<<ans<<endl;
    return 0;
}
```

### 斜率优化

# ST表

解决 **可重复贡献问题** 的数据结构

## 什么是可重复贡献问题？

**可重复贡献问题** 是指对于运算 opt ，满足 x opt x = x ，则对应的区间询问就是一个可重复贡献问题。

其次， 运算操作 opt 还应满足结合律。

例如：区间最大值、最小值、最大公约数、区间按位或、区间按位与

## 模板

预处理 + 查询 （无法更新）

ST表 的实现（递推）  ->   O(nlogn)

ST表 每次查询            ->   O(1)

$f[i][j]表示区间[i,i+2^j-1]的最大值$

$转移方程：f[i][j]=max(f[i][j-1],f[i+2^{j-1}][j-1]) $

```cpp
#include <bits/stdc++.h>
using namespace std;
const int logn = 21;
const int maxn = 2000001;
int f[maxn][logn + 1], Logn[maxn + 1];

int read() {  // 快读
  char c = getchar();
  int x = 0, f = 1;
  while (c < '0' || c > '9') {
    if (c == '-') f = -1;
    c = getchar();
  }
  while (c >= '0' && c <= '9') {
    x = x * 10 + c - '0';
    c = getchar();
  }
  return x * f;
}

void pre() {  // 准备工作，初始化
  Logn[1] = 0;
  Logn[2] = 1;
  for (int i = 3; i < maxn; i++) {
    Logn[i] = Logn[i / 2] + 1;
  }
}

int main() {
  int n = read(), m = read();
  for (int i = 1; i <= n; i++) f[i][0] = read();
  pre();
// 实现ST表
  for (int j = 1; j <= logn; j++)
    for (int i = 1; i + (1 << j) - 1 <= n; i++)
      f[i][j] = max(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);  // ST表具体实现，递推
// 查询
  for (int i = 1; i <= m; i++) {
    int x = read(), y = read();
    int s = Logn[y - x + 1];
    printf("%d\n", max(f[x][s], f[y - (1 << s) + 1][s]));
  }
  return 0;
}

```





# 左偏树（实现堆）

***优点***： 高效地插入元素，查询最大元素，删除最大元素，两个堆的合并

**节点的距离 distance(dist)**
某个节点被称为外节点，仅当这个节点的左子树或右子树为空。
某一个节点的距离即该节点到与其最近的外节点经过的边数。易得，外节点的距离为 0，空节点距离为 ?1.

***左偏树的性质***：

1. 堆的性质，即对于任意节点 p, val(p) ≤ val(ls), val(rs)。（假
   设定义的是***小根堆***）
2. dist(ls) ≥ dist(rs)，即左子树距离一定大于等于右子树距离，
   这也是左偏树这一名字的由来
3. dist(x) = dist(rs) + 1，也就是说，任意节点的距离等于其右
   儿子的距离 +1

---

***核心操作***：合并 Merge

左偏树的合并是一个递推操作:

1. 设 x，y 是两个要合并的左偏树的根节点编号。不妨设 x 的权值较小，否则可以交换 x 和 y。
   我们将 x 作为被插入树，y 作为插入树，每次合并就是先把y 和 x 的右儿子合并, 再将合并后的新树的根节点作为 x 的右儿子。item 边界条件是当 x 和 y 代表的树中有一棵为空时，直接返回另一棵非空的树。
2. 因此如果 x 的右儿子为空时，相当于直接将 y 作为 x 的右
   儿子。
3. 特别要注意的是，在每次插入完成后，还需要检查左右儿子的距离是否满足左偏树的要求，如果不满足，还需要交换左右儿子。

其他操作：插入insert , 查询 query, 删除 erase

这些操作都可以基于Merge进行

---

***代码模板(还是有点小问题)：***

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e7+5;
int n;
// 左偏树 leftist tree / leftist heap //
struct lheap{
    int val;  // 权值
    int fa;   // father，根节点的父节点为0
    int ls,rs;   // left son & right son ->  没有即为0(若用指针表示就是NULL)
    int dist;   // 距离，0号节点初始化为-1，其余初始化为0或不初始化均可
}tr[maxn];
// 合并操作
int Merge(int x,int y)
{
    if(!x||!y)  return x+y;  // 返回x，y中的非零者或0
    if(tr[x].val>tr[y].val) swap(x,y);   // 以小根堆举例，此处保证x节点的权值比y节点的权值小，然后把y插入x
    int &ur=tr[x].rs,&ul=tr[x].ls;
    ur=Merge(ur,y);    // 为什么要与柚子树合并？ 因为dist[rs]<=dist[ls],这是左偏树的性质,该性质保证了合并时的复杂度
    tr[ur].fa=x;   // 不能忘记，因为合并的时候，可能交换过左右子树
    // 合并完了，看看是否还符合左偏树的结构，调整结构
    if(tr[ur].dist>tr[ul].dist) swap(ur,ul);
    tr[x].dist=tr[ur].dist+1;   // 更新该节点的距离
    return x;  // 返回该节点
}
// 插入操作
// 一个节点x 插入以root为根的左偏树，可以把单节点x看做一棵左偏树，然后合并
void Insert(int root,int x)
{
    Merge(root,x);
    return;
}
// 删除根节点
void Erase(int x)
{
    int ur=tr[x].rs,ul=tr[x].ls;
    tr[x].val=-1;   // 用一个值表式该点未初始化，或单独用flag数组表示也可以
    tr[x].ls=0,tr[x].rs=0;
    int r=Merge(ur,ul);   // 返回新的根节点
    tr[r].fa=0;   // 根节点的fa为0 ， 容易忘记这一点，尤其是在维护多个左偏树的时候
    return;
}
// 删除任意节点
void Delete(int x)
{
    int fa=tr[x].fa;
    int temp=Merge(tr[x].rs,tr[x].ls);
    tr[x].val=-1,tr[x].rs=0,tr[x].ls=0;
    tr[temp].fa=fa;
    int &ur=tr[fa].rs,&ul=tr[fa].ls;
    (x==ur)?ur=temp:ul=temp;    // 看看x是左儿子还是右儿子
    tr[fa].dist=tr[tr[fa].rs].dist+1;
    // 向上维护左偏性质，直到根节点或左偏性质不再被破坏 //
    while(fa&&tr[tr[fa].rs].dist<=tr[tr[fa].ls].dist)   // 当前节点不是根节点（注：根节点的父节点为0）
    {
        swap(tr[fa].rs,tr[fa].ls);
        tr[fa].dist=tr[tr[fa].rs].dist+1;  // 更新dist
        // 向上维护
        fa=tr[fa].fa;
    }
    return;
}
// 建树操作:暴力插入 复杂度O(nlogn) //
// 前置条件，tr[1]~tr[n]的权值已经初始化完毕，只是没有连接起来 //
void Build(int n)   // 参数也可以改成一个数组或其他容器
{
    int root=1;
    for(int i=2;i<=n;i++)
        root=Merge(root,i);
    return;
}

```

进阶版：引入lazytag
