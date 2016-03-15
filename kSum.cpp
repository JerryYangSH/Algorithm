// Example program
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    /**
     * @param A: an integer array.
     * @param k: a positive integer (k <= length(A))
     * @param target: a integer
     * @return an integer
     */
    // V1: 递归
    void helper(vector<int> A, int start, int k, int target, int &paths){
        if(target == 0 && k == 0){
            paths++;
            return;
        }
        
        if(target < 0 || k < 0 || start >= A.size()){
            return;
        }

        
        helper(A, start+1, k-1, target - A[start], paths);
        helper(A, start+1, k, target, paths);
    }
    int kSum(vector<int> A, int k, int target) {
        // wirte your code here
        int paths = 0;
        helper(A, 0, k, target, paths);
        return paths;
    }
    // V2: DP
    int kSum2(vector<int> A, int k, int target) {
        int n = A.size();
        // f[n][k][target]
        vector<vector<vector<int> > > f(n+1, vector<vector<int>>(k+1, vector<int>(target+1, 0)));
        for(int i = 0; i <= n; i++){
            f[i][0][0] = 1;
        }
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= k && j <= i; j++){
                for(int t = 0; t <= target; t++){
                    f[i][j][t] = f[i-1][j][t];
                    if(t >= A[i-1]){
                        f[i][j][t] += f[i-1][j-1][t-A[i-1]];
                    }
                }
            }
        }
        return f[n][k][target];
    }
};
    
int main()
{
  vector<int> A = {1,3,4,5,8,10,11,12,14,17,20,22,24,25,28,30,31,34,35,37,38,40,42,44,45,48,51,54,56,59,60,61,63,66};
  int k = 24;
  int target = 842;

  Solution sol;
  cout << sol.kSum(A, k, target)<<endl;
  cout << sol.kSum2(A, k, target)<<endl;
  return 0;
}

