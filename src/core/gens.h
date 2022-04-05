#ifndef _GENS_H_
#define _GENS_H_

#include <cstring>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "word.h"
using namespace std;

EXPORT_DLL int gen_chains_all(char* words[], int len, char* result[]);
EXPORT_DLL int gen_chain_word_unique(char* words[], int len, char* result[]);
EXPORT_DLL int gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop);
EXPORT_DLL int gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop);

#endif