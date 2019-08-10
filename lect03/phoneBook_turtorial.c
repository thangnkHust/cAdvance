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

elementtype *getElement(void *key, symbolTable *table){		//tim kiem 1 element trong symbol table

	for(int i = 0; i < table->size; i++){
		if(table->compare(table->element[i].key, key) == 0) return &(table->element[i]);
	}

	return NULL;

}

void addOneElement(elementtype *e, symbolTable *table){

	// gia han them bo nho dong, dung realloc 
	if(table->size >= table->sizeMax){
		table->element = (elementtype *)realloc(table->element, (table->sizeMax + INC_SIZE) * sizeof(elementtype));
		if(!table->element){
			printf("Cap phat bo nho loi!!!\n");
			return;
		}
		table->sizeMax += INC_SIZE;
	}
	elementtype *tmp;
	tmp = getElement(e->key, table);
	if(tmp != NULL){
		tmp->value = e->value;
	}else{
		table->element[table->size] = table->makeNode(e->key, e->value);
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

int main(){

	symbolTable tablePB;
	int count = 0;
	elementtype e;
	char name[30], phone[12];

	tablePB = creatSymbolTable(makePB, comparePB);

	printf("Nhap so luong can add: ");
	scanf("%d", &count);
	getchar();

	for(int i = 0; i < count; i++){
		printf("So %d: \n", i + 1);
		printf("\tName: ");
		gets(name);
		printf("\tPhone: ");
		gets(phone);
		e = makePB(name, phone);
		addOneElement(&e, &tablePB);
	}

	printPB(&tablePB);

	printf("Nhap ten contact search: ");
	gets(name);

	elementtype *find = getElement(name, &tablePB);
	if(find == NULL){
		printf("Khong tim thay contact\n");
	}else{
		printf("So dien thoai cua \"%s\" la: %s\n", find->key, find->value);
	}

}























