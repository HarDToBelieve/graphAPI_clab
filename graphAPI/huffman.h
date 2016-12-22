#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "../libfdr/dllist.h"
#include "../libfdr/fields.h"
#include "../libfdr/jval.h"
#include "../libfdr/jrb.h"
#include "graph_jrb.h"

typedef struct {
    Graph G;
    JRB pqueue;
    char *plain;
    char *cipher;
    int coding [256];
} HuffmanTree;

char *int2bin (int );
HuffmanTree makeHuffmanTree(char * );
char *concat (char *, char * );
void createHuffmanTable (HuffmanTree );
void compress (HuffmanTree );
void decompress (HuffmanTree );

#endif /* HUFFMAN_H */