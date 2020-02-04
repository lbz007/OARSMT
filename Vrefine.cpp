#include "global.h"


void Vrefine()
{
    int ga,ma,maxid,mpp,u,v,i,j,r1,r2,dele;
    poi p0,p1,p2;
    mp.clear();
    for (i=1;i<=numOAMSTe;i++)
    {
        mp.insert(pair<poi,int>(OAMSTedge[i].u,0));
        mp.insert(pair<poi,int>(OAMSTedge[i].v,0));
    }
    n=0;
    map<poi,int>::iterator it;
    for (it=mp.begin();it!=mp.end();it++)
    {
        it->second=++n;
        b[n]={it->first.x,it->first.y};
        //printf("%d %d %d\n",it->first.x,it->first.y,it->second);
    }

    numOARSMTe=numOAMST2e=0;
    for (i=1;i<=numOAMSTe;i++)
    {
        OAMST2edge[++numOAMST2e]={mp.find(OAMSTedge[i].u)->second,mp.find(OAMSTedge[i].v)->second};
        OAMST2edge[numOAMST2e].c=disp(OAMSTedge[i].u,OAMSTedge[i].v);
    }

    sort(OAMST2edge+1,OAMST2edge+1+numOAMST2e,cmpedge);
    initedge();
    for (i=1;i<=numOAMST2e;i++)
    {
        u=OAMST2edge[i].u;
        v=OAMST2edge[i].v;
        add(u,v,i);
        add(v,u,i);
    }
    for (i=numOAMST2e;i>=1;i--)
    {
        if (vis[i]==1) continue;
        vis[i]=1;
        ma=-INF;
        u=OAMST2edge[i].u;
        for (j=head[u];j>0;j=nex[j])
        {
            if (e[j]==OAMST2edge[i].v) 
            {
                deledge(u,j);
                continue;
            }
            ga=calcgain(b[u],b[e[j]],b[OAMST2edge[i].v]);
            if (ga>ma)
            {
                ma=ga;
                maxid=len[j]; mpp=u;
                dele=j;
            }
        }
        u=OAMST2edge[i].v;
        for (j=head[u];j>0;j=nex[j])
        {
            if (e[j]==OAMST2edge[i].u)
            {
                deledge(u,j);
                continue;
            }
            ga=calcgain(b[u],b[e[j]],b[OAMST2edge[i].u]);
            if (ga>ma)
            {
                ma=ga;
                maxid=len[j]; mpp=u;
                dele=j;
            }
        }
        if (ma<=0) 
        {
            OARSMTedge[++numOARSMTe]={b[OAMST2edge[i].u],b[OAMST2edge[i].v]};
            continue;
        }
        deledge(mpp,dele);
        if (dele%2==1) deledge(e[dele],dele+1);
        else deledge(e[dele],dele-1);
            
        vis[maxid]=1;

        int px,py;
        p0=b[mpp];
        if (OAMST2edge[i].u==mpp) p1=b[OAMST2edge[i].v];
        else p1=b[OAMST2edge[i].u];
        if (OAMST2edge[maxid].u==mpp) p2=b[OAMST2edge[maxid].v];
        else p2=b[OAMST2edge[maxid].u];

        //printf("p0: %d %d p1: %d %d p2: %d %d\n",p0.x,p0.y,p1.x,p1.y,p2.x,p2.y);
        r1=whichregion(p0,p1);
        r2=whichregion(p0,p2);
        
        if (r1>4 || r2>4)
        {
            if (r2>4) 
            {
                swap(p1,p2);
                swap(r1,r2);
            }
            if ((r1==5 && (r2==1 || r2==4)) || (r1==7 && (r2==2 || r2==3)))
                if (abs(p1.x-p0.x)<abs(p2.x-p0.x))
                {
                    OARSMTedge[++numOARSMTe]={p0,p1};
                    OARSMTedge[++numOARSMTe]={p1,p2};
                }
                else
                {
                    OARSMTedge[++numOARSMTe]={p0,{p2.x,p0.y}};
                    OARSMTedge[++numOARSMTe]={p1,{p2.x,p0.y}};
                    OARSMTedge[++numOARSMTe]={p2,{p2.x,p0.y}};
                }
            if ((r1==6 && (r2==1 || r2==2)) || (r1==8 && (r2==3 || r2==4)))
                if (abs(p1.y-p0.y)<abs(p2.y-p0.y))
                {
                    OARSMTedge[++numOARSMTe]={p0,p1};
                    OARSMTedge[++numOARSMTe]={p1,p2};
                }
                else
                {
                    OARSMTedge[++numOARSMTe]={p0,{p0.x,p2.y}};
                    OARSMTedge[++numOARSMTe]={p1,{p0.x,p2.y}};
                    OARSMTedge[++numOARSMTe]={p2,{p0.x,p2.y}};
                }
            continue;
        }

        if (abs(r1-r2)==0)
        {
            if (abs(p1.x-p0.x)<abs(p2.x-p0.x)) px=p1.x;
            else px=p2.x;
            if (abs(p1.y-p0.y)<abs(p2.y-p0.y)) py=p1.y;
            else py=p2.y;
            //OARSMTedge[++numOARSMTe]={p0,{px,p0.y}};
            //OARSMTedge[++numOARSMTe]={{px,py},{px,p0.y}};
            OARSMTedge[++numOARSMTe]={p0,{px,py}};
            OARSMTedge[++numOARSMTe]={{px,py},p1};
            OARSMTedge[++numOARSMTe]={{px,py},p2};
        }
        if (abs(r1-r2)==1||abs(r1-r2)==3)
        {
            if (r1+r2==5)
            {
                if (abs(p1.x-p0.x)>abs(p2.x-p0.x)) swap(p1,p2);
                OARSMTedge[++numOARSMTe]={p0,{p1.x,p0.y}};
                OARSMTedge[++numOARSMTe]={p1,{p1.x,p0.y}};
                // OARSMTedge[++numOARSMTe]={{p1.x,p0.y},{p2.x,p0.y}};
                // OARSMTedge[++numOARSMTe]={p2,{p2.x,p0.y}};
                OARSMTedge[++numOARSMTe]={p2,{p1.x,p0.y}};
            }
            if (r1+r2!=5)
            {
                if (abs(p1.y-p0.y)>abs(p2.y-p0.y)) swap(p1,p2);
                OARSMTedge[++numOARSMTe]={p0,{p0.x,p1.y}};
                OARSMTedge[++numOARSMTe]={p1,{p0.x,p1.y}};
                // OARSMTedge[++numOARSMTe]={{p0.x,p1.y},{p0.x,p2.y}};
                // OARSMTedge[++numOARSMTe]={p2,{p0.x,p2.y}};
                OARSMTedge[++numOARSMTe]={p2,{p0.x,p1.y}};
            }
        }
    }
    WL=0;
    for(i=1;i<=numOARSMTe;i++)
        WL+=disp(OARSMTedge[i].u,OARSMTedge[i].v);
    printf("OARSMT WL: %d\n",WL);
}