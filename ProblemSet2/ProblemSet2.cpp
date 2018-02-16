// ProblemSet2.cpp : Defines the entry point for the console application.

#include "Header.h"
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <assert.h>
#include <iostream>
#include <functional>

using namespace std;

vector<int> intersect(const vector<int> &A, const vector<int> &B) {
	int j = 0;
	vector<int> vReturn;

	for (int i = 0; i < A.size(); i++)
	{
		for (; j < B.size(); j++)
		{
			if (A[i] == B[j])
			{
				vReturn.push_back(A[i]);
				j++;
				break;
			}
			else if (A[i] < B[j])
			{
				break;
			}
		}
	}

	return vReturn;
}

int findMinXor(vector<int> &A) {
	sort(A.begin(), A.end());

	int iMinimumXORValue = INT_MAX;

	for (size_t i = 0; i < A.size() - 1; i++)
	{
		if ((A[i] ^ A[i + 1]) < iMinimumXORValue)
		{
			iMinimumXORValue = A[i] ^ A[i + 1];
		}
	}

	return iMinimumXORValue;
}

vector<vector<int> > CombinationUtil(vector<vector<int> > vv, int k, int totalnum)
{
	if (vv[0][0] + k - 1 > totalnum)
	{
		return vector<vector<int> >();
	}

	if (vv[0].size() == k)
	{
		return vv;
	}

	vector<vector<int> > vvToReturn;
	for (auto v : vv)
	{
		int start = 1;
		while (start <= totalnum)
		{
			if (v[v.size() - 1] < totalnum && start != v[v.size() - 1])
			{
				if(v[v.size() - 1] < start)
				{
					vector<int> vToInsert = v;
					vToInsert.push_back(start);
					vvToReturn.push_back(vToInsert);
				}
			}
			start++;
		}
	}

	vector<vector<int> > vvv = CombinationUtil(vvToReturn, k, totalnum);
	return vvv;
}

vector<vector<int> > Combination(int n, int k)
{
	vector<vector<int> > vvToReturn;
	for (int i = 1; i <= n; i++)
	{
		vector<vector<int> > vv{ {i} };
		vector<vector<int> > vvTemp = CombinationUtil(vv, k, n);
		vvToReturn.insert(vvToReturn.begin() + vvToReturn.size(), vvTemp.begin(), vvTemp.end());
	}

	return vvToReturn;
}

bool IsPalindrome(string s)
{
	if (s.size() == 1)
	{
		return true;
	}

	int low = 0;
	int high = s.size() - 1;

	while (low <= high)
	{
		if (s[low] == s[high])
		{
			low++;
			high--;
		}
		else
		{
			return false;
		}
	}

	return true;
}

vector<vector<string> > partition(string A) 
{
	static int sizeOfA = A.size();
	if (A.size() == 1)
	{
		vector<vector<string> > vvs{ {A} };
		return vvs;
	}

	string sOldA = A;
	A.pop_back();
	vector<vector<string> > tempvvs = partition(A);
	
	vector<vector<string> > vvToReturn;
	for (auto v : tempvvs)
	{
		vector<string> vtemp = v;
		string strToPush;
		strToPush.push_back(sOldA[sOldA.size() - 1]);
		vtemp.push_back(strToPush);

		vvToReturn.push_back(vtemp);

		bool bInsertIntoReturnvv = false;
		for (int i = v.size() - 1; i < v.size(); i++)
		{
			string str = v[i];

			str.push_back(sOldA[sOldA.size() - 1]);
			if (IsPalindrome(str))
			{
				v[i] = str;
				bInsertIntoReturnvv = true;
			}
		}

		if (bInsertIntoReturnvv)
		{
			vvToReturn.push_back(v);
		}
	}

	if (sOldA.size() == sizeOfA)
	{
		if (IsPalindrome(sOldA))
		{
			vector<string> lastVector;
			lastVector.push_back(sOldA);
			vvToReturn.push_back(lastVector);
		}
	}

	return vvToReturn;
}

vector<int> inorderTraversal(TreeNode* A) 
{
	stack<TreeNode*> stackTreeNode;
	vector<int> viInorderData;
	stackTreeNode.push(A);
	unordered_set<int> usVisitedValue;
	usVisitedValue.insert(A->val);

	// visit left node
	while (!stackTreeNode.empty())
	{
		if (stackTreeNode.top()->left != nullptr)
		{
			if (usVisitedValue.count(stackTreeNode.top()->left->val) == 0)
			{
				int value = stackTreeNode.top()->left->val;
				usVisitedValue.insert(value);
				stackTreeNode.push(stackTreeNode.top()->left);
				continue;
			}
		}

		if (stackTreeNode.top() != nullptr)
		{
			TreeNode* stackTop = stackTreeNode.top();
			int data = stackTop->val;
			viInorderData.push_back(data);

			TreeNode* stackTopsRight = stackTop->right;
			stackTreeNode.pop();
			if (stackTopsRight != nullptr)
			{
				if (usVisitedValue.count(stackTopsRight->val) == 0)
				{
					usVisitedValue.insert(stackTopsRight->val);
					stackTreeNode.push(stackTopsRight);
				}
			}
		}
	}

	return viInorderData;
}

vector<int> postorderTraversal(TreeNode* A)
{
	stack<TreeNode*> stackTreeNode;
	vector<int> viPostorderData;
	stackTreeNode.push(A);
	unordered_set<int> usVisitedValue;
	usVisitedValue.insert(A->val);

	// visit left node
	while (!stackTreeNode.empty())
	{
		TreeNode* topLeftNode = stackTreeNode.top()->left;
		if (topLeftNode != nullptr)
		{
			if (usVisitedValue.count(topLeftNode->val) == 0)
			{
				usVisitedValue.insert(topLeftNode->val);
				stackTreeNode.push(topLeftNode);
				continue;
			}
		}

		if (stackTreeNode.top()->right != nullptr)
		{
			TreeNode* topRightNode = stackTreeNode.top()->right;
			if (topRightNode != nullptr)
			{
				if (usVisitedValue.count(topRightNode->val) == 0)
				{
					usVisitedValue.insert(topRightNode->val);
					stackTreeNode.push(topRightNode);
					continue;
				}
			}
		}

		viPostorderData.push_back(stackTreeNode.top()->val);
		stackTreeNode.pop();
	}

	return viPostorderData;
}

