

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
	a.x=(float)(rand()%(200*(int)n))/(float)100 - n;
	a.y=(float)(rand()%(200*(int)n))/(float)100 - n;
	return a;
}

void many_rand_point(Point *point, int n, float r){
	int i;
	srand((int)time(0));
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