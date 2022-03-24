#ifndef _GENS_H_
#define _GENS_H_

#include <cstring>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "word.h"
using namespace std;

int gen_chains_all(char* fileName, string* result[]);
int gen_chain_word_unique(char* fileName, string* result[]);

#endif