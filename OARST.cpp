#include "global.h"

int whichregion(poi a,poi b)
{
    if (a.x==b.x || a.y==b.y) return 0;
    if (a.x<b.x && a.y<b.y) return 1;
    if (a.x>b.x && a.y<b.y) return 2;
    if (a.x>b.x && a.y>b.y) return 3;
    if (a.x<b.x && a.y>b.y) return 4;
    return 0;
}
int calcgain(poi p0,poi p1,poi p2)
{
    int r1,r2;
    r1=whichregion(p0,p1);
    r2=whichregion(p0,p2);
    if (r1==0 || r2==0)
        return 0;
    if (abs(r1-r2)==2)
        return 0;
    if (abs(r1-r2)==0)
        return (abs(p0.y-p1.y)+abs(p0.x-p2.x));
    if (abs(r1-r2)==1||abs(r1-r2)==3)
    {
        if (r1+r2==5)
        {
            if (abs(p1.x-p0.x)>abs(p2.x-p0.x)) swap(p1,p2);
            return (abs(p1.x-p0.x));
        }
        if (r1+r2!=5)
        {
            if (abs(p1.y-p0.y)>abs(p2.y-p0.y)) swap(p1,p2);
            return (abs(p1.y-p0.y));
        }
    }
    return 0;
}
void OARST()
{
    int ga,ma,maxid,mp,u,v,i,j,r1,r2,dele;
    poi p0,p1,p2;
    sort(MTSTedge+1,MTSTedge+1+numMTSTe,cmpedge);
    initedge();
    for (i=1;i<=numMTSTe;i++)
    {
        u=MTSTedge[i].u;
        v=MTSTedge[i].v;
        add(u,v,i);
        add(v,u,i);
    }
    for (i=numMTSTe;i>=1;i--)
    {
        if (vis[i]==1) continue;
        vis[i]=1;
        ma=-INF;
        u=MTSTedge[i].u;
        for (j=head[u];j>0;j=nex[j])
        {
            if (e[j]==MTSTedge[i].v) 
            {
                deledge(u,j);
                continue;
            }
            ga=calcgain(b[u],b[e[j]],b[MTSTedge[i].v]);
            if (ga>ma)
            {
                ma=ga;
                maxid=len[j]; mp=u;
                dele=j;
            }
        }
        u=MTSTedge[i].v;
        for (j=head[u];j>0;j=nex[j])
        {
            if (e[j]==MTSTedge[i].u)
            {
                deledge(u,j);
                continue;
            }
            ga=calcgain(b[u],b[e[j]],b[MTSTedge[i].u]);
            if (ga>ma)
            {
                ma=ga;
                maxid=len[j]; mp=u;
                dele=j;
            }
        }
        if (ma<=0) 
        {
            OARSTedge[++numOARSTe]={b[MTSTedge[i].u],b[MTSTedge[i].v]};
            continue;
        }
        deledge(mp,dele);
        if (dele%2==1) deledge(e[dele],dele+1);
        else deledge(e[dele],dele-1);
            
        vis[maxid]=1;

        int px,py;
        p0=b[mp];
        if (MTSTedge[i].u==mp) p1=b[MTSTedge[i].v];
        else p1=b[MTSTedge[i].u];
        if (MTSTedge[maxid].u==mp) p2=b[MTSTedge[maxid].v];
        else p2=b[MTSTedge[maxid].u];
        r1=whichregion(p0,p1);
        r2=whichregion(p0,p2);
        if (r1==0 || r2==0)
        {
            OARSTedge[++numOARSTe]={p1,p0};
            OARSTedge[++numOARSTe]={p2,p0};
            continue;
        }
        if (abs(r1-r2)==2)
        {
            OARSTedge[++numOARSTe]={p1,{p0.x,p1.y}};
            OARSTedge[++numOARSTe]={p0,{p0.x,p1.y}};
            OARSTedge[++numOARSTe]={p2,{p0.x,p2.y}};
            OARSTedge[++numOARSTe]={p0,{p0.x,p2.y}};       
        }
        if (abs(r1-r2)==0)
        {
            if (abs(p1.x-p0.x)<abs(p2.x-p0.x)) px=p1.x;
            else px=p2.x;
            if (abs(p1.y-p0.y)<abs(p2.y-p0.y)) py=p1.y;
            else py=p2.y;
            OARSTedge[++numOARSTe]={p0,{px,p0.y}};
            OARSTedge[++numOARSTe]={{px,py},{px,p0.y}};
            OARSTedge[++numOARSTe]={{px,py},p1};
            OARSTedge[++numOARSTe]={{px,py},p2};
        }
        if (abs(r1-r2)==1||abs(r1-r2)==3)
        {
            if (r1+r2==5)
            {
                if (abs(p1.x-p0.x)>abs(p2.x-p0.x)) swap(p1,p2);
                OARSTedge[++numOARSTe]={p0,{p1.x,p0.y}};
                OARSTedge[++numOARSTe]={p1,{p1.x,p0.y}};
                OARSTedge[++numOARSTe]={{p1.x,p0.y},{p2.x,p0.y}};
                OARSTedge[++numOARSTe]={p2,{p2.x,p0.y}};
            }
            if (r1+r2!=5)
            {
                if (abs(p1.y-p0.y)>abs(p2.y-p0.y)) swap(p1,p2);
                OARSTedge[++numOARSTe]={p0,{p0.x,p1.y}};
                OARSTedge[++numOARSTe]={p1,{p0.x,p1.y}};
                OARSTedge[++numOARSTe]={{p0.x,p1.y},{p0.x,p2.y}};
                OARSTedge[++numOARSTe]={p2,{p0.x,p2.y}};
            }
        }

    }
    for(i=1;i<=numOARSTe;i++)
        WL+=disp(OARSTedge[i].u,OARSTedge[i].v);
    printf("WL: %d\n",WL);
}