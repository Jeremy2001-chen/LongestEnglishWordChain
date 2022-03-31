#include "pch.h"
#include "CppUnitTest.h"

#ifdef IMPORT_DLL
#else
#define IMPORT_DLL extern "C" _declspec(dllimport)
#endif

IMPORT_DLL int handleInput(char* fileName, char* word[], int* len);

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace getwordstest
{
	TEST_CLASS(getwordstest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			char fileName[100] = "E:/softengine/LongestEnglishWordChain/test/input.txt";
			char* word[500];
			int len = 0;
			int r = handleInput(fileName, word, &len);
			//int r = 0;
			Assert::AreEqual(r, 0);
			Assert::AreEqual(len, 19);
		}
		TEST_METHOD(TestRepeat)
		{
			char fileName[100] = "E:/softengine/LongestEnglishWordChain/test/input1.txt";
			char* word[500];
			int len = 0;
			int r = handleInput(fileName, word, &len);
			//int r = 0;
			Assert::AreEqual(r, 0);
			Assert::AreEqual(len, 13);
		}
		TEST_METHOD(TestDisturbing)
		{
			char fileName[100] = "E:/softengine/LongestEnglishWordChain/test/input12.txt";
			char* word[500];
			int len = 0;
			int r = handleInput(fileName, word, &len);
			//int r = 0;
			Assert::AreEqual(r, 0);
			Assert::AreEqual(len, 13);
		}
	};
}
