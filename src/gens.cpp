#include<cstdio>
#include<cstdlib>
#include<cstring>
#include "input.h"
#include "graph.h"
#include "word.h"
#include "chain.h"
#include "gens.h"

int chain_count = 0;

vector<Word*>* chain;

int vist[MAXN_WORD];

void save_chain(string* result[], int length) {
	string *now = new string();
	for (int i = 0; i < length; i++) {
		(*now) += (*chain)[i]->getStr();
		(*now) += " ";
	}
	result[chain_count] = now;
}

void dfs_chain(int x, Graph* graph, int length, string* result[]) {
	int* first = graph->getFirst();
	for (int e = first[x]; e; e = graph->getNext(e)) {
		int to = graph->getEdgeEnd(e);
		if (!vist[to]) {
			vist[to] = 1;
			chain->push_back(graph->getEdgeWord(e));
			if (length > 0) {
				chain_count++;
				save_chain(result, length + 1);
			}
			dfs_chain(to, graph, length + 1, result);
			chain->pop_back();
			vist[to] = 0;
		}
	}
}

//int gen_chains_all(Word* word[], int len, char* result[]) {
int gen_chains_all(char* fileName, string* result[]) {
	Graph* inputGraph, * noSelfLoopGraph;
	handleInput(fileName, &inputGraph, &noSelfLoopGraph);

	int topo[MAXN_POINT];
	int r = topoSort(noSelfLoopGraph, topo);
	if (r < 0) {
		printf("Error the graph have loop!\n");
	}
	else {
		printf("Ok we don't have loop!\n");
	}

	//initial
	chain = new vector<Word*>();
	chain_count = 0;

	//start from every point
	for (int i = 0; i < SET_SIZE; i++) {
		memset(vist, 0, word_count << 2);
		dfs_chain(i, inputGraph, 0, result);
	}

	return chain_count;
}