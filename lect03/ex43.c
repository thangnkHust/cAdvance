#include <stdio.h>
#include <stdlib.h>

int min(int a, int b);


int main(){

	int (*pf) (int , int );
	pf = min;

	int temp = (*pf)(5, 4);
	printf("%d\n", temp);

}

int min(int a, int b){
	if( a > b) return b;
	return a;
}











