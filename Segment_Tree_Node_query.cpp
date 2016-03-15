/**
 * Definition of SegmentTreeNode:
 * class SegmentTreeNode {
 * public:
 *     int start, end, max;
 *     SegmentTreeNode *left, *right;
 *     SegmentTreeNode(int start, int end, int max) {
 *         this->start = start;
 *         this->end = end;
 *         this->max = max;
 *         this->left = this->right = NULL;
 *     }
 * }
 */
class Solution {
public:
    /**
     *@param root, start, end: The root of segment tree and 
     *                         an segment / interval
     *@return: The maximum number in the interval [start, end]
     */
    int query(SegmentTreeNode *root, int start, int end) {
        // write your code here
		if(root == NULL)  // should never happen
		{
			return numeric_limits<int>::min();
		}
		
		if(start == root->start && end == root->end)
		{
			return root->max;
		}
		int mid = (root->start + root->end) / 2;
		int leftMax = numeric_limits<int>::min(), rightMax = numeric_limits<int>::min();
		if(start <= mid) // 左子区
		{
			if(mid < end)
			{
				leftMax = query(root->left, start, mid);
			}
			else
			{
				leftMax = query(root->left, start, end);
			}
		}
		
		if(mid < end) // 右子区
		{
			if(start <= mid)
			{
				rightMax = query(root->right, mid+1, end);
			}
			else
			{
				rightMax = query(root->right, start, end);
			}
		}
		
		return max(leftMax, rightMax);
    }
};


对于数组 [1, 4, 2, 3], 

                  [0, 3, max=4]
                 /             \
          [0,1,max=4]        [2,3,max=3]
          /         \        /         \
   [0,0,max=1] [1,1,max=4] [2,2,max=2], [3,3,max=3]
query(root, 1, 1), return 4

query(root, 1, 2), return 4

query(root, 2, 3), return 3

query(root, 0, 2), return 4