#include <fstream>
#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

class STNode{
public:
    int start, end;
    int count;
    STNode * left, * right;
    STNode(int start, int end){
        this->start = start;
        this->end = end;
        this->count = 0;
        this->left = NULL;
        this->right = NULL;
    }
};
class SegmentTree{
public:
    STNode * _root;
    SegmentTree(int start, int end){
        _root = build(start, end);
    }
    STNode * build(int start, int end){
        if(start > end){
            return NULL;
        }
        STNode * root = new STNode(start, end);
        if(start < end){
            int mid = start + (end - start) / 2;
            root->left = build(start, mid);
            root->right = build(mid+1, end);
        }
        return root;
    }
    int query(STNode* root, int start, int end){
        if(root == NULL || start > end){
            return 0;
        }
        if(start == root->start && end == root->end){
            return root->count;
        }
        int mid = root->start + (root->end - root->start) / 2;
        
        int leftCount = 0;
        if(start <= mid){
            if(mid < end){
                leftCount = query(root->left, start, mid);
            }
            else{
                leftCount = query(root->left, start, end);
            }
        }
        int rightCount = 0;
        if(mid < end){
            if(start <= mid){
                rightCount = query(root->right, mid+1, end);
            }
            else{
                rightCount = query(root->right, start, end);
            }
        }
        return leftCount + rightCount;
    }
    void update(STNode* root, int index, int value){
        if(root == NULL){
            return;
        }
        if(root->start == index && index == root->end){
            root->count += value;
            return;
        }
        int mid = root->start + (root->end - root->start) / 2;
        if(index <= mid){
            update(root->left, index, value);
        }
        else{
            update(root->right, index, value);
        }
        root->count = root->left->count + root->right->count;
    }
};
class Solution {
public:
   /**
     * @param A: An integer array
     * @return: Count the number of element before this element 'ai' is 
     *          smaller than it and return count number array
     */
    vector<int> countOfSmallerNumberII(vector<int> &A) {
        // write your code here
        SegmentTree *stree = new SegmentTree(0, 10001);

        vector<int> result;
        for(int i = 0; i < A.size(); i++){
            int count = stree->query(stree->_root, 0, A[i]-1);
            result.push_back(count);
            stree->update(stree->_root, A[i], 1);
        }
        delete stree;
        return result;
    }
};

vector<int> loadData(string filename){
	vector<int> result;
	std::fstream fs;
	fs.open(filename, std::fstream::in);
	while((fs.rdstate() & std::ifstream::eofbit) == 0){
		char num[24]={0};
		fs.getline(num, sizeof(num), ',');
		int n = atoi(num);
		result.push_back(n);
	}
	fs.close();
	return result;
}
int main(void){
	vector<int> A = loadData("19.in");
	Solution sol;
	vector<int> result = sol.countOfSmallerNumberII(A);
	for(int x : result){
	}
	return 0;
}
