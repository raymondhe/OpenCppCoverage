#include "stdafx.h"
#include "FileCoverage.hpp"

#include "CppCoverageException.hpp"

namespace CppCoverage
{
	//-------------------------------------------------------------------------
	FileCoverage::FileCoverage(const boost::filesystem::path& path)
		: path_(path)
	{
	}

	//-------------------------------------------------------------------------
	void FileCoverage::AddLine(unsigned int lineNumber, bool hasBeenExecuted)
	{
		LineCoverage line{lineNumber, hasBeenExecuted};

		if (!lines_.emplace(lineNumber, line).second)
			THROW(L"Line " << lineNumber << L" already exists for " << path_.wstring());
	}

	//-------------------------------------------------------------------------
	const boost::filesystem::path& FileCoverage::GetPath() const
	{
		return path_;
	}

	//-------------------------------------------------------------------------
	const LineCoverage* FileCoverage::operator[](unsigned int line) const
	{
		auto it = lines_.find(line);

		if (it == lines_.end())
			return 0;

		return &it->second;
	}

	//-------------------------------------------------------------------------
	void FileCoverage::ComputeCoverageRate()
	{		
		int executedLines = 0;
		int unexecutedLines = 0;

		for (const auto& pair : lines_)
		{
			if (pair.second.HasBeenExecuted())
				++executedLines;
			else
				++unexecutedLines;
		}

		coverageRate_.SetExecutedLinesCount(executedLines);		
		coverageRate_.SetUnexecutedLinesCount(unexecutedLines);
	}

	//-------------------------------------------------------------------------
	const CoverageRate& FileCoverage::GetCoverageRate() const
	{
		return coverageRate_;
	}

}