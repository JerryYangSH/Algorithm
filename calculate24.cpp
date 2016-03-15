#include <iostream>
#include <vector>
#include <limits>
using namespace std;

const int INVALID = numeric_limits<int>::min();

bool search(vector<int> nums, int n, int target){
    if(n == 1){
        if(nums[nums.size()-1] == target){
            return true;
        }
        return false;
    }

    vector<int> path = nums;
    for(int i = 0; i < nums.size(); i++){
	if(path[i] == INVALID){
		continue;
	}
        int x = path[i];
	path[i] = INVALID;
        for(int j = 0; j < nums.size(); j++){
            if(path[j] == INVALID){
                continue;
            }
	    int y = path[j];
	    path[j] = INVALID;

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

                if(search(path,n-1, target)){
                    return true;
                }
                path.pop_back();
            }

	    path[j] = y;
        }
        path[i] = x;;
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
                if(search(nums[i],4, 24)){
                        cout<<": possible = true" <<endl;
                }
                else{
                        cout<<": possible = false" <<endl;
                }
        }

        return 0;
}

