//#include "graphAPI/graph.h"
#include "graphAPI/graph_jrb.h"
#include <stdio.h>
#include <stdlib.h>

int main () {
	int u, v;
	Graph G = createGraph();
	
	/* ------------------------------------ UNDIRECTED GRAPH ------------------------------------------ */

	/*
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
	*/

	/* ------------------------------------- DIRECTED GRAPH --------------------------------------------- */
	char *mapping[10];
	addVertex (G, mapping, "terminal1");
	addVertex (G, mapping, "terminal2");
	addVertex (G, mapping, "terminal3");
	addVertex (G, mapping, "terminal4");
	addVertex (G, mapping, "terminal5");
	addVertex (G, mapping, "terminal6");
	addVertex (G, mapping, "terminal7");
	return 0;
}
