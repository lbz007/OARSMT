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
bool cmpedge2(edge2 a,edge2 b)
{
    if (equpoi(a.u,b.u)) return cmpp(a.v,b.v);
    else
    {
        return cmpp(a.u,b.u);
    }
}
bool equpoi(poi a,poi b)
{
    return (a.x==b.x && a.y==b.y);
}
bool equedge2(edge2 a,edge2 b)
{
    if (equpoi(a.u,b.u) && equpoi(a.v,b.v))
        return 1;
    if (equpoi(a.u,b.v) && equpoi(a.v,b.u))
        return 1;
    return 0;
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
void add2(int u,int v)
{
    e2[++ee2]=v;nex2[ee2]=head2[u];head2[u]=ee2;
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
int opedge(int x)
{
    if (x%2==0) return x-1;
    else return x+1; 
}
bool inbox(poi p,poi p1,poi p2)
{
    if (p.x>=p2.x || p.x<=p1.x || p.y>=p2.y || p.y<=p1.y)
        return 0;
    return 1;
}
void initedge(int n,int m)
{
    head.clear();
    head.resize(n+1,0);
    nex.clear();
    nex.resize(m+1,0);
    pre.clear();
    pre.resize(m+1,0);
    vis.clear();
    vis.resize(n+1,0);
    e.clear();
    e.resize(m+1,0);
    ee=0;
}
void initedge2(int n,int m)
{
    head2.clear();
    head2.resize(n+1,0);
    nex2.clear();
    nex2.resize(m+1,0);
    vis2.clear();
    vis2.resize(n+1,0);
    e2.clear();
    e2.resize(m+1,0);
    ee2=0;
}
void init(int n,int m)
{
    numOASGe=numMTSTe=numte=numOARSTe=numOAMSTe=numOPMSTe=numOARSMTe=numOAMST2e=mar=AP=WL=0;
    a.clear();a.resize(n);
    b.clear();b.resize(n+n);
    p.clear();p.resize(P+1);
    o.clear();o.resize(O+1);
    OASGedge.clear();OASGedge.resize(m);
    te.clear();te.resize(m);
    MTSTedge.clear();MTSTedge.resize(n<<1);
    OPMSTedge.clear();OPMSTedge.resize(n<<1);
    OAMST2edge.clear();OAMST2edge.resize(n<<1);
    OARSTedge.clear();OARSTedge.resize(n<<1);
    OAMSTedge.clear();OAMSTedge.resize(n<<1);
    OARSMTedge.clear();OARSMTedge.resize(n<<1);
    obt.clear();obt.resize(O<<2);
    numblock.clear();numblock.resize(m,0);
    nex.clear();nex.resize(m,0);
    pre.clear();pre.resize(m,0);
    e.clear();e.resize(m,0);
    len.clear();len.resize(m,0);
    vis.clear();vis.resize(n,0);
    head.clear();head.resize(n,0);
    dis.clear();dis.resize(n,0);
    parent.clear();parent.resize(n,0);
    root.clear();root.resize(n,0);
    f.clear();f.resize(n,0);
    OB.clear();OB.resize(n,0);
    siz.clear();siz.resize(n,0);
    DIJsource.clear();DIJsource.resize(n,0);
}
int find(int x)
{
    if (parent[x]==0) return x;
    parent[x]=find(parent[x]);
    return parent[x];
}
void init_map()
{
    int i,n=0;
    mp.clear();
    for (i=1;i<=P;i++)
        mp.insert(pair<poi,int>({pp[i].x,pp[i].y,0},++n));
    for (i=1;i<=O;i++)
    {
        mp.insert(pair<poi,int>({oo[i].x1,oo[i].y1,0},++n));
        mp.insert(pair<poi,int>({oo[i].x1,oo[i].y2,0},++n));
        mp.insert(pair<poi,int>({oo[i].x2,oo[i].y1,0},++n));
        mp.insert(pair<poi,int>({oo[i].x2,oo[i].y2,0},++n));
    }
}
void refineedge(int &n, vector<edge2> &a)
{
    int i;
    vector<edge2> po;
    for (i=1;i<=n;i++)
    {
        if (equpoi(a[i].u,a[i].v))
            continue;
        if (cmpp(a[i].u,a[i].v))
            swap(a[i].u,a[i].v);
        po.push_back(a[i]);
    }
    sort(po.begin(),po.end(),cmpedge2);
    vector<edge2>::iterator new_end=unique(po.begin(),po.end(),equedge2);
    po.erase(new_end,po.end());
    n=po.size();
    for (i=0;i<n;i++)
    {
        a[i+1]=po[i];
    }        
}

void blockedgepoint(poi u,poi v,obs o,poi &pa,poi &pb)
{
    poi paa,pbb;
    if (o.x2-o.x1<abs(u.x-v.x))
    {
        pa={o.x1,o.y2};
        pb={o.x2,o.y2};
        if (disp(pa,{u.x,u.y,0})>disp(pb,{u.x,u.y,0}))
            swap(pa,pb);
        paa={o.x1,o.y1};
        pbb={o.x2,o.y1};
        if (disp(paa,{u.x,u.y,0})>disp(pbb,{u.x,u.y,0}))
            swap(paa,pbb);
        if (disp(paa,{u.x,u.y,0})+disp(pbb,{v.x,v.y,0})<disp(pa,{u.x,u.y,0})+disp(pb,{v.x,v.y,0}))
        {
            pa=paa;
            pb=pbb;
        }
    }
    else
    {
        pa={o.x1,o.y1};
        pb={o.x1,o.y2};
        if (disp(pa,{u.x,u.y,0})>disp(pb,{u.x,u.y,0}))
            swap(pa,pb);
        paa={o.x2,o.y1};
        pbb={o.x2,o.y2};
        if (disp(paa,{u.x,u.y,0})>disp(pbb,{u.x,u.y,0}))
            swap(paa,pbb);
        if (disp(paa,{u.x,u.y,0})+disp(pbb,{v.x,v.y,0})<disp(pa,{u.x,u.y,0})+disp(pb,{v.x,v.y,0}))
        {
            pa=paa;
            pb=pbb;
        }
    }    
}
bool ispointblocked(poi u)
{
    ansob.clear();
    checknode(u,1);
    if (ansob.size()==0)
        return 0;
    else
        return 1;
}
bool isedgeblocked(poi u,poi v)
{
    ansob.clear();
    checkedge(u,v,1);
    if (ansob.size()==0)
        return 0;
    else
        return 1;
}