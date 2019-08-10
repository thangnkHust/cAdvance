#include <stdio.h>
#include <string.h>
#include "graph.h"


// init graph with vertex and edge
Graph creatGraph(){
    Graph g;
    g.vertices = make_jrb();
    g.edges = make_jrb();
    return g;
}

// add vertex for graph
void addVertex(Graph g, int id, char *name){
    JRB node = jrb_find_int(g.vertices, id);
    if(node == NULL){
        jrb_insert_int(g.vertices, id, new_jval_s(strdup(name)));
    }
}

// return name of vertex
char *getVertex(Graph g, int id){
    JRB node = jrb_find_int(g.vertices, id);
    if(node == NULL){
        return NULL;
    }
    return jval_s(node->val);
}

// // return weight of edge
// double getEgde(Graph g, int id1, int id2){
//     JRB node, tmp;
//     node = jrb_find_int(g.edges, id1);
//     if(node == NULL){
//         return 0;
//     }
//     tmp = (JRB) jval_v(node->val);
//     node = jrb_find_int(tmp, id2);
//     if(node == NULL)
//         return 0;
//     return jval_d(node->val);
// }

// add edge with weight
void addEdge(Graph g, int v1, int v2, int weight){
    JRB node = jrb_find_int(g.edges, v1);
    JRB tree;
    if(node == NULL){
        tree = make_jrb();
        jrb_insert_int(g.edges, v1, new_jval_v(tree));
    }else{
        tree = (JRB) jval_v(node->val);
    }
    jrb_insert_int(tree, v2, new_jval_i(weight));
}

// return: co canh v1, v2 ?
int hasEdge(Graph g, int v1, int v2){
    JRB node = jrb_find_int(g.edges, v1);
    if(node == NULL) return 0;
    JRB tree = (JRB) jval_v(node->val);
    if( jrb_find_int(tree, v2) == NULL) return 0;
    return 1;
}

// return so canh vao, danh sach output
int inDegree(Graph g, int v, int *output){
    JRB tree, node;
    int total = 0;
    jrb_traverse(node, g.edges){
        tree = (JRB) jval_v(node->val);
        if(jrb_find_int(tree, v)){
            output[total] = jval_i(node->key);
            total++;
        }
    }
    return total;
}
int inDegreeTest(Graph g, int v){
    JRB tree, node;
    int total = 0;
    jrb_traverse(node, g.edges){
        tree = (JRB) jval_v(node->val);
        if(jrb_find_int(tree, v)){
            total++;
        }
    }
    return total;
}

int outDegree(Graph g, int v, int *output){
    int total = 0;
    JRB node = jrb_find_int(g.edges, v);
    if(node == NULL) return 0;
    JRB tree = (JRB) jval_v(node->val);
    jrb_traverse(node, tree){
        output[total] = jval_i(node->key);
        total++;
    }
    return total;
}

int DAG(Graph g){
    int start, notCycle;
    JRB vertex;
    jrb_traverse(vertex, g.vertices){
        start = jval_i(vertex->key);
        printf("Goi DFS tu dinh %d\n", start);
        notCycle = DFS_DAG(g, start);
        if(notCycle == 0){
            return 0;
        }
    }
    return 1;
}

int DFS_DAG(Graph g, int start){
    int visited[1000] = {};
    int n, output[100], i, u, v;
    Dllist node, stack;

    stack = new_dllist();
    dll_append(stack,new_jval_i(start));
    while(!dll_empty(stack)){
        node = dll_last(stack);
        u = jval_i(node->val);
        dll_delete_node(node);
        if(!visited[u]){
            visited[u] = 1;
            n = outDegree(g,u, output);
            for(i = 0; i < n; i++){
                v = output[i];
                if(v == start) return 0;
                if(!visited[v])
                    dll_append(stack, new_jval_i(v));   
            }
        }
        return 1;
    }
}

void printVertex(int v){
    printf("%-4d", v);
}

void BFS(Graph g, int start, int stop){
    int visited[100] = {};
    int output[100], u, v, n;
    Dllist queue = new_dllist();
    Dllist node;
    dll_append(queue, new_jval_i(start));
    while(!dll_empty(queue)){
        node = dll_first(queue);
        u = jval_i(node->val);
        dll_delete_node(node);
        if(!visited[u]){
            printVertex(u);
            visited[u] = 1;
            if(u == stop){
                return;
            }
            n = outDegree(g, u, output);
            // printf("%d\n", n);
            for(int i = 0; i < n; i++){
                v = output[i];
                if(!visited[v]){
                    dll_append(queue, new_jval_i(v));
                }
            }
        }
    }
}

void dropGraph(Graph g){
    JRB node, tree;
    jrb_traverse(node, g.edges){
        tree = (JRB) jval_v(node->val);
        jrb_free_tree(tree);
    }
    jrb_free_tree(g.edges);
    jrb_free_tree(g.vertices);
}

void topoSort(Graph g, int *output, int *n){
    Dllist queue = new_dllist();
    Dllist node;
    JRB tmp, tree;
    int u, v, i = 0, w, k;
    // int *tmpOutput, *op;
    // getchar();
    jrb_traverse(tmp, g.vertices){
        u = jval_i(tmp->key);
        // printf("%d\n", u);
        k = inDegreeTest(g, u);
        if(k == 0){
            // printf("%d\n", u);
            dll_append(queue, new_jval_i(u));
            // printf("%d\n", dll_first(queue));
        }
    }
    // printf("%d\n", dll_first(queue));
    // getchar();
    while(!dll_empty(queue)){
        node = dll_first(queue);
        // printf("%d\n", v);
        v = jval_i(node->val);
        dll_delete_node(node);
        output[i] = v;
        // printf("%-4d", output[i]);
        i++;
        // getchar();
        tmp = jrb_find_int(g.edges, v);
        if(tmp == NULL) continue;
        tree = (JRB) jval_v(tmp->val);
        // jrb_delete_node(node);
        jrb_traverse(tmp, tree){
            // if(tmp == NULL) return;
            w = jval_i(tmp->key);
            // printf("%d\n", w);
            k = inDegreeTest(g, w);
            k--;
            // printf("%d-%d\n",w, k);
            if(k == 0){
                dll_append(queue, new_jval_i(w));
            }
        }
        // getchar();
        // printf("%d\n", v);
        tmp = jrb_find_int(g.edges, v);
        jrb_delete_node(tmp);
        // getchar();
    }
    *n = i;
}
