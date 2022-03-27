#ifndef _CHAIN_H_
#define _CHAIN_H_

#include <cstring>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "word.h"
using namespace std;

class Chain {
private:
	int length;
	vector<Word*>* words;
public:
	Chain() {
		length = 0;
		words = new vector<Word*>();
	}
	void append(Word* word) {
		words->push_back(word);
		length += 1;
	}
	void print() {
		for (int i = 0; i < length; i++) {
			(*words)[i]->print();
		}
		printf("\n");
	}
};

#endif