#include <iostream>
#include <fstream>

using namespace std;

void output(char* path, int ans, char* result[], int len) {
    string exePath = path, solutionPath = exePath.substr(0, exePath.find_last_of('\\')) + "\\solution.txt";
    ofstream sout(solutionPath);

    sout << ans << endl;
    for (int i = 1; i <= len; ++i) {
        sout << result[i] << endl;
    }
}
