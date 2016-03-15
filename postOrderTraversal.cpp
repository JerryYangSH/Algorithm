    vector<int> postorderTraversal(TreeNode *root) {
        // write your code here
		vector<int> result;
		if(root == NULL)
		{
			return result;
		}
		
		TreeNode * prev = NULL;
		TreeNode * curr = root;
		stack<TreeNode*> s;
		s.push(curr);
		while(!s.empty())
		{
			curr = s.top();
			if(prev == NULL ||
			   curr == prev->left || curr == prev->right)
			{
				// traverse down or first node
				if(curr->left)
				{
					s.push(curr->left);
				}
				else if(curr->right)
				{
					s.push(curr->right);
				}
			}
			else if(curr->left == prev)
			{
			    //traverse up for left 
				if(curr->right != NULL)
				{
					s.push(curr->right);
				}
			}
			else
			{
			    // traverse up from right
				result.push_back(curr->val);
				s.pop();
			}
			
			prev = curr;
		}
		return result;
		
    }