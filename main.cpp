#include "global.h"

priority_queue<vert,vector<vert>,cmpheap> heap;
map<poi,int,cmpset> mp;
multiset<poi,cmpset> active;
set<int> bottomo;
set<int> lefto;
vector<int> ansob;

string FileFullName,FilePureName;   
poi p[N],a[N],b[N],pp[N];
obs o[N],oo[N];
edge OASGedge[M],MTSTedge[N],te[M];
edge2 OARSTedge[N],OAMSTedge[N];
vert v[N];
OBTree obt[N<<4];

int numOASGe,numMTSTe,numte,numOARSTe,numOAMSTe,mar,i,O,P,n,ee,WL;
int nex[M],head[N],e[M],dis[N],parent[N],len[M],root[N],f[N],pre[M],OB[N];
bool vis[M];

/* int main(int argc , char* argv[]) */
int main()
{
    /* string Name(argv[1]); */
    /* FileFullName=Name; */    
    /* ifstream fi(FileFullName,std::ios::in); */
    /* init(); */

    scanf("%d",&P);
    for (i=1;i<=P;i++)
        scanf("%d%d",&pp[i].x,&pp[i].y);
    scanf("%d",&O);
    for (i=1;i<=O;i++)
        scanf("%d%d%d%d",&oo[i].x1,&oo[i].y1,&oo[i].x2,&oo[i].y2);

    init();
    OASG();
    /* fi.close(); */
    /* addOASGedge(b[2],b[6]); */
    extendDJ();
    extendKK();
    
    OARST(); 

    Flute::readLUT();

    OAMST();

    dumpgnuplot();

    return 0;
}

