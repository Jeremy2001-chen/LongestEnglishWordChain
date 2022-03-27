#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <iostream>
#include <vector>
#include "word.h"
using namespace std;

class Edges {
private:
	int next;
	int start, end;
	int v;
	Word* word;
public:
	Edges() {
		start = end = next = v = 0;
		word = NULL;
	}
	Edges(int _start, int _end, int _next, int _v, Word* _word) {
		start = _start;
		end = _end;
		next = _next;
		v = _v;
		word = _word;
	}
	int getStart() {
		return start;
	}
	int getEnd() {
		return end;
	}
	int getValue() {
		return v;
	}
	int getNext() {
		return next;
	}
	Word* getWord() {
		return word;
	}
};

const int MAXN_POINT = 30;

class Graph {
private:
	int first[MAXN_POINT];
	int in_degree[MAXN_POINT];
	vector <Edges*>* edges;
	int point_cnt, edge_cnt;
	// self_loop (no self_loop_graph only)
	int point_weight[MAXN_POINT];
	int point_char_weight[MAXN_POINT];
	int self_edge_first[MAXN_POINT];
public:
	Graph() {
		point_cnt =	0;
		int size = (point_cnt << 2);
		memset(first, 0, size);
		memset(in_degree, 0, size);
		edges = new vector<Edges*>();
		edges->push_back(new Edges(0, 0, 0, 0, NULL));
		edge_cnt = 0;
		memset(point_weight, 0, size);
		memset(point_char_weight, 0, size);
		memset(self_edge_first, 0, size);
	}
	Graph(int _point_cnt) {
		point_cnt = _point_cnt;
		int size = (point_cnt << 2);
		memset(first, 0, size);
		memset(in_degree, 0, size);
		edges = new vector<Edges*>();
		edges->push_back(new Edges(0, 0, 0, 0, NULL));
		edge_cnt = 0;
		memset(point_weight, 0, size);
		memset(point_char_weight, 0, size);
		memset(self_edge_first, 0, size);
	}
	void link(int s, int e, int v, Word * word) {
		edge_cnt++;
		edges->push_back(new Edges(s, e, first[s], v, word));
		//cout << "link : " << s << " " << e << " " << v << endl;
		first[s] = edge_cnt;
		in_degree[e]++;
	}
	int* getInDegree() {
		return in_degree;
	}
	int* getFirst() {
		return first;
	}
	vector<Edges*>* getEdges() {
		return edges;
	}
	int getEdgeCnt() {
		return edge_cnt;
	}
	int getEdgeEnd(int e) {
		return (*edges)[e]->getEnd();
	}
	int getEdgeStart(int e) {
		return (*edges)[e]->getStart();
	}
	int getEdgeValue(int e) {
		return (*edges)[e]->getValue();
	}
	Word* getEdgeWord(int e) {
		return (*edges)[e]->getWord();
	}
	int getNext(int e) {
		return (*edges)[e]->getNext();
	}
	int getPointCount() {
		return point_cnt;
	}
	void addPointWeight(int s, int v, Word * word) {
		point_weight[s]++;
		point_char_weight[s] += word->getLength();
		edge_cnt++;
		edges->push_back(new Edges(s, s, self_edge_first[s], v, word));
		self_edge_first[s] = edge_cnt;
	}
	void setPointWeights(int x, int pw, int pcw) {
		point_weight[x] = pw;
		point_char_weight[x] = pcw;
	}
	int getPointWeight(int x) {
		return point_weight[x];
	}
	int getPointCharWeight(int x) {
		return point_char_weight[x];
	}
	int* getSelfEdgeFirst() {
		return self_edge_first;
	}
};

#define SET_SIZE 26

int topoSort(Graph*, int*);
void getNoLoopGraph(Graph* noSelfLoopGraph, Graph** noLoopGraph, Graph* subGraph, int *subGraphCnt, int* pointColor);
#endif