vector<int> preorderTraversal(TreeNode* A)
{
	stack<TreeNode*> stackTreeNode;
	vector<int> viPostorderData;
	stackTreeNode.push(A);

	// visit left node
	while (!stackTreeNode.empty())
	{
		TreeNode* node = stackTreeNode.top();
		viPostorderData.push_back(node->val);
		stackTreeNode.pop();

		if (node->right)
		{
			stackTreeNode.push(node->right);
		}

		if (node->left)
		{
			stackTreeNode.push(node->left);
		}
	}

	return viPostorderData;
}

int height(TreeNode* tn)
{
	if (tn == nullptr)
	{
		return 0;
	}

	return max(1 + height(tn->right), 1 + height(tn->left));
}

int isBalanced(TreeNode* A) 
{
	if (A == nullptr)
	{
		return 1;
	}

	if (A->left == nullptr && A->right == nullptr)
	{
		return 1;
	}

	int leftHeight = height(A->left);
	int rightHeight = height(A->right);

	if (abs(leftHeight - rightHeight) <= 1 && isBalanced(A->left) && isBalanced(A->right))
	{
		return 1;
	}

	return 0;
}

void LevelOrderTraversal(TreeNode* head)
{
	queue<TreeNode*> qTreeNode;
	qTreeNode.push(head);
	int nCurrentLevelNodesToParse = 1;
	int nNodesLeftToParseInCurrentLevel = 1;

	while (!qTreeNode.empty())
	{
		TreeNode* node = nullptr;
		node = qTreeNode.front();
		qTreeNode.pop();
		nNodesLeftToParseInCurrentLevel--;

		if (nNodesLeftToParseInCurrentLevel == 0)
		{
			nCurrentLevelNodesToParse *= 2;
			nNodesLeftToParseInCurrentLevel = nCurrentLevelNodesToParse;
		}
		else
		{
			if (!qTreeNode.empty())
			{
				TreeNode* frontNodeQueue = qTreeNode.front();
				node->next = frontNodeQueue;
			}
			else
			{
				nCurrentLevelNodesToParse *= 2;
				nNodesLeftToParseInCurrentLevel = nCurrentLevelNodesToParse;
			}
		}

		if(node->left != nullptr)
			qTreeNode.push(node->left);

		if (node->right != nullptr)
			qTreeNode.push(node->right);
	}
}

void LevelOrderTraversal2(TreeNode* head)
{
	queue<TreeNode*> qTreeNode;
	qTreeNode.push(head);
	
	while (!qTreeNode.empty())
	{
		int qSize = qTreeNode.size();
		TreeNode* node = nullptr;
		while (qSize > 0)
		{
			node = qTreeNode.front();
			qTreeNode.pop();
			if (qSize > 1)
			{
				node->next = qTreeNode.front();
			}

			if (node)
			{
				if (node->left)
				{
					qTreeNode.push(node->left);
				}
				if (node->right)
				{
					qTreeNode.push(node->right);
				}
			}

			qSize--;
		}
	}
}

bool HasPathSum(TreeNode* head, int sum)
{
	// Base Case
	if (head == nullptr)
	{
		return false;
	}
	else if (head->left == nullptr && head->right == nullptr)
	{
		return sum == head->val;
	}

	// Recursive Case
	sum = sum - head->val;

	bool bHasPathSumLeft = HasPathSum(head->left, sum);
	bool bHasPathSumRight = HasPathSum(head->right, sum);

	return bHasPathSumRight || bHasPathSumLeft;
}

// head = 4
// sum = 4
// vSinglePath = {10, 5}
vector<vector<int> > HasPathSum2Util(TreeNode *head, int sum, vector<int> vSinglePath)
{
	// Base Case
	if (head == nullptr)
	{
		return vector<vector<int> >();
	}
	else if (head->left == nullptr && head->right == nullptr) // leaf node
	{
		if (sum == head->val)
		{
			// push in to vSinglePath into the vector we are going to return
			vSinglePath.push_back(head->val);
			vector<vector<int> > vvToReturn;
			vvToReturn.push_back(vSinglePath);
			return vvToReturn;
		}
	}
	else
	{
		vSinglePath.push_back(head->val);
	}

	sum = sum - head->val;
	// Main vector to return
	vector<vector<int> > vvHasPathSum;
	
	// Recursive Case
	vector<vector<int> > vvHasPathSumLeft = HasPathSum2Util(head->left, sum, vSinglePath);
	vvHasPathSum.insert(vvHasPathSum.begin() + vvHasPathSum.size(), vvHasPathSumLeft.begin(), vvHasPathSumLeft.end());

	vector<vector<int> > vvHasPathSumRight = HasPathSum2Util(head->right, sum, vSinglePath);
	vvHasPathSum.insert(vvHasPathSum.begin() + vvHasPathSum.size(), vvHasPathSumRight.begin(), vvHasPathSumRight.end());

	return vvHasPathSum;
}

vector<vector<int> > HasPathSum2(TreeNode* head, int sum)
{
	if (head == nullptr)
	{
		return vector<vector<int> >();
	}
	else
	{
		vector<int> vSinglePath;
		return HasPathSum2Util(head, sum, vSinglePath);
	}
}

