#include <iostream>
#include <algorithm>
#include "EquationsSolver.h"

using namespace RCCodingProblem;

int main()
{
	EquationsSolver es;
	string sInputFile;
	CONSOLELOG("Please enter the file name: ");
	cin >> sInputFile;
	unordered_map<string, uint> umSolvedEquations;
	while (!es.SolveEquations(sInputFile, umSolvedEquations))
	{
		CONSOLELOG("Cannot find the file. Please re-enter the file name: ");
		cin >> sInputFile;
	}

	// Sort the unordered map 
	vector<pair<string, int> > vSortedSolvedEquations(umSolvedEquations.begin(), umSolvedEquations.end());
	sort(vSortedSolvedEquations.begin(), vSortedSolvedEquations.end());

	for (auto itr : vSortedSolvedEquations)
	{
		cout << itr.first << " : " << itr.second << endl;
	}
	
	return 0;
}
