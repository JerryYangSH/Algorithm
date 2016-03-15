#include <iostream>
#include <vector>
#include <limits>
using namespace std;

bool search(vector<int> nums, int target){
    if(nums.size() == 1){
        if(nums[0] == target){
            return true;
        }
        return false;
    }

    for(int i = 0; i < nums.size(); i++){
        int x = nums[i];
        for(int j = 0; j < nums.size(); j++){
            if(i == j){
	    	continue;
	    }	
	    int y = nums[j];
	    
	    vector<int> path;
	    for(int k = 0; k < nums.size(); k++){
		if(k != i && k != j){
			path.push_back(nums[k]);
		}
            }
	    int temp = 0;
            for(char op = 0; op < 4; op++){
                int temp = 0;
                if(op == 0){
                    temp = x + y;
                }
                else if(op == 1){
                    temp = x - y;
                }
                else if(op == 2){
                    temp = x * y;
                }
                else if(y != 0){
                    temp = x / y;
                }
		path.push_back(temp);
                if(search(path, target)){
                    return true;
                }
		path.pop_back();
	   }
        }
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

