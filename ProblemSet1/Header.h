#pragma once
#include <iostream>
#include <list>
#include <queue>
#include <deque>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <functional>
#include <math.h>
#include <memory>
#include <set>
#include <stack>
#include <initializer_list>
#include <chrono>

using namespace std;
using std::chrono::system_clock;

class ListNode
{
public:
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(nullptr) {}
};

// Graph Node for Dijkstra's Algorithm
class Node
{
public:
	char m_sName;
	char m_cFromNode{'\0'};
	int m_iMinDistanceToReachThisNode{0};
	int m_iMinCombinedHueristic{ 0 }; // For A* only - make it 1 when A* is not used
	Node() = default;
	Node(char name, int iDistance) : m_sName(name), m_iMinDistanceToReachThisNode(iDistance) {}

	bool operator==(const Node& other) const
	{
		return m_sName == other.m_sName;
	}
};

template<>
struct hash<Node>
{
	size_t operator()(const Node& node) const
	{
		return (hash<char>()(node.m_sName));
	}
};

template<>
struct hash<pair<int, Node> >
{
	size_t operator()(const pair<int, Node>& node) const 
	{
		return (hash<char>()(node.second.m_sName));
	}
};

// for all pairs we will have to template specialize the hash function
template<>
struct hash<pair<int, int> >
{
	size_t operator()(const pair<int, int>& node) const
	{
		return (hash<int>()(node.second));
	}
};

class Graph
{
public:
	// list of all unique nodes - sms - set {nodes}, m{map of name of node to adjacent nodes}, s{visited nodes}
	unordered_map<char, Node> m_Nodes{};

	// Heuristics map
	unordered_map<char, int> m_HeuristicsMap{};

	// map of name of node to set of nodes which is a pair of complete Node and its distance from the key node
	// Key - node name - char
	// Value - adjacent nodes with distance - pair <distance to reach the adjacent node, adjacent node>
	unordered_map<char, unordered_set< pair<int, Node> > > m_AdjList{};

	// set of nodes that are parsed already
	unordered_set<Node> m_usParsedNode{};
};

class TrieNode
{
public:
	// always use pointer when referencing self
	unordered_map<char, TrieNode*> m_usChildren;
	bool IsCompleteWord{false};
};

class Trie
{
public:
	TrieNode *m_TrieNode{nullptr};

	Trie()
	{
		m_TrieNode = new TrieNode;
	}

	~Trie()
	{
		delete m_TrieNode;
		m_TrieNode = nullptr;
	}

	void Insert(string word);
	bool Search(string word);
	bool StarsWith(string word);
};

class TrieNodeBinary
{
public:
	unordered_map<int, TrieNodeBinary*> m_umChildren;
	bool m_IsLastNode;
	int m_Number;
};

class TrieBinary
{
public:
	TrieNodeBinary* m_TrieNodeBinary{nullptr};

	TrieBinary()
	{
		m_TrieNodeBinary = new TrieNodeBinary();
	}

	~TrieBinary()
	{
		delete m_TrieNodeBinary;
		m_TrieNodeBinary = nullptr;
	}

	void Insert(int i);
};

class TopologicalSortGraph
{
public:
	unordered_set<char> m_NotVisitedNodes;
	unordered_map<char, unordered_set<char> > m_umAdjList;

	// Data structure to help in topological sorting
	unordered_set<char> m_sVisitedNode;
	stack<char> m_sSortedStack;
};

struct Interval {
	int start;
	int end;
	Interval() : start(0), end(0) {}
	Interval(int s, int e) : start(s), end(e) {}
};

// Tree Node
class TreeNode {
public:
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode *next;
	TreeNode() = default;
	TreeNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
};

class Codec {
public:
	deque<TreeNode*> m_dqTreeNode;
	string m_SerializedTree;

