#include "graphAPI/huffman.h"
#include <stdio.h>
#include <stdlib.h>

int main () {
    char *buffer = "Merry Christmas";
    printf ("Data: %s\n", buffer);
    HuffmanTree *tree = makeHuffmanTree(buffer);
    createHuffmanTable (tree);
    compress (tree);
    printf ("Binary data: %s\n", tree->cipher);
    printf ("Compressed data: %s\n", bin2str(tree->cipher));
    return 0;
}