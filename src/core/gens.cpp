#include "pch.h"
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include "graph.h"
#include "word.h"
#include "gens.h"


int chain_count = 0;

vector<Word*>* chain;

int vist[MAXN_WORD];

void save_chain(char* result[], int length) {
	int totLen = 0;
	for (int i = 0; i < length; i++) {
		totLen += strlen((*chain)[i]->getStr());
	}
	char* now = (char*)malloc(static_cast<size_t>((size_t)totLen + length));
	if (now != NULL) {
		char* str = now;
		for (int i = 0; i < length; i++) {
			char* ch = (*chain)[i]->getStr();
			for (char* c = ch; *c; c++) {
				(*str++) = (*c);
			}
			if (i != length - 1) {
				(*str++) = ' ';
			}
		}
		(*str) = '\0';
		result[chain_count] = now;
	}
}

void save_chain_reverse(char* result[], int length) {
	int totLen = 0;
	for (int i = length-1; i >= 0; i--) {
		totLen += strlen((*chain)[i]->getStr());
	}
	char* now = (char*)malloc(static_cast<size_t>((size_t)totLen + length));
	if (now != NULL) {
		char* str = now;
		for (int i = length-1; i >= 0; i--) {
			char* ch = (*chain)[i]->getStr();
			for (char* c = ch; *c; c++) {
				(*str++) = (*c);
			}
			if (i != 0) {
				(*str++) = ' ';
			}
		}
		(*str) = '\0';
		result[chain_count] = now;
	}
}

// job 1


void dfs_chain(int x, Graph* graph, int length, char* result[]) {
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
int gen_chains_all(char* words[], int len, char* result[]) {
	Graph* inputGraph, * noSelfLoopGraph;
	buildGraph(&inputGraph, &noSelfLoopGraph, words, len);

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
		int size = (len + 1) << 2;
		memset(vist, 0, size);
		dfs_chain(i, inputGraph, 0, result);
	}

	return chain_count;
}

// job 1 end

// job 2

