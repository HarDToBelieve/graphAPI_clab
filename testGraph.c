#include "graphAPI/graph_jrb.h"
#include <stdio.h>
#include <stdlib.h>

int main () {
	int u, v;
	Graph G = createGraph();
	char *mapping[100];
	int i, j;
	addVertex (G, mapping, "1");
	addVertex (G, mapping, "2");
	addVertex (G, mapping, "3");
	addVertex (G, mapping, "4");
	addVertex (G, mapping, "5");
	addVertex (G, mapping, "6");
	addVertex (G, mapping, "7");
	addVertex (G, mapping, "8");

	int *matrix[8] = {
		(int []){0, 3, 5, 2, 0, 0, 0, 0},
		(int []){3, 0, 1, 0, 7, 0, 0, 0},
		(int []){5, 1, 0, 4, 0, 1, 0, 0},
		(int []){2, 0, 4, 0, 0, 3, 6, 0},
		(int []){0, 7, 0, 0, 0, 2, 0, 3},
		(int []){0, 0, 1, 3, 2, 0, 4, 6},
		(int []){0, 0, 0, 6, 0, 4, 0, 5},
		(int []){0, 0, 0, 0, 3, 6, 5, 0}
	};
	
	mat2adjl (G, mapping, matrix, 8, UNDIRECTED);
	printf ("Number of vertices: %d\n", getNumofV(G));
	JRB *output = (JRB *)malloc(getNumofV(G) * sizeof(JRB));
	v = 3;
	int num = getAdjacentVertices(G, v, output);
	printf ("Number of adjacent of %s: %d\n", getVertex(G, mapping, v), num);
	for (i=0; i<num; i++)
		printf ("Index: %s\n", getVertex(G, mapping, jval_i(output[i]->key)));
	free (output);
	puts ("Check adjacence (1: true, 0: false):");
	u = 4, v = 0; 
	printf ("%s and %s: %d\n", getVertex(G, mapping, u), getVertex(G, mapping, v), adjacent(G, u, v));
	
	
	char *startName = "4";
	char *endName = "8";

	int numVertices;
	int *trace = (int *)malloc (getNumofV (G) * sizeof(int));
	int start = addVertex (G, mapping, startName);
	int stop = addVertex (G, mapping, endName);
	int shortest_weight_path = dijkstra (G, start, stop, trace, &numVertices);
	printf ("Shortest path from %s to %s: %d\nPath: ", startName, endName, shortest_weight_path);
	for (i=0; i<numVertices; ++i)
		printf ("%s ", getVertex(G, mapping, trace[i]));
	puts ("");
	/*
	if ( isDAG (G) ) {
		puts ("This is a DAG graph");
		output = (int *)malloc(getNumofV(G) * sizeof(int));
		num = toposort (G, output);
		printf ("Topological vertices: ");
		for (i=0; i<num; ++i)
			printf ("%s ", getVertex(G, mapping, output[i]));
		puts ("");
		free (output);
	}
	else
		puts ("This is not a DAG graph");
	*/
	return 0;
}