int heightMin(TreeNode* tn)
{
	if (tn == nullptr)
	{
		return 0;
	}

	int heightLeft = heightMin(tn->left);
	int heightRight = heightMin(tn->right);

	int minHeight = 0;
	if (heightLeft == 0 && heightRight == 0)
		minHeight = 1;
	if (heightRight > 0 && heightLeft > 0)
		minHeight = 1 + min(heightLeft, heightRight);
	else if (heightLeft > 0)
		minHeight = 1 + heightLeft;
	else if (heightRight > 0)
		minHeight = 1 + heightRight;

	return minHeight;
}

vector<vector<int> > ThreeSum(vector<int>& nums) 
{
	vector<vector<int> > vvResult;
	sort(nums.begin(), nums.end());
	set<vector<int> > us;

	for (int i = 0; i < nums.size(); i++)
	{
		int j = i + 1;
		int k = nums.size() - 1;
		while(j < k)
		{
			if (nums[i] + nums[j] + nums[k] == 0)
			{
				vector<int> vResult;
				vResult.push_back(nums[i]);
				vResult.push_back(nums[j]);
				vResult.push_back(nums[k]);
				us.insert(vResult);
				j++;
				k--;
			}
			else if(nums[i] + nums[j] + nums[k] < 0)
			{
				j++;
			}
			else
			{
				k--;
			}
		}
	}

	vvResult.assign(us.begin(), us.end());
	return vvResult;
}

bool IsPalindromeInteger(int x) 
{
	if (x < 0)
	{
		return false;
	}

	if (x == 0)
	{
		return true;
	}

	int largeNum = 1000000000;
	while (x / largeNum == 0)
	{
		largeNum /= 10;
	}

	int leftDigitDivisor = largeNum;
	int rightDigitDivisor = 10;

	while (leftDigitDivisor > 1)
	{
		int leftDigit = x / leftDigitDivisor;
		int rightDigit = x % 10;

		if (leftDigit != rightDigit)
		{
			return false;
		}

		// create new x
		x = x % leftDigitDivisor;
		x = x / 10;

		leftDigitDivisor /= 100;
	}

	return true;
}

void FlattenBTToList(TreeNode* root)
{
	if (root == nullptr)
	{
		return;
	}

	FlattenBTToList(root->left);

	// Handle data here
	if (root->left != nullptr)
	{
		TreeNode* pTempTreeNode = root->right;
		root->right = root->left;

		TreeNode* pTempTreeNode2 = root->right;
		while(pTempTreeNode2->right != nullptr)
			pTempTreeNode2 = pTempTreeNode2->right;

		pTempTreeNode2->right = pTempTreeNode;

		root->left = nullptr;
	}

	FlattenBTToList(root->right);
}

ListNode* reverseBetween(ListNode* head, int m, int n)
{
	if (head == nullptr)
	{
		return nullptr;
	}

	if (m >= n)
	{
		return head;
	}

	ListNode* parsingNodeLow = head;
	ListNode* parsingNodeHigh = head;
	stack<ListNode*> sListNodeStack;
	int l = 1;
	int h = 1;

	while (l < m)
	{
		parsingNodeLow = parsingNodeLow->next;
		parsingNodeHigh = parsingNodeHigh->next;
		l++;
		h++;
	}

	while (h < n)
	{
		parsingNodeHigh = parsingNodeHigh->next;
		sListNodeStack.push(parsingNodeHigh);
		h++;
	}
	sListNodeStack.pop();

	while (l < h)
	{
		int tempVal = parsingNodeLow->val;
		parsingNodeLow->val = parsingNodeHigh->val;
		parsingNodeHigh->val = tempVal;
		l++;
		h--;
		parsingNodeLow = parsingNodeLow->next;
		if (!sListNodeStack.empty())
		{
			parsingNodeHigh = sListNodeStack.top();
			sListNodeStack.pop();
		}
	}

	return head;
}

// TODO: Partially completed/correct
TreeNode* LowestCommonAncestorBT(TreeNode* root, TreeNode* p, TreeNode* q)
{
	static bool pfound = false;
	static bool qfound = false;
	TreeNode* pLCA = nullptr;
	if (root == nullptr)
	{
		return nullptr;
	}

	if (root == p || root == q)
	{
		if (root == p)
		{
			pfound = true;
		}
		else
		{
			qfound = true;
		}
		pLCA =  root;
	}

	// Recursive case
	TreeNode* leftNode = LowestCommonAncestorBT(root->left, p, q);
	if (pLCA != nullptr)
	{
		leftNode = pLCA;
	}

	TreeNode* rightNode = LowestCommonAncestorBT(root->right, p, q);
	if (pLCA != nullptr)
	{
		rightNode = pLCA;
	}

	if (leftNode != nullptr && rightNode == nullptr)
	{
		if (qfound)
		{
			return leftNode;
		}
		else
		{
			return nullptr;
		}
	}

	if (leftNode == nullptr && rightNode != nullptr)
	{
		if (pfound)
		{
			return rightNode;
		}
		else
		{
			return nullptr;
		}
	}
	
	if (leftNode && rightNode)
	{
		return root;
	}

	return nullptr;
}

bool IdenticalBinaryTree(TreeNode* t1, TreeNode* t2)
{
	if (t1 == nullptr && t2 == nullptr)
	{
		return true;
	}

	if (t1 == nullptr || t2 == nullptr)
	{
		return false;
	}

	bool b = IdenticalBinaryTree(t1->left, t2->left) && IdenticalBinaryTree(t1->right, t2->right);

	if (t1->val == t2->val)
	{
		return b;
	}
	else
	{
		return false;
	}
}

TreeNode* InvertBinaryTree(TreeNode* root)
{
	// Base case
	if (root == nullptr)
	{
		return nullptr;
	}

	// Recursive case
	TreeNode* leftNode = InvertBinaryTree(root->left);
	TreeNode* rightNode =InvertBinaryTree(root->right);

	if (leftNode != rightNode)
	{
		root->right = leftNode;
		root->left = rightNode;
	}
	
	return root;
}

