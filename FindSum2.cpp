#include <stdlib.h>
#include <vector>
#include <iostream>
using namespace std;

void helper(vector<vector<int> >&result, vector<int>&path, vector<bool> &visited, int start, int n, int sum)
{
	if(sum == 0)
	{	
		result.push_back(path);
		return;
	}
	if(sum < 0)
	{	
		return;
	}
	
	for(int i = start; i <= n; i++)
	{
		if(visited[i] == true)
		{
			continue;
		}
		path.push_back(i);
		visited[i] = true;
		helper(result, path, visited, i+1, n, sum - i);
		visited[i] = false;
		path.pop_back();
	}
}

int main()
{
	vector<vector<int> > result;
	vector<int> path;
	int n = 10;
	int m = 9;
	vector<bool> visited(n+1, false); 
	helper(result, path, visited, 1, n, m);
	for(int i = 0; i < result.size(); i++)
	{
		vector<int> oneLine = result[i];
		for(int j = 0; j < oneLine.size(); j++)
		{
			cout<<oneLine[j] << " ";
		}
		cout <<endl;
	}

   	return 0;
}

