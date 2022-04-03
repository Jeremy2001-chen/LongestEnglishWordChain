#include "cmd.h"
#include <cstdlib>
#include <string>
#include <iostream>

using namespace std;

char pipeError[] = "Pipe create error, please retry!";

char* call_by_cmd(int len, char* cmd) {
	string command, result = "";
	for (int i = 0; i < len; i++)
		command += cmd[i];
	command += " 2>&1";

	cout << command << endl;
	FILE* pipe = _popen(command.c_str(), "r");
	if (!pipe) {
		return pipeError;
	}

	char buffer[256];
	while (!feof(pipe)) {
		// use buffer to read and add to result
		if (fgets(buffer, sizeof(buffer), pipe) != NULL)
			result += buffer;
	}

	size_t resLen = result.size() + 1;
	char* res = (char*)malloc(resLen);
	for (int i = 0; i < resLen; i++)
		res[i] = result[i];
	_pclose(pipe);
	return res;
}