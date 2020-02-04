#include "global.h"

void dfs(int u)
{
    int j;
    vis[u]=1;
    siz[u]=1;
    for (j=head[u];j>0;j=nex[j])
    {
        if (vis[e[j]]) continue;
        dfs(e[j]);
        siz[u]+=siz[e[j]];
    }
}
void partition(int x)
{
    mar++;
    //printf("part x mar: %d %d\n",x,mar);
    //printf("part x: %d %d\n",b[x].x,b[x].y);
    int sz,maxlen=0,maxidu,maxidj,THRESHOLD;
    int num=0,numans=0,u,v,i,j,PP,QQ,XX[NP],YY[NP];
    bool obflag=0;
    vector<int> a;
    obs obtem;
    OBTree ob;
    poi pa,pb;

    if (P<=50) THRESHOLD=INF;
    if (P>50 && P<=100) THRESHOLD=P/2;
    if (P>100 && P<=500) THRESHOLD=P/5;
    if (P>500) THRESHOLD=P/10;
    
    a.clear();
    a.push_back(x);
    vis[x]=mar;
    while ((!a.empty()) && obflag==0)
    {
        u=*a.begin();
        for (j=head[u];j>0;j=nex[j])
        {
            if (vis[e[j]]==mar) continue;
            sz=siz[u];
            if (e[j]<=P)
                sz=min(sz,siz[e[j]]); 
            sz=min(sz,P-sz);
                //cout<<siz[u]<<' '<<siz[e[j]]<<' '<<sz<<endl;
            //if (u>P || e[j]>P) sz=10;
            //sz=10;
            if (numblock[j]>0 && sz>2)
            {
                obflag=1;
                ansob.clear();
                checkedge({b[u].x,b[u].y},{b[e[j]].x,b[e[j]].y},1);
                numans=ansob.size();
                break;
            }
            if (len[j]>maxlen && sz>2)
            {
                maxlen=len[j];
                maxidj=j;
                maxidu=u;
            }
            vis[e[j]]=mar;
            a.push_back(e[j]);
        }
        XX[num]=b[u].x;
        YY[num++]=b[u].y;
        a.erase(a.begin());
    }   
    if (obflag)
    {
        v=e[j];
        //printf("u,v,j: %d %d %d\n",u,v,j);
        initOBTreeNode(ob);
        for (i=0;i<1;i++) // 1 or numans check!
        {
            obtem=oo[ansob[i]];
            ob.xmin=min(obtem.x1,ob.xmin);
            ob.xmax=max(obtem.x2,ob.xmax);
            ob.ymin=min(obtem.y1,ob.ymin);
            ob.ymax=max(obtem.y2,ob.ymax);    
        }
        obtem={ob.xmin,ob.ymin,ob.xmax,ob.ymax};
        blockedgepoint({b[u].x,b[u].y},{b[v].x,b[v].y},obtem,pa,pb);
        //OAMSTedge[++numOAMSTe]={{b[u].x,b[u].y},pa};
        //OAMSTedge[++numOAMSTe]={{b[v].x,b[v].y},pb};
        OAMSTedge[++numOAMSTe]={pa,pb};
        b[++AP]=pa;
        add(u,AP,disp(b[u],b[AP]));
        add(AP,u,disp(b[u],b[AP]));
        b[++AP]=pb;
        add(v,AP,disp(b[v],b[AP]));
        add(AP,v,disp(b[v],b[AP]));
        deledge(v,opedge(j));
        deledge(u,j);
        partition(u);
        partition(v);
        return;
    }
    if (num>THRESHOLD)
    {
        u=maxidu;
        j=maxidj;
        v=e[j];
        OAMSTedge[++numOAMSTe]={{b[u].x,b[u].y},{b[v].x,b[v].y}};
        deledge(v,opedge(j));
        deledge(u,j);
        partition(u);
        partition(v);
        return;
    }
    //for (i=0;i<num;i++) printf("partition xy: %d %d %d\n",num,XX[i],YY[i]);
    OAflute(num,XX,YY);

}
void OAMST()
{
    int numans,i,j,k,u,v;
    int X[NP],Y[NP];
    
    initedge();
    mar=0;
    sort(OPMSTedge+1,OPMSTedge+1+numOPMSTe,cmpedge);
    for (i=1;i<=numOPMSTe;i++)
    {
        //printf("lbz: %d %d\n",OPMSTedge[i].u,OPMSTedge[i].v);
        u=OPMSTedge[i].u;v=OPMSTedge[i].v;
        ansob.clear();
        checkedge({b[u].x,b[u].y},{b[v].x,b[v].y},1);
        
        add(u,v,OPMSTedge[i].c);
        numblock[ee]=ansob.size();
        add(v,u,OPMSTedge[i].c);
        numblock[ee]=ansob.size();
    }
    memset(siz,0,sizeof(siz));
    dfs(1);
    memset(vis,0,sizeof(vis));
    AP=P;
    partition(1);

    for (i=1;i<=P;i++)
    {
        X[i-1]=pp[i].x;
        Y[i-1]=pp[i].y;
    }
    // OAflute(P,X,Y);
    
    refineedge(numOAMSTe,OAMSTedge);

    //refinev();
    WL=0;
    for(i=1;i<=numOAMSTe;i++)
        WL+=disp(OAMSTedge[i].u,OAMSTedge[i].v);
    printf("OAMST WL: %d\n",WL);

    Flute::Tree flutetree=Flute::flute(P,X,Y,12);
    //Flute::plottree(flutetree);

    // for (int i=1;i<=5;i++)
    // {
    //     X[i-1]=pp[i].x;
    //     Y[i-1]=pp[i].y;
    // }

    // Flute::Tree flutetree,flutetree1,flutetree2;
    // flutetree1=Flute::flute(5,X,Y,12);
    // for (int i=6;i<=10;i++)
    // {
    //     X[i-6]=pp[i].x;
    //     Y[i-6]=pp[i].y;
    // }
    // flutetree2=Flute::flute(5,X,Y,12);
    
    // Flute::printtree(flutetree);
    // Flute::printtree(flutetree1);
    // puts("");
    // Flute::printtree(flutetree2);
    
    // flutetree=Flute::dmergetree(flutetree1,flutetree2);
    // puts("");
    // Flute::printtree(flutetree);
    // for (i=0;i<flutetree.deg;i++)

}


