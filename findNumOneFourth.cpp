#include <iostream>
#include <vector>
using namespace std;

// 在有序数组中找出出现次数超过总长度1/4的一个数


int findFirstOccur(vector<int>& nums, int target){
	int start = 0, end = nums.size() - 1;
	while(start + 1 < end){
		int mid = start + (end - start) / 2;
		if(nums[mid] >= target){
			end = mid;
		}
		else if(nums[mid] < target){
			start = mid;
		}
	}

	int first = -1;
	if(nums[start] == target){
		first = start;
	}
	else if(nums[end] == target){
		first = end;
	}
	return first;

}
int findLastOccur(vector<int>& nums, int target){
	int start = 0, end = nums.size() - 1;
	while(start + 1 < end){
		int mid = start + (end - start) / 2;
		if(nums[mid] <= target){
			start = mid;
		}
		else if(nums[mid] > target){
			end = mid;
		}
	}

	int last = -1;
	if(nums[end] == target){
		last = end;
	}
	else if(nums[start] == target){
		last = start;
	}
	return last;

}

int findNumOneFourth(vector<int> &nums){
	int n = nums.size();
	// the number that occurs frequecy > 1 / 4 out of all MUST be at position 1/4, 1/2 or 3/4
	for(int pos = n/4 - 1; pos < n; pos += n/4){
		int target = nums[pos];
		int first = findFirstOccur(nums, target);
		int last  = findLastOccur(nums, target);
		if(last - first + 1 > n/4){
			return target;
		}
	}

	return -1;
}
int main(void){

	vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 8, 8, 8, 8};
	cout<<findNumOneFourth(nums) << endl;
	return 0;
}
