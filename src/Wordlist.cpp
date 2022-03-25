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
    printf("Running.......\n");
    printf("ready test 1\n");
    int tot = gen_chains_all(name, result);
    printf("%d\n", tot);
    for (int i = 1; i <= tot; i++) {
        cout << (*(result[i])) << endl;
    }
    printf("\n\n\n\n\n");
    printf("ready test 2\n");
    tot = gen_chain_word_unique(name, result);
    printf("%d\n", tot);
    if (tot > 0)
        cout << (*(result[1])) << endl;
    
    printf("\n\n\n\n\n");
    printf("ready test 3\n");
    tot = gen_chain_word(name, result, 0, 0, false);
    printf("%d\n", tot);
    if (tot > 0) {
        cout << (*(result[1])) << endl;
    }
    tot = gen_chain_word(name, result, 'm', 'x', false);
    printf("%d\n", tot);
    if (tot > 0) {
        cout << (*(result[1])) << endl;
    }
    tot = gen_chain_word(name, result, 'm', 0, false);
    printf("%d\n", tot);
    if (tot > 0) {
        cout << (*(result[1])) << endl;
    }
    tot = gen_chain_word(name, result, 0, 'x', false);
    printf("%d\n", tot);
    if (tot > 0) {
        cout << (*(result[1])) << endl;
    }

    printf("\n\n\n\n\n");
    printf("\n\n\n\n\n");
    printf("\n\n\n\n\n");
    printf("ready test 4\n");
    tot = gen_chain_char(name, result, 0, 0, false);
    printf("%d\n", tot);
    if (tot > 0) {
        cout << (*(result[1])) << endl;
    }
    tot = gen_chain_char(name, result, 'm', 'x', false);
    printf("%d\n", tot);
    if (tot > 0) {
        cout << (*(result[1])) << endl;
    }
    tot = gen_chain_char(name, result, 'm', 0, false);
    printf("%d\n", tot);
    if (tot > 0) {
        cout << (*(result[1])) << endl;
    }
    tot = gen_chain_char(name, result, 0, 'x', false);
    printf("%d\n", tot);
    if (tot > 0) {
        cout << (*(result[1])) << endl;
    }

    return 0;
}