#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "graphAPI/graph_jrb.h"

char *genName (int x) {
    char *tmp = (char *)malloc (10);
    sprintf (tmp, "%d", x);
    return tmp;
}

char** str_split(char* a_str, const char a_delim)
{
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    while (*tmp) {
        if (a_delim == *tmp) {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }
    count += last_comma < (a_str + strlen(a_str) - 1);
    count++;
    result = malloc(sizeof(char*) * count);
    if (result) {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);
        while (token) {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }
    return result;
}

int main () {
    freopen ("input", "r", stdin);

    Graph G = createGraph();
    char *mapping [100];

    int V; scanf ("%d\n", &V);
    int i;
    
    for (i=0; i<V; ++i) {
        addVertex (G, mapping, genName(i + 1));
    }
    
    int E = 0;
    for (i=0; i<V; ++i) {
        char buf[100];
        fgets (buf, 100, stdin);
        if ( buf[strlen(buf) - 1] == 10 )
            buf[strlen(buf) - 1] = 0;
        char **tokens = str_split (buf, ' ');
        if ( tokens ) {
            for (i = 1; *(tokens + i); i++) {
                addEdge (G, mapping, *(tokens + i), *tokens, 0, DIRECTED);
                E ++;
                free(*(tokens + i));
            }
            free (tokens);
        }
    }

    printf ("So mon hoc: %d\n",V);
    printf ("So cung: %d\n", E);

    if ( isDAG(G) ) puts ("Khong co chu trinh");
    else {
        puts ("Co chu trinh");
        return 0;
    }

    char *tmp = "4";
    int pos = -1;
    for (i=0; i<V; ++i)
        if ( !strcmp(mapping[i], tmp) ) {
            pos = i;
            break;
        }
    if ( pos == -1 ) puts ("Khong ton tai");
    else {
        int *output = (int *)malloc (V * sizeof(int));
        memset (output, 0, getNumofV(G) * sizeof(int));
        int numTemp = indegree (G, pos, output);
        printf ("So mon hoc phai hoc truoc mon %s la: %d\n", tmp, numTemp);
        printf ("Cac mon hoc truoc mon %s la: ", tmp);
        for (i=0; i<numTemp; ++i)
            printf ("%s ", getVertex(G, mapping, output[i]));
        puts ("");
        free (output);
    }

    int list [V][V];
    int numInd [V];
    int j, max = 0;
    for (i=0; i<V; ++i) {
        numInd[i] = 0;
        for (j=0; j<V; ++j)
            list [i][j] = 0;
    }
    for (i=0; i<V; ++i) {
        int num = indegree (G, i, NULL);
        list [num][numInd[num]] = i;
        numInd[num] ++;
        max = max < num ? num : max;
    }
    puts ("Danh sach cac mon hoc: ");
    for (i=0; i<=max; ++i) {
        for (j=0; j<numInd[i]; ++j)
            printf ("%s ", getVertex(G, mapping, list[i][j]));
        puts ("");
    }
    
    int *outTopo = (int *)malloc(getNumofV(G) * sizeof(int));
    memset (outTopo, 0, getNumofV(G) * sizeof(int));
    int numTopo = toposort (G, outTopo);
    puts ("Thu tu cac mon hoc: ");
    for (i=0; i<numTopo; ++i)
    	printf ("%s ", getVertex(G, mapping, outTopo[i]));
    puts ("");
    free (outTopo);
}