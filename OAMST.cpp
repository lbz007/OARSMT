#include "global.h"
int dealpoint(Flute::Tree t)
{
    int u,i,j,numans,numN=0,cuti;
    int XX[NP],YY[NP],color[NP];
    bool obflag=0;
    poi paa,pbb,pa,pb;
    OBTree ob;

    Flute::printtree(t);

    for (i=0;i<t.deg*2-2;i++)
    {
        Flute::Branch u=t.branch[i];    
        ansob.clear();
        checknode({u.x,u.y,0},1);
        numans=ansob.size();
        if (numans>0)
        {
            obflag=1;
            initOBTreeNode(ob);
            for (j=0;j<numans;j++)
            {
                obs obtem=oo[ansob[j]];
                ob.xmin=min(obtem.x1,ob.xmin);
                ob.xmax=max(obtem.x2,ob.xmax);
                ob.ymin=min(obtem.y1,ob.ymin);
                ob.ymax=max(obtem.y2,ob.ymax);    
            }
            if (ob.xmax-ob.xmin<abs(u.x-v.x))
            {
                pa={ob.xmin,ob.ymax};
                pb={ob.xmax,ob.ymax};
                if (disp(pa,{u.x,u.y,0})>disp(pb,{u.x,u.y,0}))
                    swap(pa,pb);
                paa={ob.xmin,ob.ymin};
                pbb={ob.xmax,ob.ymin};
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
                pa={ob.xmin,ob.ymin};
                pb={ob.xmin,ob.ymax};
                if (disp(pa,{u.x,u.y,0})>disp(pb,{u.x,u.y,0}))
                    swap(pa,pb);
                paa={ob.xmax,ob.ymin};
                pbb={ob.xmax,ob.ymax};
                if (disp(paa,{u.x,u.y,0})>disp(pbb,{u.x,u.y,0}))
                    swap(paa,pbb);
                if (disp(paa,{u.x,u.y,0})+disp(pbb,{v.x,v.y,0})<disp(pa,{u.x,u.y,0})+disp(pb,{v.x,v.y,0}))
                {
                    pa=paa;
                    pb=pbb;
                }
            }
            //printf("papb: %d %d\n%d %d\n",pa.x,pa.y,pb.x,pb.y);
            cuti=i;
            break;
        }    
    }
    printf("%d\n",obflag);
    puts("------------------");
    if (obflag==0)
        for (i=0;i<t.deg*2-2;i++)
        {
            if (i==t.branch[i].n) continue;
            Flute::Branch u=t.branch[i],v=t.branch[t.branch[i].n];    
            poi a={u.x,u.y,0},b={v.x,v.y,0};
            OAMSTedge[++numOAMSTe]={a,b};
        }
    else
    {
        initedge();
        memset(color,0,sizeof(color));
        for (i=0;i<t.deg*2-2;i++)
        {   
            if (i==t.branch[i].n) continue;
            if (i==cuti) continue;
            Flute::Branch u=t.branch[i],v=t.branch[t.branch[i].n]; 
            printf("edge: %d %d\n",i,t.branch[i].n);
            add(i,t.branch[i].n,0);
            add(t.branch[i].n,i,0);
        }

        vector<int> a;
        a.push_back(cuti);
        while (!a.empty())
        {
            u=*a.begin();
            color[u]=1;
            for (j=head[u];j>0;j=nex[j])
            {
                if (color[e[j]]!=0) continue;
                a.push_back(e[j]);
            }
            a.erase(a.begin());
        }
        a.clear();
        a.push_back(t.branch[cuti].n);
        while (!a.empty())
        {
            u=*a.begin();
            color[u]=2;
            a.erase(a.begin());
            for (j=head[u];j>0;j=nex[j])
            {
                if (color[e[j]]!=0) continue;
                a.push_back(e[j]);
            }
        }
        for (i=0;i<t.deg*2-2;i++)
            printf("-------color: %d %d\n",i,color[i]);

        numN=0;
        for (i=0;i<t.deg*2-2;i++)
            if (color[i]==1)
            {
                XX[numN]=t.branch[i].x;
                YY[numN++]=t.branch[i].y;
            }
        XX[numN]=pa.x;
        YY[numN++]=pa.y;

        vector<poi> po;
        for (i=0;i<numN;i++)
            po.push_back({XX[i],YY[i],0});
        sort(po.begin(),po.end(),cmpp);
        vector<poi>::iterator new_end=unique(po.begin(),po.end(),equpoi);
        po.erase(new_end,po.end());
        //printf("-------------%d----------\n",numN-po.size());
        numN=po.size();
        for (i=0;i<numN;i++)
        {
            XX[i]=po[i].x;
            YY[i]=po[i].y;
        }
        OAflute(numN,XX,YY);

        numN=0;
        for (i=0;i<t.deg*2-2;i++)
            if (color[i]==2)
            {
                XX[numN]=t.branch[i].x;
                YY[numN++]=t.branch[i].y;
            }
        XX[numN]=pb.x;
        YY[numN++]=pb.y;
        
        po.clear();
        for (i=0;i<numN;i++)
            po.push_back({XX[i],YY[i],0});
        sort(po.begin(),po.end(),cmpp);
        new_end=unique(po.begin(),po.end(),equpoi);
        po.erase(new_end,po.end());
        //printf("-------------%d----------\n",numN-po.size());
        numN=po.size();
        for (i=0;i<numN;i++)
        {
            XX[i]=po[i].x;
            YY[i]=po[i].y;
        }
        OAflute(numN,XX,YY);

        OAMSTedge[++numOAMSTe]={pa,pb};
    }
        
}
int dealedge(Flute::Tree t)
{
    int u,i,j,numans,numN=0,cuti;
    int XX[NP],YY[NP],color[NP];
    bool obflag=0;
    poi paa,pbb,pa,pb;
    OBTree ob;

    Flute::printtree(t);

    for (i=0;i<t.deg*2-2;i++)
    {
        if (i==t.branch[i].n) continue;
        Flute::Branch u=t.branch[i],v=t.branch[t.branch[i].n];    
        ansob.clear();
        checkedge({u.x,u.y},{v.x,v.y},1);
        numans=ansob.size();
        printf("numans: %d %d\n%d %d\n%d %d\n",i,numans,u.x,u.y,v.x,v.y);
        if (numans>0)
        {
            obflag=1;
            initOBTreeNode(ob);
            for (j=0;j<numans;j++)
            {
                obs obtem=oo[ansob[j]];
                ob.xmin=min(obtem.x1,ob.xmin);
                ob.xmax=max(obtem.x2,ob.xmax);
                ob.ymin=min(obtem.y1,ob.ymin);
                ob.ymax=max(obtem.y2,ob.ymax);    
            }
            if (ob.xmax-ob.xmin<abs(u.x-v.x))
            {
                pa={ob.xmin,ob.ymax};
                pb={ob.xmax,ob.ymax};
                if (disp(pa,{u.x,u.y,0})>disp(pb,{u.x,u.y,0}))
                    swap(pa,pb);
                paa={ob.xmin,ob.ymin};
                pbb={ob.xmax,ob.ymin};
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
                pa={ob.xmin,ob.ymin};
                pb={ob.xmin,ob.ymax};
                if (disp(pa,{u.x,u.y,0})>disp(pb,{u.x,u.y,0}))
                    swap(pa,pb);
                paa={ob.xmax,ob.ymin};
                pbb={ob.xmax,ob.ymax};
                if (disp(paa,{u.x,u.y,0})>disp(pbb,{u.x,u.y,0}))
                    swap(paa,pbb);
                if (disp(paa,{u.x,u.y,0})+disp(pbb,{v.x,v.y,0})<disp(pa,{u.x,u.y,0})+disp(pb,{v.x,v.y,0}))
                {
                    pa=paa;
                    pb=pbb;
                }
            }
            //printf("papb: %d %d\n%d %d\n",pa.x,pa.y,pb.x,pb.y);
            cuti=i;
            break;
        }    
    }
    printf("%d\n",obflag);
    puts("------------------");
    if (obflag==0)
        for (i=0;i<t.deg*2-2;i++)
        {
            if (i==t.branch[i].n) continue;
            Flute::Branch u=t.branch[i],v=t.branch[t.branch[i].n];    
            poi a={u.x,u.y,0},b={v.x,v.y,0};
            OAMSTedge[++numOAMSTe]={a,b};
        }
    else
    {
        initedge();
        memset(color,0,sizeof(color));
        for (i=0;i<t.deg*2-2;i++)
        {   
            if (i==t.branch[i].n) continue;
            if (i==cuti) continue;
            Flute::Branch u=t.branch[i],v=t.branch[t.branch[i].n]; 
            printf("edge: %d %d\n",i,t.branch[i].n);
            add(i,t.branch[i].n,0);
            add(t.branch[i].n,i,0);
        }

        vector<int> a;
        a.push_back(cuti);
        while (!a.empty())
        {
            u=*a.begin();
            color[u]=1;
            for (j=head[u];j>0;j=nex[j])
            {
                if (color[e[j]]!=0) continue;
                a.push_back(e[j]);
            }
            a.erase(a.begin());
        }
        a.clear();
        a.push_back(t.branch[cuti].n);
        while (!a.empty())
        {
            u=*a.begin();
            color[u]=2;
            a.erase(a.begin());
            for (j=head[u];j>0;j=nex[j])
            {
                if (color[e[j]]!=0) continue;
                a.push_back(e[j]);
            }
        }
        for (i=0;i<t.deg*2-2;i++)
            printf("-------color: %d %d\n",i,color[i]);

        numN=0;
        for (i=0;i<t.deg*2-2;i++)
            if (color[i]==1)
            {
                XX[numN]=t.branch[i].x;
                YY[numN++]=t.branch[i].y;
            }
        XX[numN]=pa.x;
        YY[numN++]=pa.y;

        vector<poi> po;
        for (i=0;i<numN;i++)
            po.push_back({XX[i],YY[i],0});
        sort(po.begin(),po.end(),cmpp);
        vector<poi>::iterator new_end=unique(po.begin(),po.end(),equpoi);
        po.erase(new_end,po.end());
        //printf("-------------%d----------\n",numN-po.size());
        numN=po.size();
        for (i=0;i<numN;i++)
        {
            XX[i]=po[i].x;
            YY[i]=po[i].y;
        }
        OAflute(numN,XX,YY);

        numN=0;
        for (i=0;i<t.deg*2-2;i++)
            if (color[i]==2)
            {
                XX[numN]=t.branch[i].x;
                YY[numN++]=t.branch[i].y;
            }
        XX[numN]=pb.x;
        YY[numN++]=pb.y;
        
        po.clear();
        for (i=0;i<numN;i++)
            po.push_back({XX[i],YY[i],0});
        sort(po.begin(),po.end(),cmpp);
        new_end=unique(po.begin(),po.end(),equpoi);
        po.erase(new_end,po.end());
        //printf("-------------%d----------\n",numN-po.size());
        numN=po.size();
        for (i=0;i<numN;i++)
        {
            XX[i]=po[i].x;
            YY[i]=po[i].y;
        }
        OAflute(numN,XX,YY);

        OAMSTedge[++numOAMSTe]={pa,pb};
    }
        
}
void OAflute(int n,int X[],int Y[])
{
    bool obflag=0;
    poi paa,pbb,pa,pb;
    OBTree ob;
    Flute::Tree t,flutetree1,flutetree2;

    t=Flute::flute(n,X,Y,12);

    dealpoint(t);
    dealedge(t);
        
}
void OAMST()
{
    int i,j,k;
    int X[NP],Y[NP];
    
    for (i=1;i<=O;i++)
        OB[i-1]=i;
    buildOBTree(1,O);
    for (i=1;i<=P;i++)
    {
        X[i-1]=pp[i].x;
        Y[i-1]=pp[i].y;
    }
    OAflute(P,X,Y);
    
    WL=0;
    for(i=1;i<=numOAMSTe;i++)
        WL+=disp(OAMSTedge[i].u,OAMSTedge[i].v);
    printf("WL: %d\n",WL);
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


