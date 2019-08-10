#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define n 10
#define arrLen 10000000

typedef union{

	int i;
	long l;
	float f;
	double d;
	void *v;
	char *s;
	char c;
	unsigned char uc;
	short sh;
	unsigned short ush;
	unsigned int ui;
	int iarray[2];
	float farray[2];
	char carray[8];
	unsigned char ucarray[8];

}jval;

int jvalI(jval j){
	return j.i;
}

float jvalF(jval j){
	return j.f;
}

jval newJvalI(int i){
	jval j;
	j.i = i;
	return j;
}

jval newJvalF(float f){
	jval j;
	j.f = f;
	return j;
}

void jvalSwap(jval *a, int j, int k, int size){

	char *buf = (char *)a;
	char temp;
	for(int i = 0; i < size; i++){
		temp = buf[size * j + i];
		buf[size * j + i] = buf[size * k + i];
		buf[size * k + i] = temp;
	}

}

void jvalQsort3way(jval *a, int num, int size, int (*compare)(const jval *, const jval *)){

	if(num <= 1) return;
	int R = num - 1;
	int i = 0, j = R + 1;
	int p = 1, q = R;
	while(1){
		while(compare(&a[++i], &a[0]) < 0)
			if(i == R) break;
		while(compare(&a[--j], &a[0]) > 0);
		if(i >= j) break;

		jvalSwap(a, i, j, size);
		if(compare(&a[0], &a[i]) == 0){
			jvalSwap(a, p, i, size);
			p++;
		}
		if(compare(&a[0], &a[j]) == 0){
			jvalSwap(a, q, j, size);
			q--;
		}

	}

	for(int k = 0; k < p; k++, j--) jvalSwap(a, k, j, size);
	for(int k = q + 1; k <= R; k++, i++) jvalSwap(a, k, i, size);

	jvalQsort3way(a, j+1, size, compare);
	jvalQsort3way(&a[i], num - i, size, compare);

}

jval *newJvalArrayInt(int n, int max){
	// Tao 1 mang jval co n phan tu
	// random tu 0 -> max

	srand(time(NULL));
	jval *array = (jval *)malloc(sizeof(jval) * n);
	for(int i = 0; i < n; i++){
		array[i] = newJvalI(rand()%(max + 1));
	}
	return array;

}

int checkArrayAscending(jval *array, int size){

	for(int i = 0; i < size - 1; i++){
		if(jvalI(array[i]) > jvalI(array[i+1])) return -1;
	}
	return 0;

}


int main(){

	// jval a, b;
	// a = newJvalI(5);
	// b = newJvalF(3.14);
	// printf("%d\n", jvalI(a));
	// printf("%g\n", jvalF(b));

	jval *array = newJvalArrayInt(arrLen, n);




}







