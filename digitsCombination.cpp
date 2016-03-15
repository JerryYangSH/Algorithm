// Microsoft interview
// 手机数字键盘的组合
#include <iostream>
#include <string>
#include <vector>
using namespace std;

void helper(vector<string> &result, string &path, vector<int> nums, string map[], int start){
	if(start >= nums.size()){
		result.push_back(path);
		return;
	}
	string str = map[nums[start]];
	for(int i =0; i < str.length(); i++){
		path += str.at(i);
		helper(result, path, nums, map, start+1);
		path.pop_back();
	}
}


int main()
{
  std::vector<int> nums = {2, 3};
  string path;
  vector<string> result;
  string map[10] = {"",
	                  "",
					  "ABC",
					  "DEF",
					  "GHI",
					  "JKL",
					  "MNO",
					  "PQRS",
					  "TUV",
					  "WXYZ"};
	
	helper(result, path, nums, map, 0);
	for(string x: result){
	    cout<<x<<endl;
	}
	return 0;
}
