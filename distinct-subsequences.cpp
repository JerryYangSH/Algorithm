#include <iostream>
#include <string>
#include <vector>
using namespace std;
// 此题用三种方式解决， 重点是如何用滚动数组优化空间

    // Time : O(N2), Memory : O(N2)
    int numDistinct1(string &S, string &T) {
        // write your code here
        int n = S.length();
        int m = T.length();
        if(n == 0 || m == 0){
            return 0;
        }
        
        vector<vector<int>> f(n+1, vector<int>(m+1, 0));
        for(int i = 0; i <= n; i++){
            f[i][0] = 1;
        }
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= m; j++){
                f[i][j] = f[i-1][j];
                if(S.at(i-1) == T.at(j-1)){
                    f[i][j] += f[i-1][j-1];
                }
            }
        }
        return f[n][m];
    }
    // V2 : 滚动数组优化Memory 到O(M)
    int numDistinct(string &S, string &T) {
        // write your code here
        int n = S.length();
        int m = T.length();
        if(n == 0 || m == 0){
            return 0;
        }
        vector<vector<int>> f(2, vector<int>(m+1, 0));
        //f[0][0] = 1;
        for(int i = 0; i <= n; i++){ // 注意 被优化的i必须在外层循环！！！
            for(int j = 0; j <= m; j++){
                if(j == 0){
                    f[i%2][0] = 1;
                }
                else if(i == 0){
                    f[i%2][j] = 0;
                }
                else{
                    f[i%2][j] = f[(i-1)%2][j];
                    if(S.at(i-1) == T.at(j-1)){
                        f[i%2][j] += f[(i-1)%2][j-1];
                    }
                }
            }
        }
        return f[n%2][m];
    }
    // V3 : 滚动数组优化Memory 到O(N)
    int numDistinct3(string &S, string &T) {
        // write your code here
        int n = S.length();
        int m = T.length();
        if(n == 0 || m == 0){
            return 0;
        }
        vector<vector<int>> f(n+1, vector<int>(2, 0));
        for(int j = 0; j <= m; j++){ // 注意 被优化的j必须在外层循环！！！
            for(int i = 0; i <= n; i++){
                if(j == 0){
                        f[i][0]= 1;
                }
                else if(i == 0){
                        f[i][j%2] = 0;
                }
                else{
                        f[i][j%2] = f[i-1][j%2];
                        if(S.at(i-1) == T.at(j-1)){
                                f[i][j%2] += f[i-1][(j-1)%2];
                        }
                }
                //cout<<i<<","<<j<<"("<<j%2<<")"<<" : "<<f[i][j%2]<<endl;
            }
        }
        return f[n][m%2];
    }

int main(void){
	string S = "ddd";
	string T = "dd";
	cout<<numDistinct(S, T)<<endl;
	return 0;
}
