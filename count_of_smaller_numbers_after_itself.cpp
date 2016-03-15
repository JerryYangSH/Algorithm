#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Node{
public:
    Node * left;
    Node * right;
    int val;
    int count;// count of smaller
    int dup;
    Node(int v){
        this->val = v;
        this->count = 0;
        this->dup = 1;
        this->left = NULL;
        this->right = NULL;
    }
};

class Solution {
private:
    int insert(Node * root, int val){
        int smallCount = 0;
        while(true) {
            if(val == root->val){
		smallCount += root->count;
                root->dup++;
                return smallCount;
            }
            else if(val < root->val) {
		root->count++;
                if(root->left == NULL) {
                    root->left = new Node(val); 
                    return smallCount; 
                }
                root = root->left;
            } 
            else {
                smallCount += root->dup + root->count;
                if(root->right == NULL) {
                    root->right = new Node(val); 
		    return smallCount;                    
                } 
                root = root->right;
            }
        }
cout<<"insert "<<root->val<<" ["<<root->count<<","<<root->dup<<"]"<<endl;
        return smallCount;
    }
public:
    vector<int> countSmaller(vector<int>& nums) {
        vector<int> result;
        int n = nums.size();
        if(n == 0){
            return result;
        }
        Node * root = new Node(nums[n-1]);
        result.push_back(0);
        for(int i = nums.size()-2; i >= 0; i--){
            int count = insert(root, nums[i]);
            result.push_back(count);
        }
        
        // reverse result
        reverse(result.begin(), result.end());
        return result;
    }
};

int main(void){
	Solution sol;
	vector<int> nums = {5, 2, 6, 1};
	vector<int> result = sol.countSmaller(nums);
	for(int x : result){
		cout<<x<<" ";
	}
	cout<<endl;
	return 0;
}
