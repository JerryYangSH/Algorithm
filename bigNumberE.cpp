#include <iostream>
#include <vector>
#include <limits>
using namespace std;

//////////////// Below is Utility ////////////////////////////////
// 比较大数， 返回 1， 0， -1
long compareBigNum(vector<long> A, vector<long> B){
        if(A.size() > B.size()){
                return 1;
        }
        else if(B.size() > A.size()){
                return -1;
        }
        
	// 从最高位到最低位开始比较
        for(long i = A.size()-1; i >= 0; i--){
                if(A[i] > B[i]){
                        return 1;
                }
                else if(A[i] < B[i]){
                        return -1;
                }
        }
        return 0;
}

vector<long> BigNumber(long n){ // 不考虑负数
        vector<long> bn;
        if(n == 0){
                bn.push_back(0);
                return bn;
        }
        while(n != 0){
                bn.push_back(n%10);
                n = n / 10;
        }
        return bn;
}

vector<long> add_helper(vector<long> A,
                        vector<long> B){
        vector<long> C;
        long len = max(A.size(), B.size());
        long carry = 0;
        for(long i = 0; i < len; i++){
                long value1 = (i >= A.size()) ? 0 :A[i];
                long value2 = (i >= B.size()) ? 0 :B[i];
                long newValue = value1 + value2 + carry;
                carry = newValue/10;
                newValue = newValue%10;
                C.push_back(newValue);
        }
        if(carry != 0){
                C.push_back(carry);
        }

        // Remove the tailing zeros
        long last = C.size() - 1;
        while(last > 0 && C[last] == 0){
                C.pop_back();
                last--;
        }
        return C;
}
vector<long> sub_helper(vector<long> A,
           vector<long> B){
        vector<long> C;
        if(compareBigNum(A, B) == 0){
                // equal
                C.push_back(0);
                return C;
        }

        long len = max(A.size(), B.size());
        long borrowIn = 0;
        long borrowOut = 0;
        for(long i = 0; i < len; i++){
                long value1 = (i >= A.size()) ? 0 :A[i];
                long value2 = (i >= B.size()) ? 0 :B[i];
                if((value1-borrowOut) < value2) {
                        borrowIn = 10;
                }
                else {
                        borrowIn = 0;
                }
                long newValue = value1 + borrowIn - borrowOut - value2;
                borrowOut = (borrowIn == 10) ? 1 : 0;
                C.push_back(newValue);
        }

        // Remove the tailing zeros
        long last = C.size() - 1;
        while(last > 0 && C[last] == 0){
                C.pop_back();
                last--;
        }
        return C;
}
vector<long> mul(vector<long> A, vector<long> B){
        vector<long> C(A.size()+B.size(), 0); // result
        for(long i = 0; i < A.size(); i++){
                long carry = 0;
                for(long j = 0; j < B.size(); j++){
                        long newValue = A[i] * B[j] + carry;
                        carry = newValue/10;
                        newValue = newValue%10;
                        C[i+j] += newValue;
                        C[i+j+1] += C[i+j]/10;
                        C[i+j] = C[i+j]%10;
                }
                if(carry != 0){
                        C[i+B.size()] += carry;
                        if(C[i+B.size()] >= 10){
                                C[i+B.size() + 1]  += C[i+B.size()] / 10;
                                C[i+B.size()] = C[i+B.size()]%10;
                        }
                }
        }

        // Remove the tailing zeros
        long last = C.size() - 1;
        while(last > 0 && C[last] == 0){
                C.pop_back();
                last--;
        }

        return C;
}

vector<long> factorial(long n){
        vector<long> ans(1, 1);
        if(n <= 1){
                return ans;
        }

        for(long i = 1; i <= n; i++){
                vector<long> temp = BigNumber(i);
                ans = mul(ans, temp);
        }
        return ans;
}

void printBN(vector<long> number){
        if(number.size() == 0){
                return;
        }
        long n = number.size();
        cout<<number[n-1];
        cout<<".";
        for(long i = n-2; i >= 0; i--){
                cout<<number[i];
        }
        cout<<endl;
        return;
}

// caculate e = 1 + 1/1! + 1 / 2! + ... + 1 / n!
//            = (1 + n + n*(n-1) + ... + n!) / n!
// Here dividend = (1 + n  + n*(n-1) + ... + n!)
//      divider = n!
vector<long> caculate_e(long n){
        vector<long> sum(1, 1);
        vector<long> reverseFactor(1, 1);
        for(long i = 1; i <= n; i++){
                vector<long> temp = BigNumber(n-i+1);
                reverseFactor = mul(reverseFactor, temp);
                sum = add_helper(sum, reverseFactor);
        }

     
        // 小数点右移101位
        sum.insert(sum.begin(), 101, 0); // dividend

        vector<long> divider = factorial(n);
//cout<<"dividend = ";printBN(sum);
//cout<<"dividor  = ";printBN(divider);
        vector<long> count;
        while(compareBigNum(sum, divider) > 0){
                vector<long> tempDivider = divider;
                for(vector<long> i = BigNumber(1); ; i = mul(i, BigNumber(2))){
                        if(compareBigNum(sum, tempDivider) < 0){
                                break;
                        }
                        sum = sub_helper(sum, tempDivider);
                        tempDivider = mul(tempDivider, BigNumber(2));//double
                        count = add_helper(count, i);
                }
        }

//cout<<"count = ";printBN(count);
        return count;
}

int main(void){
        vector<long> delta = BigNumber(5);
        vector<long> nowDelta;
        long n = 70;
        vector<long> last = caculate_e(n++);
        do{
                vector<long> y = caculate_e(n++);
                nowDelta = sub_helper(y,last);
                last = y;
        }while(compareBigNum(nowDelta, delta) > 0);// until 相邻两个数之差足够小满足精度要求

	// removing over-100 digits
	while(last.size() > 101){
		last.erase(last.begin());
	}
	
        printBN(last);

        return 0;
}

