#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../Graph/graph.h"
#include "../Dijkstra/dijkstra.h"

int menu(void);
void readFile1(Graph g, char *filename);
void readFile2(Graph g, char *filenme);
void swap1(double *a, double *b);
void swap2(int *a, int *b);
int sanPhamLq(Graph g, int id, int *w);
double duongdi(Graph g, int id1, int id2, int *output, int *getNum);

int main (){

    int selec;
    Graph g = creatGraph();
    JRB node;
    int id1, id2;
    int w[1000];
    int count = 0;
    double test = 0;

    do{
        selec = menu();
        switch(selec){
            case 1:
                readFile1(g,"products.txt");
                jrb_traverse(node, g.vertices){
                    printf("Ma san pham: %d\n", jval_i(node->key));
                    printf("Ten san pham: %s\n\n", jval_s(node->val));
                }
                break;
            case 2:
                readFile2(g, "orderhistory.txt");
                break;
            case 3:
                printf("Nhap 2 id: ");
                scanf("%d%d", &id1, &id2);
                if(!hasEdge(g, id1, id2)){
                    printf("-1\n");
                }else{
                    printf("Do lien quan giua 2 sp: %g\n", getEdgeValue(g, id1, id2));
                }

                break;
            case 4:
                printf("Nhap id: ");
                scanf("%d", &id1);
                count = sanPhamLq(g, id1, w);
                for(int i = 0; i < count; i++){
                    printf("%s\t", getVertex(g, w[i]));
                }
                printf("\n");
                break;
            case 5:
                printf("Nhap 2 sp: ");
                scanf("%d%d", &id1, &id2);
                test = duongdi(g, id1, id2, w, &count);
                if(test == INFINITIVE_VALUE){
                    printf("Hai san pham khong co lien he voi nhau\n");
                    break;
                }
                // printf("%s", getVertex(g, id2));
                // int i = w[id2];
                // while(i != id1){
                //     printf("<---- %s", getVertex(g, i));
                //     i = w[i];
                // }
                // printf("<-----%s\n", getVertex(g, i));
                for(int i = 0; i < count - 1; i++){
                    printf("%s---->", getVertex(g, w[i]));
                }
                printf("%s\n", getVertex(g, w[count-1]));
                break;
            case 6:
                printf("Thoat!!!\n");
                dropGraph(g);
                break;
            default: 
                printf("Error syntax\n");
        }
    }while(selec != 6);

}

int menu(){
    int selec;
    puts("1. In danh sach san pham");
    puts("2. In danh sach giao dich");
    puts("3. Hien thi muc do lien quan 2 sp");
    puts("4. In danh sach cac san pham lien quan");
    puts("5. Hien thi moi lien he 2 sp");
    puts("6. Thoat!!!");
    printf("Lua chon: ");
    scanf("%d", &selec);
    return selec;
}

void readFile1(Graph g, char *filename){
    IS is = new_inputstruct(filename);
    if(is == NULL){
        printf("Loi file\n");
        return;
    }

    while(get_line(is) > 0 ){
        addVertex(g, atoi(is->fields[0]), is->fields[1]);
    }
}

void readFile2(Graph g, char *filenme){
    IS is = new_inputstruct(filenme);
    int w = 0;
    int id1 = 0, id2 = 0;
    JRB node, tree;
    if(is == NULL){
        printf("Loi file\n");
        return;
    }

    while(get_line(is) > 0){
        for(int i = 0; i < is->NF; i++){
            for(int j = i+1; j < is->NF; j++){
                id1 = atoi(is->fields[i]);
                id2 = atoi(is->fields[j]);
                if(hasEdge(g, id1, id2)){
                    node = jrb_find_int(g.edges, id1);
                    tree = (JRB) jval_v(node->val);
                    node = jrb_find_int(tree, id2);
                    node->val.d += 1;
                    // printf("%g\n", node->val.d);
                }else{
                    addEdgeValue(g, id1, id2, 1);
                    addEdgeValue(g, id2, id1, 1);
                }
            }
            printf("%s\t", getVertex(g, atoi(is->fields[i])));
        }
        printf("\n");
    }

}

void swap1(double *a, double *b){
    double tmp = *a;
    *a = *b;
    *b = tmp;
}

void swap2(int *a, int *b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int sanPhamLq(Graph g, int id, int *output){
    double w[1000];
    int count = 0;
    count = outDegree(g, id, output);
    for(int i = 0; i < count; i++){
        w[i] = getEdgeValue(g, id, output[i]);
    }
    for(int i = 0; i < count; i++){
        for(int j = count-1; j >= i; j--){
            if(w[i] < w[j]){
                swap1(&w[i], &w[j]);
                swap2(&output[i], &output[j]);
            }
        }
    }
    return count;
}

double duongdi(Graph g, int id1, int id2, int *output, int *getNum){
    double w;
    w = shortestPath_s_to_t(g, id1, id2, output, getNum);
    return w;
}