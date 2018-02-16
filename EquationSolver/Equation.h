#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "FileReader.h"

namespace RCCodingProblem
{
	class Equation
	{
	private:
		// LHS - contains only variable - string - variable name, uint - value of the variable
		pair<string, uint> m_prLHSVariable;

		// RHS - contains mix of variables, unsigned int and + operator
		vector<uint> m_vnIntegerValues; // Has only numbers
		unordered_map<string, uint> m_umRHSVariables; // Has variables map with its value(uint)

		// boolean to show equation is completely solve - as in RHS does not need further evaluation
		bool m_bEquationSolved;
	public:
		// Constructor
		Equation(): m_bEquationSolved(false) {}

		// Destructor
		~Equation() {}

		// Member functions
		// Builds each equation
		bool BuildEquation(string sEquationLine);

		// Validations for varaibles and numbers
		bool ValidateVariableHasAlphabets(string sLHS);
		bool ValidateIsNumber(string sRHSInteger);

		// Calculate sum of numbers
		uint CalculateNumbersSum(vector<uint> vnIntegerValues);

		// Setter / Getter methods
		inline void SetEquationSolved(bool bEquationSolved) { m_bEquationSolved = bEquationSolved; }
		inline bool GetEquationSolved() const { return m_bEquationSolved; }

		// Make Equation Solver a friend class
		friend class EquationsSolver;
	};
}
