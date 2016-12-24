#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "../libfdr/dllist.h"
#include "../libfdr/fields.h"
#include "../libfdr/jval.h"
#include "../libfdr/jrb.h"
#include "graph_jrb.h"

struct HuffmanTree {
    Graph graph;
    char *plain;
    char *cipher;
    int coding [256];
    char *mapping [1000];
} ;

typedef struct HuffmanTree HuffmanTree;
char *int2bin (int );
char *int2str (int );
char *bin2str (char *);
HuffmanTree* makeHuffmanTree(char * );
void createHuffmanTable (HuffmanTree* );
void compress (HuffmanTree* );
void dfs (HuffmanTree* , int, int, int);

#endif /* HUFFMAN_H */