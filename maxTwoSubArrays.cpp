// Example program
#include <iostream>
#include <string>
#include <vector>
#include <limits>
using namespace std;

int maxTwoSubArrays(vector<int> nums) {
        // write your code here
        int n = nums.size();
        if(n == 0) {
            return 0;
        }
        vector<int> leftMax(n, numeric_limits<int>::min());
        vector<int> rightMax(n, numeric_limits<int>::min());
        
        int currSum = 0;
        for(int i = 0; i < n; i++) {
            if(currSum >= 0) {
                currSum += nums[i];
            }
            else {
                currSum = nums[i];
            }
            
            leftMax[i] = max(leftMax[i], currSum);
            cout<<"left["<<i<<"] :"<<leftMax[i]<<" ";
        }
        cout<<endl;
        
        currSum = 0;
        for(int i = n-1; i >= 0; i--) {
            if(currSum >= 0) {
                currSum += nums[i];
            }
            else {
                currSum = nums[i];
            }
            
            rightMax[i] = max(rightMax[i], currSum);
            cout<<"right["<<i<<"] :"<<rightMax[i]<<" ";
        }
        cout<<endl;
        
        int maxSum = numeric_limits<int>::min();
        for(int i = 0; i < n-1; i++) {
            int sum = leftMax[i] + rightMax[i+1];
            maxSum = max(maxSum, sum);
        }
        
        return maxSum;
    }
int main()
{
  vector<int> nums = {1,3,-1,2,-1,2};
  
    cout <<maxTwoSubArrays(nums)<<endl;

  return 0;
}
