#include <vector>
#include <iostream>
using namespace std;

class Solution {
private:
    bool isPeak(vector<vector<int> > &A, int i, int j )
    {
        int n = A.size();
        int m = A[0].size();

        if((i == 0) || (i == (n-1)) || (j == 0) || (j == (m-1)))
            return false;
    
        return (A[i][j] > A[i+1][j]) && 
               (A[i][j] > A[i-1][j]) &&
               (A[i][j] > A[i][j-1]) && 
               (A[i][j] > A[i][j+1]);
    }
public:
    /**
     * @param A: An integer matrix
     * @return: The index of the peak
     */
    vector<int> findPeakII(vector<vector<int> > A) {
        // write your code here
        vector<int> res;
        int row = A.size();
        if(row == 0)
        {
            return res;
        }
        int col = A[0].size();
        
        int start = 1;
        int end = row * col - 1;
        while((start + 1) < end)
        {
            int middle = start + (end - start) / 2;
            int x = middle/col;
            int y = middle%col;
	cout << "check "<< x << " " <<y<<endl;
            if(isPeak(A, x, y))
            {
                res.push_back(x);
                res.push_back(y);
                return res;
            }
            else if(A[middle/col][middle%col] > A[(middle-1)/col][(middle-1)%col])
            {
                start = middle;
            }
            else
            {
                end = middle;
            }
        }
        if(isPeak(A, start/col, start%col))
        {
            res.push_back(start/col);
            res.push_back(start%col);
        }
        else if(isPeak(A, end/col, end%col))
        {
            res.push_back(end/col);
            res.push_back(end%col);
        }
        
        return res;
    }
};
int main(void)
{
	Solution sol;
	vector<vector<int> > A(3, vector<int> (6, 0));
	A[0][0] = 1;
	A[0][1] = 2;
	A[0][2] = 3;
	A[0][3] = 4;
	A[0][4] = 5;
	A[0][5] = 6;

	A[1][0] = 14;
        A[1][1] = 15;
        A[1][2] = 16;
        A[1][3] = 17;
        A[1][4] = 18;
        A[1][5] = 8;

	A[2][0] = 12;
        A[2][1] = 13;
        A[2][2] = 11;
        A[2][3] = 10;
        A[2][4] = 9;
        A[2][5] = 7;

	vector<int> result = sol.findPeakII(A);
	for(int i = 0; i < result.size(); i++)
	{
		cout << result[i] << " ";
	}
	cout << endl;
}
