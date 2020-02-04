#include "global.h"

poi intersection(poi p1,poi p2,obs rect)
{
    Vec l1s={p1.x,p1.y};
    Vec l1e={p2.x,p2.y};
    Vec l2s,l2e,v3;
    GLine gl1,gl2;
    l2s={rect.x1,rect.y1};
    l2e={rect.x1,rect.y2};
    if (isLineCrossLine(l1s,l1e,l2s,l2e))
    {
        gl1 = makeGLine(l1s,l1e);
        gl2 = makeGLine(l2s,l2e);
        v3=lineintersect(gl1,gl2);
        return {v3.x,v3.y,0};
    }
    l2s={rect.x1,rect.y1};
    l2e={rect.x2,rect.y1};
    if (isLineCrossLine(l1s,l1e,l2s,l2e))
    {
        gl1 = makeGLine(l1s,l1e);
        gl2 = makeGLine(l2s,l2e);
        v3=lineintersect(gl1,gl2);
        return {v3.x,v3.y,0};
    }
    l2s={rect.x2,rect.y1};
    l2e={rect.x2,rect.y2};
    if (isLineCrossLine(l1s,l1e,l2s,l2e))
    {
        //printf("(%f %f) (%f %f) (%f %f) (%f %f) \n",l1s.x,l1s.y,l1e.x,l1e.y,l2s.x,l2s.y,l2e.x,l2e.y);
        gl1 = makeGLine(l1s,l1e);
        gl2 = makeGLine(l2s,l2e);
        v3=lineintersect(gl1,gl2);
        return {v3.x,v3.y,0};
    }
    l2s={rect.x1,rect.y2};
    l2e={rect.x2,rect.y2};
    if (isLineCrossLine(l1s,l1e,l2s,l2e))
    {
        gl1 = makeGLine(l1s,l1e);
        gl2 = makeGLine(l2s,l2e);
        v3=lineintersect(gl1,gl2);
        return {v3.x,v3.y,0};
    }
}
bool cmplinkp(blockedge aa,blockedge bb)
{
    return aa.v<bb.v;
}
int dealpoint(Flute::Tree t)
{
    int u,i,j,k,numans,numN=0,cuti,S,T,numlinkp,SS,TT;
    int XX[NP],YY[NP],color[NP];
    bool obflag=0;
    poi paa,pbb,pa,pb;
    OBTree ob;
    obs obtem;
    vector<blockedge> linkp;
    vector<blockedge> linkpo;
    //Flute::printtree(t);
    //Flute::plottree(t);

    for (i=0;i<t.deg*2-2;i++)
    {
        Flute::Branch u=t.branch[i];    
        ansob.clear();
        //printf("%d %d \n",u.x,u.y);
        checknode({u.x,u.y,0},1);
        numans=ansob.size();
        //printf(" %d\n",numans);
        if (numans>0)
        {
            obflag=1;
            obtem=oo[ansob[0]];

            linkp.clear();
            linkpo.clear();

            for (k=0;k<t.deg*2-2;k++)
            {
                u=t.branch[k];  
                if (inbox({u.x,u.y},{obtem.x1,obtem.y1},{obtem.x2,obtem.y2}))
                {
                    if (inbox({t.branch[u.n].x,t.branch[u.n].y},{obtem.x1,obtem.y1},{obtem.x2,obtem.y2})==0)
                        linkp.push_back({u.n,{t.branch[u.n].x,t.branch[u.n].y,0},k});  
                    for (j=0;j<t.deg*2-2;j++)
                        if (t.branch[j].n==k)
                            if (inbox({t.branch[j].x,t.branch[j].y},{obtem.x1,obtem.y1},{obtem.x2,obtem.y2})==0)
                                linkp.push_back({j,{t.branch[j].x,t.branch[j].y,0},k});              
                }
            }

            numlinkp=linkp.size();
            for (j=0;j<numlinkp;j++)
            {
                u=t.branch[int(linkp[j].v+0.5)];
                //printf("u.xy: %d %d\n",u.x,u.y);
                linkpo.push_back({linkp[j].id,intersection(linkp[j].a,{u.x,u.y,0},obtem)});
            }
            linkpo.push_back({-1,{obtem.x1,obtem.y1,0}});
            linkpo.push_back({-1,{obtem.x2,obtem.y1,0}});
            linkpo.push_back({-1,{obtem.x1,obtem.y2,0}});
            linkpo.push_back({-1,{obtem.x2,obtem.y2,0}});

            // for (j=0;j<numlinkp+4;j++)
            //     printf("linkp: %d %d %d\n",linkpo[j].id,linkpo[j].a.x,linkpo[j].a.y);
            
            for (j=0;j<numlinkp+4;j++)
                linkpo[j].v=arc_calc({linkpo[j].a.x,linkpo[j].a.y},{u.x,u.y});
            sort(linkpo.begin(),linkpo.end(),cmplinkp);
            
            //  for (j=0;j<numlinkp+4;j++)
            //      printf("linkpo: %d %d %d\n",linkpo[j].id,linkpo[j].a.x,linkpo[j].a.y);

            int hh,ss,sum,maxdis=0;
            for (j=0;j<numlinkp+4;j++)
                if (linkpo[j].id!=-1)
                {
                   hh=j;
                   break;
                }
            j=(hh+1)%(numlinkp+4); ss=hh; sum=disp(linkpo[hh].a,linkpo[j].a);
            while (1)
            {   
                if (linkpo[j].id!=-1)
                {
                    if (sum>maxdis)
                    {
                        maxdis=sum;
                        SS=ss;
                        TT=j;
                    }
                    ss=j;
                    sum=0;
                }
                if (j==hh) break;
                sum+=disp(linkpo[j].a,linkpo[(j+1)%(numlinkp+4)].a);
                j=(j+1)%(numlinkp+4);
            }

            S=linkpo[SS].id;
            T=linkpo[TT].id;
            // printf("numlinkp: %d\n",numlinkp);
            // printf("ST: %d %d\n %d %d\n%d %d\n",S,T,t.branch[S].x,t.branch[S].y,t.branch[T].x,t.branch[T].y);
            cuti=i;
            break;
        }    
    }

    //printf("%d",cuti);    puts("-------------------------------\n");
    
    // if (obflag==0)
    //     for (i=0;i<t.deg*2-2;i++)
    //     {
    //         if (i==t.branch[i].n) continue;
    //         Flute::Branch u=t.branch[i],v=t.branch[t.branch[i].n];    
    //         poi a={u.x,u.y,0},b={v.x,v.y,0};
    //         OAMSTedge[++numOAMSTe]={a,b};
    //     }

    if (obflag==1)
    {
        initedge2();
        memset(color,0,sizeof(color));
        for (i=0;i<t.deg*2-2;i++)
        {   
            Flute::Branch u=t.branch[i],v=t.branch[t.branch[i].n]; 
            if (i==u.n) continue;
            if (inbox({u.x,u.y},{obtem.x1,obtem.y1},{obtem.x2,obtem.y2})) continue;
            if (inbox({v.x,v.y},{obtem.x1,obtem.y1},{obtem.x2,obtem.y2})) continue;
            
            //printf("edge: %d %d\n",i,t.branch[i].n);
            add2(i,t.branch[i].n);
            add2(t.branch[i].n,i);
        }

        vector<int> a;
        vector<poi> po;
        int numcolor=1;
        i=TT;
        while (1)
        {
            //printf("---- %d %d ---\n",i,linkpo[i].id);
            a.clear();
            a.push_back(linkpo[i].id);
            while (!a.empty())
            {
                u=*a.begin();
                color[u]=numcolor;
                for (j=head2[u];j>0;j=nex2[j])
                {
                    if (color[e2[j]]!=0) continue;
                    a.push_back(e2[j]);
                }
                a.erase(a.begin());
            }
            if (i==SS) break;
            i=(i+1)%(numlinkp+4);
            if (linkpo[i].id==-1) 
                numcolor++;
            while (linkpo[i].id==-1)
                i=(i+1)%(numlinkp+4);
        }

        //for (j=0;j<t.deg*2-2;j++)  printf("-------color: %d %d\n",j,color[j]);

        i=TT;
        numcolor=1;numN=0;
        while (1)
        {   
            for (j=0;j<t.deg;j++)
                if (color[j]==numcolor)
                {
                    XX[numN]=t.branch[j].x;
                    YY[numN++]=t.branch[j].y;
                }
            int tem=i;
            while (linkpo[tem].id!=-1)
                tem=(tem-1+numlinkp+4)%(numlinkp+4);
            if ((tem+1)%(numlinkp+4)!=TT)
            {
                XX[numN]=linkpo[tem].a.x;
                YY[numN++]=linkpo[tem].a.y;
            }
            tem=i;
            while (linkpo[tem].id!=-1)
                tem=(tem+1)%(numlinkp+4);
            if ((tem-1+numlinkp+4)%(numlinkp+4)!=SS)
            {
                XX[numN]=linkpo[tem].a.x;
                YY[numN++]=linkpo[tem].a.y;
                if (linkpo[(tem+1)%(numlinkp+4)].id==-1)
                {
                    XX[numN]=linkpo[(tem+1)%(numlinkp+4)].a.x;
                    YY[numN++]=linkpo[(tem+1)%(numlinkp+4)].a.y;
                }
            }
            

            tem=(i+1)%(numlinkp+4);
            if (linkpo[tem].id==-1)
            {
                po.clear();
                for (j=0;j<numN;j++)
                    po.push_back({XX[j],YY[j],0});
                sort(po.begin(),po.end(),cmpp);
                vector<poi>::iterator new_end=unique(po.begin(),po.end(),equpoi);
                po.erase(new_end,po.end());
                //printf("-------------%d----------\n",numN-po.size());
                numN=po.size();
                for (j=0;j<numN;j++)
                {
                    XX[j]=po[j].x;
                    YY[j]=po[j].y;
                }
                OAflute(numN,XX,YY);
                numcolor++;
                numN=0;
            }
            if (i==SS) break;
            i=(i+1)%(numlinkp+4); 
            while (linkpo[i].id==-1)
                i=(i+1)%(numlinkp+4);
        }
    }
    return obflag;  
}

