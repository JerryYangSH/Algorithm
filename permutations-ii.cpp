#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
private:
	void helper(vector<vector<int> > &result, vector<int> &list, vector<int> &nums, bool * visited)
	{
		if(list.size() == nums.size())
		{
			result.push_back(list);
			return ;
		}
		
		for(int i = 0; i < nums.size(); i++)
		{
			if (visited[i]){
                continue;
            }
			if(i > 0)
			{
			    if(nums[i] == nums[i - 1] && !visited[i - 1])
				continue;
			}
			visited[i] = true;
			list.push_back(nums[i]);
			helper(result, list, nums, visited);
			list.pop_back();
			visited[i] = false;
		}
		return;
	}
public:
    /**
     * @param nums: A list of integers.
     * @return: A list of unique permutations.
     */
    vector<vector<int> > permuteUnique(vector<int> &nums) {
        // write your code here
		vector<vector<int> >  result;
		if(nums.size() == 0)
		{
			return result;
		}

		vector<int> list;
		bool * visited = new bool[nums.size()];

		sort(nums.begin(), nums.end());
		helper(result, list, nums, visited);
		delete [] visited;
		return result;
    }
};

int main(void)
{
	cout << "start here"<<endl;
	vector<int> mynums;
	mynums.push_back(1);
	mynums.push_back(2);
	mynums.push_back(2);
        Solution mysol;
	vector<vector<int> > vv =  mysol.permuteUnique(mynums);
	for(int i = 0; i < vv.size(); i++)
	{
		vector<int> v = vv[i];
		for(int j = 0; j < v.size(); j++)
		{
			cout << v[j] << " ";
		}
		cout << endl;
	} 
	return 0;
		
}

