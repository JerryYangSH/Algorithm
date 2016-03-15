#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    /**
     * @param A: An integer matrix
     * @return: The index of the peak
     */
    void rotateArray(vector<vector<int> > &A ) {
        // write your code here
	int n = A.size();
	if(n == 0)
	{
		return;
	}
	int m = A[0].size();
cout << n << " x "<<m<<endl;	
	for(int i = 0; i < (n+1) /2; i++)
	{
		for(int j = i; j < (m - i-1); j++)
		{
			int temp = A[i][j];
			
 
			A[i][j]	= A[n - j -1][i];
			A[n - j - 1][i] = A[n - i -1][m - j -1];
			A[n-i-1][m-j-1] = A[j][m-i-1];
			A[j][m-i-1] = temp;
		}

	}

	

    }
};
int main(void)
{
	vector<vector<int> > A(4, vector<int> (4, 0));
	A[0][0] = 1;
	A[0][1] = 2;
	A[0][2] = 3;
	A[0][3] = 4;

	A[1][0] = 5;
        A[1][1] = 6;
        A[1][2] = 7;
        A[1][3] = 8;
     

	A[2][0] = 9;
        A[2][1] = 10;
        A[2][2] = 11;
        A[2][3] = 12;

	A[3][0] = 20;
	A[3][1] = 21;
	A[3][2] = 22;
	A[3][3] = 23;

	Solution sol;
	sol.rotateArray(A);
	for(int i = 0; i < A.size(); i++)
	{
		for(int j = 0; j < A[0].size(); j++)
		{
			cout << A[i][j] << " ";
		}
		cout <<endl;
	}
	cout << endl;

	return 0;
}
