#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct tag_POINT {
	float x;
	float y;
} Point;

typedef struct tagNode {
	int a;
	struct tagNode *next;
} Node, *List;

#define h (float)0.2

void range_kutta(Point *point, int n, Point *edge, int m, Point *edge2, int m2);

float distance(Point a, Point b);

Point force(List *list, Point *point, Point *velocity, int n);

float ideal(Point point);

void listCreate(List *list, Point *point, int n);

void listAdd(List *list, int data);

void listDelete(List *list);

void listReCreate(List *list, Point *point, int n);

int filt_one(int n, Point *a, Point b);

int filt_many_5(Point point, Point *test1, int m1, Point *test2, int m2);

void range_kutta(Point *point, int n, Point *edge, int m, Point *edge2, int m2)
{
	int i, j;
	

	List *list;
	list = (List*)malloc(n * sizeof(List));
	listCreate(list, point,n);


	Point *velocity;
	velocity = (Point*)malloc(n * sizeof(Point));
	for (i = 0; i < n; ++i) {
		velocity[i].x = 0.0;
		velocity[i].y = 0.0;
	}


	Point *k1, *k2, *k3, *k4;
	Point *l1, *l2, *l3, *l4;
	Point *point_1, *point_2, *point_3;
	Point *velocity_1, *velocity_2, *velocity_3;
	Point *point_swap;
	Point *velocity_swap;

	k1 = (Point*)malloc(n * sizeof(Point));
	k2 = (Point*)malloc(n * sizeof(Point));
	k3 = (Point*)malloc(n * sizeof(Point));
	k4 = (Point*)malloc(n * sizeof(Point));

	l1 = (Point*)malloc(n * sizeof(Point));
	l2 = (Point*)malloc(n * sizeof(Point));
	l3 = (Point*)malloc(n * sizeof(Point));
	l4 = (Point*)malloc(n * sizeof(Point));

	point_1 = (Point*)malloc(n * sizeof(Point));
	point_2 = (Point*)malloc(n * sizeof(Point));
	point_3 = (Point*)malloc(n * sizeof(Point));

	velocity_1 = (Point*)malloc(n * sizeof(Point));
	velocity_2 = (Point*)malloc(n * sizeof(Point));
	velocity_3 = (Point*)malloc(n * sizeof(Point));

	point_swap = (Point*)malloc(n * sizeof(Point));
	velocity_swap = (Point*)malloc(n * sizeof(Point));
	

	for (j = 0; j < 500; ++j) {
		for (i = 0; i < n; ++i) {
			k1[i] = velocity[i];
			l1[i] = force(list, point, velocity, i);
			point_1[i].x = point[i].x + h * k1[i].x / (float) 2.0;
			point_1[i].y = point[i].y + h * k1[i].y / (float) 2.0;
			velocity_1[i].x = velocity[i].x + h * l1[i].x / (float) 2.0;
			velocity_1[i].y = velocity[i].y + h * l1[i].y / (float) 2.0;
		}
		for (i = 0; i < n; ++i) {
			k2[i].x = velocity[i].x + h * l1[i].x / (float) 2.0;
			k2[i].y = velocity[i].y + h * l1[i].y / (float) 2.0;
			l2[i] = force(list, point_1, velocity_1, i);
			point_2[i].x = point[i].x + h * k2[i].x / (float) 2.0;
			point_2[i].y = point[i].y + h * k2[i].y / (float) 2.0;
			velocity_2[i].x = velocity[i].x + h * l2[i].x / (float) 2.0;
			velocity_2[i].y = velocity[i].y + h * l2[i].y / (float) 2.0;
		}
		for (i = 0; i < n; ++i) {
			k3[i].x = velocity[i].x + h * l2[i].x / (float) 2.0;
			k3[i].y = velocity[i].y + h * l2[i].y / (float) 2.0;
			l3[i] = force(list, point_2, velocity_2, i);
			point_3[i].x = point[i].x + h * k3[i].x;
			point_3[i].y = point[i].y + h * k3[i].y;
			velocity_3[i].x = velocity[i].x + h * l3[i].x;
			velocity_3[i].y = velocity[i].y + h * l3[i].y;
		}
		for (i = 0; i < n; ++i) {
			k4[i].x = velocity[i].x + h * l2[i].x / (float) 2.0;
			k4[i].y = velocity[i].y + h * l2[i].y / (float) 2.0;
			l4[i] = force(list, point_3, velocity_3, i);
		}
		for (i = 0; i < n; ++i) {
			point_swap[i].x =
				point[i].x +
				h * (k1[i].x + (float) 2.0 * k2[i].x + (float) 2.0 * k3[i].x + k4[i].x) / (float) 6.0;
			point_swap[i].y =
				point[i].y +
				h * (k1[i].y + (float) 2.0 * k2[i].y + (float) 2.0 * k3[i].y + k4[i].y) / (float) 6.0;
			velocity_swap[i].x =
				velocity[i].x +
				h * (l1[i].x + (float) 2.0 * l2[i].x + (float) 2.0 * l3[i].x + l4[i].x) / (float) 6.0;
			velocity_swap[i].y =
				velocity[i].y +
				h * (l1[i].y + (float) 2.0 * l2[i].y + (float) 2.0 * l3[i].y + l4[i].y) / (float) 6.0;
			if (!filt_many_5(point_swap[i], edge, m, edge2, m2)) {
				point_swap[i] = point[i];
			}
		}
		for (i = 0; i < n; ++i) {
			point[i] = point_swap[i];
			velocity[i] = velocity_swap[i];
		}
		listReCreate(list, point, n);
	}

	free(list);
	free(velocity);

	free(k1);free(k2);free(k3);free(k4);
	free(l1);free(l2);free(l3);free(l4);

	free(point_1);
	free(point_2);
	free(point_3);
	free(point_swap);
	
	free(velocity_1);
	free(velocity_2);
	free(velocity_3);
	free(velocity_swap);
}