	// Encodes a tree to a single string.
	string serialize(TreeNode* root) 
	{
		m_dqTreeNode.push_back(root);

		while (!m_dqTreeNode.empty())
		{
			if (m_dqTreeNode.front() != nullptr)
			{
				m_SerializedTree.append(to_string(m_dqTreeNode.front()->val));
			}
			else
			{
				m_SerializedTree.append("null");
			}
			
			m_SerializedTree.push_back(',');

			TreeNode* currentNode = m_dqTreeNode.front();
			m_dqTreeNode.pop_front();
			
			if (currentNode != nullptr)
			{
				m_dqTreeNode.push_back(currentNode->left);
				m_dqTreeNode.push_back(currentNode->right);
			}
		}
		
		m_SerializedTree.erase(m_SerializedTree.size() - 1, 1);
		return m_SerializedTree;
	}

	// Decodes your encoded data to tree.
	TreeNode* deserialize(string data) 
	{
		string sNode;
		for (int i = 0; i < data.size(); i++)
		{
			if (data[i] != ',')
			{
				sNode.push_back(data[i]);
			}
			else
			{
				if (sNode == "null")
				{
					m_dqTreeNode.push_back(nullptr);
					sNode.clear();
				}
				else
				{
					TreeNode *tn = new TreeNode(atoi(sNode.c_str()));
					m_dqTreeNode.push_back(tn);
					sNode.clear();
				}
			}
		}

		if (sNode == "null")
		{
			m_dqTreeNode.push_back(nullptr);
			sNode.clear();
		}
		else
		{
			TreeNode *tn = new TreeNode(atoi(sNode.c_str()));
			m_dqTreeNode.push_back(tn);
			sNode.clear();
		}

		TreeNode* root = m_dqTreeNode.front();
		int itrIndex = 0;
		int indexToSubtract = 0;
		while (itrIndex < m_dqTreeNode.size())
		{
			TreeNode* currentNode = m_dqTreeNode[itrIndex];

			if (currentNode != nullptr)
			{
				currentNode->left = m_dqTreeNode[(2 * (itrIndex - indexToSubtract)) + 1];
				currentNode->right = m_dqTreeNode[(2 * (itrIndex - indexToSubtract)) + 2];
			}
			else
			{
				indexToSubtract++;
			}

			itrIndex++;
		}
		
		return root;
	}
};

template<class K, class V>
class HashNode
{
private:
	K m_Key;
	V m_Value;

public:
	HashNode() = default;
	HashNode(K key, V val) : m_Key(key), m_Value(val) {}

	K GetKey() const 
	{
		return m_Key;
	}

	V GetValue() const 
	{
		return m_Value;
	}
};

template<class K, class V>
class HashMap
{
private:
	HashNode<K, V> **table;
	int capacity{ 2 };
	int size{ 0 };

public:
	HashMap()
	{
		table = new HashNode<K, V>*[capacity] {nullptr};		
	}

	void Insert(K key, V value)
	{
		size_t hashValue = hash<K>()(key);
		size_t iIndex = hashValue % capacity;

		HashNode<K, V> *hn = new HashNode<K, V>(key, value);

		while (table[iIndex] != nullptr)
		{
			if (table[iIndex]->GetKey() == key)
			{
				size--;
				break;
			}

			iIndex++;
			iIndex %= capacity;

			if (size == capacity)
			{
				capacity++;
				iIndex = capacity - 1;
				break;
			}
		}

		size++;
		table[iIndex] = hn;
	}

	V GetValue(K key)
	{
		size_t hashValue = hash<K>()(key);
		size_t iIndex = hashValue % capacity;

		int countIfCheckedAllBuckets = 0;
		while (countIfCheckedAllBuckets < capacity - 1 && table[iIndex]->GetKey() != key)
		{
			iIndex++;
			iIndex %= capacity;
			countIfCheckedAllBuckets++;
		}

		if (countIfCheckedAllBuckets == capacity)
			return -1;

		return table[iIndex]->GetValue();
	}

	int GetBucketSize() const
	{
		return size;
	}
};

class TreeSetNode
{
public:
	char m_Num;
	pair<int, int> m_p;

	TreeSetNode() = default;
	TreeSetNode(char num, pair<int, int> p) : m_Num(num), m_p(p) {}
	bool operator<(const TreeSetNode& other) const
	{
		return m_p.second < other.m_p.second;
	}

	bool operator==(const TreeSetNode& other) const 
	{
		return m_Num == other.m_Num;
	}
};
