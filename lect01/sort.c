#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// Insertion sort algorithm
void insertionSort(int a[], int n){
	for(int i = 1; i< n; i++){
		int tmp = a[i];
		int j = i;
		while(j > 0 && a[j-1] > tmp){
			a[j] = a[j-1];
			j--;
		}
		a[j] = tmp;
	}
}

// Doi gia tri hai bien
void swap(int *a, int *b){
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

// Selection sort algorithm
void selectionSort(int a[], int n){
	for(int i =0; i<n-1; i++){
		int min = i;
		for(int j = i+1; j< n; j++){
			if(a[j] < a[min]) min = j;
		}
		swap(&a[i], &a[min]);
	}
}

// Bubble sort algorithm
void bubbleSort(int a[], int n){
	for(int i =0; i<n-1; i++){
		for(int j = n-1; j > i; j--){
			if(a[j] < a[j-1]){
				swap(&a[j], &a[j-1]);
			}
		}
	}
}

// Merge sort algorithm
// merge subArray
void merge(int a[], int L, int M, int R){
	int l = L;
	int r = M+1;
	// int i = 0;
	int TA[100000];
	for(int i = L; i<= R; i++){
		if(l > M){
			TA[i] = a[r];
			r++;
		}else{
			if(r > R){
				TA[i] = a[l];
				l++;
			}else{
				if(a[l] < a[r]){
					TA[i] = a[l];
					l++;
				}else{
					TA[i] = a[r];
					r++;
				}
			}
		}
	}
	for(int i = L ; i<= R; i++){
		a[i] = TA[i];
	}
}

// Recursive array
void mergeSort(int a[], int L, int R){
	if(L < R){
		int M = (L+R)/2;
		mergeSort(a, L, M);
		mergeSort(a, M+1, R);
		merge(a, L, M, R);
	}
}

// Quick sort algorithm, 2 way
int partition(int a[], int L, int R, int indexPivot){
	int pivot = a[indexPivot];
	swap(&a[indexPivot], &a[R]);
	int storeIndex = L;
	for(int i = L; i< R; i++){
		if(a[i] <= pivot){
			swap(&a[storeIndex], &a[i]);
			storeIndex++;
		}
	}
	swap(&a[storeIndex], &a[R]);
	return storeIndex;
}
	
void quickSort(int a[], int L, int R){
	if(L < R){
		int index = (L+R)/2; 
		index = partition(a, L, R, index);
		if(L < index){
			quickSort(a, L, index-1);
		}else{
			if(R > index){
				quickSort(a, index+1, R);
			}
		}
	}
}

// Quick sort algorithm, 3 way
void quickSort3Way(int a[], int L, int R){
	int pivot = a[L];
	int i = L+1, j = R;
	int p = L+1, q = R;
	while(L < R){
		while(a[i] < pivot) i++;
		while(a[j] > pivot) j--;
		if(i >= j) break;
		else{
			swap(&a[i], &a[j]);
			if(a[i] == pivot){
				swap(&a[p], &a[i]);
				p++;
			}
			if(a[j] == pivot){
				swap(&a[j], &a[q]);
				q--;
			}
		}
	}
	for(int k = L; k< p; k++, j--){
		swap(&a[k], &a[j]);
	}
	for(int k = q+1; k <= R; k++, i++){
		swap(&a[k], &a[i]);
	}
	if(L < j)
		quickSort3Way(a, L, j);
	if(R > i)
		quickSort3Way(a, i, R);
}

void quickSort3Way_left(int a[], int L, int R){
	if(L >= R) return;
	int pivot = a[L];
	int i = L, j = R+1;
	int p = L+1, q = R;
	while(1){
		while(a[++i] < pivot)
			if(i == R) break;
		while(pivot < a[--j]);
		if(i >= j) break;
		swap(&a[i], &a[j]);
		if(a[i] == pivot){
			swap(&a[p], &a[i]);
			p++;
		}
		if(a[j] == pivot){
			swap(&a[j], &a[q--]);
		}
	}
	for(int k = L; k< p; k++, j--){
		swap(&a[k], &a[j]);
	}
	for(int k = q+1; k <= R; k++, i++){
		swap(&a[k], &a[i]);
	}
	quickSort3Way_left(a, L, j);
	quickSort3Way_left(a, i, R);
}

int checkAscending(int a[]){
	for(int i =0; i < 1000000; i++){
		if(a[i] > a[i+1]) return 0;
	}
	return 1;
}



int main(){
	// int a[] = {13, 17, 28, 28, 42, 14, 23, 15};
	// // // selectionSort(a, 8);
	// // // bubbleSort(a, 8);
	// // // mergeSort(a, 0, 7);
	// quickSort(a, 0,  7);
	// // quickSort3Way(a, 0, 7);
	// // quickSort3Way_left(a, 0, 7);
	// for(int i =0; i<8; i++){
	// 	printf("%d ", a[i]);
	// }

	// FILE *fin;
	// fin = fopen("../file/1000000.txt", "w+");
	// srand(time(NULL));
	// for(int i = 0; i<1000000; i++){
	// 	fprintf(fin, "%d ", rand()%10 + 1);
	// }
	// rewind(fin);
	int a1[1000000], a2[1000000];
	int i =0;
	while(i < 1000000){
		a1[i] = rand()%100 + 1;
		i++;
	}
	i = 0;
	while(i < 1000000){
		a2[i] = a1[i];
		i++;
	}
	// for(int i =0; i<1000000; i++){
	// 	printf("%d\n", a1[i]);
	// }
	clock_t begin1, end1, begin2, end2;
	begin1 = clock();
	// quickSort3Way_left(a1, 0, 1000000-1);
	mergeSort(a1, 0, 100000-1);
	end1 = clock();
	printf("Time run quick sort 3 way partitioning: %lf secs\n", (double)(end1-begin1)/CLOCKS_PER_SEC);
	// for(int i =0; i<1000000; i++){
	// 	printf("%d\n", a1[i]);
	// }
	if(checkAscending(a1) == 0) printf("Sort error\n");
	else printf("Done\n");

	// begin2 = clock();
	// quickSort(a2, 0, 1000000-1);
	// end2 = clock();
	// printf("Time run quick sort 2 way partitioning: %lf secs\n", (double)(end2-begin2)/CLOCKS_PER_SEC);



}
















