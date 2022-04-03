#include "pch.h"
#include "cmd.h"
#include <cstdlib>
#include <string>
#include <iostream>
#include "control.h"

using namespace std;

char* argv[10];
int argc = 0;

char* call_by_cmd(int len, char* cmd) {
	char* st = cmd, * ed = cmd;
	FILE* logFile;
	int r = freopen_s(&logFile, "error.log", "w", stderr);
	argc = 0;
	for (int i = 0; i < len; i++) {
		if (*ed == ' ') {
			int l = ed - st;
			argv[argc++] = (char*)malloc((size_t)l + 1);
			int j = 0;
			while (st != ed) {
				argv[argc - 1][j++] = *st++;
			}
			argv[argc - 1][j] = '\0';
			st = ed + 1;
		}
		ed++;
	}

	int l = ed - st;
	argv[argc++] = (char*)malloc((size_t)l + 1);
	int j = 0;
	while (st != ed) {
		argv[argc - 1][j++] = *st++;
	}
	argv[argc - 1][j] = '\0';

	r = myControll(argc, argv);
	
	fclose(logFile);

	char* res;
	if (r < 0) {
		FILE* eFile;
		r = fopen_s(&eFile, "error.log", "r");
		char c;
		string output = "";
		while ((c = fgetc(eFile)) != EOF) {
			output += c;
		}
		res = (char*)malloc(size_t(output.size() + 1));
		for (int i = 0; i < output.size(); i++) {
			res[i] = output[i];
		}
		res[output.size()] = '\0';
		fclose(eFile);
	}
	else {
		res = (char*)malloc(1);
		res[0] = '\0';
	}

	return res;
}