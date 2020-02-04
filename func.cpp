#include "global.h"

bool cmp(poi a,poi b)
{
    return a.x+a.y<b.x+b.y;
}
bool cmpp(poi a,poi b)
{
    if (a.x==b.x) return a.y<b.y;
    else
    {
        return a.x<b.x;
    }
}
bool equpoi(poi a,poi b)
{
    return (a.x==b.x && a.y==b.y);
}
bool cmpedge(edge a,edge b)
{
    return a.c<b.c;
}
int disp(poi a,poi b)
{
    return abs(a.x-b.x)+abs(a.y-b.y);
}
int clas(poi x)
{
    if (x.id<=P) return 0;
    return (x.id-P-1)%4+1;
}

void add(int u,int v,int c)
{
    e[++ee]=v;pre[head[u]]=ee;nex[ee]=head[u];head[u]=ee;len[ee]=c;
}
void deledge(int u,int ee)
{
    pre[nex[ee]]=pre[ee];
    if (pre[ee]==0) head[u]=nex[ee];
    else nex[pre[ee]]=nex[ee];

    /* u=e[ee]; */
    /* if (ee%2==1) ee++; */
    /* else ee--; */
    /* pre[nex[ee]]=pre[ee]; */
    /* if (pre[ee]==0) head[u]=nex[ee]; */
    /* else nex[pre[ee]]=nex[ee]; */

}
bool inbox(poi p,poi p1,poi p2)
{
    if (p.x>=p2.x || p.x<=p1.x || p.y>=p2.y || p.y<=p1.y)
        return 0;
    return 1;
}
void initedge()
{
    memset(head,0,sizeof(head));
    memset(nex,0,sizeof(nex));
    memset(pre,0,sizeof(pre));
    memset(vis,0,sizeof(vis));
    ee=0;
}
int find(int x)
{
    if (parent[x]==0) return x;
    parent[x]=find(parent[x]);
    return parent[x];
}
void init()
{
    FilePureName = FileFullName.substr(0, FileFullName.rfind("."));
    n=0;
    for (i=1;i<=P;i++)
        mp.insert(pair<poi,int>({pp[i].x,pp[i].y,0},++n));
    for (i=1;i<=O;i++)
    {
        mp.insert(pair<poi,int>({oo[i].x1,oo[i].y2,0},++n));
        mp.insert(pair<poi,int>({oo[i].x1,oo[i].y1,0},++n));
        mp.insert(pair<poi,int>({oo[i].x2,oo[i].y1,0},++n));
        mp.insert(pair<poi,int>({oo[i].x2,oo[i].y2,0},++n));
    }
}