#include <stdio.h>
#include <string.h>
#include "../Graph/graph.h"
#include "../Dijkstra/dijkstra.h"

int main (){
    Graph g;
    int output[100];
    int n;
    JRB tmp;
    g = creatGraph();
    addVertex(g, 1, "a");
    addVertex(g, 2, "b");
    addVertex(g, 3, "c");
    addVertex(g, 4, "d");
    addVertex(g, 5, "e");
    addVertex(g, 6, "f");
    addVertex(g, 7, "g");
    addVertex(g, 8, "h");
    addVertex(g, 9, "i");
    addVertex(g, 10, "j");
    addEdgeValue(g, 1, 9, 1);
    addEdgeValue(g, 1, 6, 1);
    addEdgeValue(g, 4, 3, 2);
    addEdgeValue(g, 5, 7, 4);
    addEdgeValue(g, 5, 9, 3);
    addEdgeValue(g, 6, 10, 2);
    addEdgeValue(g, 6, 7, 5);
    addEdgeValue(g, 6, 5, 2);
    addEdgeValue(g, 7, 4, 2);
    addEdgeValue(g, 7, 8, 2);
    addEdgeValue(g, 8, 3, 2);
    addEdgeValue(g, 9, 2, 2);
    addEdgeValue(g, 9, 7, 2);
    // BFS(g, 1, -1);
    // if(!DAG(g)){
    //     printf("Co chu trinh\n");
    // }else{
    //     printf("Khong co chu trinh\n");
    //     printf("Topological Sort: ");
    //     topoSort(g, output, &n);
    //     for(int i = 0; i < n; i++){
    //         tmp = jrb_find_int(g.vertices, output[i]);
    //         printf("%s --> ", jval_s(tmp->val));
    //     }
    //     printf("Ket thuc\n");
        
    // }

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

    int temp[100];
    double d[100];
    int s = 1;
    shortestPath_s_to_all(g, s, temp, d);

    for(int i = 1; i < 11; i++){
        if(d[i] == INFINITIVE_VALUE){
            printf("Khong co duong di");
        }else{
            int j = i;
            do{
                printf("%s <=== ", getVertex(g, j));
                j = temp[j];
            }while(j != s);
            printf("%s - %g\n", getVertex(g, s), d[i]);
        }
    }

    dropGraph(g);

    // if(d[3] == INFINITIVE_VALUE){
    //     printf("Khong co duong di tu %s den %s\n", getVertex(g, 1), getVertex(g, 3));
    // }else{
    //     printf("Duong di ngan nhat tu %s den %s: \n", getVertex(g, 1), getVertex(g, 3));
    //     printf("Do dai la: %g\n", d[3]);
    //     int i = 3;
    //     do{
    //         printf("%s <=== ", getVertex(g, i));
    //         i = temp[i];
    //     }while(i != 1);
    //     printf("%s\n", getVertex(g, 1));
    // }

}