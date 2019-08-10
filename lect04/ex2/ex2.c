#include <stdio.h>
#include <stdlib.h>
#include "jrb.h"

int menu(void);

int main(){

    JRB tree, bn;
    int n, selec;
    tree = make_jrb();
    
    do{
        // system("cls");

        selec = menu();

        switch(selec){
            case 1:
                printf("Nhap gia tri: ");
                scanf("%d", &n);
                (void) jrb_insert_int(tree, n, new_jval_i(n));
                break;
            case 2: 
                jrb_traverse(bn, tree){
                    printf("%d\n", jval_i(bn->key));
                }
                break;
            case 3:
                jrb_free_tree(tree);
                break;
        }
    }while(selec != 3);

}

int menu(){
    int selec;
    printf("1. Insert\n2. Display\n3. Destroy\n");
    printf("Your choice: ");
    scanf("%d", &selec);
    return selec;
}