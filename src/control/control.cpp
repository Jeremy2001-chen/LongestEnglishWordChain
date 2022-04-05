#include "pch.h"
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include "parameter.h"
#include "control.h"

using namespace std;

const int MAXN = (int)1e6 + 10;

char* result[MAXN];
char* wordList[MAXN_WORD];

int myControll(int argc, char* argv[])
{
    int problemType, start = 0, end = 0;
    bool loop_enable = false;
    char* name;
    int r = parameterExtract(argv, argc, problemType, loop_enable, start, end, &name);

    if (r < 0) {
        return r;
    }

    static int wordCount = 0;
    r = handleInput(name, wordList, &wordCount);

    if (r < 0) {
        return r;
    }
    //cout << wordCount << endl;
    int tot = 0;
    switch (problemType) {
    case ProblemType::WORD_CHAIN_COUNT_PROBLEM:
        tot = gen_chains_all(wordList, wordCount, result);
        if (tot < 0) {
            return tot;
        }
        output(name, tot, result, tot);
        break;
    case ProblemType::FIRST_CHAR_NOT_SAME_PROBLEM:
        tot = gen_chain_word_unique(wordList, wordCount, result);
        if (tot < 0) {
            return tot;
        }
        output(name, tot, result, (tot > 0));
        break;
    case ProblemType::WORD_CHAIN_MAX_WORD_PROBLEM:
        tot = gen_chain_word(wordList, wordCount, result, start, end, loop_enable);
        if (tot < 0) {
            return tot;
        }
        output(name, tot, result, (tot > 0));
        break;
    case ProblemType::WORD_CHAIN_MAX_CHAR_PROBLEM:
        tot = gen_chain_char(wordList, wordCount, result, start, end, loop_enable);
        if (tot < 0) {
            return tot;
        }
        output(name, tot, result, (tot > 0));
        break;
    }
    return 0;
}