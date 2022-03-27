#ifndef _WORDLIST_H_
#define _WORDLIST_H_

#ifdef IMPORT_DLL
#else
#define IMPORT_DLL extern "C" _declspec(dllimport)
#endif

IMPORT_DLL int handleInput(char*, char* [], int*);

IMPORT_DLL int gen_chains_all(char* [], int, char* []);
IMPORT_DLL int gen_chain_word_unique(char* [], int, char* []);
IMPORT_DLL int gen_chain_word(char* [], int, char* [], int, int, bool);
IMPORT_DLL int gen_chain_char(char* [], int, char* [], int, int, bool);

IMPORT_DLL void output(char*, int, char* [], int);

#endif