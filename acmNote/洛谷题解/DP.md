# ������ͧ

## ��Ŀ����

������ͧ���ֲ��ڳ����������� $n$ ����ͧ����վ $1,2,\cdots,n$���οͿ�����Щ��ͧ����վ������ͧ���������ε��κ�һ����ͧ����վ�黹��ͧ����ͧ����վ $i$ ����ͧ����վ $j$ ֮������Ϊ $r(i,j)$��$1\le i\lt j\le n$���������һ���㷨�����������ͧ����վ $1$ ����ͧ����վ $n$ ������������

## �����ʽ

��һ������һ�������� $n$����ʾ�� $n$ ����ͧ����վ���������� $n-1$ ����һ������� $r(i,j)$��$1\le i<j\le n$����

## �����ʽ

���������Ĵ���ͧ����վ $1$ ����ͧ����վ $n$ ������������

## ���� #1

### �������� #1

```
3
5 15
7
```

### ������� #1

```
12
```

## ��ʾ

$n\le 200$����֤����������κ�ʱ����ֵ�������� $10^6$��  
<br><br>  
  
## ���
**1. dp�ⷨ:**  
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxN = 201;    // ��Ŵ�1��ʼ
typedef long long ll;
ll dp[maxN];
ll dis[maxN][maxN];
int n;
void solve()
{
    memset(dp,1000000,sizeof(dp));     // �㹻������ݼ���
    dp[1] = 0;  //��ʼ��
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

# [NOIP2006 �ռ���] ���ĵĽ���

## ��Ŀ����

��������ܿ��ģ����ﹺ�õ��·���Ҫ��Կ���ˣ��·�����һ�����Լ�ר�õĺܿ��ķ��䡣���������˵��ǣ������������˵������ķ�����Ҫ������Щ��Ʒ����ô���ã���˵���㣬ֻҪ������$N$ԪǮ���С�������һ������Ϳ�ʼ��Ԥ�㣬����������Ķ���̫���ˣ��϶��ᳬ�������޶���$N$Ԫ�����ǣ�����ÿ����Ʒ�涨��һ����Ҫ�ȣ���Ϊ$5$�ȣ�������$1-5$��ʾ����$5$������Ҫ���������������ϲ鵽��ÿ����Ʒ�ļ۸񣨶�������Ԫ������ϣ���ڲ�����$N$Ԫ�����Ե���$N$Ԫ����ǰ���£�ʹÿ����Ʒ�ļ۸�����Ҫ�ȵĳ˻����ܺ����

���$j$����Ʒ�ļ۸�Ϊ$v[j]$����Ҫ��Ϊ$w[j]$����ѡ����$k$����Ʒ���������Ϊ$j_1,j_2,��,j_k$����������ܺ�Ϊ��

$v[j_1] \times w[j_1]+v[j_2] \times w[j_2]+ ��+v[j_k] \times w[j_k]$��

��������������һ������Ҫ��Ĺ��ﵥ��

## �����ʽ

��һ�У�Ϊ$2$������������һ���ո������$n,m$������$N(<30000)$��ʾ��Ǯ����$m(<25)$Ϊϣ��������Ʒ�ĸ�������

�ӵ�$2$�е���$m+1$�У���$j$�и����˱��Ϊ$j-1$����Ʒ�Ļ������ݣ�ÿ����$2$���Ǹ�����$v,p$������$v$��ʾ����Ʒ�ļ۸�$(v \le 10000)$��$p$��ʾ����Ʒ����Ҫ��($1-5$)

## �����ʽ

$1$����������Ϊ��������Ǯ������Ʒ�ļ۸�����Ҫ�ȳ˻����ܺ͵����ֵ$(<100000000)$��

## ���� #1

### �������� #1

```
1000 5
800 2
400 5
300 5
400 3
200 2
```

### ������� #1

```
3900
```

## ��ʾ

NOIP 2006 �ռ��� �ڶ���   
<br><br>
## ���
**1. dp�ⷨ--01����**  
```cpp
// P1060 ���ĵĽ��� //
// dp�ⷨ��01���� //
#include<bits/stdc++.h>
using namespace std;
const int Max_money = 30000;
const int Max_item = 25;
int dp[2][Max_money];   // dp[i][j]��ʾǰi����Ʒ�����j���ﵽ������ֵ
//   ���ǲ��ù��������Խ�ʡ�ڴ�   //
struct node
{
    int w;
    int v;    // ֱ�Ӽ�ֵ
}item[Max_item];
int n,m;     // �ֱ�Ϊ��Ǯ����Ҫ�����Ʒ����
int solve()
{
    memset(dp,0,sizeof(dp));    // ��ʼ��
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
    // ��������
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

**2. DFS���ѣ���������ݵ�ԭ�����д��**
```cpp
// ����DFS ���� //
// TLE �汾 , ԭ���ѵ�̫���ˣ��кܶ��ظ����ˣ����ʹ��hash�����ؿ��ܿ�������ٶȣ����������ѷ�Ҳ������ //
#include<bits/stdc++.h>
using namespace std;
const int Max_money = 30000;
const int Max_item = 25;
struct node
{
    int w;    // �۸�
    int v;    // ��ֵ
}item[Max_item];
int ans;
int n,m;     // �ֱ�Ϊ��Ǯ����Ҫ�����Ʒ����
int vis[Max_item];
void dfs(int res,int value)     // res��ʾ��ǰʣ���֧��Ǯ��,value��ʾ��ǰ�ܼ�ֵ
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
        // ������ж�һ��
        if(value>ans)   ans = value;
        return;
    }
}
int main(void)
{
    // ��������
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
**�Ľ����DFS��ȥ���˺ܶ��ظ�������**
```cpp
void dfs(int res,int last,int value)     // res��ʾ��ǰʣ���֧��Ǯ��,last��ʾ��һ��ѡ����Ʒ��ţ�value��ʾ��ǰ�ܼ�ֵ
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
        // ������ж�һ��
        if(value>ans)   ans = value;
        return;
    }
}
// Ȼ����main������  ����dfs(n,0,0)���� //
```
**����������DFS����**
```cpp
void dfs(int i,int value,int res)     // res��ʾ��ǰʣ���֧��Ǯ��,value��ʾ��ǰ�ܼ�ֵ
{
    if(i==m+1)
    {
        if(value>ans)   ans = value;
        return;
    }
    else
    {
        if(res>=item[i].w)
            dfs(i+1,value+item[i].v,res-item[i].w);    // ѡ���i��
        dfs(i+1,value,res);   // ��ѡ��i��
    }
}
// ��main�������� dfs(1,0,n)���� //
```
<br><br>
# 5 ��������

## ��Ŀ����

�����ֶ��л�ˣ�ÿ��һ���˿��Ի�� 5 �����飡absi2011 ȴ���εĿ�����һЩ�����ȼ��ߵĺ��ѣ������ܷ�����Ǹɵ����ɵ����ò��پ���ġ�

## ��Ŀ����

���� absi2011 �ó��� $x$ ������װҩ��ҩ���˿ɳܡ�����׼����ʼ����Щ�˴��ˡ�

��������װҩ��ÿ��ֻ����һ�Σ����� absi2011 Ҫ������ʹ����Щҩ��������ǣ���ҩ��û�ﵽ���ٴ�ܸ������������ҩҩ�����������˱��䡣�������� $2$ ��ҩȥ����ˣ�����ȴ���� $3$ ��ҩ���ܴ������ô�൱�������˲�������������ҩ�˷��ˡ�

������ $n$ �����ѣ�����ʧ��ʱ�ɻ�õľ��顢ʤ��ʱ�ɻ�õľ��飬�����������Ҫ��ҩ����

Ҫ���������� $s$����� $5s$��

## �����ʽ

��һ����������$n$ �� $x$��

���� $n$ ��ÿ�����������ֱ��ʾʧ��ʱ��õľ��� $\mathit{lose}_i$��ʤ��ʱ��õľ��� $\mathit{win}_i$ �ʹ��Ҫ����ʹ�õ�ҩ���� $\mathit{use}_i$��

## �����ʽ

һ������������õľ�����屶��

## ���� #1

### �������� #1

```
6 8
21 52 1
21 70 5
21 48 2
14 38 3
14 36 1
14 36 2
```

### ������� #1

```
1060
```

## ��ʾ

**��Hint��**

�屶������ʱ��absi2011 ���ǳ�����ҩˮ��������������ҩ��

**�����ݷ�Χ��**

- ���� $10\%$ �����ݣ���֤ $x=0$��
- ���� $30\%$ �����ݣ���֤ $0\le n\le 10$��$0\le x\le 20$��
- ���� $60\%$ �����ݣ���֤ $0\le n,x\le 100$�� $10<lose_i,win_i\le 100$��$0\le use_i\le 5$��
- ���� $100\%$ �����ݣ���֤ $0\le n,x\le 10^3$��$0<lose_i\le win_i\le 10^6$��$0\le use_i\le 10^3$��

**����Ŀ��Դ��**

fight.pet.qq.com

absi2011 ��Ȩ��Ŀ
<br><br><br>

## ���
```cpp
// 01�������װ�->��װҲ���м�ֵ//
// ���������ᳬ��10^9�����Ի����� int //
#include<bits/stdc++.h>
using namespace std;
const int maxFri = 1001;
const int maxMed = 1001;
int dp[2][maxMed];   
// �������飬dp[i][j]��ʾ��ǰi�����ѶԾ�����ʹ��jƿҩ������¿ɻ�������ֵ
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
        for(int j=0;j<=x;j++)    // ע������j=0��ʼ���� //
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
    long long ans = solve();     // ���ݷ�Χ�Ĺ������ת��һ�¼���
    printf("%lld\n",5*ans);    
    return 0;
}
```
<br><br>
# [NOIP2001 �ռ���] װ������

## ��Ŀ����

��һ����������Ϊ $V$��ͬʱ�� $n$ ����Ʒ��ÿ����Ʒ��һ�������


���ڴ� $n$ ����Ʒ�У���ȡ���ɸ�װ�����ڣ�Ҳ���Բ�ȡ����ʹ���ӵ�ʣ��ռ���С����������Сֵ��

## �����ʽ

��һ�й�һ������ $V$����ʾ����������

�ڶ��й�һ������ $n$����ʾ��Ʒ������

������ $n$ �У�ÿ����һ������������ʾ�� $i$ ����Ʒ�������

## �����ʽ

- ��һ��һ����������ʾ������Сʣ��ռ䡣

## ���� #1

### �������� #1

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

### ������� #1

```
0
```

## ��ʾ

���� $100\%$ ���ݣ����� $0<n \le 30$��$1 \le V \le 20000$��

**����Ŀ��Դ��**

NOIP 2001 �ռ��������
<br><br>

## ���
**1. �����ⷨ**
```cpp
// ����+�Ż� , ��Ҳû�뵽�Ż�����ô�� //
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
        if(res==vol[i]) ans=0,flag=true;   // �ҵ�Ϊ0��ans��ֱ��ȫ��return���ٽ�������
        else if(res<ans) ans = res;
        return;
    }
    else    // ��ʱ����res>vol[i]
    {
        dfs(i+1,res-vol[i]);  // ѡ��i��
        dfs(i+1,res);    // ��ѡ��i��
        return;
    }
}
int main(void)
{
    scanf("%d%d",&V,&n);
    for(int i=1;i<=n;i++)
        scanf("%d",vol+i);
    sort(vol+1,vol+n+1);   // �������У�ע���±�!
    ans = V;
    dfs(1,V);
    cout<<ans<<endl;
    return 0;
}
```
**2. DP�ⷨ->��Ϊ01����**   
ÿ����Ʒ������Ϊvol[i],��ֵҲΪvol[i],ת��Ϊǰn��Ʒ��������ΪV�ı�������ɵõ�������ֵ�� **01��������**  
```cpp
// DP�ⷨ->��Ϊ01���� //
#include<bits/stdc++.h>
using namespace std;
const int maxN = 31;
const int maxV = 20001;
int n,V;
int vol[maxN];
int dp[2][maxV];    // ǰi����Ʒȡ�����������j����������ֵ
int solve()
{
    memset(dp[0],0,sizeof(dp[0]));    // ��ʼ��
    int i;
    for(i=1;i<=n;i++)
    {
        for(int j=0;j<=V;j++)    // ��0��ʼ����
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
