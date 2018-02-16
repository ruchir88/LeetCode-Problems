// ProblemSet3.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "Header.h"
#include <assert.h>

using namespace std;

void Graph::AddEdge(GraphNode gnFrom, GraphNode *gnTo)
{
	if (gnTo == nullptr)
	{
		m_umGraph[gnFrom] = list<GraphNode>();
	}
	else
	{
		m_umGraph[gnFrom].push_back(*gnTo);
	}
}

void DFSUtil(GraphNode gn, unique_ptr<Graph> &myGraph, string sLevel)
{
	cout << sLevel << " " << gn.GetNodeName() << endl;
	sLevel.append("-");
	for (auto ele : myGraph->m_umGraph[gn])
	{
		DFSUtil(ele, myGraph, sLevel);
	}
}

// LRU Implementation
DBData LRU::Read(int id)
{
	if (m_umHashMap[id] == nullptr)
	{
		cout << "Data Does Not Exist" << endl;
		assert(false);
	}

	DBData dbToReturn = *m_umHashMap[id];

	// Update LRU
	if (dbToReturn.GetID() != m_LRUCache.front().GetID())
	{
		m_LRUCache.remove(*m_umHashMap[id]);
		m_umHashMap[id] = nullptr;
		m_LRUCache.push_front(dbToReturn);
		m_umHashMap[id] = &m_LRUCache.front();
	}

	return dbToReturn;
}

void LRU::Write(DBData db)
{
	// Simply insert at the least recently used location which is the last element in the list, if the element does not exist in the map
	if (m_umHashMap[db.GetID()] == nullptr)
	{
		if (!m_LRUCache.empty() && m_LRUCache.size() == m_LRUSize)
		{
			// pop the last element since it is least used
			m_umHashMap.erase(m_LRUCache.back().GetID());
			m_LRUCache.pop_back();
		}
		m_LRUCache.push_back(db);
		m_umHashMap[db.GetID()] = &m_LRUCache.back();
	}
}

// LRU2 Implementation - to remove least recently used item first always
int LRU2::Read(int id)
{
	if (!m_umHashMap[id])
	{
		// Don't assert here instead Write
		cout << "Data Does Not Exist" << endl;
		assert(false);
	}

	int DataToReturn = m_umHashMap[id];

	// Update LRU
	if (id != m_LRUCache.front())
	{
		m_LRUCache.remove(id);
		m_LRUCache.push_front(id);
	}

	return DataToReturn;
}

void LRU2::Write(DBData db)
{
	// Simply insert at the least recently used location which is the last element in the list, if the element does not exist in the map
	if (!m_umHashMap[db.GetID()])
	{
		if (!m_LRUCache.empty() && m_LRUCache.size() == m_LRUSize)
		{
			// pop the last element since it is least used
			m_umHashMap.erase(m_LRUCache.back());
			m_LRUCache.pop_back();
		}
		m_LRUCache.push_back(db.GetID());
		m_umHashMap[db.GetID()] = db.GetValue();
	}
}

TreeNode* LCA(TreeNode* n1, TreeNode* n2)
{
	unordered_map<int, int> umMap;
	while (n1 != nullptr)
	{
		umMap[n1->m_Value] = 1;
		n1 = n1->m_pParent;
	}

	while (n2 != nullptr)
	{
		if (umMap[n2->m_Value] == 1)
		{
			return n2;
		}
		n2 = n2->m_pParent;
	}

	return nullptr;
}

TreeNode* LCA2(TreeNode* n1, TreeNode* n2)
{
	unordered_set<int> sSet;
	while (n1 != nullptr)
	{
		sSet.insert(n1->m_Value);
		n1 = n1->m_pParent;
	}

	while (n2 != nullptr)
	{
		if (sSet.count(n2->m_Value))
		{
			return n2;
		}
		n2 = n2->m_pParent;
	}

	return nullptr;
}

vector<int> PlusOne(vector<int> &A) {
	// Do not write main() function.
	// Do not read input, instead use the arguments to the function.
	// Do not print the output, instead return values as specified
	// Still have a doubt. Checkout www.interviewbit.com/pages/sample_codes/ for more details

	int carry = 0;
	vector<int> B;
	A[A.size() - 1] += 1;
	bool bCarry = false;
	for (int i = A.size() - 1; i >= 0; --i)
	{
		int temp = 0;
		if (carry == 1)
		{
			temp = 1 + A[i];
		}
		else
		{
			temp = A[i];
		}

		if (temp > 9)
		{
			carry = 1;
			B.insert(B.begin(), 0);
			if (i == 0)
			{
				B.insert(B.begin(), 1);
			}
		}
		else
		{
			carry = 0;
			B.insert(B.begin(), temp);
		}
	}

	while (*B.begin() == 0)
	{
		B.erase(B.begin());
	}

	return B;
}

