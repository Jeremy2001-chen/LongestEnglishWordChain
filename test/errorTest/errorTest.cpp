#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#ifdef IMPORT_DLL
#else
#define IMPORT_DLL extern "C" _declspec(dllimport)
#endif

IMPORT_DLL int parameterExtract(char* argv[], int argc, int& problemType, bool& loop_enable, int& start, int& end, char** name);

IMPORT_DLL int handleInput(char*, char* [], int*);

IMPORT_DLL int gen_chains_all(char* [], int, char* []);
IMPORT_DLL int gen_chain_word_unique(char* [], int, char* []);
IMPORT_DLL int gen_chain_word(char* [], int, char* [], int, int, bool);
IMPORT_DLL int gen_chain_char(char* [], int, char* [], int, int, bool);

IMPORT_DLL void output(char*, int, char* [], int);

namespace errorTest
{
	TEST_CLASS(errorTest)
	{
	public:

		enum Error {
			FILE_NOT_FIND = 1,
			HAVE_LOOP_ERROR,
			MULTI_FILE_PATH,
			PARAMETER_NOT_EXISTS,
			NO_FILE_PATH,
			FILE_PATH_FORM_ERROR,
			NO_CHAR_ERROR,
			CHAR_FORM_ERROR,
			PARAMETER_FORM_ERROR,
			ALLOC_MEMORY_ERROR,
			MULTI_WORK_ERROR,
			FIRST_CHAR_DUPLICATE,
			FINAL_CHAR_DUPLICATE,
			ENABLE_LOOP_DUPLICATE,
			N_WORK_WITH_OTHER_PARAMETER,
			M_WORK_WITH_OTHER_PARAMETER,
			WORD_NOT_AVAILABLE,
			HAVE_LOOP
		};

		TEST_METHOD(MULT_PATH_FILE_ERROR)
		{
			char* argv[] = { "Wordlist.exe", "-n", "../test/input1.txt", "../test/input2.txt" };
			int problemType, start, end;
			bool loop_enable;
			char* name;
			int r = parameterExtract(argv, 4, problemType, loop_enable, start, end, &name);
			Assert::AreEqual(r, (int)-Error::MULTI_FILE_PATH);
		}

		TEST_METHOD(PARAMETER_NOT_EXISTS_ERROR)
		{
			char* argv[] = { "Wordlist.exe", "-n", "../test/input1.txt", "-s" };
			int problemType, start, end;
			bool loop_enable;
			char* name;
			int r = parameterExtract(argv, 4, problemType, loop_enable, start, end, &name);
			Assert::AreEqual(r, (int)-Error::PARAMETER_NOT_EXISTS);

			argv[3] = "s";
			r = parameterExtract(argv, 4, problemType, loop_enable, start, end, &name);
			Assert::AreEqual(r, (int)-Error::PARAMETER_NOT_EXISTS);

			argv[3] = "≤‚ ‘“Ï≥£≤Œ ˝";
			r = parameterExtract(argv, 4, problemType, loop_enable, start, end, &name);
			Assert::AreEqual(r, (int)-Error::PARAMETER_NOT_EXISTS);
		}

		TEST_METHOD(PATH_NOT_EXISTS_ERROR)
		{
			char* argv[] = { "Wordlist.exe", "-r" };
			int problemType, start, end;
			bool loop_enable;
			char* name;
			int r = parameterExtract(argv, 2, problemType, loop_enable, start, end, &name);
			Assert::AreEqual(r, (int)-Error::NO_FILE_PATH);
		}

		TEST_METHOD(NO_CHAR)
		{
			char* argv[] = { "Wordlist.exe", "-h" };
			int problemType, start, end;
			bool loop_enable;
			char* name;
			int r = parameterExtract(argv, 2, problemType, loop_enable, start, end, &name);
			Assert::AreEqual(r, (int)-Error::NO_CHAR_ERROR);

			argv[1] = "-t";
			r = parameterExtract(argv, 2, problemType, loop_enable, start, end, &name);
			Assert::AreEqual(r, (int)-Error::NO_CHAR_ERROR);
		}

		TEST_METHOD(WRONG_CHAR_FORM)
		{
			char* argv[] = { "Wordlist.exe", "-h", "%" };
			int problemType, start, end;
			bool loop_enable;
			char* name;
			int r = parameterExtract(argv, 3, problemType, loop_enable, start, end, &name);
			Assert::AreEqual(r, (int)-Error::CHAR_FORM_ERROR);

			argv[2] = "-t";
			r = parameterExtract(argv, 3, problemType, loop_enable, start, end, &name);
			Assert::AreEqual(r, (int)-Error::CHAR_FORM_ERROR);
		}

		TEST_METHOD(MULTI_WORK)
		{
			char* argv[] = { "Wordlist.exe", "-n", "-w" };
			int problemType, start, end;
			bool loop_enable;
			char* name;
			int r = parameterExtract(argv, 3, problemType, loop_enable, start, end, &name);
			Assert::AreEqual(r, (int)-Error::MULTI_WORK_ERROR);
		}

		TEST_METHOD(FIRST_CHAR_DUP)
		{
			char* argv[] = { "Wordlist.exe", "-h", "a", "-h", "b", "-n" };
			int problemType, start, end;
			bool loop_enable;
			char* name;
			int r = parameterExtract(argv, 6, problemType, loop_enable, start, end, &name);
			Assert::AreEqual(r, (int)-Error::FIRST_CHAR_DUPLICATE);
		}

		TEST_METHOD(FINAL_CHAR_DUP)
		{
			char* argv[] = { "Wordlist.exe", "-t", "a", "-t", "b", "-n" };
			int problemType, start, end;
			bool loop_enable;
			char* name;
			int r = parameterExtract(argv, 6, problemType, loop_enable, start, end, &name);
			Assert::AreEqual(r, (int)-Error::FINAL_CHAR_DUPLICATE);
		}

		TEST_METHOD(ENABLE_LOOP_DUP)
		{
			char* argv[] = { "Wordlist.exe", "-r", "-r" };
			int problemType, start, end;
			bool loop_enable;
			char* name;
			int r = parameterExtract(argv, 3, problemType, loop_enable, start, end, &name);
			Assert::AreEqual(r, (int)-Error::ENABLE_LOOP_DUPLICATE);
		}

		TEST_METHOD(PARAMETER_CONFLICT)
		{
			char* argv[] = { "Wordlist.exe", "-n", "-r", "../test/input1.txt" };
			int problemType, start, end;
			bool loop_enable;
			char* name;
			int r = parameterExtract(argv, 4, problemType, loop_enable, start, end, &name);
			Assert::AreEqual(r, (int)-Error::N_WORK_WITH_OTHER_PARAMETER);

			argv[1] = "-m";
			r = parameterExtract(argv, 4, problemType, loop_enable, start, end, &name);
			Assert::AreEqual(r, (int)-Error::M_WORK_WITH_OTHER_PARAMETER);
		}

		TEST_METHOD(NO_FILE_ERROR)
		{
			char fileName[100] = "../test/input0.txt";
			char* word[500];
			int len = 0;
			int r = handleInput(fileName, word, &len);
			Assert::AreEqual(r, (int)-Error::FILE_NOT_FIND);
		}

		TEST_METHOD(NO_FILE_ERR)
		{
			char fileName[100] = "../test/input0.txt";
			char* word[500];
			int len = 0;
			int r = handleInput(fileName, word, &len);
			Assert::AreEqual(r, (int)-Error::FILE_NOT_FIND);
		}

		TEST_METHOD(WORD_NOT_AVAIL)
		{
			char* words[4] = { "abc", "edfg", NULL, NULL};

			char* result[10];
			int len = 4;
			int r = gen_chain_word_unique(words, len, result);
			Assert::AreEqual(r, (int)-Error::WORD_NOT_AVAILABLE);

			r = gen_chains_all(words, len, result);
			Assert::AreEqual(r, (int)-Error::WORD_NOT_AVAILABLE);

			r = gen_chain_char(words, len, result, 'a', 'z', false);
			Assert::AreEqual(r, (int)-Error::WORD_NOT_AVAILABLE);

			r = gen_chain_word(words, len, result, 'a', 'z', false);
			Assert::AreEqual(r, (int)-Error::WORD_NOT_AVAILABLE);
		}

		TEST_METHOD(LOOP_CHECK)
		{
			char* words[4] = { "gg", "abc", "cde", "ea"};
			char* result[10];
			int r = gen_chain_word_unique(words, 3, result);
			Assert::AreEqual(r, (int)-Error::HAVE_LOOP);

			r = gen_chains_all(words, 3, result);
			Assert::AreEqual(r, (int)-Error::HAVE_LOOP);

			r = gen_chain_char(words, 3, result, 'a', 'z', false);
			Assert::AreEqual(r, (int)-Error::HAVE_LOOP);

			r = gen_chain_word(words, 3, result, 'a', 'z', false);
			Assert::AreEqual(r, (int)-Error::HAVE_LOOP);
		}
	};
}
