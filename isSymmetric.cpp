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
public:
    /**
     * @param root, the root of binary tree.
     * @return true if it is a mirror of itself, or false.
     */
    bool isSymmetric(TreeNode* root) {
        return isSymmetricHelp(root, root);
    }
    bool isSymmetricHelp(TreeNode* root1, TreeNode* root2) {
        // Write your code here
        if(root1 == NULL && root2 == NULL){
            return true;
        }
        if(root1 == NULL || root2 == NULL){
            return false;
        }
        if(root1->val != root2->val){
            return false;
        }
        return isSymmetricHelp(root1->left, root2->right) && 
                isSymmetricHelp(root1->right, root2->left);
    }
};
