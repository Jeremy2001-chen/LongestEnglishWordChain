#include "graph.h"
#include "error.h"

Graph* inputGraph;

int topoSort(Graph* graph, int* sort) {
	int* tmp = graph->getInDegree(), *first = graph->getFirst();
	int degree[SET_SIZE], queue[SET_SIZE];
	int head = 0, tail = 0;
	for (int i = 0; i < SET_SIZE; ++i) {
		degree[i] = tmp[i];
	}
	for (int i = 0; i < SET_SIZE; ++i) {
		if (!degree[i]) {
			queue[tail++] = i;
			//cout << i << endl;
		}
	}
	while (head < tail) {
		int pt = queue[head++];
		for (int e = first[pt]; e; e = graph->getNext(e)) {
			int to = graph->getEdgeEnd(e);
			degree[to]--;
			//cout << to << " " << degree[to] << endl;
			if (!degree[to]) {
				queue[tail++] = to;
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