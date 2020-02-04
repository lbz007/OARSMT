#include "global.h"
#include <cmath>

using namespace std;

//Vector number multiplication
Vec nmult(double w,Vec v){
	return {w*v.x,w*v.y};
} 

//Vector addition
Vec add(Vec v1,Vec v2){
	return {v1.x+v2.x,v1.y+v2.y};
} 

//Vector subtraction
Vec sub(Vec v1,Vec v2){
	return {v1.x-v2.x,v1.y-v2.y};
} 

//Vector inner product 
double mult(Vec v1,Vec v2){
	return (v1.x*v2.x+v1.y*v2.y);
}

//Vector cross multiplication
double cmult(Vec v1,Vec v2){
	return (v1.x*v2.y-v2.x*v1.y);
} 

//Vector mod 
double mod(Vec v){
	return sqrt(pow(v.x,2)+pow(v.y,2));
}

//Vector mod square 
double mod_square(Vec v){
	return (pow(v.x,2)+pow(v.y,2));
}

//Vector unit vector 
Vec uv(Vec v){
	double l=mod(v);
	return nmult(1.0/l,v); 
}

//swap double 
void swap(double &a, double &b){
    double temp = a; a = b; b = temp;
}

//swap int 
void swap(int &a,int &b){
	int temp=a;a=b;b=temp;
}

//swap Vec 
void swap(Vec &a, Vec &b){
	Vec temp=a;a=b;b=temp;
}

//Calculate the midpoint of two points 
Vec middleNode(Vec p1,Vec p2){
	return {(p1.x+p2.x)/2.0,(p1.y+p2.y)/2.0};
} 

//Minimum of two numbers 
double min(double a,double b){
	if(a<b) return a;
	else return b;
}
 
//Maximum of two numbers 
double max(double a,double b){
	if(a<b) return b;
	else return a;
}

void decprec(Vec &p)
{
    p.x=(int)(p.x*100+0.5)/100.0;
    p.y=(int)(p.y*100+0.5)/100.0;
}
