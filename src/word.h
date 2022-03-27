#ifndef _WORD_H_
#define _WORD_H_

#include <cstring>
#include <cstdlib>
#include <iostream>
#include "error.h"
using namespace std;

const int MAXN_WORD = 10101;

class Word {
private:
	string str;
	int begin, end;
	int length;
public:
	Word() {
		str = "";
		begin = end = length = 0;
	}
	Word(string s) {
		str = std::move(s);
		length = str.length();
		begin = (int)str[0] - (int)'a';
		end = (int)str[(size_t)length - 1] - (int)'a';
	}
	void print() {
		cout << str << " ";
	}
	int getBegin() {
		return begin;
	}
	int getEnd() {
		return end;
	}
	int getLength() {
		return length;
	}
	string getStr() {
		return str;
	}
};

extern Word* word[MAXN_WORD];
extern int word_count;

#endif