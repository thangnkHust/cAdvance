#define INIT_SIZE 10
#define INC_SIZE 5


// SYMBOL TABLE 
// them makeNode va compare cho truong hop cu the

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

// ham quick sort 2 way trong stdlib.h
qsort(a, n, sizeof(int), int_compare);

// han memcpy trong stdlib.h
memcpy(e1, e2, sizeof(elementtype));	// sao chep du lieu e2 -> e1














