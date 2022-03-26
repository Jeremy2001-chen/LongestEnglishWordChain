#include <iostream>
#include "error.h"
#include "parameter.h"

using namespace std;

static bool inline checkFilePath(char* str) {
    int len = strlen(str);
    if (len < 3)
        return false;
    return str[len - 3] == 't' && str[len - 2] == 'x' && str[len - 1] == 't';
}

static bool checkChar(char* str) {
    return strlen(str) == 1 && (str[0] >= 'a' && str[0] <= 'z' || str[0] >= 'A' && str[0] <= 'Z');
}

int parameterExtract(char* argv[], int argc, int& problemType, bool& loop_enable, int& start, int& end, char** name) {
    char* parameter;
    bool pathFind = false;
    char type;
    int r;
    start = 0; end = 0;
    for (int i = 1; i < argc; i++) {
        if (checkFilePath(argv[i])) {
            if (pathFind) {
                cout << "You have done multi file path!" << endl;
                return -MULTI_FILE_PATH;
            }
            pathFind = true;
            int len = strlen(argv[i]);
            char* path = (char*)malloc(len + 1);
            for (int j = 0; j < len; j++) {
                path[j] = argv[i][j];
            }
            path[len] = '\0';
            (*name) = path;
            i++;
            continue;
        }
        if (strlen(argv[i]) != 2 || argv[i][0] != '-') {
            cout << "Parameter error!" << endl;
            return -PARAMETER_NOT_EXISTS;
        }
        switch (argv[i][1]) {
        case CALCULATE_CHAIN_COUNT_PARAMETER:
            problemType = WORD_CHAIN_COUNT_PROBLEM;
            break;
        case CALCULATE_MAX_WORD_COUNT_PARAMETER:
            problemType = WORD_CHAIN_MAX_WORD_PROBLEM;
            break;
        case CALCULATE_FIRST_CHAR_NOT_SAME_PARAMETER:
            problemType = FIRST_CHAR_NOT_SAME_PROBLEM;
            break;
        case CALCULATE_MAX_CHAR_COUNT_PARAMETER:
            problemType = WORD_CHAIN_MAX_CHAR_PROBLEM;
            break;
        case SET_FIRST_CHAR:
        case SET_LAST_CHAR:
            type = argv[i][1];
            if (i == argc - 1) {
                cout << "Parameter forget the file path!" << endl;
                return -NO_CHAR;
            }
            r = checkChar(argv[++i]);
            if (!r) {
                cout << "Character not correct!" << endl;
                return -CHAR_FORM_ERROR;
            }
            if (type == SET_FIRST_CHAR) {
                start = argv[i][0];
            }
            else {
                end = argv[i][0];
            }
            break;
        case SET_ALLOC_LOOP:
            loop_enable = true;
            break;
        default:
            cout << "Parameter form not correct!" << endl;
            return -PARAMETER_FORM_ERROR;
        }
    }
    return 0;
}
