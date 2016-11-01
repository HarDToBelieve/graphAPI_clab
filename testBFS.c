#include "graphAPI/graph_jrb.h"
#include <stdio.h>
#include <stdlib.h>

void printVertex(int v) { printf ("%d ", v); }

int main () {
    Graph g = createGraph();
    addEdge(g, 0, 1);
    addEdge(g, 1, 2);
    addEdge(g, 1, 3);
    addEdge(g, 2, 3);
    addEdge(g, 2, 4);
    addEdge(g, 4, 5);
    bfs (g, 1, 4, printVertex);
    puts("");
    dfs (g, 1, 4, printVertex);
    return 0;
}