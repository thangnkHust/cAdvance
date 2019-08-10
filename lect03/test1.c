#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define INIT_SIZE 100
#define INC_SIZE 50

typedef struct{
	int key;
	char tmp[10000];
	char value[5];
}elementtype;

typedef struct{
	elementtype element[200];
	int size, sizeMax;
}symbolTable;

// symbolTable creatSymbolTable(elementtype (*makeNode)(void *, void *, void *), int (*compare)(void *, void *)){
// 	symbolTable table;
// 	table.element = (elementtype *)malloc(INIT_SIZE * sizeof(elementtype));
// 	table.size = 0;
// 	table.sizeMax = INIT_SIZE;
// 	table.compare = compare;
// 	table.makeNode = makeNode;
// 	return table;
// }
int count = 0;
void readFile(FILE *fin, symbolTable *table){
	char str[200];
	int k = 0;

	while(fgets(str, 200, fin) != NULL){
		count++;
	}
	rewind(fin);
	for(int i = 1; i <= count; i++){
		fgets(str, 200, fin);
		if(i % 7 == 1){
			// memcpy(table->element[k].tmp, str, sizeof(char));
			strcpy(table->element[k].tmp, str);
			table->element[k].key = atoi(str);
		}else{
			if(i % 7 == 0){
				k++;
				table->size++;
			}else{
				if(i % 7 == 6){
					strcpy(table->element[k].value, str);
				}else{
					strcat(table->element[k].tmp, str);
				}
			}
		}
	}
}

void printList(symbolTable *table){
	for(int k = 0; k < count/7; k++){
		printf("%d\n", table->element[k].key);
		printf("%s", table->element[k].tmp);
		printf("%s", table->element[k].value );
	}
}

int main(){

	FILE *fin;
	if((fin = fopen("../file/Data.txt", "r")) == NULL){
		printf("Can not open file");
		return 0;
	}

	symbolTable table;
	// table = creatSymbolTable(makeNode, compare);
	readFile(fin, &table);
	printList(&table);

}

















