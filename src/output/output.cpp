#include "pch.h"
#include <iostream>
#include <fstream>
#include "output.h"

using namespace std;

void output(char* path, int ans, char* result[], int len) {
    string exePath = path, solutionPath = "";
    for (int i = (int)exePath.size() - 1; i >= 0; --i)
        if (exePath[i] == '\\' || exePath[i] == '/') {
            for (int j = 0; j <= i; ++j)
                solutionPath += exePath[j];
            break;
        }

    solutionPath += "solution.txt";
    cout << "printing solutions: " << exePath << "  " << solutionPath << endl;
    ofstream sout(solutionPath);

    sout << ans << endl;
    for (int i = 1; i <= len; ++i) {
        sout << result[i] << endl;
    }
}
