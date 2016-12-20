//#include "graphAPI/graph.h"
#include "graphAPI/graph_jrb.h"
#include <stdio.h>
#include <stdlib.h>

#define UNDIRECTED 1

int main () {
	int u, v;
	Graph G = createGraph();
	
	addEdge(G, 1, 2, UNDIRECTED);
	addEdge(G, 2, 0, UNDIRECTED);
	addEdge(G, 0, 3, UNDIRECTED);
	addEdge(G, 3, 5, UNDIRECTED);
	addEdge(G, 5, 0, UNDIRECTED);
	addEdge(G, 3, 6, UNDIRECTED);
	addEdge(G, 4, 3, UNDIRECTED);

	printf ("Number of vertices: %d\n", getNumofV(G));

	int *output = (int *)malloc(100);
	v = 3;
	int num = getAdjacentVertices(G, v, output);
	printf ("Number of adjacent of %d: %d\n", v, num);
	int i;
	for (i=0; i<num; i++)
		printf ("Index: %d\n", output[i]);

	puts ("Check adjacence (1: true, 2: false):");
	u = 0, v = 5; 
	printf ("%d and %d: %d\n",u, v, adjacent(G, u, v));

	puts ("Graph dropped");
	dropGraph(G); 
	return 0;
}
