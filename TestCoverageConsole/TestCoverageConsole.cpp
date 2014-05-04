// ConsoleForCppCoverageTest.cpp : Defines the entry point for the console application.
//

#include <windows.h>
#include <tchar.h>

#include <string>
#include <iostream>
#include "TestCoverageSharedLib/TestCoverageSharedLib.hpp"

#include "TestCoverageConsole.hpp"

namespace
{
	//-----------------------------------------------------------------------------
	void ThrowHandledException()
	{
		try
		{
			throw 42;
		}
		catch (...)
		{
		}
	}
}

//-----------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{	
	if (argc == 2)
	{
		std::wstring type = argv[1];
		if (type == TestCoverageConsole::TestThrowHandledException)
			ThrowHandledException();
		else if (type == TestCoverageConsole::TestThrowUnHandledException)
			throw 42;
		else if (type == TestCoverageConsole::TestSharedLib)
			TestCoverageSharedLib::IsOdd(42);
		else
			std::wcerr << L"Unsupported type:" << type << std::endl;
	}
	return 0;	
}

namespace TestCoverageConsole
{
	//-----------------------------------------------------------------------------
	boost::filesystem::path GetMainCppPath()
	{
		return __FILE__;
	}

	//-----------------------------------------------------------------------------
	boost::filesystem::path GetOutputBinaryPath()
	{
		return TARGET_PATH;
	}
}