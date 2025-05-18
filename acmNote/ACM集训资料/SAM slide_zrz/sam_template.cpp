const int N(1e6+5);
class Suffix_Automaton
{
    private:
        static const int maxn=N<<1;
        int last,cnt,nxt[maxn][26],fa[maxn],len[maxn],n;
        //int size[maxn]; 根据题面处理信息 以right集合大小维护出现次数为例
        inline const void extend(const char c)
        {
            int p(last);
            const int np(++cnt);
            len[last=np]=len[p]+1;
            //size[np]=1 需要维护的时候维护
            for (;p&&!nxt[p][c];p=fa[p])nxt[p][c]=np;
            if (!p)return fa[np]=1,void();
            const int q(nxt[p][c]);
            if (len[q]==len[p]+1)return fa[np]=q,void();
            const int nq(++cnt);
            len[nq]=len[p]+1;
            memcpy(nxt[nq],nxt[q],sizeof(nxt[q]));
            fa[nq]=fa[q];fa[q]=fa[np]=nq;
            for (;nxt[p][c]==q;p=fa[p])nxt[p][c]=nq;
        }
        /* 可能不用
        int tot[N],rnk[maxn];
        inline const void radixsort()
        {
            for (int i(1);i<=cnt;i++)tot[len[i]]++;
            for (int i(1);i<=n;i++)tot[i]+=tot[i-1];
            for (int i(1);i<=cnt;i++)rnk[tot[len[i]]--]=i;
        }
        */
        vector<int>son[maxn];
        inline const void dfs(int p)
        {
            for (const auto &q:son[p])dfs(q),size[p]+=size[q];
        }
        //匹配
        inline const int match(char *t)
        {
            const int m(strlen(t+1));
            int p(1);
            for (int i(1);i<=m;i++)
            {
                const char c(t[i]-'a');
                for (;!nxt[p][c];p=fa[p]);
                if (!p)p=1;
                else p=nxt[p][c];
            }
            return p;
        }
        //子串定位
        int anc[maxn][20],loc[N];
        //当然直接把fa数组改为二维就行了 因为要和一般板子分离 就用anc了
        // loc[i]表示前缀i所在的np节点 在extend时标记上即可
        inline const int match(const int &l,const int &r)
        {
            int p(loc[r]);
            for (int i(19);~i;i--)
                if (anc[p][i]&&len[anc[p][i]]>=r-l+1)
                    p=anc[p][i];
            return p;
        }
    public:
        inline const int query1(char *t) //完美匹配出现次数
        {
            int p(1);
            const int m(strlen(t+1));
            for (int i(1);i<=m;i++)
                if (!(p=nxt[p][t[i]-'a']))
                    return 0;
            return size[p];
        }
        inline const void build(char *s)
        {
            last=cnt=1;
            n=strlen(s+1);
            for (int i(1);i<=n;i++)extend(s[i]-'a');
            for (int i(cnt);i>1;i--) //因为1号点没有父亲 所以>1 这部分需要处理时再处理
                son[fa[i]].emplace_back(i);
            dfs(1);
            /* 或
            for (int i(cnt);i>1;i--)
            {
                const int p(rnk[i]);
                size[fa[p]]+=size[p];
            }
            */
            //子串定位的倍增数组预处理 一般板子不需要
            for (int i(2);i<=cnt;i++)anc[i][0]=fa[i];
            for (int j(1);j<20;j++)
                for (int i(2);i<=cnt;i++)
                    anc[i][j]=anc[anc[i][j-1]][j-1];
        }
}sam;
/* 线段树合并
inline tree *merge(const int &l,const int &r,tree *p,tree *q)
{
    if (p==null&&q==null)return null;
    if (p==null)return q;
    if (q==null)return p;
    tree *t(new tree);
    if (l==r)return t->sum=p->sum+q->sum,t; //也不一定就是sum之和 看题目具体维护啥
    const int mid(l+r>>1);
    t->lson=merge(l,mid,p->lson,q->lson);
    t->rson=merge(mid+1,r,p->rson,q->rson);
    t->pushup();
    return t;
}
*/