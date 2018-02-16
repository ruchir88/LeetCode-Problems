Classes:
	- FileReader - Reads/Parses the input file that will be entered when the program is executed. This class splits all the equations into different vector of Equations(as a string line).

	- Equation - This class is a basic equation class which has all the properties of equation like LHS variable and RHS variables and integer values(as given in the problem description). This also converts the Equation string line provided by the file reader into a proper Eqaution object.

	- Equations - Equations class contains vector of equation which will be used by EquationSolver

	- EquationSolver - This class solves each equation(from vector of Equation) and evaluates the value of each variable in lhs and rhs. Thus giving us the final result for the problem.

	- Utilities - Provides certain helper methods like string tokenizer, macros and typdefs.

Files:
	FileReader.cpp/.h
	Equation.cpp/.h
	Equations.cpp/.h
	EquationsSolver.cpp/.h
	Main.cpp/.h
	Utilities.h
	InputFile.txt - sample text file to parse.
	readme.txt - this file.
	Makefile

Running Code:
	1)make Exe - compiles and builds the project
	2)./Exe - runs the project (will prompt you to enter file name)
	3)make clean - removes all .o files and the executable file

Note: Sometimes copying/downloading InputFile.txt which contains equations may get corrupted and not be readable by the program. In that case re-writing InputFile.txt will make it work.


