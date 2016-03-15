/**
 * Definition of TreeNode:
 * class TreeNode {
 * public:
 *     int val;
 *     TreeNode *left, *right;
 *     TreeNode(int val) {
 *         this->val = val;
 *         this->left = this->right = NULL;
 *     }
 * }
 */
class Solution {
private:
	int rootToAny(TreeNode * root)
	{
		if(root == NULL)
		{
			return 0;
		}
		int left = rootToAny(root->left);
		int right = rootToAny(root->right);
		
		return max(0,
					root->val + max(left, right));
	}
public:
    /**
     * @param root: The root of binary tree.
     * @return: An integer
     */
    int maxPathSum(TreeNode *root) {
        // write your code here
		if(root == NULL)
		{
			return numeric_limits<int>::min();
		}
		
		int leftMax  = maxPathSum(root->left);
		int rightMax = maxPathSum(root->right);
		int maxPath = max(leftMax, rightMax);
		
		int leftSP = rootToAny(root->left);
		int rightSP = rootToAny(root->right);
		maxPath = max(maxPath, 
					  leftSP + rightSP + root->val);
		
		return maxPath;
    }
};
