# ��̬�滮�㷨

## ����

Dynamic Programming,DP��һ���㷨˼��**DP�㷨�������������ص�������������ӽṹ���ʵ�����**  

**���DP������������**

1. ����״̬
2. ״̬ת��
3. �㷨ʵ��

��״̬ת�Ʒ��̴���״̬��**״̬������������Ľ�**��

DP�����Ժͷ����ԣ�

1. ����DP:��˳�ƺ��������ַ���һ���ñ���ʾ
2. ������DP����������DP�������ַ��򣬼�����->��Ҷ & ��Ҷ->����

## �����ӽṹ���ص�������

`<br><br>`

## ����DP�͵��Ʒ�

example:

### 1. ����Ӳ������

```cpp
#include<bits/stdc++.h>
using namespace std;
const int VALUE = 5;  // 5����ֵ��Ӳ��
const int coin[VALUE] = {1,5,10,25,50};  // ������ֵ
const int money = 251;  // ���������
int Min[money];       // ���ܺ�min���������ˣ���ʾ���Ϊmoneyʱ����СӲ����
// ���
void solve()
{
    // ��ʼ��
    Min[0] = 0;
    for(int i=1;i<money;++i)
        Min[i] = INT_MAX;
    // ״̬ת�ƣ�ͬʱ��ֹ���
    for(int i=0;i<VALUE;++i)
        for(int j=coin[i];j<money;++j)
            Min[j] = min(Min[j],Min[j-coin[i]]+1);
}
int main(void)
{
    int m;
    solve();
    while(cin>>m)
        cout<<Min[m]<<endl;
    return 0;
}
```

### 2. ��ӡ����Ӳ�ҵ����

```cpp
#include<bits/stdc++.h>
using namespace std;
const int VALUE = 5;  // 5����ֵ��Ӳ��
const int coin[VALUE] = {1,5,10,25,50};  // ������ֵ
const int money = 251;  // ���������
int Min[money];       // ���ܺ�min���������ˣ���ʾ���Ϊmoneyʱ����СӲ����
int min_path[money];  // ·����¼��
// ���
void solve()
{
    // ��ʼ��
    Min[0] = 0;
    for(int i=1;i<money;++i)
        Min[i] = INT_MAX;
    // ״̬ת�ƣ�ͬʱ��ֹ�����ͬʱ��¼·��
    for(int i=0;i<VALUE;++i)
        for(int j=coin[i];j<money;++j)
        {
            if(Min[j]>Min[j-coin[i]]+1)
            {
                Min[j] = Min[j-coin[i]]+1;
                min_path[j] = coin[i];    // �ﵽ���j�����һöӲ�ҵ����Ϊcoin[i] 
            }
        }
}
void print_path(int m)
{
    while(m)
    {
        cout<<min_path[m]<<" ";
        m=m-min_path[m];
    }
    cout<<endl;
}
int main(void)
{
    int m;
    solve();
    while(cin>>m)      // ���ü��ɣ�����EOF����
    {
        cout<<Min[m]<<endl;
        print_path(m);
    }
    return 0;
}
```

### 3. ����Ӳ�������

```cpp
// ֻҪ�󷽰�������Ҳ���������ɺ������ //
#include<bits/stdc++.h>
using namespace std;
const int type_num = 5;
const int type[type_num] = {1,5,10,25,50};
const int money = 251;   // ������
int dp[money];
void solve()
{
    // init start //
    for(int i=1;i<money;++i)
        dp[i] = 0;
    dp[0] = 1;    // �涨
    // init end //
    for(int i=0;i<type_num;++i)
        for(int j=type[i];j<money;++j)
            dp[j] = dp[j] + dp[j-type[i]];
}
int main(void)
{
    solve();
    int m;
    while(cin>>m)
        cout<<dp[m]<<endl;
    return 0;
}
```

���װ�  (hdu 2069)

