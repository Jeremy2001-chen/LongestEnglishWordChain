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

char* words[2000];
char* result[2000];

namespace coretest
{
	TEST_CLASS(coretest)
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

		// char wordlist[20][20] = { "aaa", "aba", "aca", "ab", "ba", "bb" };

		// char *words[20] = { wordlist[0], wordlist[1], wordlist[2], wordlist[3], wordlist[4], wordlist[5]};
		// int len = 6;


		TEST_METHOD(TestGenWordNNT)
		{
			
			char filename[100] = "E:/softengine/LongestEnglishWordChain/test/input.txt";
			
			int len = 0;
			int r = handleInput(filename, words, &len);

			char path[100] = "E:/softengine/LongestEnglishWordChain/test/output.txt";
			
			int ans = gen_chain_word(words, len, result, 0, 0, true);

			output(path, ans, result, (ans > 0));

			Assert::AreEqual(ans, 14);

		}

		TEST_METHOD(TestGenWordFNT)
		{

			char filename[100] = "E:/softengine/LongestEnglishWordChain/test/input.txt";

			int len = 0;
			int r = handleInput(filename, words, &len);

			char path[100] = "E:/softengine/LongestEnglishWordChain/test/output.txt";

			int ans = gen_chain_word(words, len, result, 'f', 0, true);

			output(path, ans, result, (ans > 0));

			Assert::AreEqual(ans, 8);

		}

		TEST_METHOD(TestGenWordNFT)
		{

			char filename[100] = "E:/softengine/LongestEnglishWordChain/test/input.txt";

			int len = 0;
			int r = handleInput(filename, words, &len);

			char path[100] = "E:/softengine/LongestEnglishWordChain/test/output.txt";

			int ans = gen_chain_word(words, len, result, 0, 'f', true);

			output(path, ans, result, (ans > 0));

			Assert::AreEqual(ans, 12);

		}
		TEST_METHOD(TestGenCharNNT)
		{

			char filename[100] = "E:/softengine/LongestEnglishWordChain/test/input.txt";

			int len = 0;
			int r = handleInput(filename, words, &len);

			char path[100] = "E:/softengine/LongestEnglishWordChain/test/output.txt";

			int ans = gen_chain_char(words, len, result, 0, 0, true);

			output(path, ans, result, (ans > 0));

			Assert::AreEqual(ans, 8);

		}
		TEST_METHOD(TestGenCharNFT)
		{

			char filename[100] = "E:/softengine/LongestEnglishWordChain/test/input.txt";

			int len = 0;
			int r = handleInput(filename, words, &len);

			char path[100] = "E:/softengine/LongestEnglishWordChain/test/output.txt";

			int ans = gen_chain_char(words, len, result, 0, 'f', true);

			output(path, ans, result, (ans > 0));

			Assert::AreEqual(ans, 12);

		}
		TEST_METHOD(TestGenCharFNT)
		{

			char filename[100] = "E:/softengine/LongestEnglishWordChain/test/input.txt";

			int len = 0;
			int r = handleInput(filename, words, &len);

			char path[100] = "E:/softengine/LongestEnglishWordChain/test/output.txt";

			int ans = gen_chain_char(words, len, result, 'f', 0, true);

			output(path, ans, result, (ans > 0));

			Assert::AreEqual(ans, 8);

		}
		TEST_METHOD(TestGenCharNNF)
		{

			char filename[100] = "E:/softengine/LongestEnglishWordChain/test/input3.txt";

			int len = 0;
			int r = handleInput(filename, words, &len);


			char path[100] = "E:/softengine/LongestEnglishWordChain/test/output.txt";
			//output(path, len, words, len);

			int ans = gen_chain_char(words, len, result, 0, 0, false);

			output(path, ans, result, (ans > 0));

			Assert::AreEqual(ans, 3);

		}
		TEST_METHOD(TestGenCharNFF)
		{

			char filename[100] = "E:/softengine/LongestEnglishWordChain/test/input3.txt";

			int len = 0;
			int r = handleInput(filename, words, &len);

			char path[100] = "E:/softengine/LongestEnglishWordChain/test/output.txt";

			int ans = gen_chain_char(words, len, result, 0, 'm', false);

			output(path, ans, result, (ans > 0));

			Assert::AreEqual(ans, 2); 

		}
		TEST_METHOD(TestGenCharFNF)
		{

			char filename[100] = "E:/softengine/LongestEnglishWordChain/test/input3.txt";

			int len = 0;
			int r = handleInput(filename, words, &len);

			char path[100] = "E:/softengine/LongestEnglishWordChain/test/output.txt";

			int ans = gen_chain_char(words, len, result, 'p', 0, false);

			output(path, ans, result, (ans > 0));

			Assert::AreEqual(ans, 3);

		}
		TEST_METHOD(TestGenWordNNF)
		{

			char filename[100] = "E:/softengine/LongestEnglishWordChain/test/input3.txt";

			int len = 0;
			int r = handleInput(filename, words, &len);


			char path[100] = "E:/softengine/LongestEnglishWordChain/test/output.txt";
			//output(path, len, words, len);

			int ans = gen_chain_word(words, len, result, 0, 0, false);

			output(path, ans, result, (ans > 0));

			Assert::AreEqual(ans, 4);

		}
		TEST_METHOD(TestGenWordNFF)
		{

			char filename[100] = "E:/softengine/LongestEnglishWordChain/test/input3.txt";

			int len = 0;
			int r = handleInput(filename, words, &len);

			char path[100] = "E:/softengine/LongestEnglishWordChain/test/output.txt";

			int ans = gen_chain_word(words, len, result, 0, 'm', false);

			output(path, ans, result, (ans > 0));

			Assert::AreEqual(ans, 2);

		}
		TEST_METHOD(TestGenWordFNF)
		{

			char filename[100] = "E:/softengine/LongestEnglishWordChain/test/input3.txt";

			int len = 0;
			int r = handleInput(filename, words, &len);

			char path[100] = "E:/softengine/LongestEnglishWordChain/test/output.txt";

			int ans = gen_chain_word(words, len, result, 'p', 0, false);

			output(path, ans, result, (ans > 0));

			Assert::AreEqual(ans, 3);

		}
		TEST_METHOD(TestGenWordUniq)
		{

			char filename[100] = "E:/softengine/LongestEnglishWordChain/test/input3.txt";

			int len = 0;
			int r = handleInput(filename, words, &len);

			char path[100] = "E:/softengine/LongestEnglishWordChain/test/output.txt";

			int ans = gen_chain_word_unique(words, len, result);

			output(path, ans, result, (ans > 0));

			Assert::AreEqual(ans, 3);

		}
		TEST_METHOD(TestGenAll)
		{

			char filename[100] = "E:/softengine/LongestEnglishWordChain/test/input3.txt";

			int len = 0;
			int r = handleInput(filename, words, &len);

			char path[100] = "E:/softengine/LongestEnglishWordChain/test/output.txt";

			int ans = gen_chains_all(words, len, result);

			output(path, ans, result, (ans > 0));

			Assert::AreEqual(ans, 12);

		}
	};
}
