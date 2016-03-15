#include <iostream>
#include <vector>
#include <limits>
using namespace std;

bool search(vector<int> nums, vector<bool> used, int count, int pathnow, int target){
    	if(nums.size() == 1){
		
	}

    return false;
}

int main(void){
        vector<vector<int>> nums = {{11, 11, 5, 1},
                                    {8, 6, 2, 2},
                                    {1000, 100, 10, 1}};

        for(int i = 0; i < nums.size(); i++){
                for(int j = 0; j < nums[i].size(); j++){
                        cout<<nums[i][j]<<" ";
                }
                if(search(nums[i], 24)){
                        cout<<": possible = true" <<endl;
                }
                else{
                        cout<<": possible = false" <<endl;
                }
        }

        return 0;
}

