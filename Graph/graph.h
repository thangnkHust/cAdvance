#ifndef _Graph_
#define _Graph_

#include <stdio.h>
#include "../libfdr/jrb.h"
#include "../libfdr/dllist.h"
#include "../libfdr/fields.h"

typedef struct Graph{
    JRB vertices;
    JRB edges;
}Graph;

extern Graph creatGraph(/*graph*/); // init graph with vertex and edge
extern void addVertex(Graph g, int id, char *name); // add vertex for graph
extern char *getVertex(Graph g, int id); //return name of vertex
// extern double getEgde(Graph g, int id1, int id2); // return weight of id1 - id2
extern void addEdge(Graph g, int v1, int v2, int weight); //add Edge for graph
extern int hasEdge(Graph g, int v1, int v2);    //return co v1 -> v2 ?
extern int inDegree(Graph g, int v, int *output);   //return so canh vao va list output
extern int outDegree(Graph g, int v, int *output);  //return so canh ra va list output
extern int DAG(Graph g);    // return not cycle
extern int DFS_DAG(Graph g, int start); 
void printVertex(int v);
extern void BFS(Graph g, int start, int stop);  //Duyet cay theo BFS
extern void dropGraph(Graph g); //Giai phong cay
extern void topoSort(Graph g, int output[], int *n);
extern int inDegreeTest(Graph g, int v);
#endif
