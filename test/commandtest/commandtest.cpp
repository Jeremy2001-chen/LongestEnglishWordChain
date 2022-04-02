#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#ifdef IMPORT_DLL
#else
#define IMPORT_DLL extern "C" _declspec(dllimport)
#endif

IMPORT_DLL int parameterExtract(char* argv[], int argc, int& problemType, bool& loop_enable, int& start, int& end, char** name);

namespace commandtest
{
	TEST_CLASS(commandtest)
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
			FINAL_CHAR_DUPLICATE
		};

		TEST_METHOD(MULT_PATH_FILE_ERROR)
		{
			char* argv[] = {"Wordlist.exe", "-n", "../test/input1.txt", "../test/input2.txt" };
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
			char* argv[] = { "Wordlist.exe", "-h", "%"};
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
			char* argv[] = { "Wordlist.exe", "-h", "a", "-h", "b", "-n"};
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
	};
}
