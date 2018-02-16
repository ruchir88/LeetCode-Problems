// ProblemSet1.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "Header.h"

ListNode* MergeKSortedListUtil(int low, int high, vector<ListNode*>& lists)
{
	if (low >= high)
	{
		return lists[low];
	}

	int mid = low + (high - low) / 2;

	ListNode* L = MergeKSortedListUtil(low, mid, lists);
	ListNode* R = MergeKSortedListUtil(mid + 1, high, lists);

	// Do the merging here
	ListNode* currentL = L;
	ListNode* previousL = nullptr;

	while (currentL != nullptr && R != nullptr)
	{
		if (currentL->val >= R->val)
		{
			// Free the node of R
			ListNode* tempR = R;
			R = R->next;
			tempR->next = nullptr;

			// Handle L
			if (previousL != nullptr)
			{
				previousL->next = tempR;
				previousL = previousL->next;
			}
			
			tempR->next = currentL;
			if (previousL == nullptr)
			{
				L = tempR;
				currentL = tempR;
			}
		}
		else
		{
			previousL = currentL;
			currentL = currentL->next;
		}
	}

	if (R != nullptr)
	{
		if (previousL != nullptr)
		{
			previousL->next = R;
		}	
		else
		{
			return R;
		}
	}

	return L;
}

ListNode* MergeKLists(vector<ListNode*>& lists) 
{
	if (lists.size() == 0)
	{
		return nullptr;
	}
	else if (lists.size() == 1)
	{
		return lists[0];
	}

	int low = 0;
	int high = lists.size() - 1;

	return MergeKSortedListUtil(low, high, lists);
}

unordered_map<char, string> PhoneDictionary{ {'0', ""}, {'1', ""}, {'2', "abc"}, {'3', "def"}, {'4', "ghi"}, {'5', "jkl"}, {'6', "mno"}, {'7', "pqrs"}
, {'8', "tuv"}, {'9', "wxyz"} };

vector<string> PrintAllCombinationsOfGivenPhoneNumber(string digits)
{
	if (digits.size() == 0)
	{
		return vector<string>();
	}

	if (digits.size() == 1)
	{
		if (digits[0] == '1' || digits[0] == '0')
		{
			return vector<string>{""};
		}

		vector<string> vToReturnTemp;
		for (char c : PhoneDictionary[digits[0]])
		{
			string str(1, c);
			vToReturnTemp.push_back(str);
		}
		return vToReturnTemp;
	}

	char lastCharacter = digits[digits.size() - 1];
	digits = digits.substr(0, digits.size() - 1);
	vector<string> PartialResult = PrintAllCombinationsOfGivenPhoneNumber(digits);

	vector<string> vToReturn;
	for (string s : PartialResult)
	{
		for (char c : PhoneDictionary[lastCharacter])
		{
			string sToPush = s;
			sToPush.push_back(c);
			vToReturn.push_back(sToPush);
		}
	}

	if (vToReturn.size() == 0)
	{
		return PartialResult;
	}

	return vToReturn;
}

vector<int> spiralOrder(vector<vector<int> >& matrix) 
{
	if (matrix.size() == 0)
	{
		return vector<int>();
	}

	int i = 0;
	int j = 0;
	int last_index_i = matrix.size() - 1;
	int last_index_j = matrix[0].size() - 1;
	int first_index_i = 0;
	int first_index_j = 0;

	vector<int> vSpiralOrderVector;

	while (first_index_i < last_index_i && first_index_j < last_index_j)
	{
		while (j <= last_index_j)
		{
			vSpiralOrderVector.push_back(matrix[i][j]);
			j++;
		}
		j--;
		i++;
		while (i <= last_index_i)
		{
			vSpiralOrderVector.push_back(matrix[i][j]);
			i++;
		}
		i--;
		j--;
		while (j >= first_index_j)
		{
			vSpiralOrderVector.push_back(matrix[i][j]);
			j--;
		}
		j++;
		i--;
		while (i > first_index_i)
		{
			vSpiralOrderVector.push_back(matrix[i][j]);
			i--;
		}
		i++;
		j++;
		last_index_j--;
		last_index_i--;
		first_index_i++;
		first_index_j++;
	}

	while (j < last_index_j && i <= last_index_i)
	{
		vSpiralOrderVector.push_back(matrix[last_index_i][j]);
		j++;
	}

	while (i < last_index_i && j <= last_index_j)
	{
		vSpiralOrderVector.push_back(matrix[i][last_index_j]);
		i++;
	}

	if (j > last_index_j || i > last_index_i)
	{
		return vSpiralOrderVector;
	}
	else
	{
		vSpiralOrderVector.push_back(matrix[i][j]);
	}

	return vSpiralOrderVector;
}

void removeAll(int val, ListNode **list) {
	ListNode* head = *list;
	ListNode* prev = *list;

	while (head != nullptr)
	{
		if (head->val == val)
		{
			// remove the node
			ListNode* tempNode = head->next;
			head->next = nullptr;
			if (head == prev)
			{
				delete head;
				*list = tempNode;
				prev = tempNode;
			}
			else
			{
				prev->next = tempNode;
			}

			head = tempNode;
		}
		else
		{
			prev = head;
			head = head->next;
		}
	}
}

int CountPairs(vector<int> v, int diff)
{
	int i = 0;
	int pairs = 0;
	for (int j = 1; j < v.size(); ++j)
	{
		if (v[j] == v[i] + diff)
		{
			pairs++;
			i++;
		}
	}
	
	return pairs;
}

struct ComparatorNode
{
	size_t operator()(const Node& a, const Node& b) const 
	{
		return a.m_iMinDistanceToReachThisNode > b.m_iMinDistanceToReachThisNode;
	}
};

tuple<int, vector<char> > DijkstrasAlgorithm(Graph& g, Node& startNode, Node& endNode)
{
	priority_queue<Node, vector<Node>, ComparatorNode> pq;

	pq.push(startNode);

	// We have to BFS here with priority queue
	while (!pq.empty())
	{
		Node topNode = pq.top();
		pq.pop();

		// As soon as the end node reaches top we break! We found the shortest path!!
		if (topNode == endNode)
		{
			break;
		}

		for (auto adjNode : g.m_AdjList[topNode.m_sName])
		{
			if (g.m_usParsedNode.count(adjNode.second))
			{
				continue;
			}

			int minDistance = topNode.m_iMinDistanceToReachThisNode + adjNode.first;
			if (g.m_Nodes[adjNode.second.m_sName].m_iMinDistanceToReachThisNode == 0 
				|| minDistance < g.m_Nodes[adjNode.second.m_sName].m_iMinDistanceToReachThisNode)
			{
					g.m_Nodes[adjNode.second.m_sName].m_iMinDistanceToReachThisNode = minDistance;
					g.m_Nodes[adjNode.second.m_sName].m_cFromNode = topNode.m_sName;
			}

			pq.push(g.m_Nodes[adjNode.second.m_sName]);
		}

		g.m_usParsedNode.insert(topNode);
	}

	// Now recurse back from end node to the start node and find the full path 
	// return the tuple as shown below with the <min distance, full path>
	vector<char> vToReturn{endNode.m_sName};
	Node n = g.m_Nodes[endNode.m_sName];
	while (n.m_cFromNode != '\0')
	{
		vToReturn.push_back(n.m_cFromNode);
		n = g.m_Nodes[n.m_cFromNode];
	}
	reverse(vToReturn.begin(), vToReturn.end());

	return make_tuple(g.m_Nodes[endNode.m_sName].m_iMinDistanceToReachThisNode, vToReturn);
}

struct ComparatorAStar
{
	size_t operator()(const Node& a, const Node& b) const
	{
		return a.m_iMinCombinedHueristic > b.m_iMinCombinedHueristic;
	}
};

tuple<int, vector<char> > AStar(Graph& g, Node& startNode, Node& endNode)
{
	priority_queue <Node, vector<Node>, ComparatorAStar> pq;

	// Add heuristics here
	startNode.m_iMinCombinedHueristic = g.m_HeuristicsMap[startNode.m_sName];
	pq.push(startNode);

	// We have to BFS here with priority queue
	while (!pq.empty())
	{
		Node topNode = pq.top();
		pq.pop();

		// As soon as the end node reaches top we break! We found the shortest path!!
		if (topNode == endNode)
		{
			break;
		}

		for (auto adjNode : g.m_AdjList[topNode.m_sName])
		{
			if (g.m_usParsedNode.count(adjNode.second))
			{
				continue;
			}

			// Calculate min distance to reach adjNode node
			int minDistance = topNode.m_iMinDistanceToReachThisNode + adjNode.first;
			if (g.m_Nodes[adjNode.second.m_sName].m_iMinDistanceToReachThisNode == 0
				|| minDistance < g.m_Nodes[adjNode.second.m_sName].m_iMinDistanceToReachThisNode)
			{
				g.m_Nodes[adjNode.second.m_sName].m_iMinDistanceToReachThisNode = minDistance;
			}

			// Add min distance to reach adjNode with Heuristics of that node to get min Heuristics
			int minHeuristics = g.m_Nodes[adjNode.second.m_sName].m_iMinDistanceToReachThisNode + g.m_HeuristicsMap[adjNode.second.m_sName];
			if (g.m_Nodes[adjNode.second.m_sName].m_iMinCombinedHueristic == 0
				|| minHeuristics < g.m_Nodes[adjNode.second.m_sName].m_iMinCombinedHueristic)
			{
				g.m_Nodes[adjNode.second.m_sName].m_iMinCombinedHueristic = minHeuristics;
				g.m_Nodes[adjNode.second.m_sName].m_cFromNode = topNode.m_sName;
			}

			pq.push(g.m_Nodes[adjNode.second.m_sName]); // can modify this priority queue to have unique nodes by using set and priority_queue together
		}

		g.m_usParsedNode.insert(topNode);
	}

	// Now recurse back from end node to the start node and find the full path 
	// return the tuple as shown below with the <min distance, full path>
	vector<char> vToReturn{ endNode.m_sName }; // use list instead of vector to avoid reversing the vector
	Node n = g.m_Nodes[endNode.m_sName];
	while (n.m_cFromNode != '\0')
	{
		vToReturn.push_back(n.m_cFromNode);
		n = g.m_Nodes[n.m_cFromNode];
	}
	reverse(vToReturn.begin(), vToReturn.end());

	return make_tuple(g.m_Nodes[endNode.m_sName].m_iMinDistanceToReachThisNode, vToReturn);
}