vector<vector<int> > GeneratePascal(int A) {
	if (A == 0)
	{
		return vector<vector<int> >();
	}

	vector<vector<int> > vReturn;
	vReturn.push_back(vector<int>{1});

	for (unsigned int row = 1; row < A; row++)
	{
		vector<int> vRowVector;
		vRowVector.push_back(1);
		vReturn.push_back(vRowVector);

		for (unsigned int col = 1; col <= row; col++)
		{
			if (col == row)
			{
				vReturn[row].push_back(1);
			}
			else
			{
				vReturn[row].push_back(vReturn[row - 1][col] + vReturn[row - 1][col - 1]);
			}
		}
	}
	return vReturn;
}

// TODO: Not solved!
void SetZeroes(vector<vector<int> > &A)
{
	unordered_set<int> setRowsZeroed{};
	unordered_set<int> setColumnsZeroed{};

	for (unsigned int row = 0; row < A.size(); row++)
	{
		for (unsigned int col = 0; col < A[row].size(); col++)
		{
			if (A[row][col] == 0)
			{
				if (setRowsZeroed.find(row) == setRowsZeroed.end() && setColumnsZeroed.find(col) == setColumnsZeroed.end())
				{
					setRowsZeroed.insert(row);
					for (unsigned int col2 = 0; col2 < A[row].size(); col2++)
					{
						if (A[row][col2] != 0)
						{
							setColumnsZeroed.insert(col2);
							A[row][col2] = 0;
						}
					}

					setColumnsZeroed.insert(col);
					for (unsigned int row2 = 0; row2 < A.size(); row2++)
					{
						if (A[row2][col] != 0)
						{
							setRowsZeroed.insert(row2);
							A[row2][col] = 0;
						}
					}
				}
			}
		}
	}
}

// Merge Overlapping Intervals
vector<Interval> GetMergedOverlappingIntervals(vector<Interval> &A)
{
	vector<Interval> vToReturn;
	sort(A.begin(), A.end(), myObjectOfCompare);

	int ibegin = 0;
	int iend = 1;
	while (iend <= A.size() - 1)
	{
		if (A[ibegin].end >= A[iend].start)
		{
			A[ibegin].end = A[ibegin].end > A[iend].end ? A[ibegin].end : A[iend].end;
			iend++;
		}
		else
		{
			vToReturn.push_back(A[ibegin]);
			ibegin = iend;
			iend++;
		}
	}

	// Last element to be pushed here
	vToReturn.push_back((A[ibegin]));

	return vToReturn;
}

template<class Type, int size>
void Print(Type(&var)[size])
{
	cout << size << endl;
}

unsigned int reverse(unsigned int A) {
	unsigned int reversedBits = 0;

	while (A != 0)
	{
		// Get the least significant bit of number A
		unsigned int leastSignificantBit = A & 1;
		A = A >> 1;
		reversedBits = reversedBits << 1;
		reversedBits |= leastSignificantBit;
	}

	return reversedBits;
}

int removeElement(vector<int> &A, int B) {
	for (int i = 0; i < A.size(); i++)
	{
		if (A[i] == B)
		{
			A.erase(A.begin() + i);
			i--;
		}
	}

	return A.size();
}

void TestMessageDispatcher::FirstMessageActual(int data)
{
	cout << "This is Actual First Message: " << data << endl;
}

void TestMessageDispatcher::SecondMessageActual(int data)
{
	cout << "This is Actual Second Message: " << data << endl;
}

void TestMessageDispatcher::ThirdMessageActual(int data)
{
	cout << "This is Actual Third Message: " << data << endl;
}

void TestMessageDispatcher::FourthMessageActual(int data)
{
	cout << "This is Actual Fourth Message: " << data << endl;
}

void TestMessageDispatcher::OnMessage(string message, int data)
{
	m_Dispatcher.OnMessageFunction(message)(data);
}

int PrintSomething(int data1, int data2)
{
	cout << data1 + data2 << endl;
	return data1 + data2;
}

int powWithMod(int x, int n, int d) {
	// Do not write main() function.
	// Do not read input, instead use the arguments to the function.
	// Do not print the output, instead return values as specified
	// Still have a doubt. Checkout www.interviewbit.com/pages/sample_codes/ for more details
	int result = 1;
	while (n)
	{
		if (n & 1)
			result *= x;
		n >>= 1;
		x *= x;
	}

	int powVal = result;
	int powValSign = 1;
	if (powVal < 0)
	{
		powValSign = -1;
	}

	int l = 1;
	int h = abs(powVal);

	int modVal = 0;
	while (l <= h)
	{
		int mid = h + l / 2;

		if (mid*d == abs(powVal))
		{
			modVal = 0;
		}

		if (mid*d < abs(powVal))
		{
			l = mid + 1;
			modVal = mid*d;
		}

		if (mid*d > abs(powVal))
		{
			h = mid - 1;
		}
	}

	if (powValSign == -1)
	{
		return d + (powVal - modVal);
	}

	return powVal - modVal;
}

