#pragma once

#include <vector>
#include <utility>
#include <string>
#include <assert.h>
#include <iostream>

using namespace std;

namespace Types
{
	typedef unsigned int uint;
}

namespace StringHelpers
{
	static vector<string> TokenizeString(string sInputString, char sDelimeter)
	{
		vector<string> vsTokenizedString;
		string sToken = "";
		for (Types::uint i = 0; i < sInputString.length(); i++)
		{
			if (sInputString[i] != sDelimeter)
			{
				if (sInputString[i] != ' ')
				{
					sToken.push_back(sInputString[i]);
				}
			}
			else
			{
				vsTokenizedString.push_back(sToken);
				sToken.clear();
			}
		}
		vsTokenizedString.push_back(sToken);
		sToken.clear();
		return vsTokenizedString;
	}
}

#ifndef LOGASSERT
	#define LOGASSERT(x) {if(!x){assert(false);}}	
#endif // !LOGASSERT

#ifndef CONSOLELOG
	#define CONSOLELOG(x) {cout<<x<<endl;}
#endif // !CONSOLELOG

#ifndef DELETESAFELY
	#define DELETESAFELY(x) {if(x!=NULL){delete x; x = NULL;}}
#endif // !DELETESAFELY

