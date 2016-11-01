#ifndef GRAPH_JRB_H
#define GRAPH_JRB_H

#include "../libfdr/dllist.h"
#include "../libfdr/fields.h"
#include "../libfdr/jval.h"
#include "../libfdr/jrb.h"

#define true 1
#define false 0

typedef JRB Graph;

Graph createGraph ();
void addEdge (Graph, int, int);
int adjacent (Graph, int, int);
int getAdjacentVertices (Graph, int, int*);
void dropGraph (Graph);
int getNumofV (Graph);
void bfs (Graph, int, int, void (*func(int)));
void dfs (Graph, int, int, void (*func(int)));

#endif /* GRAPH_JRB_H */
