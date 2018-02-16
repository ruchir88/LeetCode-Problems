#include "Equations.h"

using namespace RCCodingProblem;

Equations::Equations()
{
	m_pFileReader = NULL;
}

Equations::~Equations()
{
	DELETESAFELY(m_pFileReader);
}

// Generate Equations from the file sInputFile
bool Equations::CreateEquationsFromFile(string sInputFile)
{
	m_pFileReader = new FileReader();
	vector<string> vEquationLines;

	// Parsing the file to get all the Equation lines in the file
	if (!m_pFileReader->ParseFile(sInputFile, vEquationLines))
	{
		CONSOLELOG("ERROR!! Cannot Parse File.");
		return false;
	}

	// Now convert all the Equation String lines into actual equation by calling BuildEquation of Equation class
	// Push all the Equation generated into m_vEquations vector
	for (uint i = 0; i < vEquationLines.size(); i++)
	{
		Equation e;
		if (!e.BuildEquation(vEquationLines[i]))
		{
			CONSOLELOG("ERROR!! Unable to build equations.");
			return false;
		}
		m_vEquations.push_back(e);
	}

	return true;
}
