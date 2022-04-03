#include "pch.h"
#include <iostream>
#include "error.h"
#include "parameter.h"
#include <cassert>
#include <fstream>

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
    char* parameter = NULL;
    bool pathFind = false;
    char type;
    char* path = NULL;
    int r;
    start = 0; end = 0;
    problemType = -1;
    start = end = 0;
    loop_enable = false;
    for (int i = 1; i < argc; i++) {
        if (checkFilePath(argv[i])) {
            if (pathFind) {
                cerr << "ָ���˶���ļ�·�������ָ����һ·��!" << endl;
                return -Error::MULTI_FILE_PATH;
            }
            pathFind = true;
            int len = strlen(argv[i]);
            path = (char*)malloc(static_cast<size_t>((size_t)len + 1));
            if (path == NULL) {
                cerr << "����ռ��쳣�������³���!" << endl;
                return -Error::ALLOC_MEMORY_ERROR;
            }
            else {
                char* tmp = path;
                for (int j = 0; j < len; j++) {
                    (*tmp++) = argv[i][j];
                }
                (*tmp) = '\0';
                (*name) = path;
            }
            continue;
        }
        if (strlen(argv[i]) != 2 || argv[i][0] != '-') {
            cerr << "���������ڣ�����������!" << endl;
            return -Error::PARAMETER_NOT_EXISTS;
        }
        switch (argv[i][1]) {
        case CALCULATE_CHAIN_COUNT_PARAMETER:
            if (problemType > 0) {
                cerr << "ָ���˶���������ָ��һ������" << endl;
                return -Error::MULTI_WORK_ERROR;
            }
            problemType = ProblemType::WORD_CHAIN_COUNT_PROBLEM;
            break;
        case CALCULATE_MAX_WORD_COUNT_PARAMETER:
            if (problemType > 0) {
                cerr << "ָ���˶���������ָ��һ������" << endl;
                return -Error::MULTI_WORK_ERROR;
            }
            problemType = ProblemType::WORD_CHAIN_MAX_WORD_PROBLEM;
            break;
        case CALCULATE_FIRST_CHAR_NOT_SAME_PARAMETER:
            if (problemType > 0) {
                cerr << "ָ���˶���������ָ��һ������" << endl;
                return -Error::MULTI_WORK_ERROR;
            }
            problemType = ProblemType::FIRST_CHAR_NOT_SAME_PROBLEM;
            break;
        case CALCULATE_MAX_CHAR_COUNT_PARAMETER:
            if (problemType > 0) {
                cerr << "ָ���˶���������ָ��һ������" << endl;
                return -Error::MULTI_WORK_ERROR;
            }
            problemType = ProblemType::WORD_CHAIN_MAX_CHAR_PROBLEM;
            break;
        case SET_FIRST_CHAR:
        case SET_LAST_CHAR:
            type = argv[i][1];
            if (i == argc - 1) {
                cerr << "ָ����β��ĸʱ������ĸ����!" << endl;
                return -Error::NO_CHAR_ERROR;
            }
            r = checkChar(argv[++i]);
            if (!r) {
                cerr << "ָ����ĸʱ��ʽ����ȷ��ֻ����ָ����Сд��ĸ��" << endl;
                return -Error::CHAR_FORM_ERROR;
            }
            if (type == SET_FIRST_CHAR) {
                if (start > 0) {
                    cerr << "�ظ�ָ������ĸ��" << endl;
                    return -Error::FIRST_CHAR_DUPLICATE;
                }
                start = argv[i][0];
            }
            else {
                if (end > 0) {
                    cerr << "�ظ�ָ��β��ĸ��" << endl;
                    return -Error::FINAL_CHAR_DUPLICATE;
                }
                end = argv[i][0];
            }
            break;
        case SET_ALLOC_LOOP:
            if (loop_enable) {
                cerr << "�ظ�ָ���л�����!" << endl;
                return -Error::ENABLE_LOOP_DUPLICATE;
            }
            loop_enable = true;
            break;
        default:
            cerr << "���������ڣ�����������!" << endl;
            return -Error::PARAMETER_NOT_EXISTS;
        }
    }
    if (path == NULL) {
        cerr << "�����в������ļ�·��!" << endl;
        return -Error::NO_FILE_PATH;
    }
    if ((start > 0 || end > 0 || loop_enable) && (problemType == ProblemType::WORD_CHAIN_COUNT_PROBLEM)) {
        cerr << "-n������֧�ֺ�����������ͬʹ��!" << endl;
        return -Error::N_WORK_WITH_OTHER_PARAMETER;
    }
    if ((start > 0 || end > 0 || loop_enable) && (problemType == ProblemType::FIRST_CHAR_NOT_SAME_PROBLEM)) {
        cerr << "-m������֧�ֺ�����������ͬʹ��!" << endl;
        return -Error::M_WORK_WITH_OTHER_PARAMETER;
    }
    if (problemType == -1) {
        cerr << "δָ��������ָ��һ������!" << endl;
        return -Error::NO_WORK_ERROR;
    }
    return 0;
}