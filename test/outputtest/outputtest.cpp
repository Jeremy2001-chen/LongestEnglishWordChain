#include "pch.h"
#include "CppUnitTest.h"


#ifdef IMPORT_DLL
#else
#define IMPORT_DLL extern "C" _declspec(dllimport)
#endif

IMPORT_DLL void output(char* path, int ans, char* result[], int len);

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace outputtest
{
	TEST_CLASS(outputtest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			char path[200] = "./output.txt";
			int ans = 0;
			char *result;
			int len = 0;
			output(path, ans, &result, len);
		}
	};
}
