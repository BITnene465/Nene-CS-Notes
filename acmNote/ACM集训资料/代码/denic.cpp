#include<bits/stdc++.h>
#define MAXN 50010
#define INF 0x3f3f3f3f
using namespace std;
using ll = long long;
//denic模板
ll hd[MAXN],nxt[MAXN],to[MAXN];
ll flw[MAXN],cap[MAXN];
ll depth[MAXN];
ll pos[MAXN];
ll cnt;
ll n;//点数
ll st,ed;
inline void add(ll u, ll v, ll w, ll c){
    cnt++;
    nxt[cnt] = hd[u];
    hd[u] = cnt;
    to[cnt] = v;
    flw[cnt] = w;
    cap[cnt] = c;
}

inline void init(){
    cnt = -1;
    memset(hd,-1,sizeof(hd));
    memset(nxt,-1,sizeof(nxt));
}

inline bool bfs(ll st){
    queue<ll> q;

    for(ll i = 1; i <= n; i++){
        depth[i] = INF;
    }
    depth[st] = 0;
    q.push(st);
    ll u,v;
    while (!q.empty())
    {
        u = q.front();
        q.pop();
        for(ll i = hd[u]; ~i; i = nxt[i]){
            v = to[i];
            if(depth[v] == INF && flw[i] < cap[i]){
                depth[v] = depth[u] + 1;
                q.push(v);
            }
        }
    }
    return depth[ed] != INF;
}

inline ll dfs(ll u, ll flo){
    if(u == ed || flo == 0)return flo;
    ll res = 0;
    ll f;
    ll v;
    for(ll &i = pos[u]; ~i; i = nxt[i]){
        v = to[i];
        if(depth[v] == depth[u] + 1 && (f=dfs(v,min(flo,cap[i] - flw[i]))) > 0){
            flw[i] += f;
            flw[i^1] -= f;
            res += f;flo -= f;
            if(flo == 0)break;
        }
    }
    return res;
}

inline ll search(){
    ll ans = 0;
    while(bfs(st)){
        for(ll i = 1; i <= n; i++){
            pos[i] = hd[i];
        }
        ans += dfs(st,INF);
    }
    return ans;
}