```cpp
// hdu 2069 "coin change" //
// Ӳ������ num <= 100 & ��� <= 250 //
// �ø���ά��dp����¼����ϸ��״̬ //
#include<bits/stdc++.h>
using namespace std;
const int money = 251;
const int coin_num = 101;
const int type_num = 5;
const int type[type_num] = {1,5,10,25,50};
int dp[money][coin_num];    //dp[i][j]��ʾʹ��jöӲ�Ҵﵽ���i�������
int ans[money];    //ans[i]��ʾ���i�ĺϷ�������
void solve()
{
    // init //
    dp[0][0] = 1;   // ʣ���dp[i][0] = 0
    //
    for(int i=0;i<type_num;++i)
        for(int j=1;j<coin_num;++j)
            for(int k=type[i];k<money;++k)
                dp[k][j] = dp[k][j] + dp[k-type[i]][j-1];
    //
    for(int i=0;i<money;++i)
        for(int j=0;j<coin_num;++j)
            ans[i] += dp[i][j];
}
int main(void)
{   
    solve();
    int m;
    while(cin>>m)
        cout<<ans[m]<<endl;
    return 0;
}
```

### 4. 01���� ���ޱ��� LCS LIS

```cpp
// 01���� �� dp������Ҫ��ά����¼��Ʒȡ����Ϣ��������Ϣ //
// ͨ������������ٿռ临�Ӷ� //
#include<bits/stdc++.h>
using namespace std;
const int item_num = 20;   //�����Ʒ��
const int weight_max = 100;  //��󱳰�����
typedef struct item{
    int w;
    int v;
}Item;
Item goods[item_num+1];
int N,W;      // N����Ʒ��W�����ܳ���
int dp[2][weight_max+1];   //����dp���� dp[i][j]ԭ����ʾǰi����Ʒ��ȡ������Ϊj������ֵ
void solve()
{
    memset(dp[0],0,sizeof(dp[0]));   // ��dp[0][i]ȫ����ʼ��Ϊ0
    int i;
    for(i=0;i<N;++i)   // һ��Ҫִ��N�θ�ѭ��
    {
        for(int j=0;j<=W;j++)
        {
            if(j<goods[i+1].w)     // ��ֹ���
                dp[(i+1)%2][j] = dp[i%2][j];
            else
                dp[(i+1)%2][j] = max(dp[i%2][j],dp[i%2][j-goods[i+1].w]+goods[i+1].v);
        }   
    }
    // print
    cout<<"max_value="<<dp[i%2][W]<<endl;
}
int main(void)
{
    int T;  //����������
    cin>>T;
    while(T--)
    {
        cin>>N>>W;
        for(int i=1;i<=N;++i)
            scanf("%d %d",&goods[i].w,&goods[i].v);
        solve();
    }
    return 0;
}
```

```cpp
// ���ޱ��� //
// ����01������dp����ֻ��һά����¼������Ϣ���� //
#include<bits/stdc++.h>
using namespace std;
const int item_num = 20;
const int weight_max = 100;
typedef struct item{
    int w;
    int v;
} Item;
Item goods[item_num+1];
int N,W;
int dp[weight_max];
void solve()
{
    memset(dp,0,sizeof(dp));  
    for(int i=1;i<=W;i++)    // dp[0]=0һ������
        for(int j=1;j<=N;j++)
        {
            if(i>=goods[j].w)
                dp[i] = max(dp[i],dp[i-goods[j].w]+goods[j].v);
        }
    cout<<"max_value="<<dp[W]<<endl;
}
int main(void)
{
    int T;
    cin>>T;
    while(T--)
    {
        cin>>N>>W;
        for(int i=1;i<=N;i++)
            scanf("%d %d",&goods[i].w,&goods[i].v);
        solve();
    }
    return 0;
}
```

LCS, longest common subsequence

```cpp

```

LIS,

```cpp

```

`<br><br>`

## ��ϸ���ⱳ������

### һ�� 01����

**easy!**
**״̬��** $dp[i][j]$ ��ʾǰi����Ʒ��ȡ��������������j�����ܴﵽ������ֵ��

**��ʼ����** $dp[0][k] = 0 , k=0,1,2,3,...,max\_vol  , dp[k][0] = 0 , k=0,1,2,3,...,max\_item$

**״̬ת�ƣ�** $dp[i][j] = max\{dp[i-1][j] , dp[i-1][j-w[i]]+v[i]\}$