int BinarySearch(vector<int>& v, int ele)
{
	int low = 0;
	int high = v.size() - 1;

	while (low <= high)
	{
		int mid = low + (high - low) / 2;
		if (v[mid] == ele)
		{
			return mid;
		}

		if (v[mid] < ele)
		{
			low = mid + 1;
		}
		else
		{
			high = mid - 1;
		}
	}

	return -1;
}

vector<int> NextGreaterElement(vector<int>& findNums, vector<int>& nums) 
{
	vector<int> vResult;
	
	for (size_t i = 0; i < findNums.size(); i++)
	{
		for (size_t j = 0; j < nums.size(); j++)
		{
			if (findNums[i] == nums[j])
			{
				int index = j + 1;
				while (index < nums.size())
				{
					if (nums[index] > findNums[i])
					{
						vResult.push_back(nums[index]);
						break;
					}
					index++;
				}
				if (index == nums.size())
				{
					vResult.push_back(-1);
				}
				break;
			}
		}
	}

	return vResult;
}

int maxProfit(vector<int>& prices) 
{
	int minprice = INT_MAX;
	int maxprofit = 0;

	for (int i = 0; i < prices.size(); i++)
	{
		if (prices[i] < minprice)
		{
			minprice = prices[i];
		}
		else if (prices[i] - minprice > maxprofit)
		{
			maxprofit = prices[i] - minprice;
		}
	}

	return maxprofit;
}

int MaxArea(vector<int>& height) 
{
	if (height.size() <= 1)
	{
		return 0;
	}

	int low = 0;
	int high = height.size() - 1;

	int iMaxVolume = INT_MIN;

	while (low < high)
	{
		// Calculate volume
		int minimumHeight = min(height[low], height[high]);
		int volume = minimumHeight * (high - low);
		if (volume > iMaxVolume)
		{
			iMaxVolume = volume;
		}

		if (height[low] <= height[high])
		{
			low++;
		}
		else
		{
			high--;
		}
	}

	return iMaxVolume;
}

int StrStr(string haystack, string needle) 
{
	unordered_set<string> us{ needle };
	
	for (size_t i = 0; i < haystack.size(); i++)
	{
		int lastIndex = needle.size() + i;
		if (lastIndex < haystack.size())
		{
			string substring = haystack.substr(i, needle.size());
			if (us.find(substring) != us.end())
			{
				return i;
			}
		}
	}

	return -1;
}

void quickSot(ListNode* head, int low, int high)
{
	if (head == nullptr)
	{
		return;
	}

	if (low == high)
	{
		return;
	}

	ListNode* pivot = head;
	ListNode* traversingNode = head;

	int pivotIndex = low;
	int itr = low;
	while (itr < high)
	{
		if (pivot->val > traversingNode->next->val)
		{
			// bring the greater value before pivot
			bool b = false;
			ListNode* tempNode = traversingNode->next;
			traversingNode->next = traversingNode->next->next;
			tempNode->next = nullptr;

			if (head->val == pivot->val)
			{
				b = true;
			}
			int tempVal = head->val;
			head->val = tempNode->val;

			ListNode* headNext = head->next;
			ListNode* newNode = new ListNode(tempVal);

			head->next = newNode;
			newNode->next = headNext;
			if (b)
			{
				pivot = newNode;
				traversingNode = pivot;
			}

			pivotIndex++;
		}
		else
		{
			traversingNode = traversingNode->next;
		}
		itr++;
	}

	quickSot(head, low, pivotIndex);
	quickSot(pivot->next, pivotIndex + 1, high);
}

ListNode* sortList(ListNode* head) 
{
	ListNode* lengthCalculatingNode = head;
	int length = 0;
	while (lengthCalculatingNode != nullptr)
	{
		length++;
		lengthCalculatingNode = lengthCalculatingNode->next;
	}

	quickSot(head, 0, length - 1);

	return head;
}

string reverseString(string s) {
	string sToReturn;
	for (int i = s.size() - 1; i >= 0; i--)
	{
		sToReturn.push_back(s[i]);
	}

	return sToReturn;
}

void reverseWords(string &A) {
	string tempString = "";
	bool bAlreadyAppended = false;
	vector<string> vVectorOfString;
	for (int i = 0; i < A.size(); i++)
	{
		if (A[i] != ' ')
		{
			if (bAlreadyAppended)
			{
				bAlreadyAppended = false;
			}
			tempString.push_back(A[i]);
		}
		else
		{
			if (!bAlreadyAppended)
			{
				bAlreadyAppended = true;
				vVectorOfString.push_back(tempString);
				tempString = "";
			}
		}
	}

	if (A[A.size() - 1] != ' ')
	{
		vVectorOfString.push_back(tempString);
	}

	tempString.clear();
	A.clear();
	for (int i = vVectorOfString.size() - 1; i >= 0; i--)
	{
		A.append(" ");
		A.append(vVectorOfString[i]);
	}
	
	A.erase(A.begin());
}

int GetNumberOfDigits(int num)
{
	int numDigits = 0;
	while (num > 0)
	{
		numDigits++;
		num /= 10;
	}

	return numDigits;
}

int Atoi(string str)
{
	int i = 0; 
	int signOfNum = 1;
	int numToReturn = 0;

	while (str[i] == ' ')
	{
		i++;
	}

	if (str[i] == '-' || str[i] == '+')
	{
	    signOfNum = str[i] == '-' ? -1 : 1;
		i++;
	}

	while (str[i] >= '0' && str[i] <= '9')
	{
		if (numToReturn > INT_MAX / 10 || (numToReturn == INT_MAX / 10 && str[i] > '7'))
		{
			if (signOfNum < 1)
			{
				return INT_MIN;
			}
			else
			{
				return INT_MAX;
			}
		}

		int num = str[i] - '0';
		numToReturn = numToReturn*10 + num;
		i++;
	}

	return numToReturn * signOfNum;
}

