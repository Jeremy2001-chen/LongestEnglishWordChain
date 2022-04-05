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

			if (file) {
				fprintf(file, "%d\n", len);
				for (int i = 1; i <= len; ++i) {
					fprintf(file, "%s\n", result[i]);
				}
				fclose(file);
			}
		}

		void gen_word_nnf(char filename[], int std_ans) {
			int len = 0;
			int r = handleInput(filename, words, &len);


			char path[100] = "../test/output.txt";
			//output(path, len, words, len);

			int ans = gen_chain_word(words, len, result, 0, 0, false);

			output(path, ans, result, (ans > 0));

			Assert::AreEqual(ans, std_ans);
		}

		TEST_METHOD(TestGenWordNNF)
		{

			char filename[10][100] = { "../test/input.txt",
										"../test/input1.txt",
										"../test/input2.txt",
										"../test/input3.txt",
										"../test/input4.txt",
										"../test/input5.txt",
										};
			int std_ans[10] = { -19, -19, -19, 4, -19, 2 };
			for (int i = 0; i < 6; i++) {
				gen_word_nnf(filename[i], std_ans[i]);
			}
		}

		void gen_word_fff(char filename[], int std_ans, char head, char tail) {
			int len = 0;
			int r = handleInput(filename, words, &len);


			char path[100] = "../test/output.txt";
			//output(path, len, words, len);

			int ans = gen_chain_word(words, len, result, head, tail, false);

			output(path, ans, result, (ans > 0));

			Assert::AreEqual(ans, std_ans);
		}

		TEST_METHOD(TestGenWordFFF)
		{

			char filename[10][100] = { "../test/input.txt",
										"../test/input1.txt",
										"../test/input2.txt",
										"../test/input3.txt",
										"../test/input4.txt",
										"../test/input5.txt",
			};
			int std_ans[10] = { -19, -19, -19, 2, -19, 2 };
			char head[10] = { 0, 0, 0, 'p', 0, 'a' };
			char tail[10] = { 0, 0, 0, 'm', 0, 'b' };
			for (int i = 0; i < 6; i++) {
				gen_word_fff(filename[i], std_ans[i], head[i], tail[i]);
			}
		}

		void gen_word_nnt(char filename[], int std_ans) {
			int len = 0;
			int r = handleInput(filename, words, &len);


			char path[100] = "../test/output.txt";
			//output(path, len, words, len);

			int ans = gen_chain_word(words, len, result, 0, 0, true);

			output(path, ans, result, (ans > 0));

			Assert::AreEqual(ans, std_ans);
		}

		TEST_METHOD(TestGenWordNNT)
		{

			char filename[10][100] = { "../test/input.txt",
										"../test/input1.txt",
										"../test/input2.txt",
										"../test/input3.txt",
										"../test/input4.txt",
										"../test/input5.txt",
			};
			int std_ans[10] = { 14, 12, 5, 4, 4, 2 };
			for (int i = 0; i < 6; i++) {
				gen_word_nnt(filename[i], std_ans[i]);
			}
		}

		void gen_word_fft(char filename[], int std_ans, char head, char tail) {
			int len = 0;
			int r = handleInput(filename, words, &len);


			char path[100] = "../test/output.txt";
			//output(path, len, words, len);

			int ans = gen_chain_word(words, len, result, head, tail, true);

			output(path, ans, result, (ans > 0));

			Assert::AreEqual(ans, std_ans);
		}

		TEST_METHOD(TestGenWordFFT)
		{

			char filename[10][100] = { "../test/input.txt",
										"../test/input1.txt",
										"../test/input2.txt",
										"../test/input3.txt",
										"../test/input4.txt",
										"../test/input5.txt",
			};
			int std_ans[10] = { 0, 12, 5, 2, 4, 2 };
			char head[10] = { 'f', 'w', 0, 'p', 0, 'a'};
			char tail[10] = { 'a', 'm', 0, 'm', 0, 'b'};
			for (int i = 0; i < 6; i++) {
				gen_word_fft(filename[i], std_ans[i], head[i], tail[i]);
			}
		}
	};
}
