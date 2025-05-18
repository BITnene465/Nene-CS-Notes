# 租用游艇

## 题目描述

长江游艇俱乐部在长江上设置了 $n$ 个游艇出租站 $1,2,\cdots,n$。游客可在这些游艇出租站租用游艇，并在下游的任何一个游艇出租站归还游艇。游艇出租站 $i$ 到游艇出租站 $j$ 之间的租金为 $r(i,j)$（$1\le i\lt j\le n$）。试设计一个算法，计算出从游艇出租站 $1$ 到游艇出租站 $n$ 所需的最少租金。

## 输入格式

第一行中有一个正整数 $n$，表示有 $n$ 个游艇出租站。接下来的 $n-1$ 行是一个半矩阵 $r(i,j)$（$1\le i<j\le n$）。

## 输出格式

输出计算出的从游艇出租站 $1$ 到游艇出租站 $n$ 所需的最少租金。

## 样例 #1

### 样例输入 #1

```
3
5 15
7
```

### 样例输出 #1

```
12
```

## 提示

$n\le 200$，保证计算过程中任何时刻数值都不超过 $10^6$。  
<br><br>  
  
## 题解
**1. dp解法:**  
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxN = 201;    // 序号从1开始
typedef long long ll;
ll dp[maxN];
ll dis[maxN][maxN];
int n;
void solve()
{
    memset(dp,1000000,sizeof(dp));     // 足够大的数据即可
    dp[1] = 0;  //初始化
    for(int i=2;i<=n;i++)
    {
        for(int j=1;j<=i-1;j++)
            dp[i] = min(dp[i],dp[j]+dis[j][i]);
    }
    return;
}
int main(void)
{
    scanf("%d",&n);
    for(int i=1;i<=n-1;i++)
        for(int j=i+1;j<=n;j++)
            scanf("%lld",&dis[i][j]);
    solve();
    cout<<dp[n]<<endl;
    return 0;
}
```

# [NOIP2006 普及组] 开心的金明

## 题目描述

金明今天很开心，家里购置的新房就要领钥匙了，新房里有一间他自己专用的很宽敞的房间。更让他高兴的是，妈妈昨天对他说：“你的房间需要购买哪些物品，怎么布置，你说了算，只要不超过$N$元钱就行”。今天一早金明就开始做预算，但是他想买的东西太多了，肯定会超过妈妈限定的$N$元。于是，他把每件物品规定了一个重要度，分为$5$等：用整数$1-5$表示，第$5$等最重要。他还从因特网上查到了每件物品的价格（都是整数元）。他希望在不超过$N$元（可以等于$N$元）的前提下，使每件物品的价格与重要度的乘积的总和最大。

设第$j$件物品的价格为$v[j]$，重要度为$w[j]$，共选中了$k$件物品，编号依次为$j_1,j_2,…,j_k$，则所求的总和为：

$v[j_1] \times w[j_1]+v[j_2] \times w[j_2]+ …+v[j_k] \times w[j_k]$。

请你帮助金明设计一个满足要求的购物单。

## 输入格式

第一行，为$2$个正整数，用一个空格隔开：$n,m$（其中$N(<30000)$表示总钱数，$m(<25)$为希望购买物品的个数。）

从第$2$行到第$m+1$行，第$j$行给出了编号为$j-1$的物品的基本数据，每行有$2$个非负整数$v,p$（其中$v$表示该物品的价格$(v \le 10000)$，$p$表示该物品的重要度($1-5$)

## 输出格式

$1$个正整数，为不超过总钱数的物品的价格与重要度乘积的总和的最大值$(<100000000)$。

## 样例 #1

### 样例输入 #1

```
1000 5
800 2
400 5
300 5
400 3
200 2
```

### 样例输出 #1

```
3900
```

## 提示

NOIP 2006 普及组 第二题   
<br><br>
## 题解
**1. dp解法--01背包**  
```cpp
// P1060 开心的金明 //
// dp解法，01背包 //
#include<bits/stdc++.h>
using namespace std;
const int Max_money = 30000;
const int Max_item = 25;
int dp[2][Max_money];   // dp[i][j]表示前i个物品，金额j所达到的最大价值
//   但是采用滚动数组以节省内存   //
struct node
{
    int w;
    int v;    // 直接价值
}item[Max_item];
int n,m;     // 分别为总钱数和要买的物品个数
int solve()
{
    memset(dp,0,sizeof(dp));    // 初始化
    int i;
    for(i=1;i<=m;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(j>=item[i].w)    dp[i%2][j] = max(dp[(i-1)%2][j-item[i].w]+item[i].v,dp[(i-1)%2][j]);
            else    dp[i%2][j] = dp[(i-1)%2][j];
        }
    }
    return dp[(i-1)%2][n];
}
int main(void)
{
    // 读入数据
    scanf("%d %d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%d %d",&item[i].w,&item[i].v);
        item[i].v = item[i].v*item[i].w;
    }
    //
    cout<<solve()<<endl;
    return 0;
}
```

**2. DFS爆搜（这道题数据的原因可以写）**
```cpp
// 采用DFS 爆搜 //
// TLE 版本 , 原因：搜的太多了，有很多重复搜了，如果使用hash表判重可能可以提高速度，并且这种搜法也不王道 //
#include<bits/stdc++.h>
using namespace std;
const int Max_money = 30000;
const int Max_item = 25;
struct node
{
    int w;    // 价格
    int v;    // 价值
}item[Max_item];
int ans;
int n,m;     // 分别为总钱数和要买的物品个数
int vis[Max_item];
void dfs(int res,int value)     // res表示当前剩余可支配钱数,value表示当前总价值
{
    if(res==0)
    {
        if(value>ans)   ans = value;
        return;
    }
    else
    {
        for(int i=1;i<=m;i++)
        {
            if(!vis[i]&&res>=item[i].w)
            {
                vis[i] = 1;
                dfs(res-item[i].w,value+item[i].v);
                vis[i] = 0;
            }
        }
        // 最后再判断一下
        if(value>ans)   ans = value;
        return;
    }
}
int main(void)
{
    // 读入数据
    scanf("%d %d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%d %d",&item[i].w,&item[i].v);
        item[i].v = item[i].v*item[i].w;
    }
    //
    ans = 0;
    dfs(n,0);
    printf("%d\n",ans);
    return 0;
}
```
**改进版的DFS（去掉了很多重复搜索）**
```cpp
void dfs(int res,int last,int value)     // res表示当前剩余可支配钱数,last表示上一次选择物品序号，value表示当前总价值
{
    if(res==0)
    {
        if(value>ans)   ans = value;
        return;
    }
    else
    {
        for(int i=last+1;i<=m;i++)
        {
            if(!vis[i]&&res>=item[i].w)
            {
                vis[i] = 1;
                dfs(res-item[i].w,i,value+item[i].v);
                vis[i] = 0;
            }
        }
        // 最后再判断一下
        if(value>ans)   ans = value;
        return;
    }
}
// 然后在main函数中  调用dfs(n,0,0)即可 //
```
**更加王道的DFS搜索**
```cpp
void dfs(int i,int value,int res)     // res表示当前剩余可支配钱数,value表示当前总价值
{
    if(i==m+1)
    {
        if(value>ans)   ans = value;
        return;
    }
    else
    {
        if(res>=item[i].w)
            dfs(i+1,value+item[i].v,res-item[i].w);    // 选择第i件
        dfs(i+1,value,res);   // 不选第i件
    }
}
// 在main函数调用 dfs(1,0,n)即可 //
```
<br><br>
# 5 倍经验日

## 题目背景

现在乐斗有活动了！每打一个人可以获得 5 倍经验！absi2011 却无奈的看着那一些比他等级高的好友，想着能否把他们干掉。干掉能拿不少经验的。

## 题目描述

现在 absi2011 拿出了 $x$ 个迷你装药物（嗑药打人可耻…），准备开始与那些人打了。

由于迷你装药物每个只能用一次，所以 absi2011 要谨慎的使用这些药。悲剧的是，用药量没达到最少打败该人所需的属性药药量，则打这个人必输。例如他用 $2$ 个药去打别人，别人却表明 $3$ 个药才能打过，那么相当于你输了并且这两个属性药浪费了。

现在有 $n$ 个好友，给定失败时可获得的经验、胜利时可获得的经验，打败他至少需要的药量。

要求求出最大经验 $s$，输出 $5s$。

## 输入格式

第一行两个数，$n$ 和 $x$。

后面 $n$ 行每行三个数，分别表示失败时获得的经验 $\mathit{lose}_i$，胜利时获得的经验 $\mathit{win}_i$ 和打过要至少使用的药数量 $\mathit{use}_i$。

## 输出格式

一个整数，最多获得的经验的五倍。

## 样例 #1

### 样例输入 #1

```
6 8
21 52 1
21 70 5
21 48 2
14 38 3
14 36 1
14 36 2
```

### 样例输出 #1

```
1060
```

## 提示

**【Hint】**

五倍经验活动的时候，absi2011 总是吃体力药水而不是这种属性药。

**【数据范围】**

- 对于 $10\%$ 的数据，保证 $x=0$。
- 对于 $30\%$ 的数据，保证 $0\le n\le 10$，$0\le x\le 20$。
- 对于 $60\%$ 的数据，保证 $0\le n,x\le 100$， $10<lose_i,win_i\le 100$，$0\le use_i\le 5$。
- 对于 $100\%$ 的数据，保证 $0\le n,x\le 10^3$，$0<lose_i\le win_i\le 10^6$，$0\le use_i\le 10^3$。

**【题目来源】**

fight.pet.qq.com

absi2011 授权题目
<br><br><br>

## 题解
```cpp
// 01背包进阶版->不装也能有价值//
// 最大的数不会超过10^9，所以还是用 int //
#include<bits/stdc++.h>
using namespace std;
const int maxFri = 1001;
const int maxMed = 1001;
int dp[2][maxMed];   
// 滚动数组，dp[i][j]表示和前i个好友对决，在使用j瓶药的情况下可获得最大经验值
struct node{
    int lose;
    int win;
    int use;
}fri[maxFri];
int n,x;
int solve()
{
    memset(dp[0],0,sizeof(dp[0]));
    int i;
    for(i=1;i<=n;i++)
    {
        for(int j=0;j<=x;j++)    // 注意必须从j=0开始更新 //
        {
            if(j<fri[i].use)    dp[i%2][j]=fri[i].lose+dp[(i-1)%2][j];
            else    dp[i%2][j] = max(fri[i].lose+dp[(i-1)%2][j],fri[i].win+dp[(i-1)%2][j-fri[i].use]);
        }
    }
    return dp[(i-1)%2][x];
}
int main(void)
{
    cin>>n>>x;
    for(int i=1;i<=n;i++)
        scanf("%d %d %d",&fri[i].lose,&fri[i].win,&fri[i].use);
    //
    long long ans = solve();     // 数据范围的锅，最后转换一下即可
    printf("%lld\n",5*ans);    
    return 0;
}
```
<br><br>
# [NOIP2001 普及组] 装箱问题

## 题目描述

有一个箱子容量为 $V$，同时有 $n$ 个物品，每个物品有一个体积。


现在从 $n$ 个物品中，任取若干个装入箱内（也可以不取），使箱子的剩余空间最小。输出这个最小值。

## 输入格式

第一行共一个整数 $V$，表示箱子容量。

第二行共一个整数 $n$，表示物品总数。

接下来 $n$ 行，每行有一个正整数，表示第 $i$ 个物品的体积。

## 输出格式

- 共一行一个整数，表示箱子最小剩余空间。

## 样例 #1

### 样例输入 #1

```
24
6
8
3
12
7
9
7
```

### 样例输出 #1

```
0
```

## 提示

对于 $100\%$ 数据，满足 $0<n \le 30$，$1 \le V \le 20000$。

**【题目来源】**

NOIP 2001 普及组第四题
<br><br>

## 题解
**1. 搜索解法**
```cpp
// 搜索+优化 , 我也没想到优化后这么快 //
#include<bits/stdc++.h>
using namespace std;
const int maxN = 31;
bool flag = false;
int n,V;
int ans;
int vol[maxN];
void dfs(int i,int res)
{
    if(i==n+1||res<=vol[i]||flag)
    {
        if(res==vol[i]) ans=0,flag=true;   // 找到为0的ans，直接全部return快速结束函数
        else if(res<ans) ans = res;
        return;
    }
    else    // 此时必有res>vol[i]
    {
        dfs(i+1,res-vol[i]);  // 选第i个
        dfs(i+1,res);    // 不选第i个
        return;
    }
}
int main(void)
{
    scanf("%d%d",&V,&n);
    for(int i=1;i<=n;i++)
        scanf("%d",vol+i);
    sort(vol+1,vol+n+1);   // 升序排列，注意下标!
    ans = V;
    dfs(1,V);
    cout<<ans<<endl;
    return 0;
}
```
**2. DP解法->化为01背包**   
每件物品的重量为vol[i],价值也为vol[i],转化为前n物品，最大承重为V的背包，求可得到的最大价值的 **01背包问题**  
```cpp
// DP解法->化为01背包 //
#include<bits/stdc++.h>
using namespace std;
const int maxN = 31;
const int maxV = 20001;
int n,V;
int vol[maxN];
int dp[2][maxV];    // 前i件物品取，体积不超过j，所得最大价值
int solve()
{
    memset(dp[0],0,sizeof(dp[0]));    // 初始化
    int i;
    for(i=1;i<=n;i++)
    {
        for(int j=0;j<=V;j++)    // 从0开始更新
        {
            if(j>=vol[i])    dp[i%2][j] = max(dp[(i-1)%2][j-vol[i]]+vol[i],dp[(i-1)%2][j]);
            else    dp[i%2][j] = dp[(i-1)%2][j];
        }
    }
    return V-dp[(i-1)%2][V];
}
int main(void)
{
    scanf("%d%d",&V,&n);
    for(int i=1;i<=n;i++)
        scanf("%d",vol+i);
    
    cout<<solve()<<endl;
    return 0;
}
```
