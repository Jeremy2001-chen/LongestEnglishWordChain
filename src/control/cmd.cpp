#include "pch.h"
#include "cmd.h"
#include <cstdlib>
#include <string>
#include <iostream>
#include "control.h"

using namespace std;

char* argv[10];
const char* openFileError = "Open the error log error!";
int argc = 0;

char* call_by_cmd(int len, char* cmd) {
	char* st = cmd, * ed = cmd;
	FILE* logFile;
	int r = freopen_s(&logFile, "error.log", "w", stderr);
	argc = 0;
	for (int i = 0; i < len; i++) {
		if (*ed == ' ') {
			int l = (int)(ed - st);
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

	int l = (int)(ed - st);
	argv[argc++] = (char*)malloc((size_t)l + 1);
	char* tmp = argv[argc - 1];
	if (tmp) {
		while (st != ed) {
			*tmp++ = *st++;
		}
		*tmp = '\0';
	}

	r = myControll(argc, argv);
	
	fclose(logFile);

	char* res;
	if (r < 0) {
		FILE* eFile;
		r = fopen_s(&eFile, "error.log", "r");
		if (eFile == 0) {
			res = (char*)malloc(26);
			if (res) {
				for (int i = 0; i < 26; i++)
					res[i] = openFileError[i];
			}
			return res;
		}
		int c;
		string output = "";
		while ((c = fgetc(eFile)) != EOF) {
			output += c;
		}
		res = (char*)malloc(size_t(output.size() + 1));
		if (res) {
			tmp = res;
			for (int i = 0; i < output.size(); i++) {
				*tmp++ = output[i];
			}
			*tmp = '\0';
		}
		fclose(eFile);
	}
	else {
		res = (char*)malloc(1);
		if (res) {
			res[0] = '\0';
		}
	}

	return res;
}