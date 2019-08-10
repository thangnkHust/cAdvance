#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../libfdr/jrb.h"
#include "../libfdr/dllist.h"

typedef struct tuyen{
    int w;
    char *name;
}tuyen;

// NOTE: trong struct char * -> []
//       struct *s -> can malloc
//       jval_v((void *)s)

typedef JRB Graph;
Graph creatGraph(void);
void addEdge(Graph g, int v1, int v2, tuyen *t);
int adjacent(Graph g, int v1, int v2);
int getAdjacentVertices(Graph g, int v, int *output);
void dropGraph(Graph g);
void printVertex(int v);
void BFS(Graph g, int start, int stop, void (*func)(int));
void printTuyen(Graph g, int v1, int v2);

int main(){

    Graph g = creatGraph();
    int output[100];
    int n;
    tuyen *t = malloc(sizeof(tuyen));
    t->name = malloc(sizeof(char)*20);
    strcpy(t->name, "a");
    t->w = 5;
    // printf("%d-%s", t->w, t->name);
    // getchar();
    addEdge(g, 0, 1, t);
    addEdge(g, 0, 2, t);
    addEdge(g, 1, 2, t);
    addEdge(g, 1, 3, t);
    addEdge(g, 2, 3, t);

    n = getAdjacentVertices(g, 1, output);
    if(n == 0){
        printf("Khong co dinh nao ke voi dinh 1\n");
    }else{
        if(n == -1){
            printf("Khong co dinh 1\n");
        }else{
            printf("Danh sach dinh ke voi 1 la: ");
            for(int i = 0; i < n; i++){
                printf("%-5d", output[i]);
            }
            printf("\n");
        }
    }

    printTuyen(g, 0, 1);

    printf("Duyet BFS tu 1 den 4: \n");
    BFS(g, 1, 3, printVertex);
    printf("Duyet BFS tu 1 den -1: \n");
    BFS(g, 1, -1, printVertex);

}

Graph creatGraph(){
    Graph g = make_jrb();
    return g;
}

void addEdge(Graph g, int v1, int v2, tuyen *t){
    JRB tree;
    JRB node;
    node = jrb_find_int(g, v1);
    if(node == NULL){
        tree = make_jrb();
        jrb_insert_int(g, v1, new_jval_v((void *) tree));
        jrb_insert_int(tree, v2, new_jval_v((void *) t));
    }else{
        tree = (JRB) jval_v(node->val);
        jrb_insert_int(tree, v2, new_jval_v((void *) t));
    }

}


int adjacent(Graph g, int v1, int v2){
    JRB node = jrb_find_int(g, v1);
    JRB tree;
    if(node == NULL) return -1;
    tree = (JRB)jval_v(node->val);
    if(jrb_find_int(tree, v2) == NULL){
        return 0;
    }
    return 1;
}

int getAdjacentVertices(Graph g, int v, int *output){
    JRB node = jrb_find_int(g, v);
    if(node == NULL) return 0;
    JRB tree = (JRB) jval_v(node->val);
    int total = 0;
    jrb_traverse(node, tree){
        output[total++] = jval_i(node->key);
    }
    return total;
}

void dropGraph(Graph g){
    JRB node;
    jrb_traverse(node, g){
        jrb_free_tree(jval_v(node->val));
    }
    jrb_free_tree(g);
}

void printVertex(int v){
    printf("%-4d", v);
}

void BFS(Graph g, int start, int stop, void (*func)(int)){
    int visitted[100] = {};
    int output[100], u, v, n;
    Dllist queue = new_dllist();
    Dllist node;
    dll_append(queue, new_jval_i(start));
    while(!dll_empty(queue)){
        node = dll_first(queue);
        u = jval_i(node->val);
        dll_delete_node(node);
        if(!visitted[u]){
            printVertex(u);
            visitted[u] = 1;
            if(u == stop){
                return;
            }
            n = getAdjacentVertices(g, u, output);
            for(int i = 0; i< n; i++){
                v = output[i];
                if(!visitted[v]){
                    dll_append(queue, new_jval_i(v));
                }
            }
        }
        
    }
}

void printTuyen(Graph g, int v1, int v2){
    JRB node, tree;
    tuyen *t;
    node = jrb_find_int(g, v1);
    if(node == NULL){
        printf("Khong co chuyen %d", v1);
        return;
    }
    tree = (JRB) jval_v(node->val);
    node = jrb_find_int(tree, v2);
    if(node == NULL){
        printf("Khong co dinh %d\n", v2);
        return;
    }
    t = (tuyen *) jval_v(node->val);
    printf("Tuyen %d => %d la: %d - %s\n", v1, v2, t->w, t->name);
}