float distance(Point a, Point b) {
	float x = (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
	float y = sqrtf(x);
	return y;
}

Point force(List *list, Point *point, Point *velocity, int n) {
	Point f;
	f.x = 0.0;
	f.y = 0.0;
	List p = list[n];
	while (p != NULL) {
		float x = point[p->a].x - point[n].x;
		float y = point[p->a].y - point[n].y;
		float ls = sqrtf(x * x + y * y);
		float li = (ideal(point[p->a]) + ideal(point[n]));
		float r = ls / li;
		float fr;
		if (r < 1.5)
			fr = (float) 1.25 * r * r * r - (float) 2.375 * r * r + (float) 1.125;
		else fr = (float) 0.0;
		float fx = fr * x / ls;
		float fy = fr * y / ls;
		f.x += fx;
		f.y += fy;
		p = p->next;
	}
	f.x = -f.x - (float) 3.8429 * velocity[n].x;
	f.y = -f.y - (float) 3.8429 * velocity[n].y;
	return f;
}

float ideal(Point point) {
	float a = sqrtf(point.x * point.x + point.y * point.y) / (float) 16.0 + (float) 0.02;
	return a;
}

void listCreate(List *list, Point *point, int n) {
	int i, j;
	for (i = 0; i < n; ++i) {
		list[i] = NULL;
		for (j = 0; j < n; ++j) {
			float x = point[i].x - point[j].x;
			float y = point[i].y - point[j].y;
			float ls = sqrtf(x * x + y * y);
			float li = (ideal(point[i]) + ideal(point[j]));
			float r = li / ls;
			if (distance(point[i], point[j]) < 1.5 * r && i != j) {
				listAdd(&list[i], j);
			}
		}
	}
}

void listAdd(List *list, int data) {
	List node = (List)malloc(sizeof(Node));   
	node->a = data;                           
	List temp = *list;                        
	*list = node;
	node->next = temp;
}
void listDelete(List *list) {
	List p = *list;
	List temp;
	while (p != NULL) {
		temp = p->next;
		free(p);
		p = temp;
	}
	*list = NULL;
}
void listReCreate(List *list, Point *point,int n) {
	int i;
	for (i = 0; i < n; ++i) {
		listDelete(&list[i]);
	}
	listCreate(list, point,n);
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
int filt_many_5(Point point, Point *test1, int m1, Point *test2, int m2) {
	int c = (filt_one(m1, test1, point) != filt_one(m2, test2, point));
	return c;
}