**���룺**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int item_num = 20;   //�����Ʒ��
const int weight_max = 100;  //��󱳰�����
typedef struct item{
    int w;
    int v;
}Item;
Item goods[item_num+1];
int N,W;      // N����Ʒ��W�����ܳ���
int dp[2][weight_max+1];   //����dp���� dp[i][j]ԭ����ʾǰi����Ʒ��ȡ������Ϊj������ֵ
void solve()
{
    memset(dp[0],0,sizeof(dp[0]));   // ��dp[0][i]ȫ����ʼ��Ϊ0
    int i;
    for(i=0;i<N;++i)   // һ��Ҫִ��N�θ�ѭ��
    {
        for(int j=0;j<=W;j++)
        {
            if(j<goods[i+1].w)     // ��ֹ���
                dp[(i+1)%2][j] = dp[i%2][j];
            else
                dp[(i+1)%2][j] = max(dp[i%2][j],dp[i%2][j-goods[i+1].w]+goods[i+1].v);
        }   
    }
    // print
    cout<<"max_value="<<dp[i%2][W]<<endl;
}
```

**����һά�����Ż���(��õİ汾)**

```cpp
// W Ϊ���������� , N Ϊ��Ʒ����
void solve()
{
    memset(dp,0,sizeof(dp));  
    for(int i=1;i<=N;i++)    // dp[0]=0һ������
        for(int j=W;j>=goods[i].w;j--)
        {
            dp[j] = max(dp[j],dp[j-goods[i].w]+goods[i].v);
        }
    cout<<dp[W]<<endl;
}
```

### ������ȫ���������ޱ�����

**˼·һ������01����˼·**

**״̬��** $dp[i][j]$ ��ʾǰi����Ʒ��ȡ������������j�����ܴﵽ������ֵ

**��ʼ����** **ͬ01����**

**״̬ת�ƣ�** $dp[i][j] = {max}_{k \geq 0}\{dp[i-1][j-k*w[i]] + k*v[i]\}$

**����**

```cpp

```

**�Ż�**

ת�Ʒ��̱任��$dp[i][j-v[i]] = {max}_{k \geq 0}\{dp[i-1][j-w[i]-k*w[i]] + k*v[i]\}$

����ԭ����ת�Ʒ��̣�
$dp[i][j] = max\{dp[i-1][j] , dp[i][j-w[i]]+v[i]\}$

**�Ż�����루����һά�������飩**

```cpp
// W Ϊ���������� , N Ϊ��Ʒ����
void solve()
{
    memset(dp,0,sizeof(dp));  
    for(int i=1;i<=N;i++)    // dp[0]=0һ������
        for(int j=goods[i].w;j<=W;j++)
        {
            dp[j] = max(dp[j],dp[j-goods[i].w]+goods[i].v);
        }
    cout<<dp[W]<<endl;
}
```

`<br><br>`

**˼·��**
ÿ����Ʒ�������ȡ����Σ�������dp����ʱ����Ҫ�Ѿ�ȡ�õ���Ʒ��Ϣ

**״̬��** $dp[j]$ ��ʾ������������jʱ�����ܴﵽ������ֵ

**��ʼ����** $dp[j]=0,j=0,1,2,3,...$

**״̬ת�ƣ�** $dp[j]={max}_{1 \leq k \leq max\_item}\{dp[j-w[k]]+v[k]\}$

**���룺**

```cpp
// W Ϊ���������� , N Ϊ��Ʒ����
void solve()
{
    memset(dp,0,sizeof(dp));  
    for(int i=1;i<=W;i++)    // dp[0]=0һ������
        for(int j=1;j<=N;j++)
        {
            if(i>=goods[j].w)
                dp[i] = max(dp[i],dp[i-goods[j].w]+goods[j].v);
        }
    cout<<"max_value="<<dp[W]<<endl;
}
```

### �������ر���

### �ġ���ϱ���

### �塢���鱳��

### ����

## �ݹ�DP�ͼ��仯����

�� **poj 1163 "The Triangle"** ��ʼ��

���Ƚ��ܱ��Ѻ�����DP������

**����**

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[105][105];   // ��Ŵ�1��ʼ
int n;  // ����
int ans = 0;
void dfs(int i,int j,int sum)
{
    if(i==n+1)
    {
        if(ans<sum) ans = sum;
        return;
    }
    else
    {
        dfs(i+1,j+1,sum+a[i][j]);
        dfs(i+1,j,sum+a[i][j]);
        return;
    }
}
int main(void)
{
    cin>>n;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=i;j++)
            scanf("%d",&a[i][j]);
    dfs(1,1,0);
    cout<<ans<<endl;
    return 0;
}
// ������״̬ͼ���� //
```

