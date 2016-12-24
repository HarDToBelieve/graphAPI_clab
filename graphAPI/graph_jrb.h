#ifndef GRAPH_JRB_H
#define GRAPH_JRB_H

#include "../libfdr/dllist.h"
#include "../libfdr/fields.h"
#include "../libfdr/jval.h"
#include "../libfdr/jrb.h"

#define true 1
#define false 0
#define UNDIRECTED 0
#define DIRECTED 1
#define INT_MAX 2147483647

typedef JRB Graph;

Graph createGraph ();
void mat2adjl (Graph, char *[], int *[], int, int);
void addEdge (Graph, char *[], char *, char *, int, int);
int adjacent (Graph, int, int);
int getAdjacentVertices (Graph, int, JRB*);
void dropGraph (Graph);
int getNumofV (Graph);
void bfs (Graph, int, int, void (*func)(int));
void dfs_norecur (Graph, int, int, void (*func)(int));
int shortest_noWeight_path (Graph, int, int, int*);

int addVertex (Graph, char* mapping[], char *name);
char *getVertex (Graph, char *mapping[], int);
int indegree (Graph, int, int*);
int outdegree (Graph, int, int*);
int dfs_recur (Graph, int, int, int*);
int isDAG (Graph);
int toposort (Graph, int*);
int dijkstra (Graph, int, int, int*, int *);

#endif /* GRAPH_JRB_H */
