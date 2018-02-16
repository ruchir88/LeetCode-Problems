#include "Equation.h"

using namespace RCCodingProblem;

bool Equation::BuildEquation(string sEquationLine)
{
	// Split the string at '=' sign
	vector<string> vSplitEquationLine = StringHelpers::TokenizeString(sEquationLine, '=');
	if (!ValidateVariableHasAlphabets(vSplitEquationLine[0]))
	{
		CONSOLELOG("ERROR!! Equation is not in correct format.");
		return false;
	}

	// Set/Initialize the LHS variable - value initialized to 0
	m_prLHSVariable = make_pair(vSplitEquationLine[0], 0);

	// Split the RHS (vSplitEquationLine[1]) at all the '+' signs
	vector<string> vSplitRHSString = StringHelpers::TokenizeString(vSplitEquationLine[1], '+');

	// Assign values to RHS part of the equation
	for (uint i = 0; i < vSplitRHSString.size(); i++)
	{
		if (ValidateVariableHasAlphabets(vSplitRHSString[i])) // Make sure all variable only have alphabets
		{
			// Set/Initialize RHS variables
			m_umRHSVariables[vSplitRHSString[i]] = 0;
		}
		else if(ValidateIsNumber(vSplitRHSString[i])) // Make sure all the Numbers are digits
		{
			m_vnIntegerValues.push_back(static_cast<uint>(stoi(vSplitRHSString[i])));
		}
		else
		{
			CONSOLELOG("ERROR!! Equation not in correct format.");
			return false;
		}
	}

	// if m_vumRHSVariables is empty that means the RHS has only number. This makes it clear that we can calculate the LHS variable value of this equation
	if (m_umRHSVariables.empty())
	{
		m_prLHSVariable.second = CalculateNumbersSum(m_vnIntegerValues);
		m_bEquationSolved = true;
	}

	return true;
}

// Validating if the string has only alphabets
bool Equation::ValidateVariableHasAlphabets(string sLHS)
{
	for (uint i = 0; i < sLHS.length(); i++)
	{
		if (!isalpha(sLHS[i]))
		{
			return false;
		}
	}
	return true;
}

// Validating if the string has only digits
bool Equation::ValidateIsNumber(string sRHSInteger)
{
	for (uint i = 0; i < sRHSInteger.length(); i++)
	{
		if (!isdigit(sRHSInteger[i]))
		{
			return false;
		}
	}
	return true;
}

// Evaluate the sum of all the Integer values
uint Equation::CalculateNumbersSum(vector<uint> vnIntegerValues)
{
	uint sum = 0;
	for (uint i = 0; i < vnIntegerValues.size(); i++)
	{
		sum += vnIntegerValues[i];
	}

	return sum;
}
