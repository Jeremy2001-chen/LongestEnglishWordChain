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

IMPORT_DLL int gen_chains_all(char* words[], int len, char* result[]);
IMPORT_DLL int gen_chain_word_unique(char* words[], int len, char* result[]);
IMPORT_DLL int gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop);
IMPORT_DLL int gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop);

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace wordtest
{

	char* words[20000];
	char* result[20000];
	TEST_CLASS(wordtest)
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

		void output(char* path, int ans, char* result[], int len) {
			FILE* file;
			fopen_s(&file, path, "w");

			fprintf(file, "%d\n", len);
			for (int i = 1; i <= len; ++i) {
				fprintf(file, "%s\n", result[i]);
			}
			fclose(file);
		}

		TEST_METHOD(TestGenWordUniqNo0)
		{
			char filename[100] = "../test/input.txt";

			int len = 0;
			int r = handleInput(filename, words, &len);

			char path[100] = "../test/output.txt";

			int ans = gen_chain_word_unique(words, len, result);

			output(path, ans, result, (ans > 0));

			Assert::AreEqual(ans, -1);

		}

		TEST_METHOD(TestGenWordUniqNo1)
		{

			char filename[100] = "../test/input1.txt";

			int len = 0;
			int r = handleInput(filename, words, &len);

			char path[100] = "../test/output.txt";

			int ans = gen_chain_word_unique(words, len, result);

			output(path, ans, result, (ans > 0));

			Assert::AreEqual(ans, -1);

		}

		TEST_METHOD(TestGenWordUniqNo2)
		{

			char filename[100] = "../test/input2.txt";

			int len = 0;
			int r = handleInput(filename, words, &len);

			char path[100] = "../test/output.txt";

			int ans = gen_chain_word_unique(words, len, result);

			output(path, ans, result, (ans > 0));

			Assert::AreEqual(ans, -1);

		}

		TEST_METHOD(TestGenWordUniqNo3)
		{

			char filename[100] = "../test/input3.txt";

			int len = 0;
			int r = handleInput(filename, words, &len);

			char path[100] = "../test/output.txt";

			int ans = gen_chain_word_unique(words, len, result);

			output(path, ans, result, (ans > 0));

			Assert::AreEqual(ans, 3);

		}

		TEST_METHOD(TestGenWordUniqNo4)
		{

			char filename[100] = "../test/input4.txt";

			int len = 0;
			int r = handleInput(filename, words, &len);

			char path[100] = "../test/output.txt";

			int ans = gen_chain_word_unique(words, len, result);

			output(path, ans, result, (ans > 0));

			Assert::AreEqual(ans, -1);

		}

		TEST_METHOD(TestGenWordUniqNo5)
		{

			char filename[100] = "../test/input5.txt";

			int len = 0;
			int r = handleInput(filename, words, &len);

			char path[100] = "../test/output.txt";

			int ans = gen_chain_word_unique(words, len, result);

			output(path, ans, result, (ans > 0));

			Assert::AreEqual(ans, 2);

		}
	};
}
