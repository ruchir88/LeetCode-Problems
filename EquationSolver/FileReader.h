#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Utilities.h"

using namespace Types;

namespace RCCodingProblem
{
	class FileReader
	{
	public:
		// Constructor
		FileReader() {}

		// Destructor
		~FileReader() {}

		// Member functions
		bool ParseFile(string sFileName, vector<string> &vEquationLines);
	};
}
