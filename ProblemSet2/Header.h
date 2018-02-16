#ifndef Header_h
#define Header_h

class TreeNode {
public:
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode *next;
	TreeNode() = default;
	TreeNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
};

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

#endif // Header_h