**��ͳDP**

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[105][105];   // ��Ŵ�1��ʼ
int n;  // ����
int ans = 0;
int dp[105];    // ��������,dp[i][j]��ʾ�Ӷ��㵽(i,j)��·������
void solve()
{
    memset(dp,0,sizeof(dp));
    dp[1] = a[1][1];   // ��ʼ��
    for(int i=2;i<=n;i++)
    {
        for(int j=n;j>=1;j--)   // ���뵹�����
        {
                dp[j] = max(dp[j],dp[j-1])+a[i][j];
        //  �ɳ�ʼ���Ͳ�������֪����dp[j]��dp[j-1]û�����壬��ôһ��Ϊ0,�������ݾ�Ϊ�Ǹ���ʱ�˵��Ƴ���
        }
    }
    //
    for(int i=1;i<=n;i++)
        if(ans<dp[i])   ans = dp[i];
    return; 
}
int main(void)
{
    cin>>n;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=i;j++)
            scanf("%d",&a[i][j]);
    solve();
    cout<<ans<<endl;
    return 0;
}
```

**��ͳDP�Ż���**

```cpp
int dp[106];  
// ��������,dp[i][j]��ʾ�Ӷ���(i,j)���ײ��·������
void solve()
{
    memset(dp,0,sizeof(dp));
    for(int j=1;j<=n;j++)  //��ʼ��
        dp[j] = a[n][j]; 
    for(int i=n-1;i>=1;i--)    // �ӵ����ڶ��㵽��һ��
        for(int j=1;j<=i;j++)    // ����˳�����
            dp[j] = max(dp[j],dp[j+1])+a[i][j];
    ans = dp[1];
    return;    
}
```

**�ݹ鱩���棨�ٶȺͱ��Ѳ�ࣩ**

���ۿɼ����ظ��������˷��ڴ�

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[106][106];   // ��Ŵ�1��ʼ
int n;  // ����
int dfs(int i,int j)     // ̽���ӵ�(i,j)���ײ�����·����
{
    if(i==n)
        return a[i][j];    // ����ײ�
    else
        return max(dfs(i+1,j),dfs(i+1,j+1))+a[i][j];
}  
int main(void)
{
    cin>>n;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=i;j++)
            scanf("%d",&a[i][j]);
    cout<<dfs(1,1)<<endl;   // �ݹ��ֱ��
    return 0;
}
```

**�ݹ��Ż� -> �ݹ� + ���仯����**

```cpp
int dp[106][106];
// dpȫ����ʼ��Ϊ-1 ����
int dfs(int i,int j)     // ̽���ӵ�(i,j)���ײ�����·����
{
    if(i==n)
        return a[i][j];    // ����ײ�
    if(dp[i][j]>=0)
        return dp[i][j];   // ���䣡������˾Ͳ������ˣ�
    else
        return dp[i][j]=max(dfs(i+1,j),dfs(i+1,j+1))+a[i][j];
}  
```

<br>

### ���仯����

**���ƣ�** �߼����Ӽ������

`<br><br>`

## ����DP

### ʯ�Ӻϲ�

**һ�� ��״**  

**״̬��** $dp[i][j]$ ��ʾ����$[i,j]$ ����ʯ�ӶѺϲ�����С����  
**��ʼ����** $dp[i][i]=0\qquad i=1,2,3,\dots$   
**ת�Ʒ��̣�** $dp[i][j]={min}_{i\leq k \leq j-1}\{dp[i][k]+dp[k+1][j]\}+sum(i,j)$  
���У�$sum(i,j)$��ʾ��i��ʯ�ӵ���j��ʯ�ӵ������ܺ�  

