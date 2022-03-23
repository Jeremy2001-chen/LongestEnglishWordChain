#include <cstdio>
#include <iostream>
#include "input.h"
#include "word.h"

using namespace std;

int main(int argc, char *argv[])
{
    char* name;
    name = (char*)malloc(4);
    while (argc-- > 0) {
        name = *argv++;
        printf("argc:%d, argv:%s\n", argc, name);
    }
    handleInput(name);
    return 0;
}