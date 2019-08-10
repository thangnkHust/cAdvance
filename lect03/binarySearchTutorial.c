#include <stdio.h>
#include <stdlib.h>


int binarySearch(void *buf, int size, int L, int R, void *key, int (*compare) (void const *, void const *)){
	// buf is array
	// size = sizeof( kieu du lieu )
	// key = gia tri can tim
	// int (*compare) (void const *, void const *) dung so sanh 2 gia tri ( adrress )

	if(L <= R){
		int M = (L + R) / 2;
		int temp = compare(key, (char *)buf + (size * M));
		if(temp == 0) return M;
		else if(temp > 0){
			return binarySearch(buf, size, M + 1, R, key, compare);
		}else{
			return binarySearch(buf, size, L, M - 1, key, compare);
		}
	}
	return -1;

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

	int a[10] = {-4, 6, 3, -10, 15, 6, 5, 10 , 15, 3};
	int i, n = 10, key = 3;
	qsort(a, n, sizeof(int), intCompare);
	for(int i = 0; i < n; i++){
		printf("%d\n", a[i]);
	}
	int res = binarySearch(a, sizeof(int), 0, n-1, &key, intCompare);
	if(res != -1) printf("Vi tri %d\n", res + 1);
	else printf("Khong tim thay result\n");

}









