#include "graph.h"

Graph createGraph(int sizemax) {
	Graph result;
	result.matrix = (int *)malloc(sizemax * sizemax);
	result.sizemax = sizemax;
	return result;
}

void addEdge(Graph *graph, int v1, int v2, int mode) {
	graph->matrix[v1*graph->sizemax + v2] = 1;
	if ( mode == UNDIRECTED )
		graph->matrix[v2*graph->sizemax + v1] = 1;
}

int adjacent(Graph *graph, int v1, int v2) {
	return graph->matrix[v1*graph->sizemax + v2];
}

int getAdjacentVertices(Graph *graph, int vertex, int *output) {
	int i, cnt = 0;
	output = (int *)malloc(graph->sizemax);

	for (i=0; i<graph->sizemax; ++i)
		if ( graph->matrix[vertex*graph->sizemax + i] )
			output[cnt++] = i;

	return cnt;
}

void dropGraph(Graph *graph) {
	graph->sizemax = 0;
	free(graph->matrix);
}
