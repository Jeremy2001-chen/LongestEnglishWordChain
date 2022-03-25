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
		if (!vist[e]) {
			vist[e] = 1;
			chain->push_back(graph->getEdgeWord(e));
			if (length > 0) {
				chain_count++;
				save_chain(result, length + 1);
			}
			dfs_chain(to, graph, length + 1, result);
			chain->pop_back();
			vist[e] = 0;
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
		memset(vist, 0, (word_count + 1) << 2);
		dfs_chain(i, inputGraph, 0, result);
	}

	return chain_count;
}

// job 1 end

// job 2

int gen_chain_word_unique(char* fileName, string* result[]) {
	// get graph
	Graph* inputGraph, *noSelfLoopGraph;
	handleInput(fileName, &inputGraph, &noSelfLoopGraph);
	// get topo order
	int topo[MAXN_POINT];
	int r = topoSort(noSelfLoopGraph, topo);
	if (r < 0) {
		printf("Error the graph have loop!\n");
		return r;
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
int max_cnt;

int subGraphMaxDist[MAXN_POINT][MAXN_POINT]; 
// distance between two point in one sub graph,
//including value of edges and endpoint, not including start point

void get_sub_graph_self_chain(Graph* graph, int x, vector<Word*> * subChain) {
	int* first = graph->getSelfEdgeFirst();
	for (int e = first[x]; e; e = graph->getNext(e)) {
		subChain->push_back(graph->getEdgeWord(e));
	}
}

void get_sub_graph_chain_char(Graph* graph, int x, int end, int length, vector<Word*>* subChain) { // length is needed
	if (length == 0) {
		return;
	}
	int* first = graph->getFirst();
	for (int e = first[x]; e; e = graph->getNext(e)) {
		int to = graph->getEdgeEnd(e);
		if (!vist[e]) {
			vist[e] = 1;
			int to_weight = graph->getPointWeight(to);
			if (length == subGraphMaxDist[to][end]) {
				subChain->push_back(graph->getEdgeWord(e));
				get_sub_graph_self_chain(graph, to, subChain);
				get_sub_graph_chain_char(graph, to, end, length - 1 - to_weight, subChain);
			}
			vist[e] = 0;
		}
	}
}

void dfs_sub_graph_max_dist_char(Graph* graph, int start, int x, int length) {
	int* first = graph->getFirst();
	for (int e = first[x]; e; e = graph->getNext(e)) {
		int to = graph->getEdgeEnd(e);
		cout << "!!!!! : " << to << endl;
		if (!vist[e]) {
			vist[e] = 1;
			int to_weight = graph->getPointWeight(to);
			cout << "dfs : " << start << " " << to << " " << to_weight << endl;

			subGraphMaxDist[start][to] = max(subGraphMaxDist[start][to], length + 1 + to_weight);
			dfs_sub_graph_max_dist_char(graph, start, to, length + 1 + to_weight);
			vist[e] = 0;
		}
	}
}

void get_sub_graph_max_dist_char(Graph* subLoopGraph, int subGraphCnt, int* pointColor) {
	memset(subGraphMaxDist, 255, sizeof(subGraphMaxDist));
	for (int i = 0; i < subGraphCnt; i++)
		subGraphMaxDist[i][i] = 0;
	for (int i = 0; i < subGraphCnt; i++) {
		for (int j = 0; j < SET_SIZE; j++) {
			if (pointColor[j] == i) {
				int edge_cnt = subLoopGraph[i].getEdgeCnt();
				int to_weight = subLoopGraph[i].getPointWeight(j);
				cout << &subLoopGraph[i] << " " << j << " " << i << " " << edge_cnt << endl;
				memset(vist, 0, SET_SIZE << 2);
				dfs_sub_graph_max_dist_char(&subLoopGraph[i], j, j, 0);
			}
		}
	}
}

int gen_chain_word_loop(char* fileName, string* result[], char head, char tail) {
	// get graph
	//printf("getting graph...\n");
	Graph* inputGraph, * noSelfLoopGraph;
	handleInput(fileName, &inputGraph, &noSelfLoopGraph);
	// get loopless graph
	Graph* noLoopGraph;
	Graph subLoopGraph[MAXN_POINT];
	int subGraphCnt;
	int pointColor[MAXN_POINT];
	getNoLoopGraph(noSelfLoopGraph, &noLoopGraph, subLoopGraph, &subGraphCnt, pointColor);
	// get topo order
	cout << noLoopGraph->getPointCount() << endl;
	printf("getting topo order...\n");
	//printf("%x\n", noLoopGraph);
	int topo[MAXN_POINT];
	int r = topoSort(noLoopGraph, topo);
	if (r < 0) {
		printf("Error the graph have loop!\n");
	}
	else {
		printf("Ok we don't have loop!\n");
	}
	//get sub graph max dist
	get_sub_graph_max_dist_char(subLoopGraph, subGraphCnt, pointColor);
	// get start points
	int dp[MAXN_POINT], preEdge[MAXN_POINT], preGraph[MAXN_POINT], prePoint[MAXN_POINT]; //dp[id of subgraph][id of endpoint]
	int weight[MAXN_POINT]; //record the self loop weight
	for (int i = 0; i < SET_SIZE; i++) {
		weight[i] = noSelfLoopGraph->getPointWeight(i);
	}
	memset(dp, 255, sizeof(dp));
	
	if (head == 0) {
		for (int i = 0; i < SET_SIZE; i++) { // every point is ready in itself sub graph
			dp[i] = weight[i];
		}
	}
	else {
		int x = head - 'a';
		dp[x] = weight[x];
	}
	// dp
	memset(preEdge, 0, sizeof(preEdge));
	memset(prePoint, 255, sizeof(prePoint));
	memset(preGraph, 255, sizeof(preGraph));
	// for preGraph, 0 to subGraphCnt - 1 means subGraph, subGraphCnt means noLoopGraph
	int* first = noLoopGraph->getFirst();
	//printf("Now check count: %d\n", subGraphCnt);
	for (int i = 0; i < SET_SIZE; i++)
		cout << pointColor[i] << " ";
	cout << endl;
	for (int i = 0; i < subGraphCnt; i++) {
		int x = topo[i];
		//cout << "Now in block : " << x << endl;
		// inside subGraph
		int gp[MAXN_POINT], gpPoint[MAXN_POINT];
		memset(gp, 255, SET_SIZE << 2);
		memset(gpPoint, 255, SET_SIZE << 2);
		for (int j = 0; j < SET_SIZE; j++) {
			if (pointColor[j] == x) {
				if (dp[j] < 0)
					continue;
				cout << j << "wait: " << subGraphMaxDist[12][13] << endl;
				for (int k = 0; k < SET_SIZE; k++) {
					if (pointColor[k] == x) {
						int to_weight = subLoopGraph[i].getPointWeight(k);
						if (dp[j] + subGraphMaxDist[j][k] > gp[k]) { // never use 
							gp[k] = dp[j] + subGraphMaxDist[j][k];
							gpPoint[k] = j;
						}
					}
				}
			}
		}
		for (int j = 0; j < SET_SIZE; j++) {
			if (dp[j] < gp[j]) {
				dp[j] = gp[j];
				preGraph[j] = x;
				prePoint[j] = gpPoint[j];
			}
		}
		// outside graph
		for (int e = first[x]; e; e = noLoopGraph->getNext(e)) {
			Word* tmp = noLoopGraph->getEdgeWord(e);
			int st = tmp->getBegin(), ed = tmp->getEnd();
			if (dp[st] < 0)
				continue;
			int to_weight = noLoopGraph->getPointWeight(ed);
			if (dp[ed] < dp[st] + 1 + to_weight) {
				dp[ed] = dp[st] + 1 + to_weight;
				preGraph[ed] = subGraphCnt;
				preEdge[ed] = e;
			}
		}
	}

	// get end points
	int maxa = 0;
	if (tail == 0) {
		for (int i = 0; i < SET_SIZE; i++) {
			if (dp[i] > dp[maxa]) {
				maxa = i;
			}
		}
	}
	else {
		maxa = tail - 'a';
	}

	if (dp[maxa] <= 1) {
		return 0; //todo
	}
	//initial
	chain = new vector<Word*>();
	int length = 0;
	chain_count = 1;

	int now = maxa;
	while (preEdge[now] > 0) {
		if (preGraph[now] == subGraphCnt) {
			int e = preEdge[now];
			int now_weight = noLoopGraph->getPointWeight(now);
			if (now > 0) {
				int* first = noLoopGraph->getSelfEdgeFirst();
				for (int e = first[now]; e; e = noLoopGraph->getNext(e)) {
					chain->push_back(noLoopGraph->getEdgeWord(e));
				}
			}
			int from = noLoopGraph->getEdgeStart(e);
			chain->push_back(noLoopGraph->getEdgeWord(e));
			length++;
			now = from;
		}
		else {
			int from = prePoint[now];
			int col = pointColor[from];
			vector<Word*>* subChain = new vector<Word*>();
			get_sub_graph_chain_char(&subLoopGraph[col], from, now, subGraphMaxDist[from][now], subChain);
			for (int i = 0; i < subChain->size(); i++) {
				chain->push_back((*subChain)[i]);
			}
			now = from;
		}
	}
	if (now > 0) {
		int* first = noLoopGraph->getSelfEdgeFirst();
		for (int e = first[now]; e; e = noLoopGraph->getNext(e)) {
			chain->push_back(noLoopGraph->getEdgeWord(e));
		}
	}
	save_chain_reverse(result, length);
	return length;
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
		return r;
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
	if (now > 0) {
		int* first = noSelfLoopGraph->getSelfEdgeFirst();
		for (int e = first[now]; e; e = noSelfLoopGraph->getNext(e)) {
			chain->push_back(noSelfLoopGraph->getEdgeWord(e));
		}
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
		return r;
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
	if (now > 0) {
		int* first = noSelfLoopGraph->getSelfEdgeFirst();
		for (int e = first[now]; e; e = noSelfLoopGraph->getNext(e)) {
			chain->push_back(noSelfLoopGraph->getEdgeWord(e));
		}
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