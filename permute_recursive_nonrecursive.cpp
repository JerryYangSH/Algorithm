class Solution {
public:
    void helper(vector<vector<int> > &result, vector<int> &nums, vector<int> &path, vector<bool> &visited){
        if(path.size() == nums.size()){
            result.push_back(path);
            return;
        }
        for(int i = 0; i < nums.size(); i++){
            if(visited[i]){
                continue;
            }
            visited[i] = true;
            path.push_back(nums[i]);
            helper(result, nums, path, visited);
            path.pop_back();
            visited[i] = false;
        }
    }
    /**
     * @param nums: A list of integers.
     * @return: A list of permutations.
     */
    vector<vector<int> > permute1(vector<int> nums) {
        // write your code here
        int n = nums.size();
        vector<vector<int> > result;
        if(n == 0){
            return result;
        }
        vector<int> path;
        vector<bool> visited(n, false);
        helper(result, nums, path, visited);
        return result;
    }
    
    // non-recursive
    vector<vector<int> > permute(vector<int> nums) {
        int n = nums.size();
        vector<vector<int> > result;
        if(n == 0){
            return result;
        }
        vector<int> list;
        list.push_back(-1);// 储存上一次遍历的下标
        while(!list.empty()){
            int last = list.back();
            list.pop_back(); // 去掉最后一次遍历的元素
            
            int next = -1;
            for(int i = last+1; i < n; i++){ // 找下一个还没有visited的元素
                if(find(list.begin(), list.end(), i) == list.end()){
                    next = i;
                    break;
                }
            }
            if(next == -1) { // 没找到
                continue;
            }
            //放入下一个没有visited的元素
            list.push_back(next);
            //再放入剩下的没有visited的元素
            for(int i = 0; i < n; i++){
                if(find(list.begin(), list.end(), i) == list.end()){
                    list.push_back(i);
                }
            }
            
            // copy to permutation
            vector<int> permut;
            for(int i = 0; i < list.size(); i++){
                permut.push_back(nums[list[i]]);
            }
            result.push_back(permut);
        }
        return result;
    }
};