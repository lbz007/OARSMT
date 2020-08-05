#include "global.h"

void dumpgnuplot()
{
    FilePureName="block";
    string file=FilePureName+".out";
    ofstream fo(file,ios::out);
    for (int i=1;i<=O;i++)
    {
        fo<<oo[i].x1<<' '<<oo[i].y2<<endl;
        fo<<oo[i].x1<<' '<<oo[i].y1<<endl;
        fo<<oo[i].x2<<' '<<oo[i].y1<<endl;
        fo<<oo[i].x2<<' '<<oo[i].y2<<endl;
        fo<<oo[i].x1<<' '<<oo[i].y2<<endl<<endl;
    }
    fo.close();
  
    FilePureName="OASGedge";
    file=FilePureName+".out";
    ofstream fo1(file,ios::out);
    for(int i=1;i<=numOASGe;i++)
        fo1<<a[OASGedge[i].u].x<<' '<<a[OASGedge[i].u].y<<endl<<a[OASGedge[i].v].x<<' '<<a[OASGedge[i].v].y<<endl<<endl;
    fo1.close();

    FilePureName="MTSTedge";
    file=FilePureName+".out";
    ofstream fo2(file,ios::out);
    for(int i=1;i<=numMTSTe;i++)
        fo2<<a[MTSTedge[i].u].x<<' '<<a[MTSTedge[i].u].y<<endl<<a[MTSTedge[i].v].x<<' '<<a[MTSTedge[i].v].y<<endl<<endl;
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

    FilePureName="point";
    file=FilePureName+".out";
    ofstream fo5(file,ios::out);
    for(int i=1;i<=P;i++)
        fo5<<pp[i].x<<' '<<pp[i].y<<endl<<endl;
    fo5.close();

    FilePureName="OPMSTedge";
    file=FilePureName+".out";
    ofstream fo6(file,ios::out);
    for(int i=1;i<=numOPMSTe;i++)
        fo6<<a[OPMSTedge[i].u].x<<' '<<a[OPMSTedge[i].u].y<<endl<<a[OPMSTedge[i].v].x<<' '<<a[OPMSTedge[i].v].y<<endl<<endl;
    fo6.close();

    FilePureName="OARSMTedge";
    file=FilePureName+".out";
    ofstream fo7(file,ios::out);
    for(int i=1;i<=numOARSMTe;i++)
        fo7<<OARSMTedge[i].u.x<<' '<<OARSMTedge[i].u.y<<endl<<OARSMTedge[i].v.x<<' '<<OARSMTedge[i].v.y<<endl<<endl;
    fo7.close();
}