ListNode* reverseUtil(ListNode* A, ListNode* head)
{
	if (A->next == nullptr)
	{
		return A;
	}

	ListNode* listNode = reverseUtil(A->next, head);
	listNode->next = A;
	A->next = nullptr;

	return A;
}

// Works Perfectly
ListNode* reverseList(ListNode* A)
{
	if (A->next == nullptr)
	{
		return A;
	}

	ListNode* nextNode = A->next;
	ListNode* listNode = reverseList(A->next);
	nextNode->next = A;
	A->next = nullptr;

	return listNode;
}

int main()
{
	// reverseLinkList
	ListNode *l1 = new ListNode(2);
	ListNode *l2 = new ListNode(4);
	ListNode *l3 = new ListNode(7);
	ListNode *l4 = new ListNode(9);

	l1->next = l2;
	l2->next = l3;
	l3->next = l4;

	ListNode* newListNodeReversed = reverseList(l1);

	// pow with Mod
	int iPowWithModTest = -1 % 20;
	int iPowWithMod = powWithMod(2, 3, 3);

	im_map.assign(0, 5, 'A');
	im_map.assign(2, 9, 'B');

	map<int, int> mIntervalTest;
	mIntervalTest[1] = 3;
	auto itrMap = mIntervalTest.begin();
	mIntervalTest.insert(mIntervalTest.begin(), make_pair(4, 7));

	// Pair
	pair<int, int> p1{ 1, 2 };
	pair<int, int> p2 = make_pair(6, 3);

	unordered_map<int, int> um_pair{ { 29, 1 },{ 990, 78 } };
	auto itrum = um_pair.begin();
	cout << itrum->second << endl;
	um_pair.erase(990);

	// Template Explicit Specialization
	SomeFunctionToTestTemplate<int>(1, 2);
	SomeFunctionToTestTemplate<string>("Ruchir", "Trishla");

	// My Custom Type
	string mctkey1 = "Key1";
	string mctkey2 = "Key2";
	vector<int> vimctValue{ 1,2,4,6,7 };
	vector<string> vsmctValue{ "Ruchir", "Trishla", "One", "Two" };
	unordered_map<string, vector<int> > um_imct;
	um_imct[mctkey1] = vimctValue;
	unordered_map<string, vector<string> > um_smct;
	um_smct[mctkey2] = vsmctValue;
	MyCustomType<string> mct = um_smct;

	// Lambda function
	function<int(int, int)>functionPtr;
	functionPtr = &PrintSomething;

	// Test Message Dispatcher
	TestMessageDispatcher tmd;
	tmd.OnMessage("FirstMessage Call", 122);
	tmd.OnMessage("SecondMessage Call", 542);
	tmd.OnMessage("ThirdMessage Call", 356);
	tmd.OnMessage("FourthMessage Call", 7673);
	tmd.OnMessage("Some Function Call", 1780);

	// Remove Element
	vector<int> vRemoveElement{ 4,1,1,2,1,3 };
	int iRemoveElement = removeElement(vRemoveElement, 1);

	// Reverse Bits
	unsigned int iReversedBits = reverse(11);

	// Merge Overlapping Intervals
	vector<Interval> vInterval{ Interval(2,6), Interval(1,3), Interval(8,10), Interval(15,18) };
	vector<Interval> vIntervalResult = GetMergedOverlappingIntervals(vInterval);

	// Using the type alias
	MyList<string> myCustomList;
	list<string> lListOfString{ "1", "2" };
	myCustomList.push_back(lListOfString);

	// Non type template argument
	int intta[]{ 3,4,5,3,2 };
	Print(intta);

	// Check is_same
	if (is_same<int, int>::value)
	{
		cout << "Successful!!" << endl;
	}
	// SetZeroes;
	vector<vector<int> > vSetZeroesVector{ { 0,0 },{ 1,1 } };
	SetZeroes(vSetZeroesVector);

	// Generate Pascal
	vector<vector<int> > vPascalGenerated = GeneratePascal(5);

	// PlusOne
	vector<int> vPlusOneInput{ 0,0,4,0,8 };
	vector<int> vPlusOneResult = PlusOne(vPlusOneInput);

	TreeNode *t1 = new TreeNode;
	t1->m_Value = 5;
	t1->m_pParent = nullptr;

	TreeNode *t2 = new TreeNode;
	t2->m_Value = 1;
	t2->m_pParent = t1;

	TreeNode *t3 = new TreeNode;
	t3->m_Value = 4;
	t3->m_pParent = t1;

	TreeNode *t4 = new TreeNode;
	t4->m_Value = 6;
	t4->m_pParent = t1;

	TreeNode *t5 = new TreeNode;
	t5->m_Value = 10;
	t5->m_pParent = t2;

	TreeNode *t6 = new TreeNode;
	t6->m_Value = 8;
	t6->m_pParent = t2;

	TreeNode* pReturnedNode = LCA2(t5, t4);

	// string to int, char to int, int to string etc.
	string sStringToInt = "45627";
	int stoiInt = stoi(sStringToInt);

	int iIntegerToString = 89532;
	string tostringVar = to_string(iIntegerToString);

	for (char c : sStringToInt)
	{
		int a = c - '0';
		cout << a << " " << endl;
	}

	// LRU2
	LRU2 lru2;
	lru2.Write(DBData(3345, 1));
	lru2.Write(DBData(1122, 2));
	lru2.Write(DBData(3344, 4));
	lru2.Write(DBData(5566, 6));
	lru2.Write(DBData(6622, 7));
	lru2.Write(DBData(8822, 9));

	int dbIntReturn = lru2.Read(6);
	int dbIntReturn2 = lru2.Read(4);
	int dbIntReturn3 = lru2.Read(9);
	int dbIntReturn4 = lru2.Read(9);

	lru2.Write(DBData(7832, 12));
	int dbReturned5 = lru2.Read(12);

	// LRU 
	LRU lru;
	//lru.Read(1);

	lru.Write(DBData(3345, 1));
	lru.Write(DBData(1122, 2));
	lru.Write(DBData(3344, 4));
	lru.Write(DBData(5566, 6));
	lru.Write(DBData(6622, 7));
	lru.Write(DBData(8822, 9));

	DBData dbReturned = lru.Read(6);
	DBData dbReturned1 = lru.Read(4);
	DBData dbReturned2 = lru.Read(9);
	DBData dbReturned6 = lru.Read(9);

	lru.Write(DBData(7832, 12));
	DBData dbReturned4 = lru.Read(12);

	// Regular Graph
	Node n1("USA", 1, -1);
	Node n2("California", 41, 1);
	Node n3("San Francisco", 105, 41);
	Node n4("Georgia", 42, 1);
	Node n5("Los Angeles", 103, 41);
	Node n6("Atlanta", 107, 42);
	Node n7("Nevada", 44, 1);
	Node n8("Las Vegas", 105, 44);
	Node n9("San Jose", 108, 41);
	Node n10("Savannah", 109, 42);

	vector<Node> vNodes{ n1, n2, n3, n4, n5, n6, n7, n8, n9, n10 };

	// Tree Graph
	unique_ptr<Graph> myGraph(new Graph);

	GraphNode A('A', 3, -1);
	myGraph->SetGraphNode(A.GetValue(), A);
	GraphNode B('B', 5, 3);
	myGraph->SetGraphNode(B.GetValue(), B);
	GraphNode C('C', 12, 5);
	myGraph->SetGraphNode(C.GetValue(), C);
	GraphNode D('D', 65, -1);
	myGraph->SetGraphNode(D.GetValue(), D);
	GraphNode E('E', 48, 65);
	myGraph->SetGraphNode(E.GetValue(), E);
	GraphNode F('F', 22, 3);
	myGraph->SetGraphNode(F.GetValue(), F);
	GraphNode G('G', 23, 48);
	myGraph->SetGraphNode(G.GetValue(), G);
	GraphNode H('H', 24, 5);
	myGraph->SetGraphNode(H.GetValue(), H);

	vector<GraphNode> vGraphNode{ A, B, C, D, E, F, G, H };

	// Parse each node to create map of the graph
	for (auto gn : vGraphNode)
	{
		if (gn.GetParentID() == -1)
		{
			myGraph->AddEdge(gn, nullptr);
		}
		else
		{
			myGraph->AddEdge(myGraph->GetGraphNode(gn.GetParentID()), &gn);
		}
	}

	// Temporary Implementation do this in a separate function
	// BFS
	for (auto ele : myGraph->m_umGraph)
	{
		if (ele.first.GetParentID() == -1)
		{
			queue<GraphNode> printQueue;
			printQueue.push(ele.first);

			while (!printQueue.empty())
			{
				cout << printQueue.front().GetNodeName() << endl;
				for (auto node : myGraph->m_umGraph[printQueue.front()])
				{
					printQueue.push(node);
				}
				printQueue.pop();
			}
			cout << "####" << endl;
		}
	}

	// DFS
	for (auto ele : myGraph->m_umGraph)
	{
		if (ele.first.GetParentID() == -1)
		{
			string sLevel = "-";
			cout << ele.first.GetNodeName() << endl;
			for (auto node : ele.second)
			{
				DFSUtil(node, myGraph, sLevel);
			}
		}
	}

	return 0;
}