int dealedge(Flute::Tree t)
{
    int u,i,j,numans,numN=0,cuti;
    int XX[NP],YY[NP],color[NP];
    bool obflag=0;
    poi paa,pbb,pa,pb;
    OBTree ob;
    obs obtem;

    //Flute::printtree(t);

    for (i=0;i<t.deg*2-2;i++)
    {
        if (i==t.branch[i].n) continue;
        Flute::Branch u=t.branch[i],v=t.branch[t.branch[i].n];    
        ansob.clear();
        checkedge({u.x,u.y},{v.x,v.y},1);
        numans=ansob.size();
        //printf("numans: %d %d\n%d %d\n%d %d\n",i,numans,u.x,u.y,v.x,v.y);
        if (numans>0)
        {
            obflag=1;
            initOBTreeNode(ob);
            for (j=0;j<1;j++) // 1 or numans check!
            {
                obtem=oo[ansob[j]];
                ob.xmin=min(obtem.x1,ob.xmin);
                ob.xmax=max(obtem.x2,ob.xmax);
                ob.ymin=min(obtem.y1,ob.ymin);
                ob.ymax=max(obtem.y2,ob.ymax);    
            }
            obtem={ob.xmin,ob.ymin,ob.xmax,ob.ymax};
            blockedgepoint({u.x,u.y},{v.x,v.y},obtem,pa,pb);

            cuti=i;
            break;
        }    
    }
    //printf("%d",numans); puts("------------------");
    if (obflag==0)
        for (i=0;i<t.deg*2-2;i++)
        {
            if (i==t.branch[i].n) continue;
            Flute::Branch u=t.branch[i],v=t.branch[t.branch[i].n];    
            poi a={u.x,u.y,0},b={v.x,v.y,0};
            OAMSTedge[++numOAMSTe]={a,b};
        }
    if (obflag==1)
    {
        initedge2();
        memset(color,0,sizeof(color));
        for (i=0;i<t.deg*2-2;i++)
        {   
            if (i==t.branch[i].n) continue;
            if (i==cuti) continue;
            Flute::Branch u=t.branch[i],v=t.branch[t.branch[i].n]; 
            //printf("edge: %d %d\n",i,t.branch[i].n);
            add2(i,t.branch[i].n);
            add2(t.branch[i].n,i);
        }

        vector<int> a;
        a.push_back(cuti);
        while (!a.empty())
        {
            u=*a.begin();
            color[u]=1;
            for (j=head2[u];j>0;j=nex2[j])
            {
                if (color[e2[j]]!=0) continue;
                a.push_back(e2[j]);
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
            for (j=head2[u];j>0;j=nex2[j])
            {
                if (color[e2[j]]!=0) continue;
                a.push_back(e2[j]);
            }
        }
        for (i=0;i<t.deg*2-2;i++)
            //printf("-------color: %d %d\n",i,color[i]);

        numN=0;
        for (i=0;i<t.deg;i++)
            if (color[i]==1)
            {
                XX[numN]=t.branch[i].x;
                YY[numN++]=t.branch[i].y;
            }
        XX[numN]=pa.x;
        YY[numN++]=pa.y;
        //XX[numN]=pb.x;
        //YY[numN++]=pb.y;

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
        for (i=0;i<t.deg;i++)
            if (color[i]==2)
            {
                XX[numN]=t.branch[i].x;
                YY[numN++]=t.branch[i].y;
            }
        XX[numN]=pb.x;
        YY[numN++]=pb.y;
        XX[numN]=pa.x;
        YY[numN++]=pa.y;

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

        //OAMSTedge[++numOAMSTe]={pa,pb};
    }
    return obflag; 
}
void OAflute(int n,int X[],int Y[])
{
    //printf("OAflute n: %d\n",n);
    if (n<=1) return;
    bool obflag=0;
    poi paa,pbb,pa,pb;
    OBTree ob;
    Flute::Tree t,flutetree1,flutetree2;

    t=Flute::flute(n,X,Y,12);
    //dealedge(t);
    //if (dealedge(t)==0)  dealpoint(t);
    if (dealpoint(t)==0)  dealedge(t);
    
}