bool IsValid(char c)
{
	if (isalnum(tolower(c)))
	{
		return true;
	}
	return false;
}

bool IsPalindromeWithNoCase(string A) 
{
	int l = 0;
	int h = A.size() - 1;

	while (l < h)
	{
		if (IsValid(A[l]) && IsValid(A[h]))
		{
			if (tolower(A[l]) == tolower(A[h]))
			{
				l++;
				h--;
			}
			else
			{
				return false;
			}
		}
		else if (IsValid(A[l]))
		{
			h--;
		}
		else if (IsValid(A[h]))
		{
			l++;
		}
		else
		{
			l++;
			h--;
		}
	}

	return true;
}

int kthSmallestElementUtil(TreeNode* root, int& k)
{
	if (root == nullptr)
	{
		return -1;
	}

	int kthSmallestLeftTree = kthSmallestElementUtil(root->left, k);
	if (k == 0)
	{
		return kthSmallestLeftTree;
	}
	k--;
	if (k <= 0 )
	{
		return root->val;
	}

	return kthSmallestElementUtil(root->right, k);
}

int kthSmallest(TreeNode* root, int k) 
{
	return kthSmallestElementUtil(root, k);
}

TreeNode* CreateBalancedBinaryTree(vector<int> vInput)
{
	if (vInput.size() == 0)
	{
		return nullptr;
	}

	int l = 0;
	int h = vInput.size() - 1;
	int mid = l + (h - l) / 2;

	// Create Node
	TreeNode* node = new TreeNode(vInput[mid]);

	vector<int> leftPart;
	leftPart.assign(vInput.begin(), vInput.begin() + mid);
	node->left = CreateBalancedBinaryTree(leftPart);

	vector<int> rightPart;
	rightPart.assign(vInput.begin() + mid + 1, vInput.end());
	node->right = CreateBalancedBinaryTree(rightPart);

	return node;
}

int lis(const vector<int> &A) 
{
	// Sample for having dynamic size of an array
	/*int sizeOfArrayA = A.size();
	int *arr = new int[sizeOfArrayA];*/
	vector<int> lisTracking;
	for (size_t i = 0; i < A.size(); i++)
	{
		lisTracking.push_back(1);
	}
	
	int i = 1;
	int j = 0;
	int maxValue = 1;
	
	while (i < A.size())
	{
		while (j < A.size())
		{
			if (A[i] > A[j])
			{
				if(lisTracking[i] <= lisTracking[j])
					lisTracking[i] = lisTracking[j] + 1;

				// Storing max value
				if (lisTracking[i] > maxValue)
				{
					maxValue = lisTracking[i];
				}
			}
			else if(i == j)
			{
				j = 0;
				break;
			}
			j++;
		}
		i++;
	}
	
	return maxValue;
}

int longestSubsequenceLength(const vector<int> &A) {
	vector<int> lisTrackingInc;
	vector<int> lisTrackingDec;
	for (size_t i = 0; i < A.size(); i++)
	{
		lisTrackingInc.push_back(1);
		lisTrackingDec.push_back(1);
	}

	int i = 1;
	int j = 0;
	int maxValue = 1;

	while (i < A.size())
	{
		while (j < A.size())
		{
			if (A[i] > A[j])
			{
				if (lisTrackingInc[i] <= lisTrackingInc[j])
					lisTrackingInc[i] = lisTrackingInc[j] + 1;
			}
			else if (i == j)
			{
				j = 0;
				break;
			}
			j++;
		}
		i++;
	}

	int i2 = A.size() - 2;
	int j2 = A.size() - 1;

	while (i2 >= 0)
	{
		while (j2 >= 0)
		{
			if (A[i2] > A[j2])
			{
				if (lisTrackingDec[i2] <= lisTrackingDec[j2])
					lisTrackingDec[i2] = lisTrackingDec[j2] + 1;
			}
			else if (i2 == j2)
			{
				j2 = A.size() - 1;
				break;
			}
			j2--;
		}
		i2--;
	}

	for (int i = 0; i < A.size(); i++)
	{
		if(lisTrackingInc[i] + lisTrackingDec[i] - 1 > maxValue)
		{
			maxValue = lisTrackingInc[i] + lisTrackingDec[i] - 1;
		}
	}

	return maxValue;
}

int maxPathSumUtil(TreeNode* root, int& maxsum, int sum)
{
	if (root == nullptr)
	{
		return 0;
	}

	if (root->left == nullptr && root->right == nullptr)
	{
		return root->val;
	}

	sum += max(maxPathSumUtil(root->right, maxsum, sum), maxPathSumUtil(root->left, maxsum, sum)) + root->val;
	
	if (sum > maxsum)
	{
		maxsum = sum;
	}

	return maxsum;
}

int maxPathSum(TreeNode* root)
{
	if (root == nullptr)
	{
		return 0;
	}

	if (root->left == nullptr && root->right == nullptr)
	{
		return root->val;
	}

	int maxsum = 0;
	int sum = 0;
	int leftSum = maxPathSumUtil(root->left, maxsum, sum);

	int maxsum2 = 0;
	int sum2 = 0;
	int rightSum = maxPathSumUtil(root->right, maxsum2, sum2);
}

int CanCompleteCiruit(vector<int>& gas, vector<int>& cost)
{
	if (gas.size() != cost.size())
	{
		assert(!"size should be same");
	}

	if (gas.size() == 1)
	{
		return 0;
	}

	int start = 0;
	int end = 1;

	while (start != end)
	{
		int iGasLeft = gas[start] - cost[start];
		while (iGasLeft > 0 && start != end)
		{
			iGasLeft += gas[end] - cost[end];
			end = (end + 1) % gas.size();
		}

		if (start == end)
		{
			return start;
		}

		start = (start + 1) % gas.size();
		if (start == 0)
		{
			return -1;
		}
		end = (start + 1) % gas.size();
	}

	return -1;
}

