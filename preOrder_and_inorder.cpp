 //前序
	vector<int> preorderTraversal2(TreeNode *root) {
        // write your code here
        vector<int> result;
        if(root == NULL) {
            return result;
        }
        stack<TreeNode*> s;
        TreeNode * node = root;
		s.push(node);
        while(!s.empty()) {
            node = s.top();
            s.pop();
            result.push_back(node->val);
            if(node->right != NULL) {
                s.push(node->right);
            }
            if(node->left != NULL) {
                s.push(node->left);
            } 
        }
		return result;
    }
	
//中序
vector<int> inorderTraversal(TreeNode *root) {
        // write your code here
        vector<int> result;
        if(root == NULL) {
            return result;
        }
        stack<TreeNode *> s;
        TreeNode * node = root;
        while(!s.empty() || node != NULL) {
            while(node != NULL) {
                s.push(node);
                node = node->left;
            }
            
            if(!s.empty()) {
                node = s.top();
                s.pop();
                result.push_back(node->val);
                node = node->right;
            }
        }
        return result;
    }