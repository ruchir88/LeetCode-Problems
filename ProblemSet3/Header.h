#pragma once
#include <unordered_map>
#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <typeinfo>
#include <functional>
#include <memory>
#include <string>
#include <tuple>
#include <queue>
#include <unordered_set>
#include <type_traits>

using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

// Regular Graph
class Node
{
private:
	string m_Name{""};
	int m_Id{-1};
	int m_ParentId{-1};

public:
	// Variables
	list<Node> m_AdjacentList;

	// Constructor
	Node() = default;
	Node(string name, int id, int parentId) : m_Name(name), m_Id(id), m_ParentId(parentId) {}

	// Methods
	inline string GetName() const { return m_Name; }
	inline int GetID() const { return m_Id; }
	inline int GetParentID() const { return m_ParentId; }
};

class RegularGraph
{
public:
	list<Node> m_Vertices;
};

// Tree Structure Graph
class GraphNode
{
protected:
	char m_Char{' '};
	int m_Value{0};
	int m_ParentID{ -1 };
	bool m_Visited{ false };

public:
	GraphNode() = default;
	GraphNode(char c, int v) : m_Char(c), m_Value(v) {}
	GraphNode(char c, int v, int pid) : m_Char(c), m_Value(v), m_ParentID(pid) {}

	~GraphNode() = default;

	void SetNodeName(char c)
	{
		m_Char = c;
	}

	void SetValue(int v)
	{
		m_Value = v;
	}

	char GetNodeName() const
	{
		return m_Char;
	}

	int GetValue() const
	{
		return m_Value;
	}

	void SetParentID(int pid)
	{
		m_ParentID = pid;
	}

	int GetParentID() const 
	{
		return m_ParentID;
	}

	bool IsVisited()
	{
		return m_Visited;
	}

	void SetVisited()
	{
		m_Visited = true;
	}

	bool operator==(const GraphNode& other) const
	{
		return (m_Char == other.m_Char);
	}
};

template <>
struct hash<GraphNode>
{
	size_t operator()(const GraphNode& gn) const
	{
		return (hash<char>()(gn.GetNodeName()));
	}
};

class Graph
{
protected:
	unordered_map<int, GraphNode> m_umGraphNameMap;

public:
	unordered_map<GraphNode, list<GraphNode> > m_umGraph;

	void SetGraphNode(int id, GraphNode gn)
	{
		m_umGraphNameMap[id] = gn;
	}

	GraphNode GetGraphNode(int id)
	{
		return m_umGraphNameMap[id];
	}

	void AddEdge(GraphNode gnFrom, GraphNode *gnTo);
};

// LRU Implementation
class DBData
{
public:
	DBData() = default;
	DBData(int value, int id) : m_Value(value), m_Id(id) {}

	inline int GetValue() const { return m_Value; }
	inline int GetID() const { return m_Id; }

	bool operator==(const DBData& other) const
	{
		return m_Id == other.m_Id;
	}

protected:
	int m_Value;
	int m_Id;
};

class LRU
{
public:
	LRU() = default;
	LRU(unsigned int size) : m_LRUSize(size) {}

	DBData Read(int id);
	void Write(DBData db);

protected:
	list<DBData> m_LRUCache;
	unordered_map<int, DBData*> m_umHashMap;

private:
	unsigned int m_LRUSize{ 5 };
};

class LRU2
{
public:
	LRU2() = default;
	LRU2(unsigned int size) : m_LRUSize(size) {}

	int Read(int id);
	void Write(DBData db);

protected:
	list<int> m_LRUCache;
	unordered_map<int, int> m_umHashMap;

private:
	unsigned int m_LRUSize{ 5 };
};

class TreeNode
{
public:
	int m_Value;
	TreeNode* m_pParent;
};

// Type aliases
template<typename T>
using MyList = vector<list<T> >;

// Definition for an interval.
struct Interval {
	int start;
	int end;
	Interval() : start(0), end(0) {}
	Interval(int s, int e) : start(s), end(e) {}
};

struct ObjectOfCompare 
{
	bool operator()(const Interval &i1, const Interval &i2)
	{
		return i1.start < i2.start;
	}
} myObjectOfCompare;

// Testing Dispatcher model
template<class T>
class Dispatcher
{
protected: 
	unordered_map<string, function<void(T)> > m_umMessageDipatcherMap;

public:
	void RegisterMessage(string message, function<void(T)> f)
	{
		m_umMessageDipatcherMap[message] = f;
	}

