#include <iostream>
#include <cstdio>
#include <set>

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
const int MAXN = 2e4 + 10;
namespace autochecker
{

	char* words[20000];
	char* result[20000];
	TEST_CLASS(autochecker)
	{
	public:

        std::set <std::string> wordSet;
        std::string word[MAXN];

        int handleInput(char* fileName, char* words[], int* len) {
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
                                    words[++wordCount] = tmp;
                                    wordSet.insert(s);
                                    word[++totWord] = s;
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
                        words[++wordCount] = tmp;
                        word[++totWord] = s;
                    }
                }
                (*len) = wordCount;
            }
            fclose(file);
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

        class Edges {
        public:
            int id, len;
            int from, next, to;
        };

        Edges edges[MAXN];

        int first[MAXN];

        
        int totWord = 0;

        int te = 0;

        bool vist[MAXN];
        int visp[MAXN];
        int chainCount = 0, chainLen = 0;
        int ansLen = 0, outputLen = 0;
        std::string chain[MAXN];
        std::string ans[MAXN];

        void dfs_find_chain_max(int pt, int len, bool first_diff, int END) {
            if (len > ansLen && (END == -1 || END == pt)) {
                ansLen = len;
                outputLen = chainLen;
                for (int i = 1; i <= chainLen; ++i) {
                    ans[i] = chain[i];
                }
            }
            visp[pt]++;
            for (int e = first[pt]; e; e = edges[e].next) {
                int to = edges[e].to;
                if (first_diff) {
                    if (!vist[e] && !visp[to]) {
                        vist[e] = true;
                        chain[++chainLen] = word[e];
                        dfs_find_chain_max(to, len + edges[e].len, first_diff, END);
                        chainLen--;
                        vist[e] = false;
                    }
                }
                else {
                    if (!vist[e]) {
                        vist[e] = true;
                        chain[++chainLen] = word[e];
                        dfs_find_chain_max(to, len + edges[e].len, first_diff, END);
                        chainLen--;
                        vist[e] = false;
                    }
                }
            }
            visp[pt]--;
        }

        void dfs_find_chain_go(int pt, int len) {
            if (len > 1) {
                chainCount++;
                for (int i = 1; i <= chainLen; ++i) {
                    std::cout << chain[i] << " ";
                }
                std::cout << std::endl;
            }
            for (int e = first[pt]; e; e = edges[e].next) {
                int to = edges[e].to;
                if (!vist[e]) {
                    vist[e] = true;
                    chain[++chainLen] = word[e];
                    dfs_find_chain_go(to, len + 1);
                    chainLen--;
                    vist[e] = false;
                }
            }
        }

        void link(int S, int T, int id, bool tot_character) {
            ++te;
            edges[te].from = S;
            edges[te].to = T;
            edges[te].next = first[S];
            edges[te].id = id;
            if (tot_character) {
                edges[te].len = word[id].size();
            }
            else {
                edges[te].len = 1;
            }
            first[S] = te;
        }

        int checker(char START, char END, bool find_all, bool tot_character, bool first_diff) {
            /*FILE* file;
            int r = fopen_s(&file, filename, "r");
            std::string s = "";
            wordSet.clear();

            char c;
            while ((c = fgetc(file)) != EOF) {
                if (c >= 'A' && c <= 'Z')
                    s += char(c - 'A' + 'a');
                else if (c >= 'a' && c <= 'z')
                    s += c;
                else {
                    if ((int)s.size() > 1) {
                        if (wordSet.find(s) == wordSet.end()) {
                            word[++totWord] = s;
                        }
                    }
                    s = "";
                }
            }

            fclose(file);

            if ((int)s.size() > 1 && wordSet.find(s) == wordSet.end()) {
                word[++totWord] = s;
            }
            */
            for (int i = 1; i <= totWord; i++) {
                link(word[i][0] - 'a', word[i][word[i].size() - 1] - 'a', i, tot_character);
            }

            if (find_all) {
                for (int i = 0; i < 26; i++) {
                    dfs_find_chain_go(i, 0);
                }
                return chainCount;
            }
            else {
                if (START == 0) {
                    for (int i = 0; i < 26; i++) {
                        if (END == 0) {
                            dfs_find_chain_max(i, 0, first_diff, -1);
                        }
                        else {
                            dfs_find_chain_max(i, 0, first_diff, END - 'a');
                        }
                    }
                }
                else {
                    if (END == 0) {
                        dfs_find_chain_max(START - 'a', 0, first_diff, -1);
                    }
                    else {
                        dfs_find_chain_max(START - 'a', 0, first_diff, END - 'a');
                    }
                }
                return ansLen;
            }
            return 0;
        }

        void gen_word_fft( char head, char tail, int len) {
            

            int std_ans = checker(head, tail, false, false, false);

            char path[100] = "../test/output.txt";
            //output(path, len, words, len);

            int ans = gen_chain_word(words, len, result, head, tail, true);

            output(path, ans, result, (ans > 0));
            //Assert::AreEqual(ans, std_ans);
            //Assert::AreEqual(ans, std_ans);
        }
        
        TEST_METHOD(autotest0)
        {

            char filename[100] = "../test/input4.txt";
            int len = 0;
            int r = handleInput(filename, words, &len);
            for (int i = 0; i < 10; i++) {
                char head = 'a' + i;
;                for (int j = 0; j < 10; j++) {
                    char tail = 'a' + j;
                    
                    gen_word_fft(head, tail, len);
                }
            }
        }
        
	};
}