int gen_chain_word_unique(char* words[], int len, char* result[]) {
	// get graph
	Graph* inputGraph, *noSelfLoopGraph;
	buildGraph(&inputGraph, &noSelfLoopGraph, words, len);

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

	// only destinantion can have selfloop
	for (int i = 0; i < 26; i++) {
		int i_weight = noSelfLoopGraph->getPointWeight(i);
		if (i_weight > 0) {
			dp[i] += 1;
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
	// self loop for destination
	int now_weight = noSelfLoopGraph->getPointWeight(now);
	if (now_weight > 0) {
		int* first = noSelfLoopGraph->getSelfEdgeFirst();
		int e = first[now];
		chain->push_back(noSelfLoopGraph->getEdgeWord(e));
		length++;
	}

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

Word* wordList[20202];
int pointVistCnt[MAXN_POINT];
int wordCnt = 0;
bool get_sub_graph_chain_word(Graph* graph, int x, int end, int length, vector<Word*>* subChain) { // length is needed
	//cout << "x = " << x << " length = " << length  << " end  = " << end << endl;
	if (length == 0) {
		for (int i = 1; i <= wordCnt; i++) {
			subChain->push_back(wordList[i]);
		}
		return 1;
	}
	pointVistCnt[x]++;
	int* first = graph->getFirst();
	for (int e = first[x]; e; e = graph->getNext(e)) {
		int to = graph->getEdgeEnd(e);
		if (!vist[e]) {
			vist[e] = 1;
			int lastCnt = wordCnt;
			wordList[++wordCnt] = graph->getEdgeWord(e);
			int to_weight = 0;
			if (pointVistCnt[to] > 0) {
				to_weight = 0;
			} 
			else { 
				to_weight = graph->getPointWeight(to); 
				int* selfFirst = graph->getSelfEdgeFirst();
				for (int e = selfFirst[to]; e; e = graph->getNext(e)) {
					wordList[++wordCnt] = graph->getEdgeWord(e);
				}
				// cout << "to = " << to << " to_weight = " << to_weight << endl;
			}
			if (get_sub_graph_chain_word(graph, to, end, length - 1 - to_weight, subChain)) {
				return 1;
			}
			wordCnt = lastCnt;
			vist[e] = 0;
		}
	}
	pointVistCnt[x]--;
	return 0;
}

void dfs_sub_graph_max_dist_word(Graph* graph, int start, int x, int length) {
	pointVistCnt[x]++;
	int* first = graph->getFirst();
	for (int e = first[x]; e; e = graph->getNext(e)) {
		int to = graph->getEdgeEnd(e);
		if (!vist[e]) {
			vist[e] = 1;
			int to_weight = 0;
			if (pointVistCnt[to] > 0) {
				to_weight = 0;
			}
			else {
				to_weight = graph->getPointWeight(to);
			}

			subGraphMaxDist[start][to] = max(subGraphMaxDist[start][to], length + 1 + to_weight);
			dfs_sub_graph_max_dist_word(graph, start, to, length + 1 + to_weight);
			vist[e] = 0;
		}
	}
	pointVistCnt[x]--;
}

void get_sub_graph_max_dist_word(Graph* subLoopGraph, int subGraphCnt, int* pointColor) {
	memset(subGraphMaxDist, 255, sizeof(subGraphMaxDist));
	for (int i = 0; i < subGraphCnt; i++)
		subGraphMaxDist[i][i] = 0;
	for (int i = 0; i < subGraphCnt; i++) {
		for (int j = 0; j < SET_SIZE; j++) {
			if (pointColor[j] == i) {
				int edge_cnt = subLoopGraph[i].getEdgeCnt();
				int to_weight = subLoopGraph[i].getPointWeight(j);
				memset(vist, 0, SET_SIZE << 2);
				memset(pointVistCnt, 0, SET_SIZE << 2);
				dfs_sub_graph_max_dist_word(&subLoopGraph[i], j, j, 0);
			}
		}
	}
}

Graph subLoopGraph[MAXN_POINT];

void gen_chain_word_dp_loop(int dp[], char head, int weight[], int preEdge[], int preSCCPoint[], 
	Graph * noLoopGraph, Graph subLoopGraph[], int subGraphCnt, int topo[], int pointColor[]) {

	memset(dp, 255, sizeof(dp));

	if (head == 0) {
		for (int i = 0; i < SET_SIZE; i++) { // every point is ready in itself sub graph
			dp[i] = weight[i];
		}
	}
	else {
		int x = head - 'a';
		//cout << head << " " << x << endl;
		dp[x] = weight[x];
	}
	// dp
	memset(preEdge, 0, sizeof(preEdge));
	memset(preSCCPoint, 255, sizeof(preSCCPoint));

	// for preGraph, 0 to subGraphCnt - 1 means subGraph, subGraphCnt means noLoopGraph
	int* first = noLoopGraph->getFirst();


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
				for (int k = 0; k < SET_SIZE; k++) {
					if (pointColor[k] == x) {
						int to_weight = subLoopGraph[i].getPointWeight(k);
						if (dp[j] + subGraphMaxDist[j][k] > gp[k]) {
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
				preSCCPoint[j] = gpPoint[j];
			}
		}
		// outside graph
		for (int e = first[x]; e; e = noLoopGraph->getNext(e)) {
			Word* tmp = noLoopGraph->getEdgeWord(e);
			int st = tmp->getBegin(), ed = tmp->getEnd();
			if (dp[st] < 0)
				continue;
			int to_weight = subLoopGraph[pointColor[ed]].getPointWeight(ed);
			if (dp[ed] < dp[st] + 1 + to_weight) {
				dp[ed] = dp[st] + 1 + to_weight;
				preEdge[ed] = e;
			}
		}
	}
}

int gen_chain_word_result_loop(int now, int preEdge[], int preSCCPoint[], int pointColor[],
	Graph subLoopGraph[], Graph *noLoopGraph) {
	chain = new vector<Word*>();
	int length = 0;
	chain_count = 1;

	bool inSCC = false;
	while (preEdge[now] > 0 || !inSCC && preSCCPoint[now] >= 0) {
		// cout << "now = " << now << " preSCC = " << preSCCPoint[now] << "  preEdge = " << preEdge[now] << endl;
		if (!inSCC && preSCCPoint[now] >= 0) {
			inSCC = true;
			int from = preSCCPoint[now];
			int col = pointColor[from];
			vector<Word*>* subChain = new vector<Word*>();
			wordCnt = 0;
			memset(vist, 0, sizeof(vist));
			memset(pointVistCnt, 0, SET_SIZE << 2);
			int r = get_sub_graph_chain_word(&subLoopGraph[col], from, now, subGraphMaxDist[from][now], subChain);
			if (!r) {
				//system("pause");
				exit(1);
			}
			//cout << (*subChain).size() << endl;
			for (int i = (*subChain).size() - 1; i >= 0; i--) {
				chain->push_back((*subChain)[i]);
				length++;
			}
			now = from;
		}
		else {
			inSCC = false;
			int e = preEdge[now];
			int now_weight = subLoopGraph[pointColor[now]].getPointWeight(now);
			if (now_weight > 0) {
				int* first = subLoopGraph[pointColor[now]].getSelfEdgeFirst();
				for (int e = first[now]; e; e = subLoopGraph[pointColor[now]].getNext(e)) {
					chain->push_back(subLoopGraph[pointColor[now]].getEdgeWord(e));
					length++;
				}
			}
			Word* tmp = noLoopGraph->getEdgeWord(e);
			int from = tmp->getBegin();
			// cout << " from = " << from << endl;
			chain->push_back(noLoopGraph->getEdgeWord(e));
			length++;
			now = from;
		}
		//cout << "Now: " << now << endl;
	}
	if (subLoopGraph[pointColor[now]].getPointWeight(now) > 0) {
		int* first = subLoopGraph[pointColor[now]].getSelfEdgeFirst();
		for (int e = first[now]; e; e = subLoopGraph[pointColor[now]].getNext(e)) {
			chain->push_back(subLoopGraph[pointColor[now]].getEdgeWord(e));
			length++;
		}
	}
	return length;
}

int gen_chain_word_loop(char* words[], int len, char* result[], char head, char tail) {
	// get graph
	//printf("getting graph...\n");
	Graph* inputGraph, * noSelfLoopGraph;
	buildGraph(&inputGraph, &noSelfLoopGraph, words, len);

	// get loopless graph
	Graph* noLoopGraph;

	int subGraphCnt;
	int pointColor[MAXN_POINT];
	getNoLoopGraph(noSelfLoopGraph, &noLoopGraph, subLoopGraph, &subGraphCnt, pointColor);
	// get topo order
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
	get_sub_graph_max_dist_word(subLoopGraph, subGraphCnt, pointColor);
	// get start points
	int dp[MAXN_POINT], preEdge[MAXN_POINT], preSCCPoint[MAXN_POINT]; //dp[id of subgraph][id of endpoint]
	int weight[MAXN_POINT]; //record the self loop weight
	for (int i = 0; i < SET_SIZE; i++) {
		weight[i] = noSelfLoopGraph->getPointWeight(i);
	}

	gen_chain_word_dp_loop(dp, head, weight, preEdge, preSCCPoint,
		noLoopGraph, subLoopGraph, subGraphCnt, topo, pointColor);

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

	cout << "Max len: " << dp[maxa] << endl;

	//initial
	int length = gen_chain_word_result_loop(maxa, preEdge, preSCCPoint, pointColor, subLoopGraph, noLoopGraph);

	save_chain_reverse(result, length);
	return length;
}

int gen_chain_word_loopless(char* words[], int len, char* result[], char head, char tail) {
	// get graph
	//printf("getting graph...\n");
	Graph* inputGraph, * noSelfLoopGraph;
	buildGraph(&inputGraph, &noSelfLoopGraph, words, len);
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
		if (now_weight > 0) {
			int* first = noSelfLoopGraph->getSelfEdgeFirst();
			for (int e = first[now]; e; e = noSelfLoopGraph->getNext(e)) {
				chain->push_back(noSelfLoopGraph->getEdgeWord(e));
				length++;
			}
		}
		int from = noSelfLoopGraph->getEdgeStart(e);
		chain->push_back(noSelfLoopGraph->getEdgeWord(e));
		length++;
		now = from;
	}
	int now_weight = noSelfLoopGraph->getPointWeight(now);
	if (now_weight > 0) {
		int* first = noSelfLoopGraph->getSelfEdgeFirst();
		for (int e = first[now]; e; e = noSelfLoopGraph->getNext(e)) {
			chain->push_back(noSelfLoopGraph->getEdgeWord(e));
			length++;
		}
	}
	save_chain_reverse(result, length);
	return length;
}

int gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop) {
	if (enable_loop) {
		return gen_chain_word_loop(words, len, result, head, tail);
	}
	else {
		return gen_chain_word_loopless(words, len, result, head, tail);
	}
}

// end job 3
// job 4
bool get_sub_graph_chain_char(Graph* graph, int x, int end, int length, vector<Word*>* subChain) { // length is needed
	//cout << "x = " << x << " length = " << length  << " end  = " << end << endl;
	if (length == 0) {
		for (int i = 1; i <= wordCnt; i++) {
			subChain->push_back(wordList[i]);
		}
		return 1;
	}
	pointVistCnt[x]++;
	int* first = graph->getFirst();
	for (int e = first[x]; e; e = graph->getNext(e)) {
		int to = graph->getEdgeEnd(e);
		if (!vist[e]) {
			vist[e] = 1;
			int lastCnt = wordCnt;
			wordList[++wordCnt] = graph->getEdgeWord(e);
			int to_weight = 0;
			if (pointVistCnt[to] > 0) {
				to_weight = 0;
			}
			else {
				to_weight = graph->getPointCharWeight(to);
				int* selfFirst = graph->getSelfEdgeFirst();
				for (int e = selfFirst[to]; e; e = graph->getNext(e)) {
					wordList[++wordCnt] = graph->getEdgeWord(e);
				}
				// cout << "to = " << to << " to_weight = " << to_weight << endl;
			}
			int v = graph->getEdgeValue(e);
			if (get_sub_graph_chain_char(graph, to, end, length - v - to_weight, subChain)) {
				return 1;
			}
			wordCnt = lastCnt;
			vist[e] = 0;
		}
	}
	pointVistCnt[x]--;
	return 0;
}

void dfs_sub_graph_max_dist_char(Graph* graph, int start, int x, int length) {
	pointVistCnt[x]++;
	int* first = graph->getFirst();
	for (int e = first[x]; e; e = graph->getNext(e)) {
		int to = graph->getEdgeEnd(e);
		if (!vist[e]) {
			vist[e] = 1;
			int to_weight = 0;
			if (pointVistCnt[to] > 0) {
				to_weight = 0;
			}
			else {
				to_weight = graph->getPointCharWeight(to);
			}
			int v = graph->getEdgeValue(e);
			subGraphMaxDist[start][to] = max(subGraphMaxDist[start][to], length + v + to_weight);
			dfs_sub_graph_max_dist_char(graph, start, to, length + v + to_weight);
			vist[e] = 0;
		}
	}
	pointVistCnt[x]--;
}

void get_sub_graph_max_dist_char(Graph* subLoopGraph, int subGraphCnt, int* pointColor) {
	memset(subGraphMaxDist, 255, sizeof(subGraphMaxDist));
	for (int i = 0; i < subGraphCnt; i++)
		subGraphMaxDist[i][i] = 0;
	for (int i = 0; i < subGraphCnt; i++) {
		for (int j = 0; j < SET_SIZE; j++) {
			if (pointColor[j] == i) {
				int edge_cnt = subLoopGraph[i].getEdgeCnt();
				int to_weight = subLoopGraph[i].getPointCharWeight(j);
				memset(vist, 0, SET_SIZE << 2);
				memset(pointVistCnt, 0, SET_SIZE << 2);
				dfs_sub_graph_max_dist_char(&subLoopGraph[i], j, j, 0);
			}
		}
	}
}

void gen_chain_char_dp_loop(int dp[], char head, int weight[], int preEdge[], int preSCCPoint[],
	Graph* noLoopGraph, Graph subLoopGraph[], int subGraphCnt, int topo[], int pointColor[]) {
	memset(dp, 255, sizeof(dp));

	if (head == 0) {
		for (int i = 0; i < SET_SIZE; i++) { // every point is ready in itself sub graph
			dp[i] = weight[i];
		}
	}
	else {
		int x = head - 'a';
		//cout << head << " " << x << endl;
		dp[x] = weight[x];
	}
	// dp
	memset(preEdge, 0, sizeof(preEdge));
	memset(preSCCPoint, 255, sizeof(preSCCPoint));

	// for preGraph, 0 to subGraphCnt - 1 means subGraph, subGraphCnt means noLoopGraph
	int* first = noLoopGraph->getFirst();
	//printf("Now check count: %d\n", subGraphCnt);

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
				for (int k = 0; k < SET_SIZE; k++) {
					if (pointColor[k] == x) {
						int to_weight = subLoopGraph[i].getPointCharWeight(k);
						if (dp[j] + subGraphMaxDist[j][k] > gp[k]) {
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
				preSCCPoint[j] = gpPoint[j];
			}
		}
		// outside graph
		for (int e = first[x]; e; e = noLoopGraph->getNext(e)) {
			Word* tmp = noLoopGraph->getEdgeWord(e);
			int st = tmp->getBegin(), ed = tmp->getEnd();
			if (dp[st] < 0)
				continue;
			int to_weight = subLoopGraph[pointColor[ed]].getPointCharWeight(ed);
			int v = noLoopGraph->getEdgeValue(e);
			if (dp[ed] < dp[st] + v + to_weight) {
				dp[ed] = dp[st] + v + to_weight;
				preEdge[ed] = e;
			}
		}
	}
}

int gen_chain_char_result_loop(int now, int preEdge[], int preSCCPoint[], int pointColor[],
	Graph subLoopGraph[], Graph* noLoopGraph) {
	chain = new vector<Word*>();
	int length = 0;
	chain_count = 1;

	bool inSCC = false;
	while (preEdge[now] > 0 || !inSCC && preSCCPoint[now] >= 0) {
		// cout << "now = " << now << " preSCC = " << preSCCPoint[now] << "  preEdge = " << preEdge[now] << endl;
		if (!inSCC && preSCCPoint[now] >= 0) {
			inSCC = true;
			int from = preSCCPoint[now];
			int col = pointColor[from];
			vector<Word*>* subChain = new vector<Word*>();
			wordCnt = 0;
			memset(vist, 0, sizeof(vist));
			memset(pointVistCnt, 0, SET_SIZE << 2);
			int r = get_sub_graph_chain_char(&subLoopGraph[col], from, now, subGraphMaxDist[from][now], subChain);
			if (!r) {
				//system("pause");
				exit(1);
			}
			//cout << (*subChain).size() << endl;
			for (int i = (*subChain).size() - 1; i >= 0; i--) {
				chain->push_back((*subChain)[i]);
				length++;
			}
			now = from;
		}
		else {
			inSCC = false;
			int e = preEdge[now];
			int now_weight = subLoopGraph[pointColor[now]].getPointCharWeight(now);
			if (now_weight > 0) {
				int* first = subLoopGraph[pointColor[now]].getSelfEdgeFirst();
				for (int e = first[now]; e; e = subLoopGraph[pointColor[now]].getNext(e)) {
					chain->push_back(subLoopGraph[pointColor[now]].getEdgeWord(e));
					length++;
				}
			}
			Word* tmp = noLoopGraph->getEdgeWord(e);
			int from = tmp->getBegin();
			// cout << " from = " << from << endl;
			chain->push_back(noLoopGraph->getEdgeWord(e));
			length++;
			now = from;
		}
		//cout << "Now: " << now << endl;
	}
	if (subLoopGraph[pointColor[now]].getPointCharWeight(now) > 0) {
		int* first = subLoopGraph[pointColor[now]].getSelfEdgeFirst();
		for (int e = first[now]; e; e = subLoopGraph[pointColor[now]].getNext(e)) {
			chain->push_back(subLoopGraph[pointColor[now]].getEdgeWord(e));
			length++;
		}
	}
	return length;
}

int gen_chain_char_loop(char* words[], int len, char* result[], char head, char tail) {
	// get graph
	//printf("getting graph...\n");
	Graph* inputGraph, * noSelfLoopGraph;
	buildGraph(&inputGraph, &noSelfLoopGraph, words, len);

	// delete useless edges, incase of the misleading of single long word
	Graph* tmpGraph;
	getNewNoSelfLoopGraph(noSelfLoopGraph, &tmpGraph);
	noSelfLoopGraph = tmpGraph;

	// get loopless graph
	Graph* noLoopGraph;
	int subGraphCnt;
	int pointColor[MAXN_POINT];

	getNoLoopGraph(noSelfLoopGraph, &noLoopGraph, subLoopGraph, &subGraphCnt, pointColor);
	// get topo order
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
	int dp[MAXN_POINT], preEdge[MAXN_POINT], preSCCPoint[MAXN_POINT]; //dp[id of subgraph][id of endpoint]
	int weight[MAXN_POINT]; //record the self loop weight
	for (int i = 0; i < SET_SIZE; i++) {
		weight[i] = noSelfLoopGraph->getPointCharWeight(i);
	}
	
	gen_chain_char_dp_loop(dp, head, weight, preEdge, preSCCPoint,
		noLoopGraph, subLoopGraph, subGraphCnt, topo, pointColor);


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

	cout << "Max len: " << dp[maxa] << endl;

	//initial
	int length = gen_chain_char_result_loop(maxa, preEdge, preSCCPoint, pointColor, subLoopGraph, noLoopGraph);
	save_chain_reverse(result, length);
	return length;
}

int gen_chain_char_loopless(char* words[], int len, char* result[], char head, char tail) {
	// get graph
	//printf("getting graph...\n");
	Graph* inputGraph, * noSelfLoopGraph;
	buildGraph(&inputGraph, &noSelfLoopGraph, words, len);

	// delete useless edges, incase of the misleading of single long word
	Graph* tmpGraph;
	getNewNoSelfLoopGraph(noSelfLoopGraph, &tmpGraph);
	noSelfLoopGraph = tmpGraph;

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
		if (now_weight > 0) {
			int* first = noSelfLoopGraph->getSelfEdgeFirst();
			for (int e = first[now]; e; e = noSelfLoopGraph->getNext(e)) {
				chain->push_back(noSelfLoopGraph->getEdgeWord(e));
				length++;
			}
		}
		int from = noSelfLoopGraph->getEdgeStart(e);
		chain->push_back(noSelfLoopGraph->getEdgeWord(e));
		length++;
		now = from;
	}
	int now_weight = noSelfLoopGraph->getPointWeight(now);
	if (now_weight > 0) {
		int* first = noSelfLoopGraph->getSelfEdgeFirst();
		for (int e = first[now]; e; e = noSelfLoopGraph->getNext(e)) {
			chain->push_back(noSelfLoopGraph->getEdgeWord(e));
			length++;
		}
	}
	save_chain_reverse(result, length);
	return length;
}

int gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop) {
	if (enable_loop) {
		return gen_chain_char_loop(words, len, result, head, tail);
	}
	else {
		return gen_chain_char_loopless(words, len, result, head, tail);
	}
}
// end job 4