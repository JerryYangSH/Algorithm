#include <vector>
#include <iostream>
#include <string.h>
using namespace std;

class Solution {
public:
    /**
     * @param obstacleGrid: A list of lists of integers
     * @return: An integer
     */ 
    int uniquePathsWithObstacles(vector<vector<int> > &obstacleGrid) {
        // write your code here
        int m = obstacleGrid.size();
        if(m == 0)
        {
            return 0;
        }
        int n = obstacleGrid[0].size();
        
        //allocat memory
        int ** f = new int* [m];
        for(int i=0; i < m; i++)
        {
            f[i] = new int[n];
            memset(f[i], 0, n);
        }
        
        for(int j = 0; j < n; j++)
        {
            // initialize th first line
            if(obstacleGrid[0][j] != 0)
            {
                break;
            }
            f[0][j] = 1;
        }
        for(int i = 0; i < m; i++)
        {
            // initialize th last line
            if(obstacleGrid[i][0] != 0)
            {
                break;
            }
            f[i][0] = 1;
        }

        // f[x][y] indicates path num from point(0,0) to (x,y).
        for(int i = 1; i < m; i++)
        {
            for(int j = 1; j < n; j++)
            {
                if(obstacleGrid[i][j])
                {
                    f[i][j] = 0;
                }
                else
                {
                    f[i][j] = f[i-1][j] + f[i][j-1];
                }
            }
        }
        
        
        int path = f[m-1][n-1];
        // free memory
        for(int i = 0; i < m; i++)
        {
            delete[] f[i];
        }
        delete [] f;
        
        
        return path;
    }
};

vector<int> gen_vector(int *a, int n)
{
	vector<int> v;
	for(int i = 0; i< n; i++)
	{
		v.push_back(a[i]);
	}
	return v;
}
int main(void)
{
	int array[8][7] = {
		{0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0},
		{1,0,0,0,0,0,1},
		{0,0,0,0,0,0,0},
		{0,1,0,0,0,0,0},
		{0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0},
		{1,0,0,0,0,0,0},
		};
	Solution mysol;
	vector<vector<int> > my_vv;
	for(int i = 0; i < 8; i++)
	{
		my_vv.push_back(gen_vector(&array[i][0], 7));
	}

	int paths = mysol.uniquePathsWithObstacles(my_vv);
	cout << "The path num is : "<<paths<<endl;


}

