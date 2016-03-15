#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
using namespace std;

class Solution {
public:
    /**
     * @param n: an integer
     * @param times: a vector of integers
     * @return: an integer
     */
    int copyBooksII(int n, vector<int> &times) {
        // write your code here
        if(n == 0){
            return 0;
        }
        int k = times.size();
        if(k == 0){
            return numeric_limits<int>::max();
        }
        else if (k == 1){
            //只有一个抄书员
            return times[0] * n;
        }
        //f[i][j] 表示i个人抄j本书的最小耗时
        vector<vector<int> > f(k+1, vector<int>(n+1, 0));
        for(int j = 1; j <= n; j++){
            f[0][j] = numeric_limits<int>::max();
        }
        for(int i = 1; i <= k; i++){
            for(int j = 1; j <= n; j++){
                int minTime = numeric_limits<int>::max();
                for(int x = 0; x <= j; x++){
                    minTime = min(minTime,
                                  max(f[i-1][x], (j - x) * times[i-1]));
                }
                f[i][j] = minTime;
            }
        }
        return f[k][n];
    }
};

int main(){
	Solution sol;
	int n = 0;
	ifstream input("6.in", ios::in);
	input>>n;
	cout <<"n = "<< n <<endl;
	input.seekg(input.tellg()+(long int)3);
	vector<int> times;
	
	while(!input.eof()){
		int x = 0;	
		input >> x;
		if(x == 0) 
			break;

		times.push_back(x);
		input.seekg(input.tellg()+(long int)1);
	}
	input.close();
	for(int j = 0; j < times.size(); j++){
		cout << j << ":"<<times[j]<<endl;
	}
	cout <<"Starting working \n"<<endl;	
	cout << sol.copyBooksII(n, times)<<endl;
	return 0;
}
