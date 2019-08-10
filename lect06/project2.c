#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"/Users/khacthangdev/Desktop/cAdvance/libfdr/jrb.h"
#include "/Users/khacthangdev/Desktop/cAdvance/libfdr/dllist.h"
#define INFINITIVE_VALUE  10000000

typedef struct {
   JRB edges;
   JRB vertices;
} Graph;

typedef struct {
  double weight;
  char num[20];
}bus;

Graph createGraph();
void addVertex(Graph graph, int id, char* name);
char *getVertex(Graph graph, int id);
double getEdgeValue(Graph graph, int v1, int v2);
void addEdge(Graph graph, int v1, int v2, bus* b);
int indegree(Graph graph, int v, int* output);
int outdegree(Graph graph, int v, int* output);
double shortestPath(Graph graph, int s, int t, int* path, int*length);
void dropGraph(Graph graph);
int main()
{
    int i, length, path[100], s, t;
    double w;
    Graph g = createGraph();
    JRB k, q, r;
    bus *b = (bus*)malloc(5*sizeof(bus));
    // bus b[5];
    
    b[0].weight = 1;
    b[1].weight = 2;
    b[2].weight = 1;
    b[3].weight = 2;
    b[4].weight = 3;
    strcpy(b[0].num, "wer");
    strcpy(b[1].num, "qwe");
    strcpy(b[2].num, "rty");
    strcpy(b[3].num, "rcd");
    strcpy(b[4].num, "tyr");
    addVertex(g, 0, "V0");
    addVertex(g, 1, "V1");
    addVertex(g, 2, "V2");
    addVertex(g, 3, "V3");
    addEdge(g, 0, 1, &b[0]);
    addEdge(g, 1, 2, &b[1]);
    addEdge(g, 2, 0, &b[2]);
    addEdge(g, 1, 3, &b[3]);
    addEdge(g, 3, 2, &b[4]);
    s = 0;
    t = 3;
    w = shortestPath(g, s, t, path, &length);
    if (w == INFINITIVE_VALUE)
      {
	printf("No path from %s to %s\n", getVertex(g, s), getVertex(g, t));
      }else
      {
	printf("Path from %s to %s (with total distance %g)\n", getVertex(g, s), getVertex(g, t), w);
  bus *tmp;
	for (i=0; i<length - 1; i++){
      k = jrb_find_int(g.edges, path[i]);
	    q = (JRB)jval_v(k->val);
	    r = jrb_find_int(q, path[i+1]);
      // bus *tmp;
      tmp = (bus *)jval_v(r->val);
	    printf("%s => %s tuyen %s\n", getVertex(g, path[i]), getVertex(g, path[i+1]), tmp->num);
	  }
  }   
  dropGraph(g);   
}

Graph createGraph()
{
  Graph g; 
  g.edges = make_jrb();  
  g.vertices = make_jrb();  
  return g;
}

void addVertex(Graph g, int id, char* name)
{
  JRB node = jrb_find_int(g.vertices, id);
  if (node==NULL)
    jrb_insert_int(g.vertices, id, new_jval_s(strdup(name)));            
}

char *getVertex(Graph g, int id)
{
  JRB node = jrb_find_int(g.vertices, id);
  if (node==NULL) 
    return NULL;
  else                
    return jval_s(node->val);
}     

void addEdge(Graph graph, int v1, int v2, bus* b)
{
  JRB node, tree;
  if (getEdgeValue(graph, v1, v2)==INFINITIVE_VALUE)
    {
      node = jrb_find_int(graph.edges, v1);
      if (node==NULL) {
	      tree = make_jrb();
	      jrb_insert_int(graph.edges, v1, new_jval_v(tree));
      } else
        {
	        tree = (JRB) jval_v(node->val);   
        }
      jrb_insert_int(tree, v2, new_jval_v((void*)b));
    }
}

double getEdgeValue(Graph graph, int v1, int v2)
{
  JRB node, tree;
  bus* b = malloc(sizeof(bus));
  node = jrb_find_int(graph.edges, v1);
  if (node==NULL)
    return INFINITIVE_VALUE;
  tree = (JRB) jval_v(node->val);
  node = jrb_find_int(tree, v2);
  if (node==NULL)
    return INFINITIVE_VALUE;
  else{
    b = (bus *) node->val.v;
    return b->weight;
  }
}

int indegree (Graph graph, int v, int* output)
{
  JRB tree, node;
  int total = 0;   
  
  jrb_traverse(node, graph.edges)
    {
      tree = (JRB) jval_v(node->val);
      if (jrb_find_int(tree, v))
	{
          output[total] = jval_i(node->key);
          total++;
	}                
    }
  return total;   
}

int outdegree (Graph graph, int v, int* output)
{
  JRB tree, node;
  int total;
  node = jrb_find_int(graph.edges, v);
  if (node==NULL)
    return 0;
  tree = (JRB) jval_v(node->val);
  total = 0;   
  jrb_traverse(node, tree)
    {
      output[total] = jval_i(node->key);
      total++;                
    }
  return total;   
}

double shortestPath(Graph g, int s, int t, int* path, int*length)
{
  double distance[1000], min, w, total;
  int previous[1000], tmp[1000];
  int n, output[100], i, u, v, start;
  Dllist ptr, queue, node;
  
  for (i=0; i<1000; i++)
    distance[i] = INFINITIVE_VALUE;
  distance[s] = 0;
  previous[s] = s;
  
  queue = new_dllist();
  dll_append(queue, new_jval_i(s));
  
  while ( !dll_empty(queue) )
    {  
      min = INFINITIVE_VALUE;   
      dll_traverse(ptr, queue)
	{
          u = jval_i(ptr->val);              
          if (min > distance[u])
	    {
	      min = distance[u];
	      node = ptr;
	    }                 
	}
      dll_delete_node(node);
      
      if (u == t) break;
      
      n = outdegree(g, u, output);
      for (i=0; i<n; i++)
	{
          v = output[i];
          w = getEdgeValue(g, u, v);
          if ( distance[v] > distance[u] + w )
          {    
              distance[v] = distance[u] + w;
              previous[v] = u;
          }     
          dll_append(queue, new_jval_i(v));
      }
   }
   total = distance[t]; 
   if (total != INFINITIVE_VALUE)
   {
       tmp[0] = t;
       n = 1;              
       while (t != s)
       {
             t = previous[t];
             tmp[n++] = t;
       }
       for (i=n-1; i>=0; i--)
           path[n-i-1] = tmp[i];
       *length = n;                
   }
   return total;   
}

void dropGraph(Graph graph)
{
    JRB node, tree;
    jrb_traverse(node, graph.edges)
    {
        tree = (JRB) jval_v(node->val);
        jrb_free_tree(tree);
    }
    jrb_free_tree(graph.edges);
    jrb_free_tree(graph.vertices);
}
