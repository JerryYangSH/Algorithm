#include <iostream>
using namespace std;
class Solution {
public:
    /**
     * @param s1 A string
     * @param s2 Another string
     * @return whether s2 is a scrambled string of s1
     */
    bool isValid(string s1, string s2){
        if(s1.length() != s2.length()){
            return false;
        }
        sort(s1.begin(), s1.end());
        sort(s2.begin(), s2.end());
        if(s1.compare(s2) != 0){
            return false;
        }
        return true;
    }
    
    bool isScramble(string& s1, string& s2){
        int len1 = s1.length();
        int len2 = s2.length();
        if(len1 != len2){
            return false;
        }
        if(len1 == 0 || s1.compare(s2) == 0){
            return true;
        }
        if(!isValid(s1, s2)){
            return false;
        }
        for(int k = 0; k < len1-1; k++){
            //s1 的前k个字符，和(n - k)个字符
            string s11 = s1.substr(0, k+1);
            string s12 = s1.substr(k+1, len1 - k - 1);
            //s2 的前k个字符，和(n - k)个字符
            string s21 = s2.substr(0, k+1);
            string s22 = s2.substr(k+1, len2 - k - 1);
            //s2 的前n-k个字符，和后k个字符
            string s23 = s2.substr(0, len2 - k - 1);
            string s24 = s2.substr(len2 - k -1, k+1);
            if(isScramble(s11, s21) && isScramble(s12, s22)){
                   return true;
            }
            if(isScramble(s11, s24) && isScramble(s12, s23)){
                   return true;
            }
        }
        return false;
    }

    //////////////////////////////////////////////////
    // V2: Why below also pass without DP?? 
    bool isScramble2(string& s1, string& s2) {
        // Write your code here
        
        // 1. length check
        int len1 = s1.length();
        int len2 = s2.length();
        if(len1 == 0 && len2 == 0){
            return true;
        }
        if(len1 != len2){
            return false;
        }
        // 2. check if both strings have the same word set.
        sort(s1.begin(), s1.end());
        sort(s2.begin(), s2.end());
        if(s1.compare(s2) == 0){
            return true;
        }
        return false;
    }
};

void generatePermut(vector<string>& result, string& path, string source){
	
} 
int main(void){
	Solution sol;
	string s1("");
	if(sol.isScramble(s1, s2) != sol.isScramble2(s1, s2)){
		cout<<"Error" << endl;
	}

	cout<<"Done"<<endl;
	return 0;
}
	
int main(void){

	
}