int LongestCommonSubSequence(string sequence1, string sequence2)
{
	// *vector initialization important*
	vector<vector<int> > vLCSGrid(sequence1.size(), std::vector<int>(sequence2.size()));

	for (int i = 0; i < sequence1.size(); i++)
	{
		for (int j = 0; j < sequence2.size(); j++)
		{
			if (i == 0 && j == 0)
			{
				if (sequence1[i] == sequence2[j])
				{
					vLCSGrid[i][j] += 1;
				}
			}
			else if (i == 0)
			{
				if (sequence1[i] == sequence2[j])
				{
					vLCSGrid[i][j] = vLCSGrid[i][j - 1] + 1;
				}
				else
				{
					vLCSGrid[i][j] = vLCSGrid[i][j - 1];
				}
			}
			else if (j == 0)
			{
				if (sequence1[i] == sequence2[j])
				{
					vLCSGrid[i][j] = vLCSGrid[i - 1][j] + 1;
				}
				else
				{
					vLCSGrid[i][j] = vLCSGrid[i - 1][j];
				}
			}
			else
			{
				if (sequence1[i] == sequence2[j])
					vLCSGrid[i][j] = max(vLCSGrid[i][j - 1], vLCSGrid[i - 1][j]) + 1;
				else
					vLCSGrid[i][j] = max(vLCSGrid[i][j - 1], vLCSGrid[i - 1][j]);
			}
		}
	}

	return vLCSGrid[sequence1.size() - 1][sequence2.size() - 1];
}

class Comparator
{
public:
	bool operator()(const int& a, const int& b) const
	{
		return a > b;
	}
};

void FunctionPointerParam(function<void(int)> c)
{
	c(8);
}

void FunctionPointerInt(int a)
{
	cout << a << endl;
}

class ComparatorFunctor
{
public:
	void operator()(int a)
	{
		cout << a << endl;
	}
};

int findDuplicate(vector<int> nums)
{
	int iRepeatingNumber;
	for (int i = 0; i < nums.size(); i++)
	{
		if (nums[i] != i + 1)
		{
			if (nums[i] == nums[nums[i] - 1])
			{
				iRepeatingNumber = nums[i];
				break;
			}
			int temp = nums[i];
			nums[i] = nums[nums[i] - 1];
			nums[temp - 1] = temp;
			i--;
		}
	}

	return iRepeatingNumber;
}

void MoveZeroes(vector<int>& nums)
{
	int j = 0;
	for (int i = 0; i < nums.size(); i++)
	{
		for (; j < nums.size(); j++)
		{
			if (i < j)
			{
				if (nums[i] == 0 && nums[j] != 0)
				{
					// swap array elements
					int temp = nums[i];
					nums[i] = nums[j];
					nums[j] = temp;
					break;
				}
				else if (nums[i] != 0)
				{
					break;
				}
			}
		}
	}
}

class TestObject
{
public:
	int val;
	TestObject* next;
};

int trap(const vector<int> &tank) 
{
	if (tank.size() <= 2 )
	{
		return 0;
	}

	int low = 0;
	int high = tank.size() - 1;

	int heightStart = tank[low];
	int heightEnd = tank[high];

	while (heightStart == 0)
	{
		low++;
		heightStart = tank[low];
	}

	int minHeight = min(heightStart, heightEnd);
	int iVol = 0;
	if(low < high)
		iVol = minHeight * (high - low - 1);

	if (heightStart > heightEnd)
	{
		high--;
	}
	else
	{
		low++;
	}

	while (low < high)
	{
		heightStart = tank[low];
		heightEnd = tank[high];

		if (heightStart >= heightEnd)
		{
			int minToDeduct = min(minHeight, heightEnd);
			iVol = iVol - (minToDeduct * 1);
			high--;
		}
		
		if(heightStart < heightEnd)
		{
			int minToDeduct = min(heightStart, minHeight);
			iVol = iVol - (minToDeduct * 1);
			low++;
		}

		if (heightStart > minHeight && heightEnd > minHeight)
		{
			int previousMinHeight = minHeight;
			minHeight = min(heightStart, heightEnd);
			int addVolume = (minHeight - previousMinHeight) * (high - low);

			iVol += addVolume;
		}
	}

	return iVol;
}

int MaximumUnsortedSubArray(vector<int>& nums)
{
	if (nums.size() == 0)
	{
		return 0;
	}

	if (nums.size() == 1)
	{
		return nums[0];
	}

	int maxSumSoFar = nums[0];
	int maxSumCurrent = nums[0];

	for (int i = 1; i < nums.size(); i++)
	{
		maxSumCurrent = maxSumCurrent + nums[i];
		int maximumVal = max(maxSumCurrent, nums[i]);
		maxSumCurrent = maximumVal;

		if (maximumVal > maxSumSoFar)
		{
			maxSumSoFar = maximumVal;
		}
	}

	return maxSumSoFar;
}

vector<int> subUnsort(vector<int> &nums) 
{
	if (nums.size() <= 1)
	{
		return vector<int>(-1);
	}

	int low = 0;
	int high = nums.size() - 1;

	while (nums[low] <= nums[low + 1])
	{
		if (low == nums.size() - 2)
		{
			break;
		}

		if (low < nums.size() - 2)
			low++;
	}

	while (nums[high] >= nums[high - 1])
	{
		if (high == 1)
			break;

		if (high > 1)
			high--;
	}

	vector<int> vResult;
	if (high - low <= 1)
	{
		vResult.push_back(-1);
	}
	else
	{
		if (low == 0)
			vResult.push_back(nums[low]);
		else
			vResult.push_back(nums[low - 1]);

		vResult.push_back(nums[high]);
	}

	return vResult;
}

