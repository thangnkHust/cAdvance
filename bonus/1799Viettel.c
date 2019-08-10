#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define INIT_SIZE 100
#define INC_SIZE 50

typedef struct{
	void *key;
	void *tmp;
	void *tmp1;
	void *tmp2;
	void *tmp3;
	void *tmp4;
	void *value;
}elementtype;

typedef struct{
	elementtype *element;
	int size, sizeMax;
	elementtype (*makeNode)(void *, void *, void *);
	int (*compare)(void *, void *);
}symbolTable;

symbolTable creatSymbolTable(elementtype (*makeNode)(void *, void *, void *), int (*compare)(void *, void *)){
	symbolTable table;
	table.element = (elementtype *)malloc(INIT_SIZE * sizeof(elementtype));
	table.size = 0;
	table.sizeMax = INIT_SIZE;
	table.compare = compare;
	table.makeNode = makeNode;
	return table;
}

void readFile(FILE *fin, symbolTable *table){
	void *str;
	int count = 0;
	int k = 0;
	int j = 0;

	while(fgets((char*)str, 100, fin) != NULL){
		count++;
	}
	rewind(fin);
	for(int i = 1; i <= count; i++){
		fgets(str, 100, fin);
		if(i % 7 == 1){
			// memcpy(table->element[k].tmp, str, sizeof(char));
			table->element[k].key = strdup(str);
			j = atoi(str);
			sprintf(str, "%d", j);
			memcpy(table->element[k].key, str, sizeof(char));
		}else{
			if(i % 7 == 2){
				memcpy(table->element[k].tmp1, str, sizeof(char));
				// table->element[k].key = strdup(str);
			}
			if(i % 7 == 3){
				memcpy(table->element[k].tmp2, str, sizeof(char));
			}
			if(i % 7 == 4){
				memcpy(table->element[k].tmp3, str, sizeof(char));
			}
			if(i % 7 == 5){
				memcpy(table->element[k].tmp4, str, sizeof(char));
			}
			if(i % 7 == 6){
				memcpy(table->element[k].value, str, sizeof(char));
			}
			if(i % 7 == 0){
				k++;
				table->size++;
			}
		}
	}
}

int main(){

	FILE *fin;
	if((fin = fopen("../file/data1.txt", "r")) == NULL){
		printf("Can not open file");
		return 0;
	}

	symbolTable table;
	// table = creatSymbolTable(makeNode, compare);
	readFile(fin, &table);


}

















