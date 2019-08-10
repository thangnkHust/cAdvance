#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define initialSize 10
#define incrementalSize 5

typedef struct{
	char phone[12];
	char name[30];
}entry;

typedef struct{
	entry *entries;
	int size;	//tong so contact co trong phonebook
	int sizeMax;	//so contact toi da ma phonebook co the luu
}phoneBook;

phoneBook creatPhoneBook(int sizeMax){

	phoneBook newPB;
	entry *pList = (entry *)malloc(sizeMax * sizeof(entry));
	newPB.entries = pList;
	newPB.size = 0;
	newPB.sizeMax = sizeMax;
	return newPB;

}

void dropPhoneBook(phoneBook *book){

	free(book->entries);
	// free(book);

}

void addNewPhone(entry *new, phoneBook *book){

	if(book->size >= book->sizeMax){	//phone book max --> realloc
		book->entries = (entry *)realloc(book->entries, (book->sizeMax + incrementalSize) * sizeof(entry));
		if(!book->entries){
			printf("Cap phat loi\n");
			return;
		}
		book->sizeMax += incrementalSize;
	}
	
	for(int i = 0; i < book->size; i++){
		if(strcmp(new->name, book->entries[i].name) == 0){
			strcpy(book[i].entries[i].phone, new->phone);
			return;
		}
	}
	strcpy(book->entries[book->size].name, new->name);
	strcpy(book->entries[book->size].phone, new->phone);
	book->size++;

}

char *getPB(char name[30], phoneBook *book){

	for(int i = 0; i < book->size; i++){
		if(strcmp(book->entries[i].name, name) == 0)
			return book->entries[i].phone;
	}
	return NULL;

}

void printPB(phoneBook book){

	for(int i = 0; i < book.size; i++){
		printf("%-30s%-15s\n", book.entries[i].name, book.entries[i].phone);
	}

}

char alpha[52] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefjhijklmnopqrstuvwxyz";
char number[10] = "0123456789";

char randomChar(){
	srand(time(NULL));
	int num = rand()%52;
	return alpha[num];
}

void randomName(char name[30], int size){

	for(int i = 0; i < size; i++){
		name[i] = randomChar()
	}
	name[size] = "\0";

}

char randomNum(){
	for(int i = 0)
}

vodi randomPhone(char phone[12], int size){

}


int main(){

	// int sizeMax;
	// printf("Press max element of phone book: ");
	// scanf("%d", &sizeMax);
	

	int count = 0;
	phoneBook newBook = creatPhoneBook(initialSize);
	entry new;

	printf("Nhap so luong can them: ");
	scanf("%d", &count);
	getchar();

	for(int i = 0; i < count; i++){
		printf("Nhap phan tu thu %d\n", i+1);
		printf("\tNhap name: ");
		gets(new.name);
		printf("\tNhap phone: ");
		gets(new.phone);
		addNewPhone(&new, &newBook);
	}
	printPB(newBook);
	printf("Nhap name: ");
	gets(new.name);

	char *phonet;
	phonet = getPB(new.name, &newBook);
	if(phonet == NULL){
		printf("Khong tim thay\n");
	}else{
		printf("phone: %s\n", phonet);
	}

	dropPhoneBook(&newBook);

}










