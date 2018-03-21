//将二进制文件转换为文本文件
#include<stdio.h>
#include<stdlib.h>

int main(){
	FILE *f;
	f=fopen("x_new.dat","r");
	float x[719];
	fread(x, sizeof(float), 719, f);
	fclose(f);
	f=fopen("x_new.txt","w");
	int i;
	for (i = 0; i < 719; ++i)
	{
		fprintf(f, "%f\n" ,x[i]);
	}
	fclose(f);


	f=fopen("y_new.dat","r");
	fread(x, sizeof(float), 719, f);
	fclose(f);
	f=fopen("y_new.txt","w");
	for (i = 0; i < 719; ++i)
	{
		fprintf(f, "%f\n" ,x[i]);
	}
	fclose(f);
}