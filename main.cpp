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
edge OASGedge[M],MTSTedge[N],OPMSTedge[N],OAMST2edge[N],te[M];
edge2 OARSTedge[N],OAMSTedge[N],OARSMTedge[N];
vert v[N];
OBTree obt[N<<4];

int numOASGe,numMTSTe,numte,numOARSTe,numOAMSTe,numOPMSTe,numOARSMTe,numOAMST2e,mar,i,O,P,AP,n,ee,ee2,WL;
int nex[M],head[N],e[M],dis[N],parent[N],len[M],root[N],f[N],pre[M],OB[N],siz[N],DIJsource[N];
int nex2[M],head2[N],e2[M],vis2[N],numblock[N],vis[M];

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
    for (i=1;i<=P;i++)
    {
        pp[i].x=-pp[i].x;
        pp[i].y=-pp[i].y;
    }
    for (i=1;i<=O;i++)
    {
        oo[i].x1=-oo[i].x1;
        oo[i].y1=-oo[i].y1;
        oo[i].x2=-oo[i].x2;
        oo[i].y2=-oo[i].y2;
    }
    init();
    OASG();
    for (i=1;i<=P;i++)
    {
        pp[i].x=-pp[i].x;
        pp[i].y=-pp[i].y;
    }
    for (i=1;i<=O;i++)
    {
        oo[i].x1=-oo[i].x1;
        oo[i].y1=-oo[i].y1;
        oo[i].x2=-oo[i].x2;
        oo[i].y2=-oo[i].y2;
    }
    init();
    OASG();
    for (i=1;i<=P+4*O;i++) a[mp.find(b[i])->second]=b[i];
    /* fi.close(); */
    /* addOASGedge(b[2],b[6]); */
    MTST();

    for (i=1;i<=O;i++)
        OB[i-1]=i;
    buildOBTree(1,O);
    
    OARST(); 

    OPMST();

    Flute::readLUT();

    OAMST();

    Vrefine();

    for (i=1;i<=numOARSMTe;i++)
        OAMSTedge[i]=OARSMTedge[i];
    numOAMSTe=numOARSMTe;

    Vrefine();

    dumpgnuplot();

    return 0;
}