	function<void(T)> OnMessageFunction(string message)
	{
		return m_umMessageDipatcherMap[message];
	}
};

class TestDispatcher2
{
public:
	void SomeFunction(int data)
	{
		cout << "Some Function " << data << endl;
	}
};

class TestMessageDispatcher
{
protected:
	Dispatcher<int> m_Dispatcher;
	TestDispatcher2 td2;

	// message functions
	void FirstMessageActual(int data);
	void SecondMessageActual(int data);
	void ThirdMessageActual(int data);
	void FourthMessageActual(int data);

public:
	TestMessageDispatcher()
	{
		m_Dispatcher.RegisterMessage("FirstMessage Call", bind(&TestMessageDispatcher::FirstMessageActual, this, placeholders::_1));
		m_Dispatcher.RegisterMessage("SecondMessage Call", bind(&TestMessageDispatcher::SecondMessageActual, this, placeholders::_1));
		m_Dispatcher.RegisterMessage("ThirdMessage Call", bind(&TestMessageDispatcher::ThirdMessageActual, this, placeholders::_1));
		m_Dispatcher.RegisterMessage("FourthMessage Call", bind(&TestMessageDispatcher::FourthMessageActual, this, placeholders::_1));
		m_Dispatcher.RegisterMessage("Some Function Call", bind(&TestDispatcher2::SomeFunction, &td2, placeholders::_1));
	}
	void OnMessage(string message, int data);
};


// Type Aliases
template <typename Type>
using MyCustomType = unordered_map<string, vector<Type> >;

// template explicit specialization
template <typename Type1>
void SomeFunctionToTestTemplate(Type1 t1, Type1 t2)
{
	cout << t1 << ": " << t2 << endl;
}

template<> void SomeFunctionToTestTemplate<string>(string t1, string t2)
{
	cout << t2 << ": " << t1 << endl;
}

// Think - Cell
#include <assert.h>
#include <map>
#include <limits>

void IntervalMapTest()
{
	cout << "Testing Interval Map" << endl;
}

template<class K, class V>
class interval_map {
	friend void IntervalMapTest();

private:
	std::map<K, V> m_map;

public:
	// constructor associates whole range of K with val by inserting (K_min, val)
	// into the map
	interval_map(V const& val) {
		m_map.insert(m_map.begin(), std::make_pair(std::numeric_limits<K>::lowest(), val));
	}

	// Assign value val to interval [keyBegin, keyEnd). 
	// Overwrite previous values in this interval. 
	// Do not change values outside this interval.
	// Conforming to the C++ Standard Library conventions, the interval 
	// includes keyBegin, but excludes keyEnd.
	// If !( keyBegin < keyEnd ), this designates an empty interval, 
	// and assign must do nothing.
	void assign(K const& keyBegin, K const& keyEnd, V const& val) {
		// INSERT YOUR SOLUTION HERE
		if (keyBegin > keyEnd) {
			return;
		}

		if (m_map.lower_bound(keyBegin) != m_map.end()) {
			if ((m_map.lower_bound(keyBegin))->second == val) {
				return; // This assigning is not allowed
			}
			else {
				int tempKeyBegin = keyBegin;
				int tempKeyEnd = keyEnd;
				auto itrToDelete = m_map.lower_bound(keyBegin);
				auto itrToInsert = --m_map.lower_bound(keyBegin);
				while (tempKeyBegin < keyEnd) {
					m_map.erase(itrToDelete);
					m_map.insert(itrToInsert, make_pair(tempKeyBegin, val));
					itrToDelete = itrToInsert;
					itrToInsert++;
					tempKeyBegin++;
				}
			}
		}
		else {
			int tempKeyBegin = keyBegin;
			int tempKeyEnd = keyEnd;

			auto itrToInsert = m_map.begin() == m_map.end() ? m_map.begin() : --m_map.end();
			while (tempKeyBegin < keyEnd) {
				m_map.insert(itrToInsert, make_pair(tempKeyBegin, val));
				itrToInsert++;
				tempKeyBegin++;
			}
		}
	}

	// look-up of the value associated with key
	V const& operator[](K const& key) const {
		return (--m_map.upper_bound(key))->second;
	}
};

// Many solutions we receive are incorrect. Consider using a randomized test
// to discover the cases that your implementation does not handle correctly.
// We recommend to implement a function IntervalMapTest() here that tests the
// functionality of the interval_map, for example using a map of unsigned int
// intervals to char.in





	