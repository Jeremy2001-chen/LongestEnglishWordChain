#include <cstdio>
#include <iostream>
#include <cstdlib>
#include "input.h"
#include "word.h"
#include "graph.h"
#include "gens.h"
#include "parameter.h"

using namespace std;

const int MAXN = 1e6 + 10;

string* result[MAXN];

int main(int argc, char *argv[])
{
    int problemType, start, end;
    bool loop_enable;
    char* name;
    int r = parameterExtract(argv, argc, problemType, loop_enable, start, end, &name);
    if (r < 0) {
        exit(1);
    }
    int tot;
    switch (problemType) {
    case WORD_CHAIN_COUNT_PROBLEM:
        tot = gen_chains_all(name, result);
        cout << tot << endl;
        for (int i = 1; i <= tot; i++) {
            cout << (*(result[i])) << endl;
        }
        break;
    case FIRST_CHAR_NOT_SAME_PROBLEM:
        tot = gen_chain_word_unique(name, result);
        cout << tot << endl;
        if (tot > 0)
            cout << (*(result[1])) << endl;
        break;
    case WORD_CHAIN_MAX_WORD_PROBLEM:
        tot = gen_chain_word(name, result, start, end, loop_enable);
        cout << tot << endl;
        if (tot > 0) {
            cout << (*(result[1])) << endl;
        }
        break;
    case WORD_CHAIN_MAX_CHAR_PROBLEM:
        tot = gen_chain_char(name, result, start, end, loop_enable);
        cout << tot << endl;
        if (tot > 0) {
            cout << (*(result[1])) << endl;
        }
        break;
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
    /*
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
    tot = gen_chain_word(name, result, 0, 0, true);
    printf("%d\n", tot);
    if (tot > 0) {
        cout << (*(result[1])) << endl;
    }
    tot = gen_chain_word(name, result, 'm', 'x', true);
    printf("%d\n", tot);
    if (tot > 0) {
        cout << (*(result[1])) << endl;
    }
    tot = gen_chain_word(name, result, 'm', 0, true);
    printf("%d\n", tot);
    if (tot > 0) {
        cout << (*(result[1])) << endl;
    }
    tot = gen_chain_word(name, result, 0, 'x', true);
    printf("%d\n", tot);
    if (tot > 0) {
        cout << (*(result[1])) << endl;
    }

    printf("\n\n\n\n\n");
    printf("\n\n\n\n\n");
    printf("\n\n\n\n\n");
    printf("ready test 4\n");
    tot = gen_chain_char(name, result, 0, 0, true);
    printf("%d\n", tot);
    if (tot > 0) {
        cout << (*(result[1])) << endl;
    }
    tot = gen_chain_char(name, result, 'm', 'x', true);
    printf("%d\n", tot);
    if (tot > 0) {
        cout << (*(result[1])) << endl;
    }
    tot = gen_chain_char(name, result, 'm', 0, true);
    printf("%d\n", tot);
    if (tot > 0) {
        cout << (*(result[1])) << endl;
    }
    tot = gen_chain_char(name, result, 0, 'x', true);
    printf("%d\n", tot);
    if (tot > 0) {
        cout << (*(result[1])) << endl;
    }
    */
    return 0;
}