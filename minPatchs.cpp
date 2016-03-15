#include <iostream>
#include <vector>
using namespace std;

// [1, 3], n = 6 =>  we need fill 2 , so ans is 1
// [1, 5, 10], n = 20 => we need fill [2, 4], so ans = 2

// get min patches that can fill number 1 ~ n
int minPatches(vector<int> nums, int n){
	int sum = 0;
	int index = 0;
	int ans = 0;
	if(nums.size() > 0 && nums[0]== 1){
		sum = 1;
		index = 1;
	}
	while(sum < n){
		while(index < nums.size() && nums[index] <= sum){
			sum += nums[index];
			index++;
		}

		if(sum < n){
			if(index < nums.size() && (sum+1) == nums[index]){
				index++;
			}
			else{
				ans++;
			}
			sum = 2 * sum + 1;
		}
	}
	return ans;
}
int main(void){
	vector<int> nums = {1,3};
	cout<<minPatches(nums, 5)<<endl;
	
	vector<int> nums2 = {1,5, 10};
	cout<<minPatches(nums2, 20)<<endl;
	return 0;
}
