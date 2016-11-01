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
    bfs (g, 1, -1, printVertex);
    puts("");
    dfs_norecur (g, 1, -1, printVertex);
    puts("");
    int *path = (int *)malloc(getNumofV(g));
    int shortest_path = shortest_noWeight_path(g, 1, 4, path);
    printf ("%d\n", shortest_path);
    int i=0;
    for (i=0; i<shortest_path; ++i)
        printf ("%d ", path[i]);
    puts ("");
    return 0;
}