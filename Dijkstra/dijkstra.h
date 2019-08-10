#include <stdio.h>
#include "../libfdr/jrb.h"
#include "../libfdr/dllist.h"
#include "../Graph/graph.h"
#define INFINITIVE_VALUE 99999999

// add weight type double
void addEdgeValue(Graph g, int v1, int v2, double weight);

// return weight v1-v2
double getEdgeValue(Graph g, int v1, int v2);

void swapArray(int arr[], int cnt);

// Duong di ngan nhat s-t
// Chuoi duong di la: *path, co *getNum phan tu (thu tu xuoi)
double shortestPath_s_to_t(Graph g, int s, int t, int *path, int *getNum);

void shortestPath_s_to_all(Graph g, int s, int *p, double *d);