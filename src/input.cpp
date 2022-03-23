#include "input.h"
#include <cstdio>
#include <cstring>
#include "word.h"
#include <iostream>
using namespace std;

Word* word[MAXN_WORD];
int word_count = 0;

int handleInput(char* fileName) {
	FILE* file;
	int r = fopen_s(&file, fileName, "r");
	if (r < 0) {
		return r; //todo
	}
	string s = "";
	char c;
	while ((c = fgetc(file)) != EOF) {
		if (c >= 'A' && c <= 'Z')
			s += char(c - 'A' + 'a');
		else if (c >= 'a' && c <= 'z')
			s += c;
		else if (!s.empty()) {
			word[++word_count] = new Word(s);
			s = "";
		}
	}
	if (!s.empty()) {
		word[++word_count] = new Word(s);
	}
	for (int i = 1; i <= word_count; ++i) {
		word[i]->print();
	}
	return 0;
}