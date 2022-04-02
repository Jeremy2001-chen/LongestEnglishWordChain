#ifndef _PARAMETER_H_
#define _PARAMETER_H_

#define MAXN_WORD 20202

#ifdef IMPORT_DLL
#else
#define IMPORT_DLL extern "C" _declspec(dllimport)
#endif

IMPORT_DLL int parameterExtract(char* argv[], int argc, int& problemType, bool& loop_enable, int& start, int& end, char** name);

enum Problem {
	WORD_CHAIN_COUNT_PROBLEM = 1,
	FIRST_CHAR_NOT_SAME_PROBLEM,
	WORD_CHAIN_MAX_WORD_PROBLEM,
	WORD_CHAIN_MAX_CHAR_PROBLEM
};

#define CALCULATE_CHAIN_COUNT_PARAMETER 'n'
#define CALCULATE_MAX_WORD_COUNT_PARAMETER 'w'
#define CALCULATE_FIRST_CHAR_NOT_SAME_PARAMETER 'm'
#define CALCULATE_MAX_CHAR_COUNT_PARAMETER 'c'
#define SET_FIRST_CHAR 'h'
#define SET_LAST_CHAR 't'
#define SET_ALLOC_LOOP 'r'

#endif