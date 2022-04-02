#include "pch.h"
#include <iostream>
#include <fstream>
#include "output.h"

using namespace std;

void output(char* path, int ans, char* result[], int len) {
    string exePath = path, solutionPath = "";
    if (exePath.find('\\') == exePath.npos) {
        solutionPath = ".\\solution.txt";
    }
    else {
        solutionPath = exePath.substr(0, exePath.find_last_of('\\')) + "\\solution.txt";
    }
    cout << "printing solutions: " << exePath << "  " << solutionPath << endl;
    ofstream sout(solutionPath);

    sout << ans << endl;
    for (int i = 1; i <= len; ++i) {
        sout << result[i] << endl;
    }
}
