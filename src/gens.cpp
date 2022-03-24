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
// end job 2
// job 3

int gen_chain_word_loop(char* fileName, string* result[], char head, char tail) {
	return 0;
}

int gen_chain_word_loopless(char* fileName, string* result[], char head, char tail) {
	// get graph
	//printf("getting graph...\n");
	Graph* inputGraph, * noSelfLoopGraph;
	handleInput(fileName, &inputGraph, &noSelfLoopGraph);
	// get topo order
	//printf("getting topo order...\n");
	int topo[MAXN_POINT];
	int r = topoSort(noSelfLoopGraph, topo);
	if (r < 0) {
		printf("Error the graph have loop!\n");
	}
	else {
		printf("Ok we don't have loop!\n");
	}
	// get start points
	int dp[MAXN_POINT], preEdge[MAXN_POINT];
	if (head == 0) {
		for (int i = 0; i < SET_SIZE; i++) {
			dp[i] = noSelfLoopGraph->getPointWeight(i);
		}
	} else {
		memset(dp, 255, SET_SIZE << 2);
		int x = head - 'a';
		dp[x] = noSelfLoopGraph->getPointWeight(x);
	}
	// dp
	memset(preEdge, 0, SET_SIZE << 2);
	int* first = noSelfLoopGraph->getFirst();
	for (int i = 0; i < SET_SIZE; i++) {
		int x = topo[i];
		if (dp[x] < 0)
			continue;
		for (int e = first[x]; e; e = noSelfLoopGraph->getNext(e)) {
			int to = noSelfLoopGraph->getEdgeEnd(e);
			int to_weight = noSelfLoopGraph->getPointWeight(to);
			if (dp[x] + 1 +  to_weight > dp[to]) {
				dp[to] = dp[x] + 1 + to_weight;
				preEdge[to] = e;
			}
		}
	}

	// get end points
	int maxa = 0;
	if (tail == 0) {
		for (int i = 1; i < SET_SIZE; i++) {
			if (dp[i] > dp[maxa]) {
				maxa = i;
			}
		}
	}
	else {
		maxa = tail - 'a';
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
		int now_weight = noSelfLoopGraph->getPointWeight(now);
		if (now > 0) {
			int* first = noSelfLoopGraph->getSelfEdgeFirst();
			for (int e = first[now]; e; e = noSelfLoopGraph->getNext(e)) {
				chain->push_back(noSelfLoopGraph->getEdgeWord(e));
			}
		}
		int from = noSelfLoopGraph->getEdgeStart(e);
		chain->push_back(noSelfLoopGraph->getEdgeWord(e));
		length++;
		now = from;
	}
	save_chain_reverse(result, length);
	return length;
}

int gen_chain_word(char* fileName, string* result[], char head, char tail, bool enable_loop) {
	if (enable_loop) {
		return gen_chain_word_loop(fileName, result, head, tail);
	}
	else {
		return gen_chain_word_loopless(fileName, result, head, tail);
	}
}
// end job 3
// job 4
int gen_chain_char_loop(char* fileName, string* result[], char head, char tail) {
	return 0;
}

int gen_chain_char_loopless(char* fileName, string* result[], char head, char tail) {
	// get graph
	//printf("getting graph...\n");
	Graph* inputGraph, * noSelfLoopGraph;
	handleInput(fileName, &inputGraph, &noSelfLoopGraph);
	// get topo order
	//printf("getting topo order...\n");
	int topo[MAXN_POINT];
	int r = topoSort(noSelfLoopGraph, topo);
	if (r < 0) {
		printf("Error the graph have loop!\n");
	}
	else {
		printf("Ok we don't have loop!\n");
	}
	// get start points
	int dp[MAXN_POINT], preEdge[MAXN_POINT], dpCnt[MAXN_POINT];
	if (head == 0) {
		for (int i = 0; i < SET_SIZE; i++) {
			dp[i] = noSelfLoopGraph->getPointCharWeight(i);
			dpCnt[i] = noSelfLoopGraph->getPointWeight(i);
		}
	}
	else {
		memset(dp, 255, SET_SIZE << 2);
		memset(dpCnt, 255, SET_SIZE << 2);
		int x = head - 'a';
		dp[x] = noSelfLoopGraph->getPointCharWeight(x);
		dpCnt[x] = noSelfLoopGraph->getPointWeight(x);
	}
	// dp
	memset(preEdge, 0, SET_SIZE << 2);
	int* first = noSelfLoopGraph->getFirst();
	for (int i = 0; i < SET_SIZE; i++) {
		int x = topo[i];
		if (dp[x] < 0)
			continue;
		for (int e = first[x]; e; e = noSelfLoopGraph->getNext(e)) {
			int to = noSelfLoopGraph->getEdgeEnd(e);
			int v = noSelfLoopGraph->getEdgeValue(e);
			int to_weight = noSelfLoopGraph->getPointCharWeight(to);
			if (dp[x] + v + to_weight > dp[to]) {
				dp[to] = dp[x] + v + to_weight;
				dpCnt[to] = dpCnt[x] + 1 + noSelfLoopGraph->getPointWeight(to);
				preEdge[to] = e;
			}
		}
	}

	// get end points
	int maxa = 0;
	if (tail == 0) {
		for (int i = 1; i < SET_SIZE; i++) {
			if (dp[i] > dp[maxa] && dpCnt[i] >= 2) {
				maxa = i;
			}
		}
	}
	else {
		maxa = tail - 'a';
	}
	// it's special to judge the size >= 2
	if (dpCnt[maxa] <= 1) {
		return 0;
	}
	//initial
	chain = new vector<Word*>();
	int length = 0;
	chain_count = 1;

	int now = maxa;
	while (preEdge[now] > 0) {
		int e = preEdge[now];
		int now_weight = noSelfLoopGraph->getPointWeight(now);
		if (now > 0) {
			int* first = noSelfLoopGraph->getSelfEdgeFirst();
			for (int e = first[now]; e; e = noSelfLoopGraph->getNext(e)) {
				chain->push_back(noSelfLoopGraph->getEdgeWord(e));
			}
		}
		int from = noSelfLoopGraph->getEdgeStart(e);
		chain->push_back(noSelfLoopGraph->getEdgeWord(e));
		length++;
		now = from;
	}
	save_chain_reverse(result, length);
	return length;
}
int gen_chain_char(char* fileName, string* result[], char head, char tail, bool enable_loop) {
	if (enable_loop) {
		return gen_chain_char_loop(fileName, result, head, tail);
	}
	else {
		return gen_chain_char_loopless(fileName, result, head, tail);
	}
}
// end job 4