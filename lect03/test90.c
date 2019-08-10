#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define INIT_SIZE 10
#define INC_SIZE 5

typedef struct{
	void *key;		//name of contact
	void *value;	//phone number
}elementtype;

typedef struct{
	elementtype *element;
	int size, sizeMax;
	elementtype (*makeNode)(void *, void *);	//tao ra 1 element = key + value
	int (*compare)(void *, void *);				//so sanh 2 key, dung sap xep
}symbolTable;

symbolTable creatSymbolTable(elementtype (*makeNode)(void *, void *), int (*compare)(void *, void *)){

	symbolTable table;
	table.element = (elementtype *)malloc(INIT_SIZE * sizeof(elementtype));
	table.size = 0;
	table.sizeMax = INIT_SIZE;
	table.compare = compare;
	table.makeNode = makeNode;

	return table;

}

void dropSymbolTable(symbolTable *table){	//giai phong bo nho symbol table

	for(int i = 0; i < table->size; i++){
		free(table->element[i].key);
		free(table->element[i].value);
	}
	free(table->element);

}

int binarySearch(elementtype *element, int L, int R, void *key, int *found, int (*compare)(void *, void *)){
	int i, res = 0;
	if( L <= R){
		int M = (L + R)/2;
		// res = M+1;
		if( compare(key, element[M].key) == 0){
			*found = 1;
			return M;
		}else{
			if(compare(key, element[M].key) < 0){
				return binarySearch(element, L, M-1, key, found, compare);
			}else{
				return binarySearch(element, M + 1, R, key, found, compare);
			}
		}
	}
	*found = 0;
	return L;
}

void addOneElement(elementtype *e, symbolTable *table){

	int found, pos;
	if(table->size > 0){
		pos = binarySearch(table->element, 0, table->size - 1, e->key, &found, table->compare);
		// if(pos == -1){
		// 	pos = 0;
		// 	for(int i = 0 ; i < table->size; i++){
		// 		if(table->compare(table->element[i].key, e->key) > 0){
		// 			pos = i;
		// 			break;
		// 		}
		// 		else{
		// 			pos++;
		// 		}
		// 	}
		// }
		// printf("pos = %d\n", pos);
	}else{
		pos = 0; 
		found = 0;
		// printf("pos = %d\n", pos);
	}

	if(found == 1){
		table->element[pos] = table->makeNode(e->key, e->value);
	}else{
		if(table->size >= table->sizeMax){
			table->element = (elementtype *)realloc(table->element, (table->sizeMax + INC_SIZE) * sizeof(elementtype));
			if(!table->element){
				printf("Cap phat bo nho loi!!!\n");
				return;
			}
			table->sizeMax += INC_SIZE;
		}

		if(pos < table->size){
			for(int i = table->size - 1; i >= pos; i--){
				memcpy(&(table->element[i+1]), &(table->element[i]), sizeof(elementtype));
				// table->element[i+1].key = strdup(table->element[i].key);
				// table->element[i+1].value = strdup(table->element[i].value);
				// printf("%-30s%-15s\n", table->element[i].key, table->element[i].value);
				// printf("%-30s%-15s\n", table->element[i+1].key, table->element[i+1].value);
			}
		}
		table->element[pos] = table->makeNode(e->key, e->value);
		table->size++;
	}

}

void printPB(symbolTable *table){

	printf("%-30s%-15s\n", "NAME", "PHONE");
	for(int i = 0; i < table->size; i++){
		printf("%-30s%-15s\n", table->element[i].key, table->element[i].value);
	}

}

elementtype makePB(void *name, void *phone){

	elementtype newContact;
	
	newContact.key = strdup((char *)name);		//dung strdup khong dung strcpy
	newContact.value = strdup((char *)phone);	//strdup tra ve con tro cua vung nho moi

	return newContact;

}

int comparePB(void *key1, void *key2){

	return strcmp((char *)key1, (char *)key2);

}

int menu(){
	int selec;
	puts("==============MENU==============");
	puts("1. Add phone");
	puts("2. Search phone");
	puts("3. Print list");
	puts("4. Exit");
	printf("Your choice: ");
	scanf("%d", &selec);
	return selec;
}

int main(){

	symbolTable table;
	char name[30], phone[12];
	int count = 0;
	elementtype e;
	int selec;
	int temp;
	int found;

	table = creatSymbolTable(makePB, comparePB);

	do{
		selec = menu();
		switch(selec){
			case 1:
				getchar();
				printf("Enter Name: ");
				gets(name);
				printf("Enter Phone: ");
				gets(phone);
				e = makePB(name, phone);
				addOneElement(&e, &table);
				break;
			case 2:
				getchar();
				printf("Nhap ten contact: ");
				gets(name);
				temp = binarySearch(table.element, 0, table.size - 1, name, &found, table.compare);
				if(temp == -1){
					printf("Khong thay contact!\n");
				}else{
					printf("So dien thoai cua contact \"%s\" la: %s\n", table.element[temp].key, table.element[temp].value);
				}
				break;
			case 3:
				printPB(&table);
				break;
			case 4:
				printf("Exit!!!\n");
				dropSymbolTable(&table);
				break;
			default:
				printf("Nhap sai cu phap\n");
				break;
		}
	}while(selec != 4);

}















