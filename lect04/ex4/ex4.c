#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../libfdr/jrb.h"
#include "../../libfdr/fields.h"

int menu(void);
void addTree(IS is, JRB *tree);

int main(int argc, char **argv){

    int selec;
    IS is;
    JRB tree, tmp;

    is = new_inputstruct(argv[1]);

    if(argc != 2){
        printf("Thieu file.txt\n");
        exit(0);
    }

    tree = make_jrb();
    addTree(is, &tree);

    do{

        selec = menu();
        switch(selec){
            case 1:
                // while(get_line(is) >= 0){
                //     printf("%s\n", is->fields[1]);
                //    (void) jrb_insert_str(tree, strdup(is->fields[0]), new_jval_s(is->fields[1]));
                // }
                break;
            case 2:
                
                break;

            case 3:
                break;
            case 4:
                jrb_traverse(tmp, tree){
                    printf("%-30s%20s\n", jval_s(tmp->key), jval_s(tmp->val));
                }
                break;
            case 5:
                jrb_free_tree(tree);
                break;
        }

    }while(selec != 5);


}

int menu(){

    int selec;
    puts("1. Them contact");
    puts("2. Tim kiem so dien thoai khi cho ten contact");
    puts("3. Xoa contact");
    puts("4. In danh sach contact");
    puts("5. Exit");
    printf("Your choice: ");
    scanf("%d", &selec);
    return selec;

}
void addTree(IS is, JRB *tree){
    char *name, *phone;
    while(get_line(is) >= 0){
        // (void) jrb_insert_str(*tree, strdup(is->fields[0]), new_jval_s(is->fields[1]) );
        name = malloc(sizeof(char)*30);
        phone = malloc(sizeof(char) * 20);
        strcpy(phone, is->fields[is->NF - 1]);
        strcpy(name, is->fields[0]);
        for(int i = 1; i < is->NF - 1; i++){
            strcat(name, " ");
            strcat(name, is->fields[i]);
        }
        jrb_insert_str(*tree, name, new_jval_s(strdup(phone)));
    }
}