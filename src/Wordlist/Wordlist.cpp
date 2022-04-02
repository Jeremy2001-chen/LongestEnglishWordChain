#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include "parameter.h"
#include "Wordlist.h"

using namespace std;

const int MAXN = 1e6 + 10;

char* result[MAXN];
char* wordList[MAXN_WORD];

int main(int argc, char *argv[])
{
    int problemType, start = 0, end = 0;
    bool loop_enable = false;
    char* name;
    char* args[] = { "Wordlist.exe", "-n", "../test/input1.txt"};
    argc = 3;
    int r = parameterExtract(args, argc, problemType, loop_enable, start, end, &name);
    system("pause");

    if (r < 0) {
        return 0;
    }
    
    static int wordCount = 0;
    handleInput(name, wordList, &wordCount);

    //cout << wordCount << endl;
    int tot = 0;
    switch (problemType) {
    case Problem::WORD_CHAIN_COUNT_PROBLEM:
        tot = gen_chains_all(wordList, wordCount, result);
        output(name, tot, result, tot);
        break;
    case Problem::FIRST_CHAR_NOT_SAME_PROBLEM:
        tot = gen_chain_word_unique(wordList, wordCount, result);
        output(name, tot, result, (tot > 0));
        break;
    case Problem::WORD_CHAIN_MAX_WORD_PROBLEM:
        tot = gen_chain_word(wordList, wordCount, result, start, end, loop_enable);
        output(name, tot, result, (tot > 0));
        break;
    case Problem::WORD_CHAIN_MAX_CHAR_PROBLEM:
        tot = gen_chain_char(wordList, wordCount, result, start, end, loop_enable);
        output(name, tot, result, (tot > 0));
        break;
    }

    return 0;
}