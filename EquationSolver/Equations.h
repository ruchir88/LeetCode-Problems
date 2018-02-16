#pragma once

#include "FileReader.h"
#include "Equation.h"

namespace RCCodingProblem
{
	class Equations
	{
	private:
		FileReader* m_pFileReader;
		vector<Equation> m_vEquations;
	public:
		// Constructor
		Equations();

		// Destructor
		~Equations();

		// Member functions
		bool CreateEquationsFromFile(string sInputFile);
		inline vector<Equation> GetEquations() const { return m_vEquations; }
	};
}
