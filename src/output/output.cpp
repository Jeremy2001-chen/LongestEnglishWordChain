#include "pch.h"
#include <iostream>
#include <fstream>
#include "output.h"

using namespace std;

void output(char* path, int ans, char* result[], int len, bool useFile) {
    if (useFile) {
        string exePath = path, solutionPath = "";
        
        for (int i = (int)exePath.size() - 1; i >= 0; --i)
            if (exePath[i] == '\\' || exePath[i] == '/') {
                for (int j = 0; j <= i; ++j)
                    solutionPath += exePath[j];
                break;
            }
        solutionPath += "solution.txt";

        FILE* file;
        int r = freopen_s(&file, solutionPath.c_str(), "w", stdout);
        //cout << ans << endl;
        
        for (int i = 1; i <= len; ++i) {
            int l = 0, f = strlen(result[i]);
            for (char* st = result[i]; l < f ; st++, l++) {
                if (*st == ' ')
                    cout << endl;
                else
                    cout << *st;
            }
        }
        r = freopen_s(&file, "CON", "w", stdout);
    }
    else {
        cout << ans << endl;
        for (int i = 1; i <= len; ++i) {
            if (i < len)
                cout << result[i] << endl;
            else
                cout << result[i];
        }
    }
}