**���루�ݹ�+���仯������-> O(n^3)**
```cpp
// ʯ�Ӻϲ�(��״) ,����С����//
// �ݹ� + ���仯���� //
#include<bits/stdc++.h>
using namespace std;
int dp[301][301];
int n;
int stone[301];
int sum[301];   
int dfs(int i,int j)
{
    if(dp[i][j]>0)  return dp[i][j];
    else if(i==j)   return 0;
    else
    {
        int Min = INT_MAX;
        for(int k=i;k<j;k++)
        {
            dp[i][k] = dfs(i,k);
            dp[k+1][j] = dfs(k+1,j);
            if(Min>dp[i][k]+dp[k+1][j]) Min = dp[i][k]+dp[k+1][j];
        }
        return dp[i][j] = Min + sum[j] - sum[i-1];
    }
}
int main(void)
{
    cin>>n;
    sum[0] = 0;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",stone+i);
        sum[i] = sum[i-1] + stone[i];
    }
    memset(dp,0,sizeof(dp));
    cout<<dfs(1,n)<<endl;
    return 0;
}
```

**���루ѭ����+ƽ���ı����Ż���-> �ӽ�O(n^2)**
```cpp
// ʯ�Ӻϲ�(��״) ,����С����//
// ѭ�� + ƽ���ı����Ż� //
#include<bits/stdc++.h>
using namespace std;
int dp[301][301];
int n;
int stone[301];
int sum[301]; 
int s[301][301];  // s[i][j]������¼����[i,j]����ѷָ��
int Minval()
{
    // ��ʼ��
    for(int i=1;i<=n;i++)
    {
        dp[i][i] = 0;
        s[i][i] = i;
    }
    //
    for(int len=1;len<n;len++)
    {
        for(int i=1;i<=n-len;i++)
        {
            int j = i + len;
            dp[i][j] = INT_MAX;
            for(int k=s[i][j-1];k<=s[i+1][j];k++)   // ƽ���ı����Ż�
            {
                if(dp[i][k]+dp[k+1][j]+sum[j]-sum[i-1]<dp[i][j])
                {
                    dp[i][j] = dp[i][k]+dp[k+1][j]+sum[j]-sum[i-1];
                    s[i][j] = k;    // ��¼��ѷָ��
                }
            }
        }
    }
    //
    return dp[1][n];
}
int main(void)
{
    cin>>n;
    sum[0] = 0;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",stone+i);
        sum[i] = sum[i-1] + stone[i];
    }
    cout<<Minval()<<endl;
    return 0;
}
```

<br>

**������״**  

ת��Ϊ2*n���ȵ���״�ϲ�ʯ��  

**����**  
```cpp
// ����ʯ�Ӻϲ� �� ��������С���� //
// ������Ϊ2*n�������� //
#include<bits/stdc++.h>
using namespace std;
int stone[250];
int n;
int dp[250][250];  // ��¼��С����
int dp2[250][250]; // ��¼��󻨷�
int ans1, ans2;
int sum[250];  // ������¼ǰ׺��
int dfs(int i,int j)
{
    if(i==j)
        return 0;   // ��С����
    else if(dp[i][j]>0)
        return dp[i][j]; // ���䣬�Ѿ��������
    else   
    {
        int Min = INT_MAX;
        for(int k=i;k<=j-1;k++)
        {
            dp[i][k] = dfs(i,k);
            dp[k+1][j] = dfs(k+1,j);
            if(Min>dp[i][k]+dp[k+1][j]) Min = dp[i][k]+dp[k+1][j];
        }
        return dp[i][j] = Min + sum[j]-sum[i-1];
    } 
}
int dfs2(int i,int j)
{
    if(i==j)    return 0;
    else if(dp2[i][j]>0) return dp2[i][j];
    else
    {
        int Max = 0;
        for(int k=i;k<=j-1;k++)
        {
            dp2[i][k] = dfs2(i,k);
            dp2[k+1][j] = dfs2(k+1,j);
            if(Max<dp2[i][k]+dp2[k+1][j]) Max = dp2[i][k]+dp2[k+1][j];
        }
        return dp2[i][j] = Max + sum[j] - sum[i-1];
    }
}
int main(void)
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",stone+i);
        stone[n+i] = stone[i];
    }
    // ����ǰ׺��
    sum[0] = 0;
    for(int i=1;i<=2*n;i++)
        sum[i] = sum[i-1]+stone[i];
    // end
    memset(dp,0,sizeof(dp));
    memset(dp2,0,sizeof(dp2));
    dfs(1,2*n);
    dfs2(1,2*n);
    ans1 = INT_MAX;
    ans2 = 0;
    for(int i=1;i<=n;i++)
    {
        ans1 = min(ans1,dp[i][n-1+i]);
        ans2 = max(ans2,dp2[i][n-1+i]);
    }
    cout<<ans1<<endl<<ans2<<endl;
    return 0;
}
```

