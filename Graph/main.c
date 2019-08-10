#include <stdio.h>
#include <string.h>
#include "graph.h"
#include "../Dijkstra/dijkstra.h"

int main (){
    Graph g;
    g = creatGraph();
    int output[100], n;
    // output = (int *)malloc(sizeof(int)*100);
    addVertex(g, 1, "giap_bat");
    addVertex(g, 2, "nuoc_ngam");
    addVertex(g, 3, "long_bien");
    addVertex(g, 4, "yen_nghia");
    addVertex(g, 5, "son_tay");
    addEdgeValue(g, 1, 2, 1);
    addEdgeValue(g, 1, 4, 1);
    addEdgeValue(g, 1, 5, 2);
    addEdgeValue(g, 2, 3, 4);
    addEdgeValue(g, 5, 4, 3);
    addEdgeValue(g, 4, 3, 2);
    addEdgeValue(g, 4, 2, 5);
    // BFS(g, 1, -1);

    double w;
    int p[100];
    w = shortestPath_s_to_t(g, 1, 3, p);
    if(w == INFINITIVE_VALUE){
        printf("Khong co duong di tu %s den %s\n", getVertex(g, 1), getVertex(g, 3));
    }else{
        printf("Duong di ngan nhat tu %s den %s: \n", getVertex(g, 1), getVertex(g, 3));
        printf("Do dai la: %g\n", w);
        int i = 3;
        do{
            printf("%s <=== ", getVertex(g, i));
            i = p[i];
        }while(i != 1);
        printf("%s\n", getVertex(g, 1));
    }
    dropGraph(g);
}
