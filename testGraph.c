//#include "graphAPI/graph.h"
#include "graphAPI/graph_jrb.h"
#include <stdio.h>
#include <stdlib.h>

int main () {
	int u, v;
	Graph G = createGraph();
	
	addEdge(G, 1, 2);
	addEdge(G, 2, 0);
	addEdge(G, 0, 3);
	addEdge(G, 3, 5);
	addEdge(G, 5, 0);
	addEdge(G, 3, 6);
	addEdge(G, 4, 3);

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
