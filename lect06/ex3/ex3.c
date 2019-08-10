#include <stdio.h>
#include "../../libfdr/jrb.h"

typedef JRB Graph;
Graph creatGraph(void);
void addEdge(Graph g, int v1, int v2);
int adjacent(Graph g, int v1, int v2);
int getAdjacentVertices(Graph g, int v, int *output);
void dropGraph(Graph g);

int main(){

    Graph g = creatGraph();
    int output[100];
    int n;
    addEdge(g, 0, 1);
    addEdge(g, 0, 2);
    addEdge(g, 1, 2);
    addEdge(g, 1, 3);
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

}

Graph creatGraph(){
    Graph g = make_jrb();
    return g;
}

void addEdge(Graph g, int v1, int v2){
    JRB tree;
    JRB node, tmp;

    node = jrb_find_int(g, v1);
    if(node == NULL){
        tree = make_jrb();
        jrb_insert_int(g, v1, new_jval_v((void *) tree));
        // printf("%d\n", jval_i(g->key));
        // jrb_traverse(tmp, g){
        //     printf("%d\n", jval_i(tmp->key));
        // }
        tmp = jrb_first(g);
        printf("%d\n", jval_i(tmp->key));
        jrb_insert_int(tree, v2, new_jval_i(1));
    }else{
        tree = (JRB) jval_v(node->val);
        jrb_insert_int(tree, v2, new_jval_i(1));
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