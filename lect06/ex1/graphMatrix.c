// Cai dat do thi dung ma tran ke
#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int *matrix;
    int n;
}Graph;

Graph creatGraph(int n);
void addEdge(Graph g, int v1, int v2);
int adjacent(Graph g, int v1, int v2);
int getAdjacentVertices(Graph g, int v, int *output);
void dropGraph(Graph g);

int main(){

    int i, n, output[100];
    Graph g = creatGraph(100);
    addEdge(g, 0, 1);
    addEdge(g, 0, 2);
    addEdge(g, 1, 2);
    addEdge(g, 1, 3);
    n = getAdjacentVertices(g, 1, output);
    if(n == 0){
        printf("Khong co dinh ke nao\n");
    }else{
        printf("Danh sach cac dinh ke voi dinh 1: ");
        for(int i = 0; i < n; i++){
            printf("%-5d", output[i]);
        }
    }
    dropGraph(g);

}

Graph creatGraph(int n){
    Graph g;
    g.n = n;
    g.matrix = (int *)malloc(sizeof(int) * n*n);
    return g;
}

void addEdge(Graph g, int v1, int v2){
    g.matrix[g.n * v1 + v2] = 1;
    g.matrix[g.n * v2 + v1] = 1;
}

int adjacent(Graph g, int v1, int v2){
    return g.matrix[g.n*v1 + v2];
}

int getAdjacentVertices(Graph g, int v, int *output){
    int total = 0;
    for(int i = 0; i < g.n; i++){
        if(adjacent(g, v, i) == 1){
            output[total++] = i;
        }
    }
    return total;
}

void dropGraph(Graph g){
    free(g.matrix);
    g.matrix = NULL;
    g.n = 0;
}