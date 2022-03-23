#ifndef _WORD_H_
#define _WORD_H_

#include <cstring>
#include <cstdlib>
#include <iostream>
using namespace std;

const int MAXN_WORD = 10101;

class Word {
private:
	string str;
	char begin, end;
	int length;
public:
	Word() {}
	Word(string s) {
		str = std::move(s);
		length = str.length();
		begin = str[0];
		end = str[length - 1];
	}

	void print() {
		cout << str << endl;
	}
};

extern Word* word[MAXN_WORD];
extern int word_count;

#endif