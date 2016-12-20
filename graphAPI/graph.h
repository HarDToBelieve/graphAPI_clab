#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>

#define UNDIRECTED 0
#define DIRECTED 1

typedef struct {
	int *matrix;
	int sizemax;
} Graph;

Graph createGraph(int);
void addEdge(Graph*, int, int, int);
int adjacent(Graph*, int, int);
int getAdjacentVertices(Graph*, int, int*);
void dropGraph(Graph*);

#endif /* GRAPH_H */
