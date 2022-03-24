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
	string* now = new string();
	for (int i = 0; i < length; i++) {
		(*now) += (*chain)[i]->getStr();
		(*now) += " ";
	}
	result[chain_count] = now;
}

void save_chain_reverse(string* result[], int length) {
	string* now = new string();
	for (int i = length - 1; i >= 0; i--) {
		(*now) += (*chain)[i]->getStr();
		(*now) += " ";
	}
	result[chain_count] = now;
}

// job 1


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

// job 1 end

// job 2

int gen_chain_word_unique(char* fileName, string* result[]) {
	// get graph
	Graph* inputGraph, * noSelfLoopGraph;
	handleInput(fileName, &inputGraph, &noSelfLoopGraph);
	// get topo order
	int topo[MAXN_POINT];
	int r = topoSort(noSelfLoopGraph, topo);
	if (r < 0) {
		printf("Error the graph have loop!\n");
	}
	else {
		printf("Ok we don't have loop!\n");
	}
	// dp
	int dp[MAXN_POINT], preEdge[MAXN_POINT];
	memset(dp, 0, SET_SIZE << 2);
	memset(preEdge, 0, SET_SIZE << 2);
	int* first = noSelfLoopGraph->getFirst();
	for (int i = 0; i < SET_SIZE; i++) {
		int x = topo[i];
		for (int e = first[x]; e; e = noSelfLoopGraph->getNext(e)) {
			int to = noSelfLoopGraph->getEdgeEnd(e);
			if (dp[x] + 1 > dp[to]) {
				dp[to] = dp[x] + 1;
				preEdge[to] = e;
			}
		}
	}
	int maxa = 0;
	for (int i = 1; i < SET_SIZE; i++) {
		if (dp[i] > dp[maxa]) {
			maxa = i;
		}
	}
	if (dp[maxa] <= 1) {
		return 0;
	}

	//initial
	chain = new vector<Word*>();
	int length = 0;
	chain_count = 1;

	int now = maxa;
	while (preEdge[now] > 0) {
		int e = preEdge[now];
		int from = noSelfLoopGraph->getEdgeStart(e);
		chain->push_back(noSelfLoopGraph->getEdgeWord(e));
		length++;
		now = from;
	}
	save_chain_reverse(result, length);
	return length;
}