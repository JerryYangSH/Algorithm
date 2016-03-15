#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

class Solution {
public:
    string fractionToDecimal(int numerator, int denominator) {
		if(numerator == 0){
			return "0";
		}
		if(denominator == 0){
			return "INVALID";
		}
		string ans("");
		bool neg = false;
		cout<<"sizof long = "<<sizeof(long)<<endl;
		cout<<"sizof long long = "<<sizeof(long long)<<endl;
		long num = numerator;
 		long den = denominator;
		if(num < 0){
			neg = true;
			num = -num;
		}
		if(den < 0){
			neg = !neg;
			den = -den;
		}
		long integral = num / den;
		ans += to_string(integral);
		long rmd = num % den;
		if(rmd > 0){
			ans += ".";
		}
		unordered_map<long, int> map;
		while(rmd > 0){
			if(map.find(rmd) != map.end()){
				ans.insert(ans.begin() + map[rmd], '(');
				ans.push_back(')');
				break;
			}
			map[rmd] = ans.length();
			rmd *= 10;
			ans  += to_string(rmd/den);
			rmd = rmd % den;			
		}
		
		if(neg){
		    ans.insert(ans.begin(), '-');
		}
	
	        return ans;
    }
};

int main(void){
	Solution sol;
	cout<<sol.fractionToDecimal(-1, -2147483648)<<endl;
	return 0;
}
