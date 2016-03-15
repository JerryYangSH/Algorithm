#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class UnionFind {
public:
    unordered_map<int, int> father;
    UnionFind(vector<int>& nums){
        for(int i = 0; i < nums.size(); i++){
            father[nums[i]] = nums[i]; // plus one
            father[nums[i]+1] = nums[i]+1;
        }
    }
    // find the super father of x
    int find(int x) {
        int parent = father.at(x);
        while(parent != father.at(parent)){
            parent = father.at(parent);
        }
        return parent;
    }
    int compressed_find(int x){
        int parent = father.at(x);
        while(parent != father.at(parent)){
            parent = father.at(parent);
        }
        
        //带路径压缩的find
        int fa = father.at(x);
        while(fa != father.at(fa)){
            int tmp = father.at(fa);
            father.at(fa) = parent;
            fa = tmp;
        }
        
        return parent;
    }
    int union_both(int x, int y) {
        int fa_x = compressed_find(x);
        int fa_y = compressed_find(y);
        if(fa_x != fa_y) {
            father.at(fa_x) = fa_y;
        }
    }
};
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        UnionFind uf(nums);
        for(int i = 0; i < nums.size(); i++){
            uf.union_both(nums[i], nums[i]+1);
        }
        unordered_map<int, unordered_set<int>> map; // father -> nums

        for(int i = 0; i < nums.size(); i++){

            int father = uf.find(nums[i]);
            if(map.find(father) == map.end()){
                unordered_set<int> set = {nums[i]};
                map[father] = set;
            }
            else{
                map[father].insert(nums[i]);
            }
        }
        int len = 0;
        for(auto it = map.begin(); it != map.end(); it++){
            len = max(len, (int)(it->second.size()));
        }
        return len;
        
    }
};
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        UnionFind uf(nums);
        unordered_map<int, int> map; // father -> nums
        for(int i = 0; i < nums.size(); i++){
            int father = uf.find(nums[i]);
            if(map.find(father) == map.end()){
                map[father] = 1;
            }
            else{
                map[father] = map[father] + 1;
            }
        }
        int len = 0;
        for(auto it = map.begin(); it != map.end(); it++){
            len = max(len, it->second);
        }
        return len;
        
    }
};

int main(void){
	Solution sol;
	vector<int> A = {0, 1};
	cout << sol.longestConsecutive(A)<<endl;
	return 0;	
}