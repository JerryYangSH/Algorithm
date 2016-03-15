class STNode {
public:
	int start;
	int end;
	int count;
	STNode * left;
	STNode * right;
	STNode(int _start, int _end, int _count){
		this->start = _start;
		this->end = _end;
		this->count = _count;
		this->left = NULL;
		this->right = NULL;
	}
};
class SegmentTree{
public:
	STNode * build(vector<int> &A, int start, int end){
		if(start > end){
			return NULL;
		}
		
		STNode* root = new STNode(start, end, 0);
		if(start != end){
			int middle  = start + (end - start) / 2;
			root->left  = build(A, start, middle);
			root->right = build(A, middle+1, end);
			root->count = root->left->count + root->right->count;
		}
		else{
			root->count = 0; // initially empty
		}
		return root;		
	}
	//query the count of value range [start ~ end]
	int queryCount(STNode * root, int start, int end){
		if(root == NULL){
			return 0;
		}
		if(start == root->start && root->end == end){
			return root->count;
		}
		
		int middle = root->start + (root->end - root->start) / 2;
		int leftCount = 0;
		if(start <= middle){
			if(middle < end){
				leftCount = queryCount(root->left, start, middle);
			}
			else{
				leftCount = queryCount(root->left, start, end);
			}
		}
		int rightCount = 0;
		if(middle < end){
			if(start <= middle){
				rightCount = queryCount(root->right, middle+1, end);
			}
			else{
				rightCount = queryCount(root->right, start, end);
			}
		}
		
		return leftCount + rightCount;
	}
	void modify(STNode * root, int index, int value){
		if(root == NULL){
			return;
		}
		if(root->start == index && index == root->end){
			root->count += value;
			return;
		}
		int middle = root->start + (root->end - root->start) / 2;
		if(index <= middle){
			modify(root->left, index, value);
		}
		else {
			modify(root->right, index, value);
		}
		root->count = root->left->count + root->right->count;
	}
};
class Solution {
public:
   /**
     * @param A: An integer array
     * @return: The number of element in the array that 
     *          are smaller that the given integer
     */
    // V1 循环方法 O(N * K)
    vector<int> countOfSmallerNumber1(vector<int> &A, vector<int> &queries) {
        // write your code here
        vector<int> result;
        int n = A.size();
        int k = queries.size();
        for(int i = 0; i < k; i++){
            int target = queries[i];
            int count = 0;
            for(int j = 0; j < n; j++){
                if(A[j] < target){
                    count++;
                }
            }
            result.push_back(count);
        }
        return result;
    }
    
    // V2 
    vector<int> countOfSmallerNumber(vector<int> &A, vector<int> &queries) {
		vector<int>  ans;
		SegmentTree tree;
		STNode * root = tree.build(A, 0, 10000);
		for(int i = 0; i < A.size(); i++){
			tree.modify(root, A[i], 1);
		}
		for(int k = 0; k < queries.size(); k++){
			int count = 0;
			if(queries[k] > 0){
				count = tree.queryCount(root, 0, queries[k]-1);
			}
			ans.push_back(count);
		}
        return ans;
    }
};
