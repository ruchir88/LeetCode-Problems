#include "EquationsSolver.h"

using namespace RCCodingProblem;

EquationsSolver::EquationsSolver()
{
	m_pEquations = NULL;
}

EquationsSolver::~EquationsSolver()
{
	DELETESAFELY(m_pEquations);
}

 bool EquationsSolver::SolveEquations(string sInputFile, unordered_map<string, uint> &umSolvedEquation)
{
	m_pEquations = new Equations();

	if (!m_pEquations->CreateEquationsFromFile(sInputFile))
	{
		CONSOLELOG("ERROR!! Cannot create equations.");
		return false;
	}

	// TODO: Solve the Equation
	EvaluateEquations(m_pEquations, umSolvedEquation);

	return true;
}

 void EquationsSolver::EvaluateEquations(Equations* eEquations, unordered_map<string, uint> &umSolvedEquation)
 {
	 vector<Equation> vEquations = m_pEquations->GetEquations();

	 // First store all variables that are already solved in the Solved Equation map
	 for (uint i = 0; i < vEquations.size(); i++)
	 {
		 if (vEquations[i].m_bEquationSolved)
		 {
			 // Since size of LHSVariable is always 1 we can use .begin()
			 umSolvedEquation[vEquations[i].m_prLHSVariable.first] = vEquations[i].m_prLHSVariable.second;
		 }
	 }

	 // Now solve all the unsolved equations
	 uint indx = 0;
	 // We have to do this because we don't know the order of the equation, for example there first equation might have on RHS variable which is not solved or evaluated.
	 // If that happens we have to make sure that we have to come back to this unsolved equation after finding the value of one of RHS variables.
	 while(AllEquationsNotSolved(vEquations)) 
	 {
		 indx  %= vEquations.size(); // This is to make sure we only access elements within the range

		 uint sum = 0; // The sum that will be used to assign value to LHS variable - only when the equation is solved otherwise the sum will be discarded

		 // SOlve the unsolved equations
		 if (!vEquations[indx].m_bEquationSolved)
		 {
			 // Then we solve all the RHS variables of the equation
			 // This vector will be used to store key values which needs to be deleted from the equation because their values are found and merge or add their values to the sum
			 vector<string> vsKeyValuePairToEraseFromMap;

			 // Iterate through the RHS variables and check if variables exist in Solved Equations map. If it does we save the value in the vsKeyValuesToEraseFromMap vector
			 for (unordered_map<string, uint>::iterator itr = vEquations[indx].m_umRHSVariables.begin(); itr != vEquations[indx].m_umRHSVariables.end(); itr++)
			 {
				 if (umSolvedEquation.find(itr->first) != umSolvedEquation.end())
				 {
					 itr->second = umSolvedEquation[itr->first];
					 sum += itr->second;
					 vsKeyValuePairToEraseFromMap.push_back(itr->first);
				 }
				 else
				 {
					 // There might be a situation where we have one variable on RHS that cannot be evaluated. In that case we delete the vector of strings and break.
					 // We will have to go through this whole equation again.
					 vsKeyValuePairToEraseFromMap.clear();
					 break;
				 }
			 }

			 // If all the RHS variables were found in the umSolvedEquation map then we are good
			 // Delete all the keys that were found on the above iteration
			 for (uint k = 0; k < vsKeyValuePairToEraseFromMap.size(); k++)
			 {
				 unordered_map<string, uint>::iterator delitr = vEquations[indx].m_umRHSVariables.find(vsKeyValuePairToEraseFromMap[k]);
				 vEquations[indx].m_umRHSVariables.erase(delitr);
			 }

			 // Finally if the RHS variables are empty for an equation and it is not solved yet then we assign the sum to the LHS variable and set bool variable m_bEquationSolved to true
			 // And add the key value pair of variable and value to umSolvedEquations map
			 if (vEquations[indx].m_umRHSVariables.empty())
			 {
				 // Sum up all the integer values of unsolved equation
				 for (uint j = 0; j < vEquations[indx].m_vnIntegerValues.size(); j++)
				 {
					 sum += vEquations[indx].m_vnIntegerValues[j];
				 }

				 vEquations[indx].m_prLHSVariable.second = sum;
				 vEquations[indx].m_bEquationSolved = true;
				 umSolvedEquation[vEquations[indx].m_prLHSVariable.first] = vEquations[indx].m_prLHSVariable.second;
			 }
		 }
		 indx++;
	 }
 }

 // Check if all the equations are solved in the map or not
 bool EquationsSolver::AllEquationsNotSolved(vector<Equation> vEquations)
 {
	 for (uint i = 0; i < vEquations.size(); i++)
	 {
		 if (!vEquations[i].m_bEquationSolved)
		 {
			 return true;
		 }
	 }
	 return false;
 }
 