vector<int> nextPermutationUtil(vector<int> nums)
{
	static bool found = false;
	if (nums.size() == 1)
	{
		return nums;
	}

	int beginValue = nums[0];
	nums.erase(nums.begin());
	vector<int> tempVectorReturned = nextPermutationUtil(nums);
	nums.insert(nums.begin(), beginValue);

	if (found)
	{
		return tempVectorReturned;
	}

	int compare = nums.size() - 2;
	int high = nums.size() - 1;

	while (high > 0)
	{
		while (compare >= 0)
		{
			if (nums[compare] < nums[high])
			{
				// sort from compare to high - 1
				// and push the high element before compare
				int numToInsertInBegining = nums[high];
				nums.erase(nums.begin() + high);
				sort(nums.begin() + compare, nums.end());
				nums.insert(nums.begin() + compare, numToInsertInBegining);
				found = true;
				return nums;
			}
			compare--;
		}

		high--;
		compare = high - 1;
	}

	if (high == 0)
	{
		return nums;
	}
}

void nextPermutation(vector<int>& nums) {
	if (nums.size() == 1)
	{
		return;
	}
	
	vector<int> vToReturn;
	vector<int> vChangedVector = nextPermutationUtil(nums);
	if (vChangedVector == nums)
	{
		reverse(nums.begin(), nums.end());
		return;
	}
	else
	{
		int changingIndex = nums.size() - vChangedVector.size();
		int someCounter = 0;
		for (int i=0; i<nums.size(); i++)
		{
			if (i >= changingIndex)
			{
				vToReturn.push_back(vChangedVector[someCounter]);
				someCounter++;
			}
			else
			{
				vToReturn.push_back(nums[i]);
			}
		}
	}

	nums = vToReturn;
}

void nextPermutation2(vector<int>& nums)
{
	int i = nums.size() - 1;
	int j = 0;
	int iJustGreaterIndex = 0;
	int iReplacingIndex = 0;

	while (i > 0)
	{
		if (nums[i - 1] < nums[i])
		{
			iReplacingIndex = i - 1;
			j = i;
			iJustGreaterIndex = i;
			while (j < nums.size())
			{
				if (nums[j] > nums[iReplacingIndex] && nums[j] <= nums[iJustGreaterIndex])
				{
					iJustGreaterIndex = j;
				}
				j++;
			}
			break;
		}
		i--;
	}

	if (i == 0 && i == j)
	{
		reverse(nums.begin(), nums.end());
		return;
	}

	// swap i with j 
	int temp = nums[iReplacingIndex];
	nums[iReplacingIndex] = nums[iJustGreaterIndex];
	nums[iJustGreaterIndex] = temp;

	reverse(nums.begin() + iReplacingIndex + 1, nums.end());
}

bool IsPowerOfThree(unsigned int value)
{
	double Power3IntMax = log(UINT_MAX) / log(3);
	unsigned int valuePow3 = pow(3, floor(Power3IntMax));
	return value > 0 && valuePow3 % value == 0;
}

bool PowOfFour(int num)
{
	if (num < 1)
	{
		return false;
	}

	if (num == 1)
	{
		return true;
	}

	if (num && !(num & (num - 1)))
	{
		int powerTo2 = log(num) / log(2);
		return powerTo2 > 1 && powerTo2 % 2 == 0;
	}

	return false;
}

bool wordBreak(string s, vector<string>& wordDict) {
	if (wordDict.size() == 0)
		return false;

	unordered_set<string> setOfWords(wordDict.begin(), wordDict.end());
	vector<bool> bWordExists(s.size() + 1);
	bWordExists[0] = true;

	for (int i = 1; i <= s.size(); i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (bWordExists[j] && setOfWords.find(s.substr(j, i - j)) != setOfWords.end())
			{
				bWordExists[i] = true;
				break;
			}
		}
	}

	return bWordExists[s.length()];
}

int numSquares(int n) {
	int sqrtOfn = sqrt(n);
	vector<int> squareOfValidNum;
	for (int i = 1; i <= sqrtOfn; i++)
	{
		squareOfValidNum.push_back(i*i);
	}

	int minSquareNums = INT_MAX;
	for (int i = squareOfValidNum.size() - 1; i >= 0; --i)
	{
		for (int j = i; j >= 0; --j)
		{
			int tempNum = n - squareOfValidNum[i];
			int count = 1;
			int tempIndex = j;
			while (tempNum != 0)
			{
				while (tempNum - squareOfValidNum[tempIndex] < 0)
				{
					tempIndex--;
				}

				tempNum -= squareOfValidNum[tempIndex];
				count++;
			}
			if (count < minSquareNums)
			{
				minSquareNums = count;
			}
		}
	}

	return minSquareNums;
}

int guess(int num)
{
	if (num > 6)
	{
		return 1;
	}
	else if (num < 6)
	{
		return -1;
	}
	
	return 0;
}

int guessNumber(int n) {
	int low = 0;
	int high = n;

	while (low < high)
	{
		int mid = low + (high - low) / 2;
		int range = guess(mid);

		if (range == 0)
		{
			return mid;
		}

		// number is lower so search in higher range
		if (range == -1)
		{
			low = mid + 1;
		}

		// number is higher so search in lower range
		if (range == 1)
		{
			high = mid - 1;
		}
	}

	return -1;
}

vector<string> summaryRanges(vector<int>& nums) {
	if (nums.size() == 0)
	{
		return vector<string>();
	}

	int rangeStart = 0;
	int rangeEnd = 1;

	vector<string> vsStringToReturn;
	string sStringToPush;

	// as long as difference is 1 keep appending to the string
	while (rangeEnd < nums.size())
	{
		if(sStringToPush.empty())
			sStringToPush.append(to_string(nums[rangeStart]));

		if (nums[rangeEnd] - nums[rangeStart] != 1)
		{
			if (nums[rangeStart] != atoi(sStringToPush.c_str()))
			{
				sStringToPush.append("->");
				sStringToPush.append(to_string(nums[rangeStart]));
			}
			vsStringToReturn.push_back(sStringToPush);
			sStringToPush.clear();
		}

		rangeStart++;
		rangeEnd++;
	}

	if (sStringToPush.empty())
	{
		sStringToPush.append(to_string(nums[rangeStart]));
	}
	else
	{
		sStringToPush.append("->");
		sStringToPush.append(to_string(nums[rangeStart]));
	}

	vsStringToReturn.push_back(sStringToPush);
	sStringToPush.clear();

	return vsStringToReturn;
}

void wiggleSort(vector<int>& nums) {
	if (nums.size() == 0 || nums.size() == 1)
	{
		return;
	}

	int startIndex = 0;
	int compareIndex = 1;

	bool bStrategyNextGreator = true;
	while (compareIndex < nums.size())
	{
		if (bStrategyNextGreator)
		{
			while (compareIndex < nums.size() && nums[compareIndex] <= nums[startIndex])
			{
				compareIndex++;
			}

			bStrategyNextGreator = false;
		}
		else
		{
			while (compareIndex < nums.size() && nums[compareIndex] >= nums[startIndex])
			{
				compareIndex++;
			}

			bStrategyNextGreator = true;
		}
		
		if (compareIndex == nums.size())
		{
			compareIndex--;
			if (compareIndex != startIndex)
			{
				// swap
				int temp = nums[compareIndex];
				nums[compareIndex] = nums[startIndex];
				nums[startIndex] = temp;
			}
		}

		if (compareIndex != startIndex + 1)
		{
			// do the swap
			int temp = nums[compareIndex];
			nums[compareIndex] = nums[startIndex + 1];
			nums[startIndex + 1] = temp;
		}

		startIndex++;
		compareIndex = startIndex + 1;
	}
}

int GetSign(int numerator, int denominator)
{
	if ((numerator < 0 && denominator < 0) || (numerator > 0 && denominator > 0))
	{
		return 1;
	}

	return -1;
}

string GetAfterDecimalValue(int numerator, int denominator)
{
	string returnString{ "" };

	map<int, int> mAfterDecimalNumberMap;

	long long remainder = numerator % denominator;

	while (remainder != 0 && (mAfterDecimalNumberMap.find(remainder) == mAfterDecimalNumberMap.end()))
	{
		mAfterDecimalNumberMap[remainder] = returnString.size();

		// get the quotient after decimal
		remainder *= 10;
		int decimalNumber = remainder / denominator;
		returnString.append(to_string(abs(decimalNumber)));

		// get the remainder for further calculation 
		remainder = remainder % denominator;
	}

	if (remainder == 0)
	{
		return returnString;
	}
	else
	{
		return returnString.substr(0, mAfterDecimalNumberMap[remainder]) + "(" + returnString.substr(mAfterDecimalNumberMap[remainder]) + ")";
	}
}

