#include "input.h"
#include <cstdio>
#include <cstring>
#include "word.h"
#include "graph.h"
#include <iostream>
using namespace std;

Word* word[MAXN_WORD];
int word_count = 0;

static void buildGraph(Graph** graph, Graph** noLoopGraph, Word* wd, int cnt) {
	Graph* graph1, *graph2;
	graph1 = new Graph(SET_SIZE);
	graph2 = new Graph(SET_SIZE);
	for (int i = 1; i <= cnt; i++) {
		int s = word[i]->getBegin(), t = word[i]->getEnd();
		graph1->link(s, t, 1, word[i]);
		if (s != t)
			graph2->link(s, t, 1, word[i]);
	}
	*graph = graph1;
	*noLoopGraph = graph2;
}

int handleInput(char* fileName, Graph** inputGraph, Graph** noSelfLoopGraph) {
	FILE* file;
	int r = fopen_s(&file, fileName, "r");
	if (r < 0) {
		return FILE_NOT_FIND; //todo
	}
	string s = "";
	char c;
	while ((c = fgetc(file)) != EOF) {
		if (c >= 'A' && c <= 'Z')
			s += char(c - 'A' + 'a');
		else if (c >= 'a' && c <= 'z')
			s += c;
		else {
			if ((int)s.size() > 1)
				word[++word_count] = new Word(s);
			s = "";
		}
	}
	if (!s.empty()) {
		word[++word_count] = new Word(s);
	}

	buildGraph(inputGraph, noSelfLoopGraph, word[0], word_count);

	for (int i = 1; i <= word_count; ++i) {
		word[i]->print();
	}
	return 0;
}