<br><br>

### ���Ĵ�

**״̬��**  $ dp[i][j]$ ��ʾ ���Ӵ�$s[i,j]$��Ϊ���Ĵ�����С���� 

**��ʼ����** $dp[i][i+1]=min\{w[i],w[i+1]\} \qquad dp[i][i]=0$  

**ת�Ʒ��̣�** 
$$
dp[i][j]=
\begin{cases}
    dp[i-1][j-1] & \textit{if\quad $s[i]=s[j]$}\\
    min\{dp[i+1][j]+w[i],dp[i][j-1]+w[j]\} & \textit{if\quad $s[i] \neq s[j]$} \\
\end{cases}
$$
**˵����**  

**����**  
```cpp
// poj 3280 "Cheapest Palindrome" //
// ����DP �� ���Ĵ� //
#include<bits/stdc++.h>
using namespace std;
char s[2100];
int dp[2100][2100];
int n,m;      // ��n����ͬ��Сд��ĸ������Ϊm���ַ���
int cost[100];   // add & del Ч����ͬ��̰��ȡ��С���۵Ĳ�������
int dfs(int i,int j)
{
    if(j<=i)    return 0;
    else if(dp[i][j]>0) return dp[i][j];
    else if(s[i]==s[j]) return dp[i][j] = dfs(i+1,j-1);
    else    return dp[i][j] = min(dfs(i+1,j)+cost[s[i]],dfs(i,j-1)+cost[s[j]]);
}
int main(void)
{
    cin>>n>>m;
    cin>>s;
    int x,y;
    char ch;
    for(int i=0;i<n;i++)
    {
        cin>>ch>>x>>y;
        cost[ch] = min(x,y);
    }
    cout<<dfs(0,m-1)<<endl;
    return 0;
}
```


### �����Ӵ�����ͳ�� (easy!)

**״̬��** $dp[i][j]$ ,bool type, ��ʾ�Ӵ� $[i,j]$ �Ƿ�Ϊ�����ַ���   
**ת�Ʒ��̣�**    
$$dp[i][j]=
\begin{cases}
    dp[i-1][j-1] & \textit{if $s[i]=s[j]$}\\
    false & \textit{if $s[i]\neq s[j]$} \\
    true & \textit{if $j-i=0\quad$}\\ 
\end{cases}$$

### ����������
**hdu 4632 "Palindrome Subsequence"**   
![1689258265163](image/DP�㷨/1689258265163.png)