string fractionToDecimal(int numerator, int denominator) {
	if (denominator == 0)
	{
		return "";
	}
	if (numerator == 0)
	{
		return "0";
	}

	int ans = abs(numerator) / abs(denominator);

	string res = "";
	res = to_string(ans);

	string afterDecimalValue = GetAfterDecimalValue(numerator, denominator);
	if (afterDecimalValue.size() > 0)
	{
		res.push_back('.');
		res.append(afterDecimalValue);
	}

	if (GetSign(numerator, denominator) == -1)
	{
		res.insert(res.begin(), '-');
	}

	return res;
}

void DFSUtil(int i, int j, vector<vector<bool>>& vVectorVisited, vector<vector<char>>& grid)
{
	// basically visit all the neighbors of i, j index
	if (i != 0)
	{
		// Check left first
		if (grid[i - 1][j] == '1' && !vVectorVisited[i - 1][j])
		{
			vVectorVisited[i - 1][j] = true;
			DFSUtil(i - 1, j, vVectorVisited, grid);
		}
	}

	if (i < grid.size() - 1)
	{
		// Check right second
		if (grid[i + 1][j] == '1' && !vVectorVisited[i + 1][j])
		{
			vVectorVisited[i + 1][j] = true;
			DFSUtil(i + 1, j, vVectorVisited, grid);
		}
	}

	if (j != 0)
	{
		// Check up first
		if (grid[i][j - 1] == '1' && !vVectorVisited[i][j - 1])
		{
			vVectorVisited[i][j - 1] = true;
			DFSUtil(i, j - 1, vVectorVisited, grid);
		}
	}

	if(j < grid[0].size() - 1)
	{
		// Check down second
		if (grid[i][j + 1] == '1' && !vVectorVisited[i][j + 1])
		{
			vVectorVisited[i][j + 1] = true;
			DFSUtil(i, j + 1, vVectorVisited, grid);
		}
	}
}

int numIslands(vector<vector<char>>& grid) {
	vector<vector<bool> > vVisited(grid.size(), vector<bool>(grid[0].size()));
	int countIslands = 0;
	for (int i = 0; i < grid.size(); i++)
	{
		for (int j = 0; j < grid[0].size(); j++)
		{
			if (!vVisited[i][j] && grid[i][j] == '1')
			{
				vVisited[i][j] = true;
				DFSUtil(i, j, vVisited, grid);
				countIslands++;
			}
		}
	}

	return countIslands;
}

bool searchMatrix(vector<vector<int>>& matrix, int target) {
		if (matrix.size() == 0 || matrix[0].size() == 0)
		{
			return false;
		}

		// 2D Binary Search
		int startingRow = 0;
		int columnWidth = matrix[0].size() - 1;

		while (startingRow < matrix.size() && columnWidth >= 0)
		{
			int i = startingRow;
			int lowx = 0;
			int highx = columnWidth;
			while (target > matrix[i][highx])
			{
				if (i == matrix.size() - 1)
				{
					return false;
				}
				i++;
			}

			int horizontalMid = (highx - lowx) / 2;
			while (lowx <= highx)
			{
				int mid = lowx + (highx - lowx) / 2;
				if (matrix[i][mid] == target)
				{
					return true;
				}

				if (matrix[i][mid] > target)
				{
					highx = mid - 1;
				}

				if (matrix[i][mid] < target)
				{
					lowx = mid + 1;
				}
			}
			if (lowx < horizontalMid)
			{
				columnWidth = lowx;
			}
			else
			{
				columnWidth = lowx - 1;
			}

			if (columnWidth < 0)
			{
				return false;
			}

			int j = columnWidth;
			int lowy = startingRow;
			int highy = matrix.size() - 1;
			if (target > matrix[highy][j])
			{
				return false;
			}

			while (lowy < highy)
			{
				int mid = lowy + (highy - lowy) / 2;
				if (matrix[mid][j] == target)
				{
					return true;
				}

				if (matrix[mid][j] > target)
				{
					highy = mid;
				}

				if (matrix[mid][j] < target)
				{
					lowy = mid + 1;
				}
			}

			startingRow = lowy;
		}
}

void Trie::Insert(string word)
{
	TrieNode *current = m_TrieNode;
	for (int i = 0; i < word.length(); i++)
	{
		if (current->m_usChildren.find(word[i]) == current->m_usChildren.end())
		{
			current->m_usChildren[word[i]] = new TrieNode;
		}
		current = current->m_usChildren[word[i]];
	}

	current->IsCompleteWord = true;
}

bool Trie::Search(string word)
{
	TrieNode *current = m_TrieNode;
	for (int i = 0; i < word.length(); i++)
	{
		if (current->m_usChildren.find(word[i]) != current->m_usChildren.end())
		{
			current = current->m_usChildren[word[i]];
		}
		else
		{
			return false;
		}
	}

	return current->IsCompleteWord;
}

bool Trie::StarsWith(string word)
{
	TrieNode* current = m_TrieNode;
	for (int i = 0; i < word.length(); i++)
	{
		if (current->m_usChildren.find(word[i]) != current->m_usChildren.end())
		{
			current = current->m_usChildren[word[i]];
		}
		else
		{
			return false;
		}
	}

	return true;
}

void TrieBinary::Insert(int i)
{
	TrieNodeBinary* current = m_TrieNodeBinary;
	for (int itr = 31; itr >= 0; itr--)
	{
		int currBit = (i >> itr) & 1; // Get bits from most significant bit position

		// if current Bit is not present add the current bit into the map
		if (current->m_umChildren.find(currBit) == current->m_umChildren.end())
		{
			current->m_umChildren[currBit] = new TrieNodeBinary;
		}

		// go to the children of current node to store next bit of the number
		current = current->m_umChildren[currBit];
	}

	current->m_IsLastNode = true;
	current->m_Number = i;
}

int FindMaxXORUtil(TrieBinary& trie, vector<int>& nums, vector<int>& vPair)
{
	int iMaximumValue = INT_MIN;

	for (auto num : nums)
	{
		TrieNodeBinary* current = trie.m_TrieNodeBinary;
		int currSum = 0;
		for (int itr = 31; itr >= 0; itr--)
		{
			int currentBit = (num >> itr) & 1;
			if (current->m_umChildren.find(currentBit ^ 1) != current->m_umChildren.end())
			{
				currSum += (1 << itr);
				current = current->m_umChildren[currentBit ^ 1];
			}
			else
			{
				current = current->m_umChildren[currentBit];
			}
		}

		if (currSum > iMaximumValue)
		{
			vPair.clear();
			vPair.push_back(num);
			vPair.push_back(current->m_Number);
		}
		iMaximumValue = max(iMaximumValue, currSum);
	}

	return iMaximumValue;
}

int findMaximumXOR(vector<int>& nums, vector<int>& vPair)
{
	TrieBinary tbinary;

	for (auto num : nums)
	{
		tbinary.Insert(num);
	}
	
	return FindMaxXORUtil(tbinary, nums, vPair);
}

void DFSTopologicalSort(char startNode, TopologicalSortGraph& tpg)
{
	for (auto adjNode : tpg.m_umAdjList[startNode])
	{
		if (tpg.m_sVisitedNode.find(adjNode) == tpg.m_sVisitedNode.end())
		{
			tpg.m_sVisitedNode.insert(adjNode);
			DFSTopologicalSort(adjNode, tpg);
		}		
	}

	tpg.m_sSortedStack.push(startNode);
}

stack<char> TopologicalSort(TopologicalSortGraph tpg)
{	
	for (char node : tpg.m_NotVisitedNodes)
	{
		if (tpg.m_sVisitedNode.find(node) == tpg.m_sVisitedNode.end())
		{
			tpg.m_sVisitedNode.insert(node);
			DFSTopologicalSort(node, tpg);
		}
	}

	cout << tpg.m_sSortedStack.top() << endl;
	return tpg.m_sSortedStack;
}

vector<Interval> mergeIntervals(vector<Interval>& intervals) {
	auto pComparator = [](const Interval& a, const Interval& b) -> bool {
		return a.start < b.start;
	};

	sort(intervals.begin(), intervals.end(), pComparator);

	for (int i = 0; i < intervals.size() - 1; i++)
	{
		Interval tempInterval;
		// compare the second element of i with first element of i+1
		if (intervals[i].end >= intervals[i + 1].start) // if this is satisfied - intervals are going to merge
		{
			tempInterval.end = max(intervals[i].end, intervals[i + 1].end);
		}
		else
		{
			continue;
		}

		// compare first elements of i and i+1 index
		if (intervals[i].start < intervals[i + 1].start)
		{
			tempInterval.start = intervals[i].start;
		}
		else
		{
			tempInterval.start = intervals[i + 1].start;
		}

		// if the code reaches this point that means there has been a merge
		intervals.erase(intervals.begin() + i, intervals.begin() + i + 2);
		intervals.insert(intervals.begin() + i, tempInterval);
		i--;
	}

	return intervals;
}

enum SomeEnum
{
	Car,
	Bike
};

