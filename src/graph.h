#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <iostream>
#include <vector>
using namespace std;

class Edges {
private:
	int next;
	int start, end;
	int v;
public:
	Edges() {
		start = end = next = v = 0;
	}
	Edges(int _start, int _end, int _next, int _v) {
		start = _start;
		end = _end;
		next = _next;
		v = _v;
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
};

const int MAXN_POINT = 30;

class Graph {
private:
	int first[MAXN_POINT];
	int in_degree[MAXN_POINT];
	vector <Edges*>* edges;
	int point_cnt, edge_cnt;
public:
	Graph(int _point_cnt) {
		point_cnt = _point_cnt;
		memset(first, 0, point_cnt << 2);
		memset(in_degree, 0, point_cnt << 2);
		edges = new vector<Edges*>();
		edges->push_back(new Edges(0, 0, 0, 0));
		edge_cnt = 0;
	}
	void link(int s, int e, int v) {
		edge_cnt++;
		edges->push_back(new Edges(s, e, first[s], v));
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
	int getEdgeEnd(int e) {
		return (*edges)[e]->getEnd();
	}
	int getEdgeStart(int e) {
		return (*edges)[e]->getStart();
	}
	int getNext(int e) {
		return (*edges)[e]->getNext();
	}
	int getPointCount() {
		return point_cnt;
	}
};

#define SET_SIZE 26

int topoSort(Graph*, int*);
#endif