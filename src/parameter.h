#ifndef _PARAMETER_H_
#define _PARAMETER_H_

int parameterExtract(char* argv[], int argc, int& problemType, bool& loop_enable, int& start, int& end, char** name);

#define WORD_CHAIN_COUNT_PROBLEM 1
#define FIRST_CHAR_NOT_SAME_PROBLEM 2
#define WORD_CHAIN_MAX_WORD_PROBLEM 3
#define WORD_CHAIN_MAX_CHAR_PROBLEM 4

#define CALCULATE_CHAIN_COUNT_PARAMETER 'n'
#define CALCULATE_MAX_WORD_COUNT_PARAMETER 'w'
#define CALCULATE_FIRST_CHAR_NOT_SAME_PARAMETER 'm'
#define CALCULATE_MAX_CHAR_COUNT_PARAMETER 'c'
#define SET_FIRST_CHAR 'h'
#define SET_LAST_CHAR 't'
#define SET_ALLOC_LOOP 'r'

#endif