int lengthLongestPath(string input)
{
	int iMaxLen = 0;
	unordered_map<int, int> m_umLevelToLengthMap{ {0,0} };

	string token;
	int iLevel = 1;
	for (int i = 0; i < input.length(); i++)
	{
		// if we find \n we skip that step or reach the end of the string
		if (input[i] == '\n' || i == input.length() - 1)
		{
			if (token.find('.') != string::npos)
			{
				int iLengthOfCurrentFile = token.length() + m_umLevelToLengthMap[iLevel - 1];
				
				// if the file is found at the end of the string add one to include the last character of the string
				if (i == input.length() - 1)
				{
					iLengthOfCurrentFile += 1;
				}

				// if the length calculated is more than current iMaxLen we update iMaxLen
				if (iLengthOfCurrentFile > iMaxLen)
				{
					iMaxLen = iLengthOfCurrentFile;
				}
			}
			else
			{
				// if its a sub directory and not a file we update the current dictionary of level and length for current iLevel
				m_umLevelToLengthMap[iLevel] = token.length() + 1;
				m_umLevelToLengthMap[iLevel] += m_umLevelToLengthMap[iLevel - 1];
			}

			// Reset iLevel and token
			iLevel = 1;
			token.clear();

			continue;
		}

		if (input[i] == '\t')
		{
			// if we reached here that means the character is equal to \t, count number of \t to set iLevel value
			while (input[i] == '\t')
			{
				iLevel++;
				i++;
			}
			i--;
		}

		// if current character is not \t, push back in token string
		if (input[i] != '\t')
		{
			// push every character into the token
			token.push_back(input[i]);
		}
	}

	return iMaxLen;
}

bool isPalindrome(string str)
{
	int i = 0;
	int j = str.size() - 1;

	while (i < j) {
		if (str[i++] != str[j--]) return false;
	}

	return true;
}

vector<vector<int>> palindromePairs(vector<string>& words) 
{
	vector<vector<int> > vvRes;
	unordered_map<string, int> umRevWords;

	for (int i = 0; i < words.size(); i++)
	{
		string sKey = words[i];
		reverse(sKey.begin(), sKey.end());
		umRevWords[sKey] = i;
	}

	if (umRevWords.find("") != umRevWords.end())
	{
		for (int i = 0; i < words.size(); i++)
		{
			if (i != umRevWords[""])
			{
				if (isPalindrome(words[i]))
				{
					vvRes.push_back({ umRevWords[""], i });
				}
			}
		}
	}

	for (int i = 0; i < words.size(); i++)
	{
		for (int j = 0; j < words[i].size(); j++)
		{
			string left = words[i].substr(0, j);
			string right = words[i].substr(j, words[i].size() - j);

			if (umRevWords.find(left) != umRevWords.end() && isPalindrome(right) && i != umRevWords[left])
			{
				vvRes.push_back({ i, umRevWords[left] });
			}

			if (umRevWords.find(right) != umRevWords.end() && isPalindrome(left) && i != umRevWords[right])
			{
				vvRes.push_back({ umRevWords[right], i });
			}
		}
	}

	return vvRes;
}

// not working
string removeDuplicateLetters(string s)
{
	string sTempString;
	unordered_set<char> usTempSet;
	sTempString.push_back(s[0]);
	usTempSet.insert(s[0]);

	int itr = 1;
	while (itr < s.size())
	{
		if (usTempSet.find(s[itr]) == usTempSet.end())
		{
			sTempString.push_back(s[itr]);
			usTempSet.insert(s[itr]);
		}
		else
		{
			string sTempTempString = sTempString;
			size_t position = sTempTempString.find(s[itr]);
			sTempTempString.erase(sTempTempString.begin() + position);
			sTempTempString.push_back(s[itr]);

			if (sTempTempString < sTempString)
			{
				sTempString = sTempTempString;
			}
		}
		itr++;
	}

	string forwardTempString = sTempString;

	sTempString.clear();
	usTempSet.clear();
	sTempString.push_back(s[s.size() - 1]);
	usTempSet.insert(s[s.size() - 1]);

	itr = s.size() - 2;
	while (itr >= 0)
	{
		if (usTempSet.find(s[itr]) == usTempSet.end())
		{
			sTempString.insert(sTempString.begin(), s[itr]);
			usTempSet.insert(s[itr]);
		}
		else
		{
			string sTempTempString = sTempString;
			size_t position = sTempTempString.find(s[itr]);
			sTempTempString.erase(sTempTempString.begin() + position);
			sTempTempString.insert(sTempTempString.begin(), s[itr]);

			if (sTempTempString < sTempString)
			{
				sTempString = sTempTempString;
			}
		}
		itr--;
	}

	if (forwardTempString < sTempString)
	{
		sTempString = forwardTempString;
	}

	return sTempString;
}

void DFSWordBreak2(unordered_map<int, vector<string> > um, 
				   int sizeOfString, 
				   vector<string>& res, 
				   vector<string> vString, 
				   int totalIndex, 
				   string finalString)
{
	if (totalIndex >= sizeOfString)
	{
		return;
	}

	for (string str : vString)
	{
		int prevTotalIndex = totalIndex;
		string prevFinalString = finalString;

		int indexToAdd = str.size();
		finalString.append(" ");
		finalString.append(str);
		totalIndex += indexToAdd;

		DFSWordBreak2(um, sizeOfString, res, um[totalIndex], totalIndex, finalString);

		if (totalIndex >= sizeOfString)
		{
			finalString.erase(finalString.begin());
			res.push_back(finalString);
		}	

		// Go to previous state of finalString
		finalString = prevFinalString;
		totalIndex = prevTotalIndex;
	}
}

vector<string> wordBreak2(string s, vector<string>& wordDict)
{
	if (s.size() == 0 || wordDict.size() == 0)
	{
		return vector<string>();
	}

	unordered_set<string> us(wordDict.begin(), wordDict.end());
	vector<bool> vbWordExists(s.size() + 1);
	vector<string> res;
	unordered_map<int, vector<string> > um;

	vbWordExists[0] = true;

	for (int i = 1; i <= s.size(); i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (vbWordExists[j] && us.find(s.substr(j, i - j)) != us.end())
			{
				um[j].push_back(s.substr(j, i - j));
				vbWordExists[i] = true;
			}
		}
	}
	// store a key value pair for size of string which will be "" empty string to avoid edge case
	um[s.size()].push_back("");

	if (!vbWordExists[s.size()])
	{
		return vector<string>();
	}

	// iterate through um[0] to get all possible string combinations
	DFSWordBreak2(um, s.size(), res, um[0], 0, "");

	return res;
}

void gameOfLife(vector<vector<int>>& board) 
{
	if (board.size() == 0)
		return;

	// If we flip the bits we use ^
	for (int i = 0; i < board.size(); i++)
	{
		for (int j = 0; j < board[0].size(); j++)
		{
			int iNumBitsAlive = 0;
			for (int innerI = max(i - 1, 0); innerI < min(i + 2, (int)board.size()); innerI++)
			{
				for (int innerJ = max(j - 1, 0); innerJ < min(j + 2, (int)board[0].size()); innerJ++)
				{
					if (innerI != i || innerJ != j)
					{
						iNumBitsAlive += board[innerI][innerJ] & 1;
					}
				}
			}

			// Bit flipping condition
			if (((iNumBitsAlive < 2 || iNumBitsAlive > 3) && board[i][j] == 1) || (iNumBitsAlive == 3 && board[i][j] == 0))
			{
				board[i][j] |= 2;
			}
		}
	}

	// Regenerate the 2d matrix
	for (int i = 0; i < board.size(); i++)
	{
		for (int j = 0; j < board[0].size(); j++)
		{
			if (board[i][j] == 3)
			{
				board[i][j] = 0;
			}
			else if (board[i][j] == 2)
			{
				board[i][j] = 1;
			}
		}         
	}
}

string shortestPalindrome(string s)
{
	if (isPalindrome(s))
		return s;

	int left = 0;
	int right = 0;
	int center = -1;

	if (s.size() % 2 == 0)
	{
		left = (s.size() - 1) / 2;
		right = left + 1;
	}
	else
	{
		left = (s.size() - 1) / 2;
		right = left;
	}

	while (left >= 0)
	{
		if (s[left] == s[right])
		{
			center = left;
			left--;
			right++;
		}
		else if (center != -1 && s[left] == s[center])
		{
			right = center;
		}
		else
		{
			center = left;
			left = center - 1;
			right = center + 1;
		}
	}

	int iCopyingIndexStart = right;

	string str;
	while (iCopyingIndexStart < s.size())
	{
		str.insert(str.begin(), s[iCopyingIndexStart]);
		iCopyingIndexStart++;
	}

	s.insert(0, str);

	return s;
}

string shortestPalindrome2(string s)
{
	string rev(s);
	reverse(rev.begin(), rev.end());

	int i = 0;
	int j = 0;

	int indexTillWhichPalindromeExists = 0;

	while (i < rev.size())
	{
		int t = i;
		while (t < rev.size() && s[j] == rev[t])
		{
			j++;
			t++;
		}

		if (t == rev.size())
		{
			indexTillWhichPalindromeExists = j;
			break;
		}

		j = 0;
		i++;
	}

	string substrToAdd = s.substr(indexTillWhichPalindromeExists);
	reverse(substrToAdd.begin(), substrToAdd.end());

	return substrToAdd + s;
}

string reduce_string(string input_string) 
{
	for (int i = 0; i < input_string.size() - 1; i++)
	{
		if (input_string[i] == 'e' && input_string[i+1] == 'e')
		{
			input_string.erase(i, 1);
			i--;
		}
	}

	return input_string;
}

