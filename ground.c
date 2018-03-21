

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265


typedef struct tag_POINT {
    float x;
    float y;
} Point;


void circleEdgeCreate(Point *edge, int n, float r) {
    float step;
    float theta = 0.0;
    int i;
    //step应当取小;
    step = (float) (2.0 * PI / (double) n);
    for (i = 0; i < n; i++) {
        edge[i].x = r * cosf(theta);
        edge[i].y = r * sinf(theta);
        theta += step;
    }
}


int filt_one(int n, Point *a, Point b) {
    int i, j, c = 0;
    for (i = 0, j = n - 1; i < n; j = i++) {
        if (((a[i].y > b.y) != (a[j].y > b.y)) &&
            (b.x < (a[j].x - a[i].x) * (b.y - a[i].y) / (a[j].y - a[i].y) + a[i].x)) 
        {
            c = !c;
        }
    }
    return c;
}



Point rand_point(float n){
	// srand((int)time(0));
	Point a;
	a.x=(float)(rand()%(20000*(int)n))/(float)10000 - n;
	a.y=(float)(rand()%(20000*(int)n))/(float)10000 - n;
	return a;
}

void many_rand_point(Point *point, int n, float r){
	int i;
	for (i=0;i<n;i++){
		point[i]=rand_point(r);
	}
}

int filt_many_1(Point *in,int n,Point *test, int m){
	int i;
	int c=0;
	for (i = 0; i < n; ++i)
	{
		c += filt_one(m, test, in[i]);
	}
	return c;
}


void filt_many_2(Point *in,int n,Point *test, int m, Point *out){
	int i;
	int c=0;
	for(i = 0; i < n; ++i)
	{
		if (filt_one(m, test, in[i])){
			out[c] = in[i];
			c += 1;
		}
	}
}


int filt_many_3(Point *in,int n,Point *test1, int m1,Point *test2, int m2){
	int i;
	int c=0;
	for (i = 0; i < n; ++i)
	{
		c += (filt_one(m1, test1, in[i])  !=  filt_one(m2, test2, in[i]));
	}
	return c;
}


void filt_many_4(Point *in,int n,Point *test1, int m1,Point *test2, int m2, Point *out){
	int i;
	int c=0;
	for(i = 0; i < n; ++i)
	{
		if (filt_one(m1, test1, in[i])  !=  filt_one(m2, test2, in[i])){
			out[c] = in[i];
			c += 1;
		}
	}
}


float ideal(Point point) {
    float a = sqrtf(point.x * point.x + point.y * point.y) / (float) 16.0 + (float) 0.02;
    return a;
}


Point force(Point *point, Point *velocity, int m, int n) {
    Point f;
    f.x = 0.0;
    f.y = 0.0;
    List p = list[n];
    for (int i = 0; i < m; ++i)
    {
        float x = point[p->a].x - point[n].x;
        float y = point[p->a].y - point[n].y;
        float ls = sqrtf(x * x + y * y);
        float li = (ideal(point[p->a]) + ideal(point[n]));
        float r = ls / li;
        float fr;
        if (r < 1.5)
            fr = (float) 1.25 * r * r * r - (float) 2.375 * r * r + (float) 1.125;
        else fr=(float)0.0;
        float fx = fr * x / ls;
        float fy = fr * y / ls;
        f.x += fx;
        f.y += fy;
    }
    f.x = -f.x - (float) 3.8429 * velocity[n].x;
    f.y = -f.y - (float) 3.8429 * velocity[n].y;
    return f;
}

int filt_many_5(Point point,Point *test1, int m1,Point *test2, int m2){
	int c = (filt_one(m1, test1, point)  !=  filt_one(m2, test2, point));
	return c;
}


int main(){

    Point r_point[1000];
    Point e_point_1[100];
    Point e_point_2[50];


    circleEdgeCreate(e_point_1, 100, 8);
    circleEdgeCreate(e_point_2, 50, 6);


    many_rand_point(r_point,1000,10);
    
 	int c = filt_many_3(r_point,1000,e_point_1, 100,e_point_2, 50);
 	printf("%d\n", c);
 	
}