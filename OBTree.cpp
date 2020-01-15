#include "global.h"

bool cmpobx(int a,int b)
{
    return (oo[a].x1+oo[a].x2)<(oo[b].x1+oo[b].x2);
}
bool cmpoby(int a,int b)
{
    return (oo[a].y1+oo[a].y2)<(oo[b].y1+oo[b].y2);
}
void initOBTreeNode(OBTree &s)
{
    s.xmin=s.ymin=INF;
    s.xmax=s.ymax=-INF;
    s.a=0;
}
void buildOBTree(int s,int k)
{
    int i,h;
    vector<int> OBtem;

    initOBTreeNode(obt[s]);
    for (i=0;i<k;i++) obt[s].xmin=min(oo[OB[i]].x1,obt[s].xmin);
    for (i=0;i<k;i++) obt[s].xmax=max(oo[OB[i]].x2,obt[s].xmax);
    for (i=0;i<k;i++) obt[s].ymin=min(oo[OB[i]].y1,obt[s].ymin);
    for (i=0;i<k;i++) obt[s].ymax=max(oo[OB[i]].y2,obt[s].ymax);
    if (k==1)
        obt[s].a=OB[0];
    if (k>1)
    {
        h=k/2;
        for (i=0;i<k;i++) OBtem.push_back(OB[i]);
        if (obt[s].xmax-obt[s].xmin>obt[s].ymax-obt[s].ymin)
            sort(OBtem.begin(),OBtem.end(),cmpobx);
        else
            sort(OBtem.begin(),OBtem.end(),cmpoby);
        for (i=0;i<h;i++) OB[i]=OBtem[i];
        buildOBTree(s*2,h);
        for (i=0;i<k-h;i++) OB[i]=OBtem[h+i];
        buildOBTree(s*2+1,k-h);
    }
    return;
}

void checknode(poi p,int s)
{
    if (inbox(p,{obt[s].xmin,obt[s].ymin},{obt[s].xmax,obt[s].ymax})==0)
    //if (p.x>=obt[s].xmax || p.x<=obt[s].xmin || p.y>=obt[s].ymax || p.y<=obt[s].ymin)
        return ;
    if (obt[s].a!=0)
    {
        ansob.push_back(obt[s].a);
        return;
    }
    checknode(p,s*2);
    checknode(p,s*2+1);
    return ;
}

void checkedge(poi p1,poi p2,int s)
{
    bool blockflag=0;
    if (inbox(p1,{obt[s].xmin,obt[s].ymin},{obt[s].xmax,obt[s].ymax})==1)
        blockflag=1;
    if (inbox(p2,{obt[s].xmin,obt[s].ymin},{obt[s].xmax,obt[s].ymax})==1)
        blockflag=1;

    if (p1.y>obt[s].ymin && p1.y<obt[s].ymax && p2.y>obt[s].ymin && p2.y<obt[s].ymax)
        if ((p1.x<=obt[s].xmin && p2.x>=obt[s].xmax) || (p2.x<=obt[s].xmin && p1.x>=obt[s].xmax))
            blockflag=1;
    if (p1.x>obt[s].xmin && p1.x<obt[s].xmax && p2.x>obt[s].xmin && p2.x<obt[s].xmax)
        if ((p1.y<=obt[s].ymin && p2.y>=obt[s].ymax) || (p2.y<=obt[s].ymin && p1.y>=obt[s].ymax))
            blockflag=1;

    if (blockflag==0)
        return;
    
    if (obt[s].a!=0)
    {
        if (inbox(p1,{obt[s].xmin,obt[s].ymin},{obt[s].xmax,obt[s].ymax})==1) 
            return;
        if (inbox(p2,{obt[s].xmin,obt[s].ymin},{obt[s].xmax,obt[s].ymax})==1) 
            return;
        ansob.push_back(obt[s].a);
        return;
    }
    checkedge(p1,p2,s*2);
    checkedge(p1,p2,s*2+1);
    return ;
}