void MergeSortCountSmallerUtil(vector<pair<int, vector<int> > >& nums, int l, int h)
{
	if (l == h)
	{
		return;
	}

	int mid = l + (h - l) / 2;
	MergeSortCountSmallerUtil(nums, l, mid);
	MergeSortCountSmallerUtil(nums, mid+1, h);

	int leftIndex = l;
	int rightIndex = mid + 1;

	vector<pair<int, vector<int> > > tempVector;
	while (leftIndex < mid+1 && rightIndex <= h)
	{
		if (nums[leftIndex].first <= nums[rightIndex].first)
		{
			tempVector.push_back(nums[leftIndex]);
			leftIndex++;
		}
		else
		{
			int tempLeftIndex = leftIndex;
			while (nums[tempLeftIndex] > nums[rightIndex])
			{
				nums[tempLeftIndex].second[1]++;
				tempLeftIndex++;
			}
			
			tempVector.push_back(nums[rightIndex]);
			rightIndex++;
		}
	}

	while (leftIndex < mid + 1)
	{
		tempVector.push_back(nums[leftIndex]);
		leftIndex++;
	}

	while (rightIndex <= h)
	{
		tempVector.push_back(nums[rightIndex]);
		rightIndex++;
	}

	for (int i = l; i < l + tempVector.size(); i++)
	{
		nums[i] = tempVector[i - l];
	}
}

vector<int> countSmaller(vector<int>& nums) 
{
	if (nums.size() == 0)
	{
		return vector<int>();
	}

	vector<pair<int, vector<int> > > numsMod;
	vector<int> res(nums.size());

	for (int i = 0; i < nums.size(); i++)
	{
		numsMod.push_back(make_pair(nums[i], vector<int>{ i, 0 }));
	}

	MergeSortCountSmallerUtil(numsMod, 0, numsMod.size() - 1);

	for (int i = 0; i < numsMod.size(); i++)
	{
		res[numsMod[i].second[0]] = numsMod[i].second[1];
	}

	return res;
}

bool isMatch(string s, string p) 
{
	s.insert(0, 1, ' ');
	p.insert(0, 1, ' ');
	vector<vector<bool> > T(s.size(), vector<bool>(p.size()));

	for (int i = 0; i < T.size(); i++)
	{
		for (int j = 0; j < T[0].size(); j++)
		{
			if (s[i] == p[j] || p[j] == '.')
			{
				if (i - 1 >= 0 && j - 1 >= 0)
				{
					T[i][j] = T[i - 1][j - 1];
				}
				else if(i == j)
				{
					T[i][j] = true;
				}
				else
				{
					T[i][j] = false;
				}
			}
			else if (p[j] == '*')
			{
				if ((j - 2) >= 0 && T[i][j - 2])
				{
					T[i][j] = true;
				}
				else if ((j - 1) >= 0 && (i - 1) >= 0 && (s[i] == p[j - 1] || p[j - 1] == '.'))
				{
					T[i][j] = T[i - 1][j];
				}
				else
				{
					T[i][j] = false;
				}
			}
		}
	}

	return T[s.size() - 1][p.size() - 1];
}

double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2)
{
	if (nums1.size() == 0 && nums2.size() == 0)
	{
		return 0;
	}

	int minSize = min(nums1.size(), nums2.size());
	if (minSize == nums2.size())
	{
		nums1.swap(nums2);
	}

	int start = 0;
	int end = nums1.size();

	int partitionx = 0;
	int partitiony = 0;

	while (start <= end)
	{
		partitionx = (start + end) / 2;
		partitiony = ((nums1.size() + nums2.size() + 1) / 2) - partitionx;

		int maxLeftX = (partitionx == 0) ? INT_MIN : nums1[partitionx - 1];
		int minRightX = (partitionx == nums1.size()) ? INT_MAX : nums1[partitionx];

		int maxLeftY = (partitiony == 0) ? INT_MIN : nums2[partitiony - 1];
		int minRightY = (partitiony == nums2.size()) ? INT_MAX : nums2[partitiony];

		if (maxLeftX <= minRightY && maxLeftY <= minRightX)
		{
			if ((nums2.size() + nums1.size()) % 2 == 0)
			{
				double dVal = max(maxLeftX, maxLeftY) + min(minRightX, minRightY);
				return dVal / 2;
			}

			return max(maxLeftX, maxLeftY);
		}
		else if (maxLeftY > minRightX)
		{
			start = partitionx + 1;
		}
		else
		{
			end = partitionx - 1;
		}
	}

	return -1;
}

int maxCoins(vector<int>& nums) 
{
	vector<vector<int> > T(nums.size(), vector<int>(nums.size()));

	for (int len = 1; len <= nums.size(); len++)
	{
		for (int i = 0; i <= nums.size() - len; i++)
		{
			int j = len + i - 1;
			for (int k = i; k <= j; k++)
			{
				// The k balloon will be last one to burst so select left and right accordingly
				// i and j are the edges of the window
				int leftNum = 1;
				int rightNum = 1;

				if (i != 0)
				{
					leftNum = nums[i - 1];
				}

				if (j != nums.size() - 1)
				{
					rightNum = nums[j + 1];
				}

				int before = 0;
				int after = 0;

				if (i != k)
				{
					before = T[i][k - 1];
				}

				if (j != k)
				{
					after = T[k + 1][j];
				}

				int product = (leftNum * nums[k] * rightNum) + before + after;

				T[i][j] = max(T[i][j], product);
			}
		}
	}

	return T[0][nums.size() - 1];
}

bool KMP(string text, string pattern)
{
	// first built a prefix array
	vector<int> patternPrefix(pattern.size());

	int j = 0;
	int i = 1;

	while (i < pattern.size())
	{
		if (pattern[i] == pattern[j])
		{
			patternPrefix[i] = j + 1;
			j++;
			i++;
		}
		else
		{
			while (j > 0 && pattern[patternPrefix[j - 1]] != pattern[i])
			{
				j = patternPrefix[j - 1];
			}

			if (j == 0)
			{
				if (pattern[j] == pattern[i])
				{
					patternPrefix[i] = j + 1;
					j++;
					i++;
				}
			}
			else
			{
				patternPrefix[i] = patternPrefix[j - 1] + 1;
			}
			i++;
		}
	}

	// Now do pattern matching
	int itrPatternIndex = 0;
	bool bPatternMatches = false;
	for (int i = 0; i < text.size(); i++)
	{
		if (text[i] != pattern[itrPatternIndex])
		{
			itrPatternIndex = patternPrefix[itrPatternIndex - 1];
		}

		itrPatternIndex++;
		if (itrPatternIndex == pattern.size())
		{
			bPatternMatches = true;
			break;
		}
	}

	return bPatternMatches;
}

void print(initializer_list<string> input)
{
	for (string ele : input)
	{

	}
}

void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void PermuteUtil(vector<int> num, int begin, vector<vector<int> >& res)
{
	if (begin >= num.size())
	{
		res.push_back(num);
		return;
	}

	for (int i = begin; i < num.size(); i++)
	{
		swap(&num[begin], &num[i]);
		PermuteUtil(num, begin + 1, res);
		swap(&num[begin], &num[i]);
	}
}

vector<vector<int> > permute(vector<int> &A)
{
	vector<vector<int> > res;

	PermuteUtil(A, 0, res);
	return res;
}

// a, a, b, a
void PalindromePartitionUtil(vector<string> vString, int begin, vector<vector<string> >& vvRes, string str)
{
	if (begin >= str.size())
	{
		vvRes.push_back(vString);
		return;
	}

	for (int i = begin; i < str.size(); i++)
	{
		string strToPush = str.substr(begin, (i - begin) + 1);
		vString.push_back(strToPush);

		if (isPalindrome(strToPush))
		{
			PalindromePartitionUtil(vString, begin + (i - begin) + 1, vvRes, str);
		}

		vString.pop_back();
	}
}

vector<vector<string> > partitionPalindrome(string A) 
{
	vector<string> vString{};
	vector<vector<string> > res;

	PalindromePartitionUtil(vString, 0, res, A);
	
	return res;
}

/************************************************************************/
/*
Recursion Tricks

Example of DFS:
void DFS()
{
	// have a exit condition here
	if(someVariable reaches certain value or conditional value)
	{
		exit / return;
	}
	// usually will require using for loop

	for(index...end) // sometimes may be two for loops as given in one of the problem below
	{
		- modify the input a bit ex: swap, insert, append, increment etc;
		- call the recursive function here;
		- reset the input to its previous state;
	}

	// some times we can do it without for loop like in trees or linked lists
}
*/
/************************************************************************/

void DFSNumberOfPatternsUtil(vector<vector<int> >& vvKeyPad, int i, int j, int maxn, int minm, unordered_set<int> us, int& eachCount)
{
	if (maxn == us.size())
	{
		return;
	}

	for (int InnerI = max(i - 1, 0); InnerI < min(i+2, (int)vvKeyPad.size()); InnerI++)
	{
		for (int InnerJ = max(j - 1, 0); InnerJ < min(j + 2, (int)vvKeyPad[0].size()); InnerJ++)
		{
			if (InnerI != i || InnerJ != j)
			{
				if (us.find(vvKeyPad[InnerI][InnerJ]) == us.end())
				{
					us.insert(vvKeyPad[InnerI][InnerJ]);
					if (us.size() <= maxn && us.size() >= minm)
					{
						eachCount++;
					}

					DFSNumberOfPatternsUtil(vvKeyPad, InnerI, InnerJ, maxn, minm, us, eachCount);

					us.erase(vvKeyPad[InnerI][InnerJ]);
				}
			}
		}
	}
}

int numberOfPatterns(int n, int m)
{
	vector<vector<int> > vvKeyPad{ {1,2,3}, {4,5,6}, {7,8,9} };
	unordered_set<int> us;
	int eachCount = 0;

	for (int i = 0; i < vvKeyPad.size(); i++)
	{
		for (int j = 0; j < vvKeyPad[0].size(); j++)
		{
			us.insert(vvKeyPad[i][j]);
			if(m == 1)
				eachCount++;
			DFSNumberOfPatternsUtil(vvKeyPad, i, j, n, m, us, eachCount);
			us.clear();
		}
	}

	return eachCount;
}

