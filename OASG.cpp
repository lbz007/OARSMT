#include "global.h"

void addOASGedge(poi a,poi b)
{
    if (mar==1)
    {
        a.y=-a.y;
        b.y=-b.y;
    }
    if (mar==2)
    {
        swap(a.x,a.y);
        swap(b.x,b.y);
    }
    if (mar==3)
    {
        a.y=-a.y;
        b.y=-b.y;
        swap(a.x,a.y);
        swap(b.x,b.y);
    }
    OASGedge[++numOASGe]={mp.find(a)->second,mp.find(b)->second,disp(a,b)};
    // OASGedge[++numOASGe]={a.id,b.id,disp(a,b)};
    add(OASGedge[numOASGe].u,OASGedge[numOASGe].v,disp(a,b));
    add(OASGedge[numOASGe].v,OASGedge[numOASGe].u,disp(a,b));
    /* printf("%d %d\n",a.x,b.x); */
}
bool cblock(poi aa,poi bb)
{
    /* return 0; */
    set<int>::iterator i;
    poi p1,p2;
    for (i=lefto.begin();i!=lefto.end();i++)
    {
        p1=b[(*i)-1];
        p2=b[(*i)];
        if (aa.y<p1.y&&aa.y>p2.y&&bb.y<p1.y&&bb.y>p2.y)
        {
            if ((aa.x-p1.x)*(bb.x-p1.x)<0)
                return true;
            if ((aa.x-p1.x)*(bb.x-p1.x)==0 && aa.x+bb.x>p1.x+p2.x)
                return true;    
        }
    }
    for (i=bottomo.begin();i!=bottomo.end();i++)
    {
        p1=b[(*i)+1];
        p2=b[(*i)];
        if (aa.x<p1.x&&aa.x>p2.x&&bb.x<p1.x&&bb.x>p2.x)
        {
            if ((aa.y-p1.y)*(bb.y-p1.y)<0)
                return true;
            if ((aa.y-p1.y)*(bb.y-p1.y)==0 && aa.y+bb.y>p1.y+p2.y)
                return true;
        }
    }
    return false;
}
void regionOASG(bool flago)
{
    int i,j,nums;
    poi pp,nearestp,s[N];
    multiset<poi,cmpset> active;
    n=0;
    active.insert({-INF,0,0});
    for (i=1;i<=P;i++)
        a[++n]={p[i].x,p[i].y,n};
    for (i=1;i<=O;i++)
    {
        a[++n]={o[i].x1,o[i].y2,n};
        a[++n]={o[i].x1,o[i].y1,n};
        a[++n]={o[i].x2,o[i].y1,n};
        a[++n]={o[i].x2,o[i].y2,n};
    }
    for (i=1;i<=n;i++)
        b[i]=a[i];
    sort(a.begin()+1,a.begin()+1+n,cmp);
    for (i=1;i<=n;i++)
    {
        nums=0;
        nearestp={-INF,0,0};
        multiset<poi,cmpset>::iterator x;
        pp={a[i].x,-INF,0};
        x=active.lower_bound(pp);
        while ((*x).x>-INF)
        {
            /* printf("ll: %d %d\n",(*x).x,(*x).y); */
            if ((*x).x-(*x).y<a[i].x-a[i].y) break;s[++nums]=(*x);
            if (cblock((*x),a[i])==0)
            {
                
                if (disp((*x),a[i])<disp(nearestp,a[i]))
                    nearestp=(*x);  
            }          
            x++;
        }
        if (nearestp.x>-INF)
            addOASGedge(a[i],nearestp);
        for (j=1;j<=nums;j++)
            active.erase(s[j]);
        if (clas(a[i])==2)
        {
             bottomo.insert(a[i].id);
             lefto.insert(a[i].id);
        }
        if (clas(a[i])==1)
            lefto.erase(a[i].id+1);
        if (clas(a[i])==3)
        {
            bottomo.erase(a[i].id-1);
            pp={a[i].x,-INF,0};
            x=active.lower_bound(pp);
            while((*x).x>-INF)
            {
                if ((*x).x<b[a[i].id-1].x) break;
                if ((*x).x-(*x).y<=a[i].x-a[i].y && (*x).y<a[i].y)
                {
                    active.erase(x);
                    x--;
                }
                x++;
            }

        }
        active.insert(a[i]);

        /* for(x=active.begin();x!=active.end();x++) */
        /*     printf("%d %d\n",(*x).x,(*x).y); */
        /* printf("----------------------\n"); */

    }
}

void OASG()
{
    int i;
    for (i=1;i<=P;i++)
    {  
        p[i].x=pp[i].x;
        p[i].y=-pp[i].y;
    }
    for (i=1;i<=O;i++)
    {
        o[i].x1=oo[i].x1;
        o[i].y1=-oo[i].y1;
        o[i].x2=oo[i].x2;
        o[i].y2=-oo[i].y2;
        if (o[i].x1>o[i].x2) swap(o[i].x1,o[i].x2);
        if (o[i].y1>o[i].y2) swap(o[i].y1,o[i].y2);
    }
    mar=1;
    regionOASG(0);
    /* OASG(1); */
     
    for (i=1;i<=P;i++)
    {  
        p[i].x=pp[i].y;
        p[i].y=pp[i].x;
    }
    for (i=1;i<=O;i++)
    {
        o[i].x1=oo[i].y1;
        o[i].y1=oo[i].x1;
        o[i].x2=oo[i].y2;
        o[i].y2=oo[i].x2;
        if (o[i].x1>o[i].x2) swap(o[i].x1,o[i].x2);
        if (o[i].y1>o[i].y2) swap(o[i].y1,o[i].y2);
    }
    mar=2;
    regionOASG(0);   
    /* OASG(1); */

    for (i=1;i<=P;i++)
    {  
        p[i].x=pp[i].y;
        p[i].y=-pp[i].x;
    }
    for (i=1;i<=O;i++)
    {
        o[i].x1=oo[i].y1;
        o[i].y1=-oo[i].x1;
        o[i].x2=oo[i].y2;
        o[i].y2=-oo[i].x2;
        if (o[i].x1>o[i].x2) swap(o[i].x1,o[i].x2);
        if (o[i].y1>o[i].y2) swap(o[i].y1,o[i].y2);
    }
    mar=3;
    regionOASG(0);   
    /* OASG(1); */
    for (i=1;i<=P;i++)
    {  
        p[i].x=pp[i].x;
        p[i].y=pp[i].y;
    }
    for (i=1;i<=O;i++)
    {
        o[i].x1=oo[i].x1;
        o[i].y1=oo[i].y1;
        o[i].x2=oo[i].x2;
        o[i].y2=oo[i].y2;
        if (o[i].x1>o[i].x2) swap(o[i].x1,o[i].x2);
        if (o[i].y1>o[i].y2) swap(o[i].y1,o[i].y2);
    }
    mar=4;
    regionOASG(0);
}