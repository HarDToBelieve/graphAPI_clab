#include "graph_jrb.h"
#include "huffman.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *int2bin (int x) {
    char *res = (char *)malloc(64);
    int n = x, cnt = 0;
    while (n) {
        if (n & 1)
            res [cnt++] = '1';
        else res [cnt++] = '0';
        n >>= 1;
    }
    return res;
}

char *int2str (int x) {
    char *res = (char *)malloc (10);
    sprintf (res, "%d", x);
    return res;
}

HuffmanTree *makeHuffmanTree (char *string) {
    HuffmanTree *tree = (HuffmanTree *)malloc (sizeof(HuffmanTree));
    tree->graph = createGraph();
    tree->plain = (char *)malloc (strlen(string));
    strcpy (tree->plain, string);
    tree->cipher = NULL;
    int i;
    for (i=0; i<256; ++i)
        tree->coding[i] = 0;
    for (i=0; i<256; ++i)
        tree->mapping[i] = NULL;
    return tree;
}

void dfs (HuffmanTree *tree, int u, int value, int height) {
    int i;
    JRB *output = (JRB *)malloc (2 * sizeof(JRB));
    int num = getAdjacentVertices (tree->graph, u, output);    
    if ( num == 0 ) {
        char *name = getVertex(tree->graph, tree->mapping, u);
        //printf ("%s ------ %d ----- %s\n", name, value, int2bin(value));
        tree->coding [name[0]] = value;
    }
    else {
        for (i=0; i<num; ++i) {
            JRB v = output[i];
            //printf ("Par: %s, Child: %s, Str Value: %s, Value: %d, height: %d, par val: %d, weight: %d\n", getVertex(tree->graph, tree->mapping, u), getVertex(tree->graph, tree->mapping, jval_i(v->key)), int2bin(value + jval_i(v->val) << (height + 1)), value + jval_i(v->val) << (height + 1), height + 1, value, jval_i(v->val));
            dfs (tree, jval_i(v->key), value + (jval_i(v->val) << (height + 1)), height + 1);
        }
    }
}

void createHuffmanTable (HuffmanTree *tree) {
    int counter[256], i;
    JRB pqueue = make_jrb();

    for (i=0; i<256; ++i)
        counter[i] = 0;
    for (i=0; i<strlen(tree->plain); ++i)
        counter[tree->plain[i]] ++;
    for (i=0; i<256; ++i)
        if ( counter[i] != 0 ) {
            char *name = (char *)malloc (2);
            name[0] = i;
            name[1] = '\0';
            addVertex(tree->graph, tree->mapping, name);
            jrb_insert_int (pqueue, counter[i], new_jval_s(name));
        }
    /*
    JRB tmp;
    jrb_traverse (tmp, pqueue) {
        printf ("%s ", jval_s(tmp->val));
    }
    puts ("");
    */
    while ( getNumofV(pqueue) > 1 ) {
        JRB left = jrb_first(pqueue);
        int left_freq = jval_i(left->key);
        char *left_name = jval_s(left->val);
        jrb_delete_node (left);

        JRB right = jrb_first(pqueue);
        int right_freq = jval_i(right->key);
        char *right_name = jval_s(right->val);
        jrb_delete_node (right);

        int par_freq = left_freq + right_freq;
        char *par_name = (char *)malloc(strlen(left_name) + strlen(right_name) + 1);
        memcpy (par_name, left_name, strlen(left_name));
        memcpy (par_name + strlen(left_name), right_name, strlen(right_name) + 1);
        addVertex (tree->graph, tree->mapping, par_name);
        addEdge (tree->graph, tree->mapping, par_name, left_name, 0, DIRECTED);
        addEdge (tree->graph, tree->mapping, par_name, right_name, 1, DIRECTED);
        jrb_insert_int (pqueue, par_freq, new_jval_s(par_name));
        /*
        JRB tmp;
        jrb_traverse (tmp, pqueue)
            printf ("%s ", jval_s(tmp->val));
        puts ("");
        */
    }
    JRB root = jrb_first(pqueue);
    char *root_name = jval_s(root->val);
    dfs (tree, addVertex(tree->graph, tree->mapping, root_name), 0, -1);
    /*
    for (i=0; i<256; ++i)
        if ( tree->coding[i] != 0 )
            printf ("%c ---- %s\n", i, int2bin(tree->coding[i]));
    */
}

void compress (HuffmanTree *tree) {
    int i;
    for (i=0; i<strlen(tree->plain); ++i) {
        char c = tree->plain[i];
        char *binary = int2bin(tree->coding[c]);
        int old_len;
        if ( tree->cipher == NULL ) 
            old_len = 0;
        else old_len = strlen(tree->cipher);
        tree->cipher = realloc(tree->cipher, old_len + strlen(binary));
        strcat (tree->cipher, binary);
    }
}

char *bin2str (char *s) {
    int cnt = 0, i, index = 0;
    int value = 0;
    char *res = (char *)malloc (strlen(s)/8);
    for (i=0; i<strlen(s); ++i) {
        value += (s[i] - '0') << (cnt++);
        if ( cnt == 8 ) {
            res [index++] = value;
            cnt = 0, value = 0;
        }
    }
    return res;
}