#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int maxSubArrayLen(vector<int> nums, int k){

	int n = nums.size();
	if(n == 0){
		return 0;
	}
	int sum = 0;
	int len = -1;
	unordered_map<int, int> map;
	map[0] = -1;
	for(int i = 0; i < n; i++){
		sum = sum + nums[i];
		if(map.find(sum-k) != map.end()){
			len = max(len, i - map[sum-k]);
		}
		if(map.find(sum) == map.end()){
			map[sum] = i;
		}
	}
	return len;
}


vector<int> maxSubArray(vector<int>& nums, int k){
	int n = nums.size();
	int sum = 0;
	vector<int> ans(2,-1);
	int len = -1;
	unordered_map<int, int> map;
	map[0] = -1;
	for(int i = 0; i < n; i++){
		sum = sum + nums[i];
		if(map.find(sum-k) != map.end()){
			if(len < (i - map[sum-k])){
				ans[0]= map[sum-k]+1;
				ans[1] = i;		
				len = i - map[sum-k];
			}
		}
		if(map.find(sum) == map.end()){
			map[sum] = i;
		}
	}
	return ans;
}
int main(void){
    vector<int> nums = {1, -1, 5, -2, 3};
    cout<<maxSubArrayLen(nums, 3)<<endl;
    vector<int> ans = maxSubArray(nums, 3);
    cout<<ans[0]<<" "<<ans[1]<<endl;
    
    vector<int> nums2 = {-2,-1,2,1};
    cout<<maxSubArrayLen(nums2, 1)<<endl;
    ans = maxSubArray(nums2, 1);
    cout<<ans[0]<<" "<<ans[1]<<endl;

    vector<int> nums3 = {1, 4, 20, 3, 10,5};
    cout<<maxSubArrayLen(nums3, 33)<<endl; 
    ans = maxSubArray(nums3, 33);
    cout<<ans[0]<<" "<<ans[1]<<endl;
    return 0;

}
