#include <iostream>
#include <vector>
using namespace std;

void sumOfNum1(vector<vector<int> > &result, vector<int> &path, int sum, int start, int n)
{
	if(sum < 0 || start > n)
	{
		return;
	}
	
	if(sum == 0)
	{
		result.push_back(path);
		return;
	}
	for(int i = start; i<= n; i++)
	{
		path.push_back(i);
		sumOfNum1(result, path, sum - i, i+1, n);
		path.pop_back();	
	}
}
void sumOfNum(vector<vector<int> > &result, vector<int> &path, int sum, int n)
{
    if(sum < 0 || n <= 0)
    {
	return;
    }
    if(sum == 0)
    {
        result.push_back(path);
        return;
    }
    
    path.push_back(n);
//    cout<<"pushing "<<n<<" looking for "<<sum-n<<endl;
    sumOfNum(result, path, sum - n, n-1);
//    cout<<"Poping out "<<path.back()<<endl;
    path.pop_back();
    
    sumOfNum(result, path, sum, n-1);
}

int main()
{
  cout<<"Test"<<endl;
  vector<vector<int> > result;
  vector<int> path;
  sumOfNum1(result, path, 7, 1, 6);
  //sumOfNum(result, path, 7, 6);
  for(int i = 0; i < result.size(); i++)
  {
      for(int j = 0; j < result[i].size(); j++)
      {
          std::cout <<result[i][j]<< " ";
      }
      std::cout << endl;
  }
}
