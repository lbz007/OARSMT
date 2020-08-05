#include "global.h"

priority_queue<vert,vector<vert>,cmpheap> heap;
map<poi,int,cmpset> mp;
set<int> bottomo;
set<int> lefto;
vector<int> ansob;

string FileFullName,FilePureName;   
vector<poi> p,a,b,pp;
vector<obs> o,oo;
vector<edge> OASGedge,MTSTedge,OPMSTedge,OAMST2edge,te;
vector<edge2> OARSTedge,OAMSTedge,OARSMTedge;
vector<OBTree> obt;

int numOASGe,numMTSTe,numte,numOARSTe,numOAMSTe,numOPMSTe,numOARSMTe,numOAMST2e,mar,i,O,P,AP,n,ee,ee2,WL;
vector<int> nex,head,e,dis,parent,len,root,f,pre,OB,siz,DIJsource;
vector<int> nex2,head2,e2,vis2,numblock,vis;

/* int main(int argc , char* argv[]) */
int main()
{
    /* string Name(argv[1]); */
    /* FileFullName=Name; */    
    /* ifstream fi(FileFullName,std::ios::in); */
    /* init(); */
    
    scanf("%d",&P);
    pp.resize(P+1);
    for (i=1;i<=P;i++)
        scanf("%d%d",&pp[i].x,&pp[i].y);
    scanf("%d",&O);
    oo.resize(O+1);
    for (i=1;i<=O;i++)
        scanf("%d%d%d%d",&oo[i].x1,&oo[i].y1,&oo[i].x2,&oo[i].y2);
        
    init(P+O*4+2,16*(P+O*4)+2);
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
    init_map();
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
    init_map();
    OASG();
    for (i=1;i<=P+4*O;i++) a[mp.find(b[i])->second]=b[i];

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

