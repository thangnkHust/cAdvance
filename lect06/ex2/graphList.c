#include <stdio.h>
#include <stdlib.h>
#include "../../libfdr/jrb.h"
#include "../../libfdr/dllist.h"

typedef JRB Graph;
Graph creatGraph(void);     //tao 1 do thi
void addEdge(Graph g, int v1, int v2);  //add Edge
int adjacent(Graph g, int v1, int v2);  //return v1 v2 co ke nhau?
int getAdjacentVertices(Graph g, int v, int *output);   //list ke cua v
void dropGraph(Graph g);    //free graph
void printVertex(int v);    // *(func)
void BFS(Graph g, int start, int stop, void (*func)(int));  //Duyet BFS
void DFS(Graph g, int start, int stop, int (*func)(int));   //Duyet DFS
void BFS_shortest(Graph g, int start, int stop, int *before);   //Duong di tu start -> stop
int numVertices(Graph g);   //Dem so dinh
void getComponents(Graph g);    //may thanh phan lien thong, gom nhung dinh nao
void BFS_Connected(Graph g, int start, int *id, int lt);    //id[vertex] = lt
int DFS_DAG(Graph g, int s);    //Xuat phat tu s -> co chu trinh?
int DAG(Graph g);   //kiem tra tren tat ca do thi


int main(){

    Graph g = creatGraph();
    int output[100];
    int n;
    addEdge(g, 0, 1);
    // addEdge(g, 1, 0);
    addEdge(g, 0, 2);
    // addEdge(g, 2, 0);
    addEdge(g, 1, 2);
    // addEdge(g, 2, 1);
    addEdge(g, 1, 3);
    // addEdge(g, 3, 1);
    addEdge(g, 2, 3);
    // addEdge(g, 3, 2);
    addEdge(g, 2, 4);
    // addEdge(g, 4, 2);
    addEdge(g, 5, 1);
    // addEdge(g, 6, 5);
    addEdge(g, 4, 5);
    // addEdge(g, 6, 7);
    int before[100] = {-1};
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
    // printf("Duyet BFS tu 1 den 4: \n");
    // BFS(g, 1, 4, printVertex);
    // printf("\n");
    // printf("Duyet BFS tu 1 den -1: \n");
    // BFS(g, 1, -1, printVertex);
    // printf("\n");

    // DFS(g, 1, -1, printVertex);
    // printf("\n");

    // int start = 1, stop = 5;
    // BFS_shortest(g, start, stop, before);
    // if(before[stop] != -1){
    //     printf("Duong di ngan nhat tu %d den %d: ", start, stop);
    //     int i = stop;
    //     do{
    //         printf("%d <------ ", i);
    //         i = before[i];
    //     }while(i != start);
    //     printf("%d\n", start);
    // }
    int count = numVertices(g);
    printf("dinh %d\n", count);
    getComponents(g);

    if(DAG(g) == 1){
        printf("Do thi khong co chu trinh\n");
    }else{
        printf("Do thi co chu trinh\n");
    }


}

Graph creatGraph(){
    Graph g = make_jrb();
    return g;
}

void addEdge(Graph g, int v1, int v2){
    JRB tree;
    JRB node;

    node = jrb_find_int(g, v1);
    if(node == NULL){
        tree = make_jrb();
        jrb_insert_int(g, v1, new_jval_v((void *) tree));
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


void DFS(Graph g, int start, int stop, int (*func)(int)){
    int visitted[100] = {};
    int output[100], u, v, n;
    Dllist stack = new_dllist();
    Dllist node;
    dll_append(stack, new_jval_i(start));
    while(!dll_empty(stack)){
        node = dll_last(stack);
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
                    dll_append(stack, new_jval_i(v));
                }
            }
            
        }
    }
}

void BFS_shortest(Graph g, int start, int stop, int *before){
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
            visitted[u] = 1;
            if(u == stop){
                return;
            }
            n = getAdjacentVertices(g, u, output);
            for(int i = 0; i< n; i++){
                v = output[i];
                if(!visitted[v]){
                    before[v] = u;                    
                    dll_append(queue, new_jval_i(v));
                }
            }
        }
        
    }
}

int numVertices(Graph g){
    JRB tmp;
    int n = 0;
    jrb_traverse(tmp, g){
        n++;
    }
    return n;
}

void getComponents(Graph g){
    int lt = 0;
    int id[1000];
    int n = numVertices(g);
    for(int i = 0; i < n; i++){
        id[i] = -1;
    }
    for(int i = 0; i < n; i++){
        if(id[i] == -1){
            lt++;
            BFS_Connected(g, i, id, lt);
        }
    }
    // printf("%d\n", n);
    if(lt == 1){
        printf("Do thi da cho lien thong\n");
    }else{
        printf("Do thi da cho khong lien thong\n");
        printf("So thanh phan lien thong cua do thi: %d\n", lt);
        for(int i = 1; i <= lt; i++){
            printf("Cac dinh thuoc thanh phan lien thong thu %d: ", i);
            for(int j = 0; j < n; j++){
                if(id[j] == i) printf("%d ", j);
            }
            printf("\n");
        }
    }
}

void BFS_Connected(Graph g, int start, int *id, int lt){
    int n, output[100], i, u, v;
    Dllist node, queue;
    queue = new_dllist();
    dll_append(queue, new_jval_i(start));
    while(!dll_empty(queue)){
        node = dll_first(queue);
        u = jval_i(node->val);
        dll_delete_node(node);
        if(id[u] == -1){
            id[u] = lt;
            n = getAdjacentVertices(g, u, output);
            for(int i = 0; i < n; i++){
                v = output[i];
                if(id[v] == -1){
                    dll_append(queue, new_jval_i(v));
                }
            }
        }
    }
}

int DFS_DAG(Graph g, int s){
    int visitted[100] = {};
    int output[100], u, v, n;
    Dllist stack = new_dllist();
    Dllist node;
    dll_append(stack, new_jval_i(s));
    while(!dll_empty(stack)){
        node = dll_last(stack);
        u = jval_i(node->val);
        dll_delete_node(node);
        if(!visitted[u]){
            visitted[u] = 1;
            n = getAdjacentVertices(g, u, output);
            for(int i = 0; i< n; i++){
                v = output[i];
                if(v == s) return 0;
                if(!visitted[v]){
                    dll_append(stack, new_jval_i(v));
                }
            }
        }
    }
    return 1;
}

int DAG(Graph g){
    int start, notCycle;
    JRB vertex;
    jrb_traverse(vertex, g){
        start = jval_i(vertex->key);
        printf("Goi DFS xuat phat tu dinh %d\n", start);
        notCycle = DFS_DAG(g, start);
        if(notCycle == 0) return 0;
    }
    return 1;
}




