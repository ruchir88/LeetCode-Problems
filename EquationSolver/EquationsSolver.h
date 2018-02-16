#pragma once
#include <unordered_map>

#include "Equations.h"

using namespace Types;

namespace RCCodingProblem
{
	class EquationsSolver
	{
	private:
		Equations* m_pEquations;
	public:
		// Constructor
		EquationsSolver();

		// Destructor
		~EquationsSolver();

		// Member Functions
		bool SolveEquations(string sInputFile, unordered_map<string, uint> &umSolvedEquation);
		void EvaluateEquations(Equations* eEquations, unordered_map<string, uint> &umSolvedEquation);
		bool AllEquationsNotSolved(vector<Equation> vEquations);
	};
}
