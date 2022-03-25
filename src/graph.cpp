#include "graph.h"
#include "error.h"

Graph* inputGraph;

int topoSort(Graph* graph, int* sort) {
	int* tmp = graph->getInDegree(), *first = graph->getFirst();
	int degree[SET_SIZE];
		//, queue[SET_SIZE];
	int head = 0, tail = 0;
	for (int i = 0; i < SET_SIZE; ++i) {
		degree[i] = tmp[i];
	}
	for (int i = 0; i < SET_SIZE; ++i) {
		if (!degree[i]) {
			sort[tail++] = i;
			//cout << i << endl;
		}
	}
	while (head < tail) {
		int pt = sort[head++];
		for (int e = first[pt]; e; e = graph->getNext(e)) {
			int to = graph->getEdgeEnd(e);
			degree[to]--;
			//cout << to << " " << degree[to] << endl;
			if (!degree[to]) {
				sort[tail++] = to;
			}
		}
	}

	int tot = graph->getPointCount();
	//for (int i = 0; i < head; ++i)
	//	cout << queue[i] << " ";
	//cout << endl;
	//cout << head << " " << tail << " " << tot << endl;

	if (tail != tot) {
		return -HAVE_LOOP;
	}

	return 0;
}

// find the scc of the graph
int sccStack[MAXN_POINT], top = 0;
bool sccVisit[MAXN_POINT], sccInStack[MAXN_POINT];
int sccLow[MAXN_POINT], sccDfn[MAXN_POINT], dfsNum = 0, blockNum = 0;
int sccColor[MAXN_POINT];

void tarjan(Graph* graph, int x) {
	sccLow[x] = sccDfn[x] = ++dfsNum;
	sccStack[++top] = x;
	sccVisit[x] = sccInStack[x] = true;
	for (int e = graph->getFirst()[x]; e; e = graph->getNext(e)) {
		int to = graph->getEdgeEnd(e);
		if (!sccVisit[to]) {
			tarjan(graph, to);
			sccLow[x] = min(sccLow[x], sccLow[to]);
		}
		else if (sccInStack[x]) {
			sccLow[x] = min(sccLow[x], sccDfn[to]);
		}
	}
	int topPoint;
	do {
		topPoint = sccStack[top--];
		sccInStack[topPoint] = false;
		sccColor[topPoint] = blockNum;
	} while (topPoint != x);
	blockNum++;
}


void getNoLoopGraph(Graph* noSelfLoopGraph, Graph** noLoopGraph, Graph* subGraph[], int* subGraphCnt, int* pointColor[]){
	//printf("No Loop Graph is building!\n");
	int originPointCnt = noSelfLoopGraph->getPointCount();
	memset(sccVisit, 0, (originPointCnt + 1) << 2);
	dfsNum = blockNum = 0;
	for (int i = 0; i < originPointCnt; i++) {
		if (!sccVisit[i]) {
			top = 0;
			tarjan(noSelfLoopGraph, i);
		}
	}
	for (int i = 0; i < originPointCnt; i++) {
		(*pointColor)[i] = sccColor[i];
	}
	for (int i = 0; i < blockNum; i++) {
		(*subGraph)[i] = Graph(originPointCnt);
	}
	Graph* crossGraph = new Graph(blockNum);
	for (int i = 0; i < originPointCnt; i++) {
		for (int e = noSelfLoopGraph->getFirst()[i]; e; e = noSelfLoopGraph->getNext(e)) {
			int to = noSelfLoopGraph->getEdgeEnd(e);
			if (sccColor[i] != sccColor[to]) {
				crossGraph->link(sccColor[i], sccColor[to], noSelfLoopGraph->getEdgeValue(e), noSelfLoopGraph->getEdgeWord(e));
			}
			else {
				(*subGraph)[sccColor[i]]->link(i, to, noSelfLoopGraph->getEdgeValue(e), noSelfLoopGraph->getEdgeWord(e));
			}
		}
	}
	noLoopGraph = &crossGraph;
	(*subGraphCnt) = blockNum;
}