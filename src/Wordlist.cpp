#include <cstdio>
#include <iostream>
#include "input.h"
#include "word.h"
#include "graph.h"

using namespace std;

int main(int argc, char *argv[])
{
    char* name;
    name = (char*)malloc(4);
    while (argc-- > 0) {
        name = *argv++;
        printf("argc:%d, argv:%s\n", argc, name);
    }
    Graph *inputGraph, *noSelfLoopGraph;
    handleInput(name, &inputGraph, &noSelfLoopGraph);
    int topo[MAXN_POINT];
    int r = topoSort(noSelfLoopGraph, topo);
    if (r < 0) {
        printf("Error the graph have loop!\n");
    }
    else {
        printf("Ok we don't have loop!\n");
    }
    return 0;
}