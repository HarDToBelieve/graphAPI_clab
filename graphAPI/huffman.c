#include "graph_jrb.h"
#include <stdio.h>
#include <stdlib.h>

char *int2bin (int x) {
    char *res = (char *)malloc(10);
    int n = x, cnt = 0;
    while (n) {
        if (n & 1)
            res [cnt++] = 1;
        else res [cnt++] = 0;
        n >>= 1;
    }
    return res;
}

char *