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
    int r = parameterExtract(argv, argc, problemType, loop_enable, start, end, &name);
    if (r < 0) {
        exit(1);
    }
    
    static int wordCount = 0;
    handleInput(name, wordList, &wordCount);

    cout << wordCount << endl;
    int tot = 0;
    switch (problemType) {
    case WORD_CHAIN_COUNT_PROBLEM:
        tot = gen_chains_all(wordList, wordCount, result);
        output(name, tot, result, tot);
        break;
    case FIRST_CHAR_NOT_SAME_PROBLEM:
        tot = gen_chain_word_unique(wordList, wordCount, result);
        output(name, tot, result, (tot > 0));
        break;
    case WORD_CHAIN_MAX_WORD_PROBLEM:
        tot = gen_chain_word(wordList, wordCount, result, start, end, loop_enable);
        output(name, tot, result, (tot > 0));
        break;
    case WORD_CHAIN_MAX_CHAR_PROBLEM:
        tot = gen_chain_char(wordList, wordCount, result, start, end, loop_enable);
        output(name, tot, result, (tot > 0));
        break;
    }

    return 0;
}