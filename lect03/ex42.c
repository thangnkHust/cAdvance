#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 100

typedef struct{
	int age, marks;
	char name[20];
}student;

void inputStudent(student sv[], int *size);
int markCompare(void const *x, void const *y);
int ageCompare(void const *x, void const *y);
int nameCompare(void const *x, void const *y);

int main(){

	student sv[max];
	int count = 0;

	printf("Nhap so luon hoc sinh: ");
	scanf("%d", &count);
	getchar();

	inputStudent(sv, &count);
	psort(sv, count, sizeof(student), nameCompare);

	for(int i =0; i < count; i++){
		printf("%-20s%-5d%-5d\n", sv[i].name, sv[i].age, sv[i].marks);
	}


}


void inputStudent(student sv[], int *size){

	for(int i = 0; i < *size; i++){
		printf("Nhap sinh vien thu %d: \n", i+1);
		printf("\tName: ");
		gets(sv[i].name);
		printf("\tAge: ");
		scanf("%d", &sv[i].age);
		printf("\tMarks: ");
		scanf("%d", &sv[i].marks);
		getchar();
	}

}

// so sanh marks su dung cho qsort function 
int markCompare(void const *x, void const *y){

	int m, n;
	m = ((student *)x)->marks;
	n = ((student *)y)->marks;
	return m - n;

}

// so sanh age su dung cho qsort function
int ageCompare(void const *x, void const *y){

	int m, n;
	m = ((student *)x)->age;
	n = ((student *)y)->age;
	return m - n;

}

int nameCompare(void const *x, void const *y){

	char m[20], n[20];
	strcpy(m, ((student *)x)->name);
	strcpy(n, ((student *)y)->name);
	return strcmp(m, n);

}





