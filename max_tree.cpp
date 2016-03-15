#include <iostream>
#include <vector>
#include <stack>
#include <limits>
using namespace std;

class TreeNode {
 public:
      int val;
      TreeNode *left, *right;
      TreeNode(int val) {
          this->val = val;
          this->left = this->right = NULL;
      }
}; 

TreeNode* maxTree(vector<int> A) {
	stack<TreeNode*> s;
	TreeNode* root = NULL;
	
	for(int i = 0; i <= A.size(); i++)
	{
		int rightValue = (i == A.size())? numeric_limits<int>::max() :
										  A[i];
		TreeNode * rightNode = new TreeNode (rightValue);
		while(!s.empty())
		{
			TreeNode * currentNode = s.top();
			if(rightNode->val < currentNode->val)
			{
				break;
			}
			
			s.pop();
			if(s.empty())
			{
				rightNode->left = currentNode;
			}
			else
			{
				TreeNode * leftNode = s.top();
				if(leftNode->val < rightNode->val)
				{
					leftNode->right = currentNode;
				}
				else
				{
					rightNode->left = currentNode;
				}
			}
		}
		
		s.push(rightNode);
	}
	
	return (s.top())->left;
}
int main(void)
{
	vector<int> a;
	a.push_back(2);	
	a.push_back(5);	
	a.push_back(6);	
	a.push_back(0);	
	a.push_back(3);	
	a.push_back(1);	

	TreeNode * n = maxTree(a);

	//inorder(n);
	return 0;
}
