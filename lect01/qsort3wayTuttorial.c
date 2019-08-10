#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void swap(void *v1, void *v2, int size){

	char temp[size];
	memcpy(temp, v1, size);
	memcpy(v1, v2, size);
	memcpy(v2, temp, size);

}


void qsort3way(void *buf, int L, int R, int size, int (*compare)(void const *, void const *)){

	if(L > R) return;
	void *pivot = (char *)(buf + size * L);
	int i = L, j = R + 1;
	int p = L + 1, q = R;
	void *bufi, *bufj, *bufp, *bufq;
	while(1){
		while( compare((char *)buf + (++i) * size, pivot) < 0)
			if(i == R) break;
		while(compare((char *)buf + (--j) * size, pivot) > 0);
		if(i >= j) break;

		bufi = (char *)buf + i * size;
		bufj = (char *)buf + j * size;

		swap(bufi, bufj, size);

		if(compare(pivot, bufi) == 0){
			bufp = (void *)buf + p * size;
			swap(bufp, bufi, size);
			p++;
		}
		if(compare(pivot, bufj) == 0){
			bufq = (void *)buf + q * size;
			swap(bufj, bufq, size);
			q--;
		}
	}

	void *bufk;
	for(int k = L; k< p; k++, j--){
		bufk = (void *)buf + k * size;
		bufj = (void *)buf + j * size;
		swap(bufk, bufj, size);
	}

	for(int k = q+1; k <= R; k++, i++){
		bufk = (void *)buf + k * size;
		bufi = (void *)buf + i * size;
		swap(bufk, bufi, size);
	}
	qsort3way(buf, L, j, size, compare);
	qsort3way(buf, i, R, size, compare);

}

int intCompare(void const *x, void const *y){

	int m, n;
	m = *((int *)x);
	n = *((int *)y);
	if(m == n) return 0;
	else if(m > n) return 1;
	return -1;

}

int main(){

	int a[10] = {4, 3, 9, 15, 3, 2, 100, 34, -10, 5};
	int n = 10;
	qsort3way(a, 0, n-1, sizeof(int), intCompare);
	for(int i = 0; i < n; i++){
		printf("%d ", a[i]);
	}
	puts("");

}