ListNode* SwapNodeInPairs(ListNode* head)
{
	// TODO: Implement the function
	return nullptr;
}

string LongestPalindromicSubstring(string str)
{
	int iMaximumSizeOfPalindrome = 0;
	string sLongestPalindrome(1, str[0]);

	for (int i = 0; i < str.size(); i++)
	{
		string tempStr;
		tempStr.push_back(str[i]);
		for (int j = i + 1; j < str.size(); j++)
		{
			tempStr.push_back(str[j]);
			if (IsPalindrome(tempStr))
			{
				if (tempStr.size() > iMaximumSizeOfPalindrome)
				{
					iMaximumSizeOfPalindrome = tempStr.size();
					sLongestPalindrome = tempStr;
				}
			}
		}
	}

	return sLongestPalindrome;
}

int main()
{
	list<int> listToTestUnique;
	listToTestUnique.push_back(1);
	listToTestUnique.push_back(2);
	listToTestUnique.push_back(3);
	listToTestUnique.push_back(6);
	listToTestUnique.push_back(6);
	listToTestUnique.push_back(6);

	listToTestUnique.unique();

	// Longest Palindromic substring
	string sLongestPalindromicSubstringResult = LongestPalindromicSubstring("babaddab"); // ans: baddab

	// next permutation
	string nextPermutationNumInput{ "231" };
	//sort(nextPermutationNumInput.begin(), nextPermutationNumInput.end());

	do 
	{
		cout << nextPermutationNumInput << endl;
	} while (next_permutation(nextPermutationNumInput.begin(), nextPermutationNumInput.end()));

	// Distance
	vector<int> vFindDistance{ 2,4,5,6,1,10,8 };
	auto itrFindDistance = find(vFindDistance.begin(), vFindDistance.end(), 10);
	int indexOfFindDistance = distance(vFindDistance.begin(), itrFindDistance);

	// Sub array that sort the whole array
	vector<int> vSubUnsortInput{ 1,1 };
	vector<int> vSubUnsortResult = subUnsort(vSubUnsortInput);

	// Max Sum in Sub array
	vector<int> vMaximumUnsortedSubArray{ -2,1,-3,4,-1,2,1,-5,4 };
	int iMaximumSumResult = MaximumUnsortedSubArray(vMaximumUnsortedSubArray);

	// Trapped Water
	vector<int> vTrappedWaterInput{ 0,1,0,2,1,0,1,3,2,1,2,1 };
	int iTrappedWaterResult = trap(vTrappedWaterInput);

	// Testing that custom object pointers can be key for unordered map or set
	unordered_map<TestObject*, int> uumm;
	TestObject* t = new TestObject;
	t->val = 10;
	t->next = nullptr;

	TestObject* t1 = new TestObject;
	t1->val = 39;
	t1->next = nullptr;

	int *a = new int[10];
	int *b = new int(5);
	uumm[t] = 11;
	uumm[t1] = 6;

	// Move Zero's
	vector<int> vMoveZeroes{ 2,8,0,0,0,0,55,6,0,0,77,0,1,0,3,12,0,0 };
	MoveZeroes(vMoveZeroes);

	// Find Duplicates
	int FindDuplicateResult = findDuplicate({ 3,4,1,4,1 });

	// sort using comparator
	vector<int> vSortVectorInput{ 1,5,6,2,37,1,4,65 };
	sort(vSortVectorInput.begin(), vSortVectorInput.end(), Comparator());

	FunctionPointerParam(FunctionPointerInt);

	priority_queue<int, vector<int>, Comparator> pq;
	pq.push(4);
	pq.push(6);
	pq.push(2);
	pq.push(10);
	pq.push(1);
	pq.pop();
	pq.pop();
	pq.pop();
	pq.pop();

	// Longest Common SubSequence
	string sLCSInput1 = "ABDFGM";
	string sLCSInput2 = "ACDBFKG";
	int LongestCommonSubSequenceResult = LongestCommonSubSequence(sLCSInput1, sLCSInput2);

	// Gas Station
	vector<int> vCanCompleteCircuitInputGas{ 2,3,2 };
	vector<int> vCanCompleteCircuitInputCost{ 4,6,3 };
	int CanCompleteCiruitResult = CanCompleteCiruit(vCanCompleteCircuitInputGas, vCanCompleteCircuitInputCost);

	// Longest Subsequence 
	vector<int> lsInput{ 1,11,2,10,4,5,2,1 };
	int lsResult = longestSubsequenceLength(lsInput);

	// Longest Increasing Subsequence
	vector<int> lisInput{ 14, 24, 18, 46, 55, 53, 82, 18, 101, 20, 78, 35, 68, 9, 16, 93, 101, 85, 81, 28, 78 };
	int lisResult = lis(lisInput);

	// Create Balanced Binary Tree
	TreeNode* tnBalancedBinaryTree = CreateBalancedBinaryTree({ 1,3,5,7,9,10,11 });

	// Is Palindrome with no case
	bool bIsPalindromeNoCase = IsPalindromeWithNoCase("race a car");

	// isdigit, isalnum, tolower and toupper
	char c = tolower('A');
	bool isAlphaNum = isalnum('B');

	// Implement atoi
	int ffffff = atoi("-2147483648");
	int num = Atoi("-2147483648");

	// Reverse Words
 	string reverseWordsInput = "   Hello  my   name   is Ruchir ";
	reverseWords(reverseWordsInput);

	// Reverse String
	string reversedStringResult = reverseString("Hello");

	// Sort List
	ListNode* sln1 = new ListNode(3);
	ListNode* sln2 = new ListNode(2);
	ListNode* sln3 = new ListNode(1);
	ListNode* sln4 = new ListNode(11);
	ListNode* sln5 = new ListNode(6);
	sln1->next = sln2;
	sln2->next = sln3;
	sln3->next = sln4;
	sln4->next = sln5;

	// sort list
	ListNode* sortListResult = sortList(sln1);

	// Swap in pairs
	ListNode* swapNodeInPairsResult = SwapNodeInPairs(sln1);

	// StrStr
	string sStrStrInput1{ "Getting Something" };
	string sStrStrInput2{ "Some" };
	int sStrStrResult = StrStr(sStrStrInput1, sStrStrInput2);

	// Max Area and height
	vector<int> vMaxAreaInput{ 2,1,3,10,1,1,10,3 };
	int iMaxAreaResult = MaxArea(vMaxAreaInput);

	// Best time to Sell Stocks
	vector<int> vBestTimeToSellStocksInput{ 7,1,5,3,6,4 };
	int iBestTimeToSellStocksResult = maxProfit(vBestTimeToSellStocksInput);

	// Next greater number
	vector<int> nums1NextGreaterNum{ 2,3 };
	vector<int> nums2NextGreaterNum{ 1,2,3,4 };
	vector<int> nextGreaterNumResult = NextGreaterElement(nums1NextGreaterNum, nums2NextGreaterNum);

	// Tree Node
	TreeNode* tn1 = new TreeNode(2);
	TreeNode* tn2 = new TreeNode(-1);
	TreeNode* tn3 = new TreeNode(3);
	TreeNode* tn4 = new TreeNode(4);
	TreeNode* tn5 = new TreeNode(5);
	TreeNode* tn6 = new TreeNode(6);
	TreeNode* tn7 = new TreeNode(7);
	TreeNode* tn8 = new TreeNode(8);
	TreeNode* tn9 = new TreeNode(9);

	tn1->left = tn2;
	tn2->left = tn3;
	tn2->right = tn4;
	tn1->right = tn5;
	tn5->left = tn6;
	tn5->right = tn7;
	tn3->left = tn8;
	tn3->right = tn9;

	// Max Path Sum
	int maxPathSumResult = maxPathSum(tn1);

	// Invert Binary Tree
	TreeNode* invertedBTTreeNode = InvertBinaryTree(tn1);

	ListNode* l1 = new ListNode(1);
	ListNode* l2 = new ListNode(2);
	ListNode* l3 = new ListNode(3);
	ListNode* l4 = new ListNode(4);
	ListNode* l5 = new ListNode(5);

	l1->next = l2;
	l2->next = l3;
	l3->next = l4;
	l4->next = l5;

	// Reverse Between
	ListNode* lnReverseBetweenResult = reverseBetween(l1, 2, 1);

	// Is number Palindrome
	bool bIsPalidromeIntegerResult = IsPalindromeInteger(0);

	// Testing vector ==operator
	vector<int> vvv1{ 1,4,7 };
	vector<int> vvv2{ 1,6,7 };
	vector<int> vvv3{ 3,5,7 };

	vector<vector<int> > vvvv;
	vvvv.push_back(vvv1);
	vvvv.push_back(vvv2);

	if (find(vvvv.begin(), vvvv.end(), vvv2) != vvvv.end())
	{
		cout << "Same" << endl;
	}

	// Three Sum Zero
	vector<int> vVectorInt {-1,0,1,2,-1,-4,2,-1};
	vector<vector<int> > vvThreeSum = ThreeSum(vVectorInt);

	// Inorder without recurrsive;
	TreeNode* t10 = new TreeNode(2);
	TreeNode* t5 = new TreeNode(1);
	TreeNode* t21 = new TreeNode(21);
	TreeNode* t4 = new TreeNode(4);
	TreeNode* t7 = new TreeNode(7);
	TreeNode* t25 = new TreeNode(25);
	TreeNode* t8 = new TreeNode(8);
	TreeNode* t20 = new TreeNode(20);
	TreeNode* t15 = new TreeNode(15);
	TreeNode* t9 = new TreeNode(9);

	t10->left = t5;
	t5->right = t7;
	t10->right = t20;
	t20->left = t15;
	t20->right = t25;
	t25->left = t21;
	t7->right = t9;
	t5->left = t4;
	t9->left = t8;

	// kth Smallest Element in binary tree
	int kthSmallesElementResult = kthSmallest(t10, 2);

	vector<int> vInorderListResult = inorderTraversal(t10);
	vector<int> vPostOrderListResult = postorderTraversal(t10);
	vector<int> vPreOrderListResult = preorderTraversal(t10);

	// Identical Binary Tree
	// bool bIdenticalBinaryTreeResult = IdenticalBinaryTree(t10, t102);

	// LeastCommon Ancestor
	TreeNode* pLeastCommonAncestorResult = LowestCommonAncestorBT(t10, t5, t4);

	// Flatten BST to List
	FlattenBTToList(t10);

	// Level order traversal
	LevelOrderTraversal2(t10);

	// Is tree balanced
	int bIsBinaryTreeBalancedResult = isBalanced(t10);

	// Has Path Sum
	bool bHasPathSumResult = HasPathSum(t10, 45);

	// Has Path Sum
	vector<vector<int> > vvHasPathSumResult = HasPathSum2(t10, 45);
	
	// Minimum Height
	int minHeight = heightMin(t10);

	// PartitionPalindromen - incomplete
	vector<vector<string> > vPartitionResult = partition("cnoonb");

	// Combination
	vector<vector<int> > vvCombinationResult = Combination(6, 5);

	// Intersection in two vectors
	vector<int> vIntersect1{ 6,7,10,11,12,12,13 };
	vector<int> vIntersect2{ 1,5,8,11,12 };
	vector<int> vIntersectResult = intersect(vIntersect1, vIntersect2);

	vector<int> vFindMinXOR{ 12,4,6,2 };
	int iFindMinXORResult = findMinXor(vFindMinXOR);

    return 0;
}

