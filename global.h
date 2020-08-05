#ifndef _GLOBAL_
#define _GLOBAL_ 

#include "flute.h"
#include "geo.h"
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <fstream>
#include <set>
#include <map>
#include <queue>
#include <cstring>
#include <cmath>
#include <vector>
using namespace std;

const int INF=2100000000;
const int NP=2010;
const int N=50000;
const int M=800000;

struct poi
{
    int x,y,id;
};
struct obs
{      
    int x1,y1,x2,y2;
};
struct blockedge
{
    int id;
    poi a;
    double v;
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
extern vector<poi> p,a,b,pp;
extern vector<obs> o,oo;
extern vector<edge> OASGedge,MTSTedge,OPMSTedge,OAMST2edge,te;
extern vector<edge2> OARSTedge,OAMSTedge,OARSMTedge;
extern vector<OBTree> obt;

extern priority_queue<vert,vector<vert>,cmpheap> heap;
extern map<poi,int,cmpset> mp;
extern set<int> bottomo;
extern set<int> lefto;
extern vector<int> ansob;

extern string FileFullName,FilePureName;   

extern int numOASGe,numMTSTe,numte,numOARSTe,numOAMSTe,numOPMSTe,numOARSMTe,numOAMST2e,mar,i,O,P,AP,n,ee,WL,ee2;
// extern int nex[M],head[N],e[M],dis[N],parent[N],len[M],root[N],f[N],pre[M],OB[N],siz[N],DIJsource[N];
extern vector<int> nex,head,e,dis,parent,len,root,f,pre,OB,siz,DIJsource;
extern vector<int> nex2,head2,e2,vis2,numblock,vis;

void OASG();
void OARST();
void MTST();
void OAMST();
void OPMST();
void Vrefine();

void OAflute(int n,vector<int> &XX,vector<int> &YY);

bool cmp(poi a,poi b);

bool cmpp(poi a,poi b);

bool equpoi(poi a,poi b);

bool cmpedge(edge a,edge b);

int disp(poi a,poi b);

int clas(poi x);

void add(int u,int v,int c);
void add2(int u,int v);

void deledge(int u,int ee);

int opedge(int x);

bool inbox(poi p,poi p1,poi p2);

void init(int n,int m);
void initedge(int n,int m);
void initedge2(int n,int m);
void init_map();

int find(int x);

void dumpgnuplot();

void buildOBTree(int s,int k);

void initOBTreeNode(OBTree &s);

void checknode(poi p,int s);

void checkedge(poi p1,poi p2,int s);

void refineedge(int &n, vector<edge2> &a);

void blockedgepoint(poi u,poi v,obs o,poi &pa,poi &pb);

int whichregion(poi a,poi b);

int calcgain(poi p0,poi p1,poi p2);

bool ispointblocked(poi u);

#endif
