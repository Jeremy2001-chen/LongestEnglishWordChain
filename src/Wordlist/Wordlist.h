#ifndef _WORDLIST_H_
#define _WORDLIST_H_

#ifdef IMPORT_DLL
#else
#define IMPORT_DLL extern "C" _declspec(dllimport)
#endif

IMPORT_DLL int myControll(int argc, char* argv[]);

#endif