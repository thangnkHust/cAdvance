#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jrb.h"

int menu(void);

int main(){

    int selec;
    JRB tree, bn;
    tree = make_jrb();
    long number;
    char name[80];

    do{

        selec = menu();
        switch(selec){
            case 1:
                printf("Nhap name: ");
                getchar();
                gets(name);
                printf("Nhap so dien thoai: ");
                scanf("%d", &number);
                if(jrb_find_str(tree, name) == NULL){
                    jrb_insert_str(tree,strdup(name), new_jval_l(number));
                }
                break;
            case 2:
                printf("Nhap ten contact: ");
                getchar();
                gets(name);
                bn = jrb_find_str(tree, name);
                if(bn != NULL){
                    printf("Sdt cua \"%s\" la: %d\n", jval_s(bn->key), jval_l(bn->val));
                }else{
                    printf("Khong co contact\n");
                }
                break;
            case 3:
                printf("Nhap ten can xoa: ");
                getchar();
                gets(name);
                bn = jrb_find_str(tree, name);
                if(bn != NULL){
                    jrb_delete_node(bn);
                    printf("Xoa contact thanh cong\n");
                }else{
                    printf("Khong ton tai contact\n");
                }
                break;
            case 4:
                printf("Danh sach contact la: \n");
                jrb_traverse(bn, tree){
                    printf("%-10s%-10d\n", jval_s(bn->key), jval_l(bn->val));
                }
                break;
            case 5:
                jrb_free_tree(tree);
                break;
            default:
                printf("Sai!!!");
                break;
        }

    }while(selec != 5);

}

int menu(){
    int selec;
    puts("1. Them contact");
    puts("2. Tim kiem sdt");
    puts("3. Xoa contact");
    puts("4. Print List");
    puts("5. Thoat");
    printf("Your choice: ");
    scanf("%d", &selec);
    return selec;
}