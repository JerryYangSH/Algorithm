#include <iostream>
#include <string>
#include <string.h>
#include <vector>
using namespace std;

void helper(bool &valid, string &path, string &source, string &target, vector<int> &visited)
{
	if(path.length() == source.length())
	{
		if(strstr(target.c_str(), path.c_str()) != NULL)
		//if(isSubstring())
		{
			valid = true;
		}
		return;
	}
	for(int i = 0; i < source.length(); i++)
	{
		if((visited[i] != 0) || 
		   (i> 0 && visited[i-1] == 0 && source.at(i) == source.at(i-1)))
			continue;

		visited[i]= 1;
		path.push_back(source.at(i));
		helper(valid, path, source, target, visited);
		path.pop_back();
		visited[i] = 0;
	}
		
}
int main(void)
{
	string str1 = "ab8cb";
	string str2 = "xbbacy";
	int n = str1.length();
	bool valid = false;
	vector<int> visited(n, 0);
	string path;
	helper(valid, path, str1, str2, visited);
	if(valid)
	{
		cout << "yes"<<endl;
	}
	return 0;
}

