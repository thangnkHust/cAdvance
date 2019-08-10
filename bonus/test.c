#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../libfdr/jrb.h"
#include "../libfdr/fields.h"

typedef struct diem{
    double toan, ly, hoa;
}diem;

// int compare(Jval j1, Jval j2){
//     diem *d1, *d2;
//     d1 = (diem *) j1.v;
//     d2 = (diem *) j2.v;
//     return strcmp(d1->name, d2->name);
// }

int main(int argc, char **argv){

    // if(argc != 2){
    //     printf("thieu file.txt\n");
    //     return 0;
    // }

    IS is;
    is = new_inputstruct(argv[1]);

    diem *score;
    score = malloc(sizeof(diem));
    char name[20];
    JRB tree, tmp;

    tree = make_jrb();

    printf("Nhap ten: ");
    gets(name);

    score->toan = 8;
    score->ly = 9;
    score->hoa = 9.5;

    jrb_insert_str(tree, name, new_jval_v((void *)score));
    // jrb_insert_gen(tree, new_jval_v((void *) score), new_jval_v(NULL), compare);

    jrb_traverse(tmp, tree){
        score = (diem *) tmp->val.v;
        // printf("%s-%g-%g-%g\n", score->name, score->toan, score->ly, score->hoa);
        printf("%s-%g", jval_s(tmp->key), score->toan);
    }


}