**״̬��**  $dp[i][j]$ ��ʾ�Ӵ�$s[i,j]$�Ļ�����������    
**��ʼ����**  
**״̬ת�ƣ�**   
**���룺**   
```cpp
// hdu 4632 "Palindrome Subsequence" //
// ����DP //
// TLE�汾 �� ���仯������Ȼʱ�临�ӶȺ�ѭ����һ�������ǳ������ߣ����³�ʱ//
#include<bits/stdc++.h>
using namespace std;
int T;
int dp[1001][1001];
char s[1002];
const int mod = 10007;
int ans[51];
int dfs(int i,int j)
{
    if(i>j) return 0;
    else if(i==j)    return 1;
    else if(dp[i][j]>0) return dp[i][j];
    else 
    {
        if(s[i]==s[j])
        return dp[i][j] = (dfs(i,j-1)+dfs(i+1,j)+1)%mod;  //���1ʮ�ֹؼ�
        else
        return dp[i][j] = (dfs(i,j-1)+dfs(i+1,j)-dfs(i+1,j-1))%mod;
    }
}
int main(void)
{
    cin>>T;
    for(int i=1;i<=T;i++)
    {
        scanf("%s",s);
        memset(dp,0,sizeof(dp));
        int len = strlen(s);
        ans[i] = dfs(0,len-1);
    }
    // print
    for(int i=1;i<=T;i++)
        printf("Case %d: %d\n",i,ans[i]);
    return 0;
}
```
**���루ѭ���棩**
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e3+100;
const int mod = 1e4+7;
int dp[N][N];
char s[N];
int main(){
	int t;
	scanf("%d",&t);
	for(int o = 1; o <= t; o++){
		memset(dp,0,sizeof(dp));
		scanf("%s",s+1);
		int len = strlen(s+1);
		for(int i = 1; i <= len; i++) dp[i][i]=1;
		for(int i = 2; i <= len; i++){
			for(int l = 1; l <= len-i+1; l++){
				int r = l+i-1;
				dp[l][r]=(dp[l][r-1]+dp[l+1][r]-dp[l+1][r-1]+mod)%mod;
				if(s[l]==s[r]) dp[l][r]=(dp[l][r]+dp[l+1][r-1]+1)%mod;
			}
		}
		printf("Case %d:",o);
		printf("%d\n",dp[1][len]);
	}
	return 0;
}
```
<br><br>

## ����DP
����һ��ӵ�����õݹ����ʵ����ݽṹ��ʹ��DP���߼��ȽϺö�  

### ̸һ̸��ô�洢���ṹ

���ô洢������  
- �ڽӱ�ͼ������������棩
- ���ӱ�ʾ�����������ڽӱ�  
  ����ڽӱ������ͼʱ��û�и������ȼ������ӱ�ʾ������ʱ���и��ӹ�ϵ��
- �����ֵܱ�ʾ�����ö������洢��
- ����˫�ױ�ʾ��

���巽�������������뷽ʽ����;������  

### ����
һ��hdu 1520 "Anniversary Party"  

**״̬��** $dp[i][0],dp[i][1]$ �ֱ��ʾ��iΪ���ڵ����±�������ѡ�ú�ѡ�ýڵ�i������£��ɵõ������Ȩֵ��   
**��ʼ����** ��Ҷi��$dp[i][0]=0,dp[i][1]=value[i]$  
**ת�Ʒ��̣�**
$$
\begin{cases}
    dp[i][0] = \sum_{j \in child(i)}max\{dp[j][0],dp[j][1]\} \\
    dp[i][1] = \sum_{j \in child(i)}dp[j][0] \quad +\quad value[i] \\
\end{cases}
$$

**����->����DP**  
ÿ���ڵ㶼�պñ���һ�飬ʱ�临�Ӷ�ΪO(n)  
```cpp
// hdu 1520 "Aniversary Party" //
// ����DP //
#include<bits/stdc++.h>
using namespace std;
const int N = 6005; //���ڵ���
vector<int> tree[N];  // ���ӱ�ʾ��
int value[N]; // Ȩֵ
int n;   // �������
int father[N];  // ����Ѱ�Ҹ��ڵ�
int dp[N][2];  // dp[i][0]��dp[i][1]�ֱ��ʾ��ѡ�ú�ѡ�ýڵ�i����iΪ���ڵ㣬�ɵõ������Ȩֵ��
void dfs(int x)
{
    dp[x][0] = 0;
    dp[x][1] = value[x];
    for(int i=0;i<tree[x].size();i++)
    {
        int child = tree[x][i];
        dfs(child);    // ������һ�£�ʹ�ú�����ֵ�ɼ�
        dp[x][0] += max(dp[child][1],dp[child][0]);
        dp[x][1] += dp[child][0];
    }
    return;
} 
int main(void)
{
    while(~scanf("%d",&n))
    {
        for(int i=1;i<=n;i++)
        {
            scanf("%d",value+i);
            tree[i].clear();  // ��ʼ��
            father[i] = -1;   // ��ʼ��
        }
        int a,b;
        while(1)
        {
            scanf("%d %d",&a,&b);
            if(a==0&&b==0)  break;
            tree[b].push_back(a);
            father[a] = b;    // b��a�ĸ���
        }
        int root=1;
        while(father[root]!=-1) root = father[root];  // Ѱ�Ҹ��ڵ�
        dfs(root);
        cout<<max(dp[root][0],dp[root][1])<<endl;
    }
    return 0;
}
```
<br>

����hdu 2196 "Computer"  











