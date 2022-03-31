#include "pch.h"
#include "CppUnitTest.h"
#include <cstdio>
#include <cstring>
#include <iostream>
#include <set>
#include <fstream>

#ifdef IMPORT_DLL
#else
#define IMPORT_DLL extern "C" _declspec(dllimport)
#endif

IMPORT_DLL void output(char* path, int ans, char* result[], int len);

char* words[2000];
char* result[2000];

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace outputtest
{
	TEST_CLASS(outputtest)
	{
	public:

		std::set <std::string> wordSet;

		int handleInput(char* fileName, char* word[], int* len) {
			FILE* file;
			int r = fopen_s(&file, fileName, "r");
			if (file == NULL) {
				return -1;
			}
			else {
				std::string s = "";
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
				(*len) = wordCount;
			}
			return 0;
		}
		TEST_METHOD(TestMethod1)
		{
			char filename[100] = "E:/softengine/LongestEnglishWordChain/test/input.txt";

			int len = 0;
			int r = handleInput(filename, words, &len);

			char path[200] = "E:/softengine/LongestEnglishWordChain/test/";

			int ans = 2;
			//char* result[20] = {"ab", "bc"};
			output(path, len, words, len);
		}

		TEST_METHOD(TestRepeat)
		{
			char filename[100] = "E:/softengine/LongestEnglishWordChain/test/input1.txt";

			int len = 0;
			int r = handleInput(filename, words, &len);

			char path[200] = "E:/softengine/LongestEnglishWordChain/test/";

			int ans = 2;
			//char* result[20] = {"ab", "bc"};
			output(path, len, words, len);
		}

		TEST_METHOD(TestDisturbing)
		{
			char filename[100] = "E:/softengine/LongestEnglishWordChain/test/input12.txt";

			int len = 0;
			int r = handleInput(filename, words, &len);

			char path[200] = "E:/softengine/LongestEnglishWordChain/test/";

			int ans = 2;
			//char* result[20] = {"ab", "bc"};
			output(path, len, words, len);
		}
	};
}
