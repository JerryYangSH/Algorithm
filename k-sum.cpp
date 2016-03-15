#include <iostream>
#include <vector>
using namespace std;

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
int main(void){
	vector<int> A = {1,3,4,5,8,10,11,12,14,17,20,22,24,25,28,30,31,34,35,37,38,40,42,44,45,48,51,54,56,59,60,61,63,66};

	cout<<kSum(A, 24, 842)<<endl;
	return 0;
}
