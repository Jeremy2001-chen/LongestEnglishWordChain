#include <cstdio>
#include <iostream>
#include <cstdlib>
#include "input.h"
#include "word.h"
#include "graph.h"
#include "gens.h"

using namespace std;

const int MAXN = 1e6 + 10;

string* result[MAXN];

int main(int argc, char *argv[])
{
    char* name;
    name = (char*)malloc(4);
    while (argc-- > 0) {
        name = *argv++;
        printf("argc:%d, argv:%s\n", argc, name);
    }
    /*Graph* inputGraph, * noSelfLoopGraph;
    handleInput(name, &inputGraph, &noSelfLoopGraph);
    int topo[MAXN_POINT];
    int r = topoSort(noSelfLoopGraph, topo);
    if (r < 0) {
        printf("Error the graph have loop!\n");
    }
    else {
        printf("Ok we don't have loop!\n");
    }*/
    printf("ready test 1\n");
    int tot = gen_chains_all(name, result);
    printf("%d\n", tot);
    for (int i = 1; i <= tot; i++) {
        cout << (*(result[i])) << endl;
    }
    return 0;
}