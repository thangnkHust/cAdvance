#include <stdio.h>
#include <stdlib.h>

// so sanh de su dung trong function qsort
// m - n thi tang dan, n - m giam dan
int int_compare(void const *x, void const *y){

	int m, n;
	m = *((int *)x);
	n = *((int *)y);
	return m - n;

}

int main(){

	int a[] = {5, 10, 27, 3, 6};
	int n = 5;
	printf("Day truoc sap xep: \n");
	for(int i =0; i < n; i++){
		printf("%d ", a[i]);
	}
	printf("\n");

	// qsort sap xep theo quick sort 2 way
	qsort(a, n, sizeof(int), int_compare);

	printf("Day sau sap xep la: \n");
	for(int i =0; i < n; i++){
		printf("%d ", a[i]);
	}
	printf("\n");

}