#ifndef _GEO_
#define _GEO_ 

#define MAX 1000000000.0
#define MIN 0.00000000001
#define PI (acos(-1))

struct Vec{											//A vector,can represent points and vectors
	double x,y;
	Vec(double _x,double _y):x(_x),y(_y){}
	Vec(){}
};
 
struct GLine{										//General equation representing a straight line: ax+by+c=0 a>=0
	double a,b,c;
};

struct dvec{Vec p;Vec v;};							//A point and its direction 
struct line{int s,e;};   							//A line segment,represented by an index of two vertices
struct LINE{Vec s;Vec e;};							//A line segment, represented by two coordinates
struct boundry{double xmin,xmax,ymin,ymax;}; 		//Bounding box

struct EE{											//A line segment represented by id,and overload operator < with its id
	int s,e,id;
	bool operator<(const EE & e)const{
		return id<e.id;
	}
};

//---------------------------------------------------Function---------------------------------------------------//
//vec
Vec nmult(double,Vec);  								//Vector number multiplication
Vec add(Vec,Vec);       								//Vector addition
Vec sub(Vec,Vec);       								//Vector subtraction
double mult(Vec,Vec);      								//Vector inner product
double cmult(Vec,Vec);     								//Vector cross multiplication
double mod(Vec);        								//Vector mod
double mod_square(Vec); 								//Vector mod square
Vec uv(Vec v);											//Vector unit vector 
Vec middleNode(Vec,Vec);								//Calculate the midpoint of two points
double min(double,double);								//Maximum of two numbers
double max(double,double);								//Minimum of two numbers

//geometric
boundry cal_line_boundry(Vec s,Vec e);
bool isBoxCrossBox(boundry ,boundry );					//Determine if the two boxes overlap, the tangency is overlap
bool isLineCrossLine(Vec,Vec,Vec,Vec);					//Determine whether two line segments intersect. Vector method Tangent counts into intersections Partial coincidence also intersects
GLine makeGLine(Vec ,Vec );								//According to the known two-point coordinates, the straight line analytical equations of these two points are obtained: a*x+b*y+c = 0  (a >= 0) 
Vec lineintersect(GLine ,GLine );						//If two lines l1 (a1*x+b1*y+c1 = 0) and l2(a2*x+b2*y+c2 = 0) intersect, return the intersection point p. If parallel, it will return an invalid value.


//lbz
double arc_calc(Vec a,Vec b);

#endif
