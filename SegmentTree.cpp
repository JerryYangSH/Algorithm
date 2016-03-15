#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class SegmentTreeNode {
public:
    int start;
    int end;
    int count;
    SegmentTreeNode* left;
    SegmentTreeNode* right;
    SegmentTreeNode(int start, int end, int count){
        this->start = start;
        this->end = end;
        this->count = count;
        this->left = this->right = NULL;
    }
};

class Solution {
private:
    SegmentTreeNode* root;
    SegmentTreeNode* build(int start, int end){ // Range start ~ end
        if(start > end) {
            return NULL;
        }
        //default count of range  is zero.
        SegmentTreeNode* root = new SegmentTreeNode(start, end, 0);
        if(start != end) {
            int middle = start + (end - start) / 2;
            root->left = build(start, middle);
            root->right = build(middle+1, end);
        }
        return root;
    }
    int querySegmentTree(SegmentTreeNode* root, int start, int end) {
cout<<"querying "<<start << " : "<<end <<endl;
        if(start > end) {
            return 0;
        }
        if(start <= root->start && root->end <= end) {
            return root->count;
        }
        int leftCount = 0, rightCount = 0;
        int middle = root->start + (root->end - root->start) / 2;
        if(start <= middle) {
            if(middle < end) {
                leftCount = querySegmentTree(root->left, start, middle);
            }
            else {
                leftCount = querySegmentTree(root->left, start, end);
            }
        }
        if(middle < end) {
            if(start <= middle) {
                rightCount = querySegmentTree(root->right, middle+1, end);
            }
            else {
                rightCount = querySegmentTree(root->right, start, end);
            }
        }
        return leftCount + rightCount;

    }
    // insert a value in this index position, that means count increases!
    void modifySegmentTree(SegmentTreeNode* root, int index, int value){
        if(root == NULL || index < root->start || index > root->end) {
            return;
        }
        if(root->start == index && index == root->end){
            root->count += value; // increase count !
            return;
        }
        int middle = root->start + (root->end - root->start) / 2;
        if(index <= middle) {
            modifySegmentTree(root->left, index, value);
        }
        else {
            modifySegmentTree(root->right, index, value);
        }
        root->count = root->left->count + root->right->count;
    }
public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        int n = nums.size();
        if(n == 0){
            return 0;
        }
        int ans = 0;
        vector<int> presum(nums);
        for(int i = 1; i < n; i++){
            presum[i] += presum[i-1];
        }
        sort(presum.begin(), presum.end());
cout<<"presum : ("<<presum.size()<<")"<<endl;
for(int x : presum){
	cout<<x<<" ";
}
cout<<endl;
        SegmentTreeNode* root = build(presum[0], presum[n-1]);
        for(int i = 0; i < n; i++){
            modifySegmentTree(root, presum[i], 1);
        }
        for(int i = 0; i < n; i++){
cout<<"["<<i<<endl;
	    int lowBound = max(root->start, presum[i]+lower);
	    int highBound = min(root->end, presum[i]+upper);
            int tmp = querySegmentTree(root, lowBound, highBound);
	    ans += tmp;
cout<<"]count of "<<lowBound<<":"<<highBound<<" = "<<tmp<<endl;
        }

        delete root;
        return ans;
    }
};
int main(void){
	Solution sol;
	vector<int> nums = {-2, 5, -1};
	cout<<sol.countRangeSum(nums, -2, 2)<<endl;
	return 0;
}
