#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../Graph/graph.h"
#include "../Dijkstra/dijkstra.h"
#define max 100

int menu(void);
void readFile(Graph g, Graph g2, char *filename, int *n);
void printMatrix(Graph g, double arr[100][100], int n);
void printDanhsachke(Graph g);
int checkDibo(Graph g, int id1, int output[max], int cnt);
void chucnang3a(Graph g);
void chucnang3b(Graph);
void duongDiMin(Graph g, int s, int t);
void chucnang5(Graph g, int s, int t);

int main(){

    int selec;
    Graph g = creatGraph();
    Graph g2 = creatGraph();
    int n;
    double arr[max][max] = {};


    int case1 = 0;
    int s, t;

    do{

        selec = menu();
        switch(selec){
            case 1:
                readFile(g, g2, "dothi.txt", &n);
                printMatrix(g, arr, n);
                case1 = 1;
                break;
            case 2:
                if(case1 == 1)
                    printDanhsachke(g);
                else{
                    printf("***Hay chay case 1 de doc file!\n");
                }
                break;
            case 3:
                if(case1 == 1){
                    printf("Danh sach thanh tri chi co the den no bang di bo la: ");
                    chucnang3a(g);
                    printf("Danh sach thanh tri co nhieu duong di den no nhat la: ");
                    chucnang3b(g);     
                }else{
                    printf("***Hay chay case 1 de doc file!\n");
                }
                break;
            case 4:
                if(case1 == 1){
                    printf("Nhap thanh tri xuat phat: ");
                    scanf("%d", &s);
                    printf("Nhap thanh tri dich: ");
                    scanf("%d", &t);
                    duongDiMin(g, s, t);
                }else{
                    printf("***Hay chay case 1 de doc file!\n");
                }
                break;
            case 5:
                if(case1 == 1){
                    printf("Nhap thanh tri xuat phat: ");
                    scanf("%d", &s);
                    printf("Nhap thanh tri dich: ");
                    scanf("%d", &t);
                    chucnang5(g2, s, t);
                }else{
                    printf("***Hay chay case 1 de doc file!\n");
                }
                break;
            case 6:
                dropGraph(g);
                dropGraph(g2);
                printf("Thoat!!!\n");
                break;
            default:
                puts("Lua chon sai");
                break;
        }
        
    }while(selec != 6);

}

int menu(){
    int selec;
    puts("===========MENU==========");
    puts("1. Doc do thi cac thanh tri");
    puts("2. In ra ma tran ke cua moi thanh tri");
    puts("3. Dua ra");
    puts("4. Tim duong di ngan nhat");
    puts("5. Duong di bo ngan nhat");
    puts("6. Thoat!!!");
    printf("Nhap lua chon: ");
    scanf("%d", &selec);
    return selec;
}

void readFile(Graph g, Graph g2, char *filename, int *n){
    IS is = new_inputstruct(filename);
    int m;
    double w;
    int id1, id2;
    get_line(is);
    *n = atoi(is->fields[0]);
    m = atoi(is->fields[1]);
    while(get_line(is) > 0){
        id1 = atoi(is->fields[0]);
        id2 = atoi(is->fields[1]);
        addVertex(g, id1, is->fields[0]);
        addVertex(g, id2, is->fields[1]);
        w = atof(is->fields[2]);
        addEdgeValue(g, id1, id2, w);
        addEdgeValue(g, id2, id1, w);
        if(w >= 50){
            addVertex(g2, id1, is->fields[0]);
            addVertex(g2, id2, is->fields[1]);
            addEdgeValue(g2, id1, id2, w);
            addEdgeValue(g2, id2, id1, w);
        }
    }
}

void printMatrix(Graph g, double arr[max][max], int n){
    for(int i = 1; i <= n-1; i++){
        for(int j = i+1; j <= n; j++){
            if(hasEdge(g, i, j)){
                // arr[i][j] = getEdgeValue(g, i, j);
                // arr[j][i] = getEdgeValue(g, i, j);
                arr[i][j] = 1;
                arr[j][i] = 1;
            }
        }
    }
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            printf("%-5g", arr[i][j]);
        }
        printf("\n");
    }
}

void printDanhsachke(Graph g){
    JRB node;
    int cnt;
    jrb_traverse(node, g.vertices){
        int ouput[max];
        printf("Castle %s: ", getVertex(g, jval_i(node->key)));
        cnt = outDegree(g, jval_i(node->key), ouput);
        for(int i = 0; i < cnt; i++){
            printf("%d ", ouput[i]);
        }
        printf("\n");
    }
}

int checkDibo(Graph g, int id1, int output[max], int cnt){
    for(int i = 0; i < cnt; i++){
        if(getEdgeValue(g, output[i], id1) < 50){
            return 0;
        }
    }
    return 1;
}

void chucnang3a(Graph g){
    JRB node;
    int cnt;
    jrb_traverse(node, g.vertices){
        int ouput[max];
        cnt = inDegree(g, jval_i(node->key), ouput);
        if(checkDibo(g, jval_i(node->key), ouput, cnt) == 1){
            printf("%d ", jval_i(node->key));
        }
    }
    printf("\n");
}

void chucnang3b(Graph g){
    JRB node;
    int mark = 0;
    int cnt;
    jrb_traverse(node, g.vertices){
        int output[max];
        cnt = inDegree(g, jval_i(node->key), output);
        if(cnt > mark){
            mark = cnt;
        }
    }

    // printf("%d", jval_i(tmp->key));
    jrb_traverse(node, g.vertices){
        int output[max];
        cnt = inDegree(g, jval_i(node->key), output);
        if(cnt == mark){
            printf("%d ", jval_i(node->key));
        }
    }
    printf("\n");
}

void duongDiMin(Graph g, int s, int t){
    if(jrb_find_int(g.vertices, s) == NULL || jrb_find_int(g.vertices, t) == NULL){
        printf("ROUTE NOT FOUND\n");
        return;
    }
    int output[max];
    double w;
    int cnt;
    w = shortestPath_s_to_t(g, s, t, output, &cnt);
    if(w == INFINITIVE_VALUE){
        printf("ROUTE NOT FOUND\n");
    }else{
        printf("Duong di ngan nhat tu %d den %d: \n", s, t);
        printf("\tDo dai duong di: %g\n", w);
        printf("\t");
        for(int i = 0; i < cnt-1; i++){
            printf("%d --> ", output[i]);
        }
        printf("%d\n", output[cnt-1]);
    }
}

void chucnang5(Graph g, int s, int t){
    if(jrb_find_int(g.vertices, s) == NULL || jrb_find_int(g.vertices, t) == NULL){
        printf("ROUTE NOT FOUND\n");
        return;
    }
    int output[max];
    double w;
    int cnt;
    w = shortestPath_s_to_t(g, s, t, output, &cnt);
    if(w == INFINITIVE_VALUE){
        printf("ROUTE NOT FOUND\n");
    }else{
        printf("Duong di bo ngan nhat tu %d den %d: \n", s, t);
        printf("\tDo dai duong di: %g\n", w);
        printf("\t");
        for(int i = 0; i < cnt-1; i++){
            printf("%d --> ", output[i]);
        }
        printf("%d\n", output[cnt-1]);
    }
}