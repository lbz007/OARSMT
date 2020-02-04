#include "global.h"

void extendDJ()
{
    int i,j,u;
    vert tmp;
    for (i=1;i<=P;i++)
    {
        dis[i]=0;
        heap.push({dis[i],i});
    }
    for (i=P+1;i<=n;i++)
    {
        dis[i]=INF;
        heap.push({dis[i],i});
    }
    while (!heap.empty())
    {
        tmp=heap.top();
        u=tmp.id;
        heap.pop();
        if (dis[u]<tmp.dis) continue;
        j=head[u];
        while (j>0)
        {
            if (dis[e[j]]>dis[u]+len[j])
            {
                dis[e[j]]=dis[u]+len[j];
                parent[e[j]]=u;
                heap.push({dis[e[j]],e[j]});
            }
            j=nex[j];
        }
    }
}
void extendKK()
{
    int i,PP,QQ,u,v;
    for (i=1;i<=n;i++)
        f[i]=parent[i];
    //for (i=1;i<=n;i++)        printf("%d %d %d\n",b[i].x,b[i].y,f[i]);
    for (i=1;i<=n;i++)
        root[i]=find(i);
    for (i=1;i<=numOASGe;i++)
    {
        u=OASGedge[i].u;
        v=OASGedge[i].v;
        if (root[u]!=root[v])
            te[++numte]={u,v,dis[v]+OASGedge[i].c+dis[u]};
    }
    sort(te+1,te+1+numte,cmpedge);
    
    for (i=1;i<=numte;i++)
    {
        PP=find(te[i].u);
        QQ=find(te[i].v);
        if (PP!=QQ)
        {
            parent[PP]=QQ;
            MTSTedge[++numMTSTe]={te[i].u,te[i].v,disp(b[te[i].u],b[te[i].v])};
            u=te[i].u;v=te[i].v;
            for (u=te[i].u;f[u]!=0;u=f[u])
            {
                if (vis[u]) break;
                vis[u]=1;
                MTSTedge[++numMTSTe]={u,f[u]};
            }
            for (v=te[i].v;f[v]!=0;v=f[v])
            {
                if (vis[v]) break;
                vis[v]=1;
                MTSTedge[++numMTSTe]={v,f[v]};
            }
        }
    }
}