void DFSNumberOfPatternsUtil2(map<int, vector<int> >& umKeyPad, map<int, vector<pair<int, int> > > umKeyPadForEdges, int maxn, int minm, unordered_set<int> us, int& eachCount, int key)
{
	if (maxn == us.size())
	{
		return;
	}

	for (auto ele : umKeyPad[key])
	{
		if (us.find(ele) == us.end())
		{
			us.insert(ele);
			if (us.size() <= maxn && us.size() >= minm)
			{
				eachCount++;
				cout << eachCount << endl;
			}

			DFSNumberOfPatternsUtil2(umKeyPad, umKeyPadForEdges, maxn, minm, us, eachCount, ele);

			us.erase(ele);
		}
		else
		{
			for (auto p : umKeyPadForEdges[key])
			{
				if (p.first == ele && us.find(p.second) == us.end())
				{
					us.insert(p.second);
					if (us.size() <= maxn && us.size() >= minm)
					{
						eachCount++;
					}

					DFSNumberOfPatternsUtil2(umKeyPad, umKeyPadForEdges, maxn, minm, us, eachCount, p.second);

					us.erase(p.second);
				}
			}
		}
	}
}

int numberOfPatterns2(int n, int m)
{
	if (n > 9)
	{
		return 0;
	}

	map<int, vector<int> > umKeyPad{ { 1, {2,4,5,6,8} }, {2, {1,4,5,6,3,7,9} }, { 3, {2,5,6,4,8} }, {4, {1,2,5,8,7,3,9} }, 
											   { 5, {1,2,3,4,6,7,8,9} }, {6, {2,3,5,8,9,1,7} }, { 7, {4,5,8,2,6} }, {8, {7,4,5,6,9,1,3} }, 
											   { 9, {5,6,8,4,2} } };
	map<int, vector<pair<int, int> > > umKeyPadFarEdges{ {1, {{2,3},{5,9},{4,7}} }, {2, {{5,8}} }, {3, {{2,1},{5,7},{6,9}} }, {4, {{5,6}} }, {6, {{5,4}} }, 
																   {7, {{4,1}, {5,3}, {8,9}} }, {8, {{5,2}} }, {9, {{8,7}, {5,1}, {6,3}} } };
	unordered_set<int> us;
	int eachCount = 0;

	for (auto ele : umKeyPad)
	{
		us.insert(ele.first);
		if (m == 1)
			eachCount++;
		DFSNumberOfPatternsUtil2(umKeyPad, umKeyPadFarEdges, n, m, us, eachCount, ele.first);
		us.clear();
	}

	return eachCount;
}

bool isMatchWildCard(string s, string p) {
	vector<vector<bool> >  T(s.size() + 1, vector<bool>(p.size() + 1));

	s.insert(0, " ");
	p.insert(0, " ");

	for (int i = 0; i < s.size(); i++)
	{
		for (int j = 0; j < p.size(); j++)
		{
			if (p[j] == s[i] || p[j] == '?')
			{
				if (i == 0 && j == 0)
				{
					T[i][j] = true;
				}
				else
				{
					T[i][j] = (i == 0 || j == 0) ? false : T[i - 1][j - 1];
				}
			}
			else if (p[j] == '*')
			{
				T[i][j] = (i == 0) ? T[i][j - 1] : T[i - 1][j] || T[i][j - 1];
			}
			else
			{
				T[i][j] = false;
			}
		}
	}

	return T[s.size() - 1][p.size() - 1];
}

string longestPalindrome(string str) {
	vector<vector<bool> > T(str.size(), vector<bool>(str.size()));
	pair<int, int> pMaxPair(0, 0);

	for (int len = 1; len <= str.size(); len++)
	{
		for (int j = len - 1; j < str.size(); j++)
		{
			int i = (j - len) + 1;

			if (len == 1)
			{
				T[i][j] = true;
			}
			else if (len == 2)
			{
				if (str[i] == str[j])
				{
					pMaxPair.first = i;
					pMaxPair.second = j;
					T[i][j] = true;
				}
			}
			else
			{
				if (str[i] == str[j] && T[i + 1][j - 1])
				{
					T[i][j] = true;
					pMaxPair.first = i;
					pMaxPair.second = j;
				}
			}
		}
	}

	return str.substr(pMaxPair.first, pMaxPair.second - pMaxPair.first + 1);
}

string hexValue { "0123456789abcdef" };
string base62Value{ "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ" };
using uint64 = unsigned long long;
unordered_map<string, string> umShortLongURLMap;

// convert md5 encoded data to base 10
uint64 ConvertFromHexToBase10(char* md5)
{
	size_t md5len = strlen(md5);
	uint64 finalVal = 0;
	for (int i = 0; i < md5len; i++)
	{
		uint64 val = hexValue.find(md5[i]);
		finalVal += val * pow(16, md5len - i - 1);
	}

	return finalVal;
}

// Convert base 10 to base 62 for storing in hash maps
string ConvertToBase62(uint64 nBase10Value)
{
	string str;
	
	while (nBase10Value != 0)
	{
		uint64 val = nBase10Value % 62;
		str.insert(str.begin(), base62Value[val]);

		nBase10Value /= 62;
	}

	while (str.size() < 6)
	{
		str.insert(str.begin(), '0');
	}

	while (str.size() > 6)
	{
		str.erase(str.begin());
	}

	return str;
}

char* GenerateMD5(string longURL)
{
	char* cToReturn = new char[64]{};
	for (int i = 0; i < 11; i++)
	{
		int randVal = rand() % 16;
		cToReturn[i] = hexValue[randVal];
	}

	return cToReturn;
}

string GenerateShortURL(string longURL)
{
	// Convert from hex to base 10
	//char* md5 = new char[64]{ "d93a360dc5f" };
	char* md5 = GenerateMD5(longURL);
	uint64 nBase10Val = ConvertFromHexToBase10(md5);
	/*time_t timet = system_clock::to_time_t(system_clock::now());
	nBase10Val = nBase10Val << 8;
	timet = timet & 63;
	nBase10Val = nBase10Val | timet;*/

	string sBase62Value = ConvertToBase62(nBase10Val);
	umShortLongURLMap[sBase62Value] = longURL;

	return "http://tiny.url/" + sBase62Value;
}

string GetLongURL(string shortURL)
{
	size_t len = strlen("http://tiny.url/");
	string shortURLSubStr = shortURL.substr(len);
	return umShortLongURLMap[shortURLSubStr];
}

TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) 
{
	if (inorder.size() == 0 || postorder.size() == 0)
	{
		return nullptr;
	}

	// First get the root 
	// last element of postorder is root
	int lastNode = postorder[postorder.size() - 1];

	TreeNode* currentRoot = new TreeNode(lastNode);

	vector<int> newInorderLeftArray(inorder.begin(), find(inorder.begin(), inorder.end(), lastNode));
	vector<int> newPostOrderLeftArray(postorder.begin(), postorder.begin() + newInorderLeftArray.size());
	currentRoot->left = buildTree(newInorderLeftArray, newPostOrderLeftArray);

	vector<int> newInorderRightArray(find(inorder.begin(), inorder.end(), lastNode) + 1, inorder.end());
	vector<int> newPostOrderRightArray(postorder.begin() + newInorderLeftArray.size(), postorder.begin() + (postorder.size() - 1));
	currentRoot->right = buildTree(newInorderRightArray, newPostOrderRightArray);

	return currentRoot;
}

TreeNode* buildTreePreAndIn(vector<int>& preorder, vector<int>& inorder) {
	if (inorder.size() == 0 || preorder.size() == 0)
	{
		return nullptr;
	}

	// First get the root 
	// last element of postorder is root
	int firstNode = preorder[0];

	TreeNode* currentRoot = new TreeNode(firstNode);

	vector<int> newInorderLeftArray(inorder.begin(), find(inorder.begin(), inorder.end(), firstNode));
	vector<int> newPreOrderLeftArray(preorder.begin() + 1, preorder.begin() + newInorderLeftArray.size() + 1);
	currentRoot->left = buildTreePreAndIn(newPreOrderLeftArray, newInorderLeftArray);

	vector<int> newInorderRightArray(find(inorder.begin(), inorder.end(), firstNode) + 1, inorder.end());
	vector<int> newPreOrderRightArray(preorder.begin() + newInorderLeftArray.size() + 1, preorder.end());
	currentRoot->right = buildTreePreAndIn(newPreOrderRightArray, newInorderRightArray);

	return currentRoot;
}

vector<vector<int> > GetSortedBuildings(vector<vector<int> >& buildings)
{
	vector<vector<int> > sortedBuildings;
	for (int i = 0; i < buildings.size(); i++)
	{
		sortedBuildings.push_back(vector<int>{buildings[i][0], buildings[i][2], 0}); // 0 is start
		sortedBuildings.push_back(vector<int>{buildings[i][1], buildings[i][2], 1}); // 1 is end
	}

	sort(sortedBuildings.begin(), sortedBuildings.end(), [](const vector<int>& va, const vector<int>& vb)
	{
		if (va[0] == vb[0])
		{
			if ((va[2] == 0 && vb[2] == 0))
			{
				if (va[1] > vb[1])
				{
					return true;
				}
				else if (va[1] < vb[1])
				{
					return false;
				}
			}
			else if ((va[2] == 1 && vb[2] == 1))
			{
				if (va[1] < vb[1])
				{
					return true;
				}
				else if(va[1] > vb[1])
				{
					return false;
				}
			}

			if (va[2] == 1 && vb[2] == 0)
				return false;
			else if (va[2] == 0 && vb[2] == 1)
				return true;
		}

		return va[0] < vb[0];
	});

	return sortedBuildings;
}

