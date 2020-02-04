#include "global.h"

void dfs(int u,int f,int d)
{
    int j;
    vis[u]=1;
    for (j=head[u];j!=0;j=nex[j])
    {
        if (vis[e[j]]==1) continue;
        if (e[j]>P)
            dfs(e[j],f,d+len[j]);
        else
        {
            OPMSTedge[++numOPMSTe]={f,e[j],d};
            dfs(e[j],e[j],0);
        }
    } 
}

void OPMST()
{
    int i,u,v;
    initedge();
    for (i=1;i<=numMTSTe;i++)
    {
        u=MTSTedge[i].u;v=MTSTedge[i].v;
        if (DIJsource[u]!=DIJsource[v])
            OPMSTedge[++numOPMSTe]={DIJsource[u],DIJsource[v],disp(b[DIJsource[u]],b[DIJsource[v]])};
    }
        
    // for (i=1;i<=numMTSTe;i++)
    // {
    //     add(MTSTedge[i].u,MTSTedge[i].v,MTSTedge[i].c);
    //     add(MTSTedge[i].v,MTSTedge[i].u,MTSTedge[i].c);
    // }
    // dfs(1,1,0);
    
    WL=0;
    for(i=1;i<=numOPMSTe;i++)
        WL+=disp(b[OPMSTedge[i].u],b[OPMSTedge[i].v]);
    printf("OPMST WL: %d\n",WL);
}