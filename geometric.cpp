#include "global.h"

boundry cal_line_boundry(Vec s,Vec e){
	double xmin = s.x;
	double xmax = e.x;
	double ymin = s.y;
	double ymax = e.y;
	if(xmin>xmax) swap(xmin,xmax);
	if(ymin>ymax) swap(ymin,ymax);
	return {xmin,xmax,ymin,ymax};
}
//------------------BOX-------------------------
//Returns the boundary of a line segment
//Determine if the two boxes overlap, the tangency is overlap
bool isBoxCrossBox(boundry b1,boundry b2){
	if(b1.xmin>b2.xmax) {
		return false;
	}
	else if(b1.xmax<b2.xmin){ 
		return false;
	} 
	else if(b1.ymin>b2.ymax){ 
		return false;
	}
	else if(b1.ymax<b2.ymin){
		return false;
	} 
	else 
	{
		return true;
	}
} 

//-----------------------LINE--------------------------
//Determine whether two line segments intersect. Vector method Tangent counts into intersections Partial coincidence also intersects 
bool isLineCrossLine(Vec l1s,Vec l1e,Vec l2s,Vec l2e){
	boundry b1 = cal_line_boundry(l1s,l1e);
	boundry b2 = cal_line_boundry(l2s,l2e);
	if(!isBoxCrossBox(b1,b2)) return false;
	else{
		Vec l1s_e = sub(l1e,l1s);
		Vec l2s_e = sub(l2e,l2s);
		Vec l1s_l2s = sub(l2s,l1s);
		Vec l1s_l2e = sub(l2e,l1s);
		Vec l2s_l1s = sub(l1s,l2s);
		Vec l2s_l1e = sub(l1e,l2s);
		bool flag1 = cmult(l1s_l2s,l1s_e)*cmult(l1s_l2e,l1s_e)<=0 ? true:false;
		bool flag2 = cmult(l2s_l1s,l2s_e)*cmult(l2s_l1e,l2s_e)<=0 ? true:false;
		if(flag1 & flag2) return true;
		else return false; 
	}
}



//According to the known two-point coordinates, the straight line analytical equations of these two points are obtained: a*x+b*y+c = 0  (a >= 0)  
GLine makeGLine(Vec v1,Vec v2){ 
	GLine gl; 
	int sign = 1; 
	gl.a=v2.y-v1.y; 
	if(gl.a<0) { 
		sign = -1; 
		gl.a=sign*gl.a; 
	} 
	gl.b=sign*(v1.x-v2.x); 
	gl.c=sign*(v1.y*v2.x-v1.x*v2.y); 
	return gl; 
}

Vec getlineprojection(Vec P, Vec A, Vec B){
    Vec v=sub(B,A);
    return add(A,nmult((mult(v,sub(P,A))/mult(v,v)),v));
}

//If two lines l1 (a1*x+b1*y+c1 = 0) and l2(a2*x+b2*y+c2 = 0) intersect, return the intersection point p. If parallel, it will return an invalid value.
Vec lineintersect(GLine l1,GLine l2){ 
	Vec v;
	double d=l1.a*l2.b-l2.a*l1.b; 
	v.x = (l2.c*l1.b-l1.c*l2.b)/d; 
	v.y = (l2.a*l1.c-l1.a*l2.c)/d; 
	return v; 
}

double arc_calc(Vec a,Vec b)//base point is b
{
    /* double dis=sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)); */
    /* double si=dis/(a.y-b.y); */
    return atan2((a.y-b.y),(a.x-b.x));
}


