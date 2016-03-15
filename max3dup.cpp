#include <iostream>
#include <vector>
using namespace std;
void printDiagonal(vector<vector<int> > array)
{
	int m = array.size();
	if(m == 0)
	{
		return;
	}
	int n = array[0].size();
	if(n == 0)
	{
		return;
	}

	for(int start_col = 0; start_col < n; start_col++)
	{
		for(int row = 0, col = start_col;
		    row < m && col >= 0;
		    row++, col--)
		{
			cout << array[row][col] << " ";
		}
		cout << endl;
	}

	for(int start_row = 1; start_row < m; start_row++)
	{
		for(int row = start_row, col = n-1; 
			row < m && col >= 0; 
			row++, col--)
		{
			cout<<array[row][col] << " ";
		}
		cout << endl;
	}
	return;

}
bool isOk(int array[], int n)
{
	int count = 1;
	for(int i=1; i < n; i++)
	{
		if(array[i] == array[i-1])
		{
			count++;
		}
		else
		{
			count = 1;
		}
		if(count >= 3)
		{
			return true;
		}
	}
	return false;
}
int main(void)
{
	int array[]={1, 2, 2,2, 2,2,3, 3, 4, 4};
	if(isOk(array, sizeof(array)/sizeof(int)))
	{
		cout << "Yes"<<endl;
	}

	vector<vector<int> > vv;
	for(int i = 0; i < 3; i++)
	{
		vector<int> v;
		v.push_back(i*4 + 1);
		v.push_back(i*4 + 2);
		v.push_back(i*4 + 3);
		v.push_back(i*4 + 4);
		vv.push_back(v);
		
	}

	printDiagonal(vv);
	return 0;
}
