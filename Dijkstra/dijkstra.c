#include <stdio.h>
#include "dijkstra.h"

void addEdgeValue(Graph g, int v1, int v2, double weight){
    JRB node, tree;
    if(getEdgeValue(g, v1, v2) == INFINITIVE_VALUE){
        node = jrb_find_int(g.edges, v1);
        if(node == NULL){
            tree = make_jrb();
            jrb_insert_int(g.edges, v1, new_jval_v(tree));
        }else{
            tree = (JRB) jval_v(node->val);
        }
        jrb_insert_int(tree, v2, new_jval_d(weight));
    }
}

double getEdgeValue(Graph g, int v1, int v2){
    JRB node, tree;
    node = jrb_find_int(g.edges, v1);
    if(node == NULL) return INFINITIVE_VALUE;
    tree = (JRB) jval_v(node->val);
    node = jrb_find_int(tree, v2);
    if(node == NULL) return INFINITIVE_VALUE;
    return jval_d(node->val);
}

void swapArray(int arr[], int cnt){
    for(int i = 0; i < cnt/2; i++){
        int c = arr[i];
        arr[i] = arr[cnt - 1 - i];
        arr[cnt - 1 - i] = c;
    }
}


double shortestPath_s_to_t(Graph g, int s, int t, int *path, int *getNum){
    double d[100], k[100], min, w;
    int n, output[100], u, v;
    int p[100];
    Dllist ptr, queue;
    JRB node;

    // Khoi tao
    for(int i = 0; i < 100; i++){
        d[i] = INFINITIVE_VALUE;
        k[i] = 0;
    }
    d[s] = 0;
    p[s] = s;

    // Dung hang doi uu tien
    // Ngan nhat = ddnn v1-v2 bat ky
    queue = new_dllist();
    jrb_traverse(node, g.vertices){     //add cac dinh vao queue
        dll_append(queue, new_jval_i(jval_i(node->key)));
    }

    while(!dll_empty(queue)){
        min = INFINITIVE_VALUE + 1;
        dll_traverse(ptr, queue){   //Lan 1: Tim dinh bat dau, xoa khoi queue
            v = jval_i(ptr->val);
            if(min > d[v]){
                min = d[v];
                node = ptr;
                u = v;
            }
        }
        k[u] = 1;
        dll_delete_node(node);

        if(u == t) break;

        n = outDegree(g, u, output);    //tim ddnn tren danh sach ke

        for(int i = 0; i < n; i++){
            v = output[i];
            if(k[v] == 0){
                w = getEdgeValue(g, u, v);
                if(d[v] > d[u] + w){
                    d[v] = d[u] + w;
                    p[v] = u;
                }
            }
        }
    }

    // Bat dau the array -> path, swap ra path
    int count = 0;
    int i = t;
    path[count++] = i;
    while(i != s){
        i = p[i];
        path[count++] = i;
    }
    *getNum = count;

    swapArray(path, count);

    return d[t];
}

void shortestPath_s_to_all(Graph g, int s, int *p, double *d){
    JRB node;
    // double w;
    int getNum = 0;
    jrb_traverse(node, g.vertices){
        d[jval_i(node->key)] = shortestPath_s_to_t(g, s, jval_i(node->key), p, &getNum);
    }
}