vector<pair<int, int> > getSkyline(vector<vector<int> >& buildings)
{
	// Split start and end
	vector<pair<int, int> > vpRes;
	vector<vector<int> > sortedBuildings = GetSortedBuildings(buildings);

	map<int, int, greater<int> > priorityQueue{ {0, 1} };
	int iMaxValue = 0;

	// when the input is start we insert the height into priority queue
	for (int i = 0; i < sortedBuildings.size(); i++)
	{
		if (sortedBuildings[i][2] == 0) // it means that its a start of a building
		{
			if (sortedBuildings[i][1] > priorityQueue.begin()->first)
			{	
				iMaxValue = sortedBuildings[i][1];
				vpRes.push_back(make_pair(sortedBuildings[i][0], sortedBuildings[i][1]));
			}

			if (priorityQueue.find(sortedBuildings[i][1]) != priorityQueue.end())
				priorityQueue[sortedBuildings[i][1]]++;
			else
				priorityQueue[sortedBuildings[i][1]] = 1;
		}
		else if (sortedBuildings[i][2] == 1) // this means its an end of the building
		{
			if (priorityQueue.find(sortedBuildings[i][1]) != priorityQueue.end())
				priorityQueue[sortedBuildings[i][1]]--;

			if(priorityQueue[sortedBuildings[i][1]] == 0)
				priorityQueue.erase(sortedBuildings[i][1]);

			if (priorityQueue.begin()->first != iMaxValue)
			{
				iMaxValue = priorityQueue.begin()->first;
				vpRes.push_back(make_pair(sortedBuildings[i][0], iMaxValue));
			}
		}
	}

	return vpRes;
}

void LetterCombinationUtil(vector<string>& res, string digits, int currentIndex, string word)
{
	if (digits.size() == 0)
	{
		return;
	}

	if (currentIndex >= digits.size())
	{
		res.push_back(word);
		return;
	}

	for (int i = 0; i < PhoneDictionary[digits[currentIndex]].size(); i++)
	{
		word.push_back(PhoneDictionary[digits[currentIndex]][i]);
		LetterCombinationUtil(res, digits, currentIndex + 1, word);
		word.erase(word.end() - 1);
	}
}

vector<string> letterCombinationsInPhoneNumberMod(string digits) 
{
	vector<string> res;
	string word;
	LetterCombinationUtil(res, digits, 0, word);
	return res;
}

