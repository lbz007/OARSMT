#include "global.h"

void dumpgnuplot()
{
    FilePureName="block";
    string file=FilePureName+".out";
    ofstream fo(file,ios::out);
    for (int i=1;i<=O;i++)
    {
        fo<<o[i].x1<<' '<<o[i].y2<<endl;
        fo<<o[i].x1<<' '<<o[i].y1<<endl;
        fo<<o[i].x2<<' '<<o[i].y1<<endl;
        fo<<o[i].x2<<' '<<o[i].y2<<endl;
        fo<<o[i].x1<<' '<<o[i].y2<<endl<<endl;
    }
    fo.close();
  
    FilePureName="OASGedge";
    file=FilePureName+".out";
    ofstream fo1(file,ios::out);
    for(int i=1;i<=numOASGe;i++)
        fo1<<b[OASGedge[i].u].x<<' '<<b[OASGedge[i].u].y<<endl<<b[OASGedge[i].v].x<<' '<<b[OASGedge[i].v].y<<endl<<endl;
    fo1.close();

    FilePureName="MTSTedge";
    file=FilePureName+".out";
    ofstream fo2(file,ios::out);
    for(int i=1;i<=numMTSTe;i++)
        fo2<<b[MTSTedge[i].u].x<<' '<<b[MTSTedge[i].u].y<<endl<<b[MTSTedge[i].v].x<<' '<<b[MTSTedge[i].v].y<<endl<<endl;
    fo2.close();

    FilePureName="OARSTedge";
    file=FilePureName+".out";
    ofstream fo3(file,ios::out);
    for(int i=1;i<=numOARSTe;i++)
        fo3<<OARSTedge[i].u.x<<' '<<OARSTedge[i].u.y<<endl<<OARSTedge[i].v.x<<' '<<OARSTedge[i].v.y<<endl<<endl;
    fo3.close();

    FilePureName="OAMSTedge";
    file=FilePureName+".out";
    ofstream fo4(file,ios::out);
    for(int i=1;i<=numOAMSTe;i++)
        fo4<<OAMSTedge[i].u.x<<' '<<OAMSTedge[i].u.y<<endl<<OAMSTedge[i].v.x<<' '<<OAMSTedge[i].v.y<<endl<<endl;
    fo4.close();
}
