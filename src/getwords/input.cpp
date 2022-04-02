#include "pch.h"
#include "input.h"
#include <cstdio>
#include <cstring>
#include <iostream>
#include <set>
#include "error.h"

using namespace std;

set <string> wordSet;

int handleInput(char* fileName, char* word[], int* len){
	FILE* file;
	int r = fopen_s(&file, fileName, "r");
	if (file == NULL) {
		cerr << "单词表所在文件不存在！" << endl;
		return -FILE_NOT_FIND; //todo
	}
	else {
		string s = "";
		char c;
		int wordCount = 0;
		wordSet.clear();
		while ((c = fgetc(file)) != EOF) {
			if (c >= 'A' && c <= 'Z')
				s += char(c - 'A' + 'a');
			else if (c >= 'a' && c <= 'z')
				s += c;
			else {
				if ((int)s.size() > 1) {
					if (wordSet.find(s) == wordSet.end()) {
						char* tmp = (char*)malloc(s.length() + 1);
						if (tmp != NULL) {
							char* str = tmp;
							for (int i = 0; i < s.length(); i++) {
								(*str++) = s[i];
							}
							(*str) = '\0';
							word[++wordCount] = tmp;
							wordSet.insert(s);
						}
					}
				}
				s = "";
			}
		}
		if ((int)s.size() > 1 && wordSet.find(s) == wordSet.end()) {
			char* tmp = (char*)malloc(s.length() + 1);
			if (tmp != NULL) {
				char* str = tmp;
				for (int i = 0; i < s.length(); i++) {
					(*str++) = s[i];
				}
				(*str) = '\0';
				word[++wordCount] = tmp;
			}
		}
		(* len) = wordCount;
		//buildGraph(inputGraph, noSelfLoopGraph, word[0], word_count);

		/*for (int i = 1; i <= word_count; ++i) {
			word[i]->print();
		}
		printf("\n");
		*/
	}
	return 0;
}

