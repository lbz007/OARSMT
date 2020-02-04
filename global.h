#ifndef _GLOBAL_
#define _GLOBAL_ 

#include "flute.h"
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <fstream>
#include <set>
#include <map>
#include <queue>
#include <cstring>
using namespace std;

const int INF=2100000000;
const int NP=2010;
const int N=50000;
const int M=400000;

struct poi
{
    int x,y,id;
};
struct obs
{
    int x1,y1,x2,y2;
};
struct cmpset
{
    bool operator()(poi a,poi b)
    {
        if (a.x>b.x) return 1;
        if (a.x==b.x && a.x-a.y>b.x-b.y) return 1;
        return 0;
    }
};
struct edge
{
    int u,v,c;
};
struct edge2
{
    poi u,v;
};
struct vert
{
    int dis,id;
};
struct cmpheap
{
    bool operator()(vert a,vert b)
    {
        return a.dis>b.dis;
    }
};
struct OBTree
{
    int xmin,xmax,ymin,ymax,a;
};

extern string FileFullName,FilePureName;   
extern poi p[N],a[N],b[N],pp[N];
extern obs o[N],oo[N];
extern edge OASGedge[M],MTSTedge[N],te[M];
extern edge2 OARSTedge[N],OAMSTedge[N];
extern vert v[N];
extern OBTree obt[N<<4];

extern priority_queue<vert,vector<vert>,cmpheap> heap;
extern map<poi,int,cmpset> mp;
extern multiset<poi,cmpset> active;
extern set<int> bottomo;
extern set<int> lefto;
extern vector<int> ansob;

extern string FileFullName,FilePureName;   

extern int numOASGe,numMTSTe,numte,numOARSTe,numOAMSTe,mar,i,O,P,n,ee,WL;
extern int nex[M],head[N],e[M],dis[N],parent[N],len[M],root[N],f[N],pre[M],OB[N];
extern bool vis[M];

void OASG();
void OARST();
void extendDJ();
void extendKK();
void OAMST();

bool cmp(poi a,poi b);

bool cmpp(poi a,poi b);

bool equpoi(poi a,poi b);

bool cmpedge(edge a,edge b);

int disp(poi a,poi b);

int clas(poi x);

void add(int u,int v,int c);

void deledge(int u,int ee);

bool inbox(poi p,poi p1,poi p2);

void initedge();

void init();

int find(int x);

void dumpgnuplot();

void buildOBTree(int s,int k);

void initOBTreeNode(OBTree &s);

void checknode(poi p,int s);

void checkedge(poi p1,poi p2,int s);

#endif
