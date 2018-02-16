#include "FileReader.h"

using namespace RCCodingProblem;

bool FileReader::ParseFile(string sFileName, vector<string> &vEquationLines)
{
	ifstream inputFile;
	inputFile.open(sFileName);

	// Read each line of the file which is an equation and store it the local variable vEquationLines
	if (inputFile.is_open())
	{
		string sEquationLine;
		while (!inputFile.eof())
		{
			getline(inputFile, sEquationLine, '\n');
			vEquationLines.push_back(sEquationLine);
			inputFile >> ws;
		}

		inputFile.close();
	}
	else
	{
		cout<<strerror(errno) << endl;
		CONSOLELOG("Cannot open file!!");
		return false;
	}

	// Check if the number of equation lines we got are more than zero
	if (vEquationLines.size() > 0)
	{
		return true;
	}

	return false;
}

