#include <iostream>
#include <vector>
#include <limits>
using namespace std;

class Solution {
private:
    vector<int> getMaxArray(vector<int>& nums, int k){
        vector<int> result;
        int n = nums.size();
        for(int i = 0; i < nums.size(); i++){
            while(result.size() > 0 && 
               nums[i] > result[result.size()-1] &&
               result.size() + n - i > k){
                result.pop_back();       
            }
            
            result.push_back(nums[i]);
        }
        if(result.size() > k){
            result.erase(result.begin()+k, result.end());
        }
        return result;
    }
    vector<int> merge(vector<int>& nums1, vector<int>& nums2, int k){
        vector<int> result;
        for (int i = 0, j = 0, r = 0; 
             r < k; 
             ++r){
            result.push_back(greater(nums1, i, nums2, j) ? nums1[i++] : nums2[j++]);
        }

        return result;
    }
    bool greater(vector<int>& nums1, int start1, 
                 vector<int>& nums2, int start2) {
        while(start1 < nums1.size() && start2 < nums2.size()){
            if(nums1[start1] > nums2[start2]) return true;   
            if(nums1[start1] < nums2[start2]) return false;
            start1++;
            start2++;
        }
        return start1 != nums1.size();
    }
public:
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
        vector<int> result;
        if(k <= 0 || k > nums1.size()+nums2.size()){
            return result;
        }
        int len1 = nums1.size();
        int len2 = nums2.size();
        for(int i = max(0, k - len2);
                i <= min(len1, k);
                i++){

            vector<int> array1 = getMaxArray(nums1, i);
            vector<int> array2 = getMaxArray(nums2, k-i);
            vector<int> localAns = merge(array1, array2, k);
            if(greater(localAns, 0, result, 0)){
                result = localAns;
            }
        }
        return result;
    }
};
int main(void){
	Solution sol;
	vector<int> nums1 = {8, 6, 9};
	vector<int> nums2 = {1, 7, 5};
	vector<int> result = sol.maxNumber(nums1, nums2, 3);
	for(int x : result){
		cout << x <<endl;
	}
	return 0;
}