int main()
{
	// Testing Tree Set
	set<TreeSetNode> treenodeset;
	TreeSetNode treenodesetvar;
	treenodesetvar.m_Num = 90;
	treenodesetvar.m_p = make_pair(1, 9);

	TreeSetNode treenodesetvar1;
	treenodesetvar1.m_Num = 23;
	treenodesetvar1.m_p = make_pair(1, 5);

	TreeSetNode treenodesetvar2;
	treenodesetvar2.m_Num = 67;
	treenodesetvar2.m_p = make_pair(1, 14);

	treenodeset.insert(treenodesetvar);
	treenodeset.insert(treenodesetvar1);
	treenodeset.insert(treenodesetvar2);

	// Better letter combination algorithm
	vector<string> letterCombinationResultMod = letterCombinationsInPhoneNumberMod("1");

	// testing std::map with greater<int> comparator
	std::map<int, int, std::greater<int>> m{ { -1, 77 },{ 0, 42 },{ 1, 84 } };
	for (const auto& p : m)
		std::cout << '[' << p.first << ',' << p.second << "]\n";

	// testing that everything is in ascending order
	set<int, greater<int> > testset {3, 5, 1, 4, 8, 101, 12};
	for (auto itr = testset.begin(); itr != testset.end(); itr++)
	{
		cout << *itr << endl;
	}

	// Skyline problem
	vector<vector<int> > vvBuildings{ {0,2,3}, {2,5,3} };
	vector<pair<int, int> > vpSkyline = getSkyline(vvBuildings);

	// Create Tree from inorder and postorder & inorder and preorder
	vector<int> vInOrderInput{ 9,10,14,20,21,26 };
	vector<int> vPostOrderInput{ 9,14,10,21,26,20 };
	vector<int> vPreOrderInput{ 20,10,9,14,26,21 };

	TreeNode* pTreeFromInAndPostOrder = buildTree(vInOrderInput, vPostOrderInput);
	TreeNode* pTreeFromInAndPreOrder = buildTreePreAndIn(vPreOrderInput, vInOrderInput);

	// Creating own hash map
	HashNode<int, int>** ppHashNode = new HashNode<int, int>*;
	HashNode<int, int>* pHashNode = new HashNode<int, int>(2, 100);

	ppHashNode[101] = pHashNode;
	ppHashNode[100] = new HashNode<int, int>{}; // {} initialize object with value equivalent to 0 / empty based on the data types in object

	cout << ppHashNode[100]->GetKey() << endl;

	// Hash Map
	HashMap<int, int> hmHashMap;
	hmHashMap.Insert(4, 1000);
	hmHashMap.Insert(16, 9897);
	hmHashMap.Insert(25, 19908);
	hmHashMap.Insert(16, 1666908);

	cout << hmHashMap.GetValue(4) << endl;
	cout << hmHashMap.GetValue(16) << endl;
	cout << hmHashMap.GetValue(25) << endl;

	// Tiny URL base62 encoder
	string sShortURLResult = GenerateShortURL("http://www.google.com");
	string sGetLongURLResult = GetLongURL(sShortURLResult);

	// Longest Palindromic Substring
	string sLongestPalindromicSubstring = longestPalindrome("cmabbamtuepp");

	// Wild Card
	bool bIsMatchWildCard = isMatchWildCard("dasayaba", "*?a*b*");

	// Android key chain
	int numberOfPatternResult = numberOfPatterns2(2, 1);

	// Palindrome Partitioning
	string palindromePartitioning{ "noonbaba" };
	vector<vector<string> > vvPalindromePartioning = partitionPalindrome(palindromePartitioning);

	// Permutations
	vector<int> vPermutationsInput{ 1,2,3 };
	vector<vector<int> > PermutationsResult = permute(vPermutationsInput);

	// Initializer list
	initializer_list<string> initializerListInput{ "hello", "world", "awesome", "great" };
	initializer_list<string>::iterator itr = initializerListInput.begin();

	// KMP algorithm
	string KMPInputText{ "abxabcabcabyhgmnjuytabcya" };
	string KMPInputPattern{ "abcabyhgmk" };
	bool bKMPIsPatternMatch = KMP(KMPInputText, KMPInputPattern);

	// Burst Balloons
	vector<int> vBurstBalloonsInput{ 3,1,5,8 };
	int iBurstBalloonsResult = maxCoins(vBurstBalloonsInput);

	// Median of two sorted arrays
	vector<int> dmtsa1{ 1 };
	vector<int> dmtsa2{ };
	double dMedianOfTwoSortedArraysResult = findMedianSortedArrays(dmtsa1, dmtsa2);

	// Reg ex matching
	bool IsRegExMatchingResult = isMatch("aa", "a*");

	// Count number less than after self
	vector<int> vCountNumAfterSelfInput{};
	vector<int> vCountNumAfterSelfResult = countSmaller(vCountNumAfterSelfInput);
	float somesqrtValue = sqrt(32);

	// Challenge question
	string reduceStringResult = reduce_string("asdheeeeskaeeele");

	// Shortest Palindrome
	string sShortestPalindromeResult = shortestPalindrome2("aacecaaa");

	// Serialize and De serialize Binary Tree
	TreeNode* tn1 = new TreeNode(5);
	TreeNode* tn2 = new TreeNode(2);
	TreeNode* tn3 = new TreeNode(3);
	TreeNode* tn4 = new TreeNode(2);
	TreeNode* tn5 = new TreeNode(4);
	TreeNode* tn6 = new TreeNode(3);
	TreeNode* tn7 = new TreeNode(1);

	tn1->left = tn2;
	tn1->right = tn3;
	tn3->left = tn4;
	tn3->right = tn5;
	tn4->left = tn6;
	tn4->right = tn7;

	Codec treeCodec;
	string serializedBT = treeCodec.serialize(tn1);
	TreeNode* deserializedBT = treeCodec.deserialize(serializedBT);

	// Game of life
	vector<vector<int> > vGameOfLifeInput{ {1,1,1,0,1,0,0} };
	gameOfLife(vGameOfLifeInput);

	// Word Break 2
	vector<string> vWordBreak2Input{ "cat", "cats", "and", "andd", "an", "sand", "dog", "og", "ddog", "anddo", "g" };
	//vector<string> vWordBreak2Input{ "a","aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa","aaaaaaaaaa" };
	vector<string> vWordBreak2Result = wordBreak2("catsanddog", vWordBreak2Input);

	// Remove Duplicate Letters "fggcdfbbmncbxgds" 
	string sRemoveDupLettersResult = removeDuplicateLetters("mitnlruhznjfyzmtmfnstsxwktxlboxutbic");
	cout << sRemoveDupLettersResult << endl;

	// palindrome pairs
	vector<string> vsPalindromePairsInput = { "", "a" };
	vector<vector<int> > vvPalindromePairsResult = palindromePairs(vsPalindromePairsInput);

	// Convert a file string name to directory structure and find the longest file path
	string sFilePathInput = "dir\n\tsubdir1\n\tsubdir2\n\t\t\t\t";
	cout << sFilePathInput << endl;
	int iLongestFilePath = lengthLongestPath(sFilePathInput);

	// converting INT_MAX to float, we also have FLT_MAX that we can use
	float someFloatValueMax = static_cast<float>(INT_MAX);

	// Enum stuff
	SomeEnum someEnum;
	someEnum = SomeEnum::Bike;

	// Initializing 2d vector
	int dimension = 10;
	vector<vector<int> > vvInitializeVectorOfVector(dimension, vector<int>(dimension));

	// Merge Intervals
	//vector<Interval> vIntervalsInput{ Interval{1,3}, Interval{2,6}, Interval{8,10}, Interval{15,18} };
	vector<Interval> vIntervalsInput{ Interval{ 2,3 }, Interval{ 2,2 }, Interval{ 3,3 }, Interval{ 1,3 }, Interval{ 5,7 }, Interval{ 2,2 }, Interval{ 4,6 } };
	vector<Interval> vIntervalResult = mergeIntervals(vIntervalsInput);

	// Topological Sort Graph
	TopologicalSortGraph tpg;
	tpg.m_NotVisitedNodes.insert('a');
	tpg.m_NotVisitedNodes.insert('b');
	tpg.m_NotVisitedNodes.insert('d');
	tpg.m_NotVisitedNodes.insert('c');

	tpg.m_umAdjList['d'] = unordered_set<char>{ 'a' };
	tpg.m_umAdjList['b'] = unordered_set<char>{ 'a','d' };
	tpg.m_umAdjList['a'] = unordered_set<char>{ 'c' };

	stack<char> sTopologicalSortResult = TopologicalSort(tpg);

	// Max of XOR
	vector<int> vMaxXORInput{ 3,5,10,25,2,8 };
	vector<int> vFindMaxXORPair{};
	int maxXORResult = findMaximumXOR(vMaxXORInput, vFindMaxXORPair);

	// Trie
	Trie trie;
	trie.Insert("car");
	trie.Insert("cart");
	trie.Insert("card");
	trie.Insert("math");
	trie.Insert("mathematics");
	trie.Insert("tan");
	trie.Insert("tangent");
	trie.Insert("tangerine");

	bool IsWordPresent = trie.Search("tangerine");
	bool IsStartsWith = trie.StarsWith("car");

	// Search Matrix
	vector<vector<int> > vSearchMatrixInput{ {  } };

	bool bSearchMatrixResult = searchMatrix(vSearchMatrixInput, 1);

	// Number of Islands
	/*vector<vector<char> > vNumsIslandsInput{ { '1','1','1','1','0' }, 
											 { '1','1','0','1','0' }, 
											 { '1','1','1','0','0' }, 
											 { '0','0','1','0','1' } };*/
	vector<vector<char> > vNumsIslandsInput{ {  } };
	
	int numIslandsResult = numIslands(vNumsIslandsInput);

	// Fraction of recurring decimals
	string sFractionOfRecurringDecimalsResult = fractionToDecimal(-2147483647, 1); // do not use -2147483648

	// modulo negative number
	int moduloNegativeNumber = -45 % -34;

	// Check float stuff
	float valueFromDouble = (7.0 / 3.0);

	// Wiggle Sort
	vector<int> vWiggleSortInput{ 7,2 };
	wiggleSort(vWiggleSortInput);

	// Summary Ranges
	vector<int> vSummaryRangesInput{ 0,2,3,4,6,7,9,10,11,15 };
	vector<string> vsSummaryRangesResult = summaryRanges(vSummaryRangesInput);

	// Guess game
	int guessGameResult = guessNumber(10);

	// check ! operator - makes a 0 to 1 and any number to 0
	int numpower2 = 143;
	int ispower2 = !(numpower2 & (numpower2 - 1));

	// sqrt num & num squares
	int sqrtnumresult = sqrt(3);
	int iNumSquaresResult = numSquares(13);

	// Initializing vector of bool with false
	vector<bool> vbVectorOfBool(6);

	// Word Break
	vector<string> vWordBreak{ "aaaa", "aaa" };
	bool bWordBreakResult = wordBreak("aaaaaaa", vWordBreak);

	// Power of four
	bool IsPowerOfFour = PowOfFour(4096);
	double doubleValue = log(8) / log(2);

	// log
	double logValue = log(8);
	double logValue2 = log(8) / log(2);
	double Power3IntMax = log(UINT_MAX) / log(3);
	unsigned int valuePow3 = pow(3, floor(Power3IntMax));

	// find if power of three
	bool IsPowerOfThreeResult = IsPowerOfThree(1);

	// Testing string stuff
	string sShortURL("t.co/");
	size_t hashName = hash<string>()("Ruchir");
	sShortURL.append(to_string(hashName));

	// next permutation
	vector<int> vNextPermutation { 1,2,3 };

	// Testing conversion of vector to set
	unordered_set<int> sUnorderedSetFromVector(vNextPermutation.begin(), vNextPermutation.end());
	nextPermutation2(vNextPermutation);

	// Dijkstra's Algorithm
	Graph g;
	Node* A = new Node('A', 0);
	Node* B = new Node('B', 0);
	Node* C = new Node('C', 0);
	Node* D = new Node('D', 0);
	Node* H = new Node('H', 0);
	Node* I = new Node('I', 0);
	Node* J = new Node('J', 0);

	g.m_Nodes[A->m_sName] = *A;
	g.m_Nodes[B->m_sName] = *B;
	g.m_Nodes[C->m_sName] = *C;
	g.m_Nodes[D->m_sName] = *D;
	g.m_Nodes[H->m_sName] = *H;
	g.m_Nodes[I->m_sName] = *I;
	g.m_Nodes[J->m_sName] = *J;

	// Heuristics from A to I
	g.m_HeuristicsMap[A->m_sName] = 10;
	g.m_HeuristicsMap[B->m_sName] = 8;
	g.m_HeuristicsMap[C->m_sName] = 4;
	g.m_HeuristicsMap[D->m_sName] = 9;
	g.m_HeuristicsMap[H->m_sName] = 6;
	g.m_HeuristicsMap[J->m_sName] = 3;
	g.m_HeuristicsMap[I->m_sName] = 0;

	g.m_AdjList[A->m_sName].insert(make_pair(1, *D));
	g.m_AdjList[A->m_sName].insert(make_pair(5, *C));
	g.m_AdjList[A->m_sName].insert(make_pair(3, *B));

	g.m_AdjList[D->m_sName].insert(make_pair(1, *A));
	g.m_AdjList[D->m_sName].insert(make_pair(1, *C));

	g.m_AdjList[C->m_sName].insert(make_pair(1, *D));
	g.m_AdjList[C->m_sName].insert(make_pair(5, *A));
	g.m_AdjList[C->m_sName].insert(make_pair(1, *H));
	g.m_AdjList[C->m_sName].insert(make_pair(7, *I));

	g.m_AdjList[B->m_sName].insert(make_pair(3, *A));
	g.m_AdjList[B->m_sName].insert(make_pair(2, *H));

	g.m_AdjList[H->m_sName].insert(make_pair(2, *B));
	g.m_AdjList[H->m_sName].insert(make_pair(1, *C));
	g.m_AdjList[H->m_sName].insert(make_pair(4, *J));

	g.m_AdjList[I->m_sName].insert(make_pair(7, *C));
	g.m_AdjList[I->m_sName].insert(make_pair(1, *J));

	g.m_AdjList[J->m_sName].insert(make_pair(4, *H));
	g.m_AdjList[J->m_sName].insert(make_pair(1, *I));

	// tuple / tie example
	int a, b;
	tie(a, b) = make_tuple(1, 6);
	
	//tuple<int, vector<char> > tShortestPath = DijkstrasAlgorithm(g, *A, *I);
	tuple<int, vector<char> > tShortestPathAStar = AStar(g, *A, *I);
	int shortestPathWeight;
	vector<char> shortestPathAStar;

	tie(shortestPathWeight, shortestPathAStar) = AStar(g, *A, *I);

	// Count Pairs with difference
	vector<int> vWithDiff{ 1,2,3,4,5 };
	int iCountPairsResult = CountPairs(vWithDiff, 2);

	// Spiral order printing
	vector<vector<int> > vvSpiralOrderInput{ {1,7,4}, {2,8,9}, {11,12,13}, {15,16,17}, {91,92,93} };
	vector<int> vSpiralOrderResult = spiralOrder(vvSpiralOrderInput);

	// Return all possible combinations
	vector<string> vAllCombinationsOfPhoneNubmber = PrintAllCombinationsOfGivenPhoneNumber("111261511000");

	// Merge K sorted List
	ListNode* l1 = new ListNode(2);
	ListNode* l2 = new ListNode(10);
	ListNode* l3 = new ListNode(14);
	ListNode* l4 = new ListNode(17);
	l1->next = l2;
	l2->next = l3;
	l3->next = l4;

	// removeAll(10, &l1);

	ListNode* m1 = new ListNode(12);
	ListNode* m2 = new ListNode(14);
	ListNode* m3 = new ListNode(22);
	ListNode* m4 = new ListNode(51);
	ListNode* m5 = new ListNode(59);
	m1->next = m2;
	m2->next = m3;
	m3->next = m4;
	m4->next = m5;

	ListNode* n1 = new ListNode(1);
	ListNode* n2 = new ListNode(7);
	ListNode* n3 = new ListNode(11);
	ListNode* n4 = new ListNode(21);
	n1->next = n2;
	n2->next = n3;
	//n3->next = n4;

	ListNode* o1 = new ListNode(3);
	ListNode* o2 = new ListNode(4);
	ListNode* o3 = new ListNode(9);
	ListNode* o4 = new ListNode(15);
	o1->next = o2;
	o2->next = o3;
	o3->next = o4;

	vector<ListNode*> vVectorOfListNode{m1, l1};
	ListNode* lMergeKSortedList = MergeKLists(vVectorOfListNode);

    return 0;
}

