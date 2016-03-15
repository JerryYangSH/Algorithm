#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
private:
    string buildIP(vector<string> IPnums){
        // insert dots
        string result("");
        for(string str : IPnums){
            result.append(str);
            result.append(".");
        }
        result.pop_back();
	return result;
    }
    bool isValidNum(string str){
        if(str.length() == 0){
            return false;
        }
        int num = 0;
        for(int i = 0; i < str.length(); i++){
            if(str.at(i) < '0' || str.at(i) > '9'){
                return false;
            }
            num = num * 10 + str.at(i) - '0';
        }
        return num <= 255 && num >= 0;
    }
    void helper(vector<string> &result, vector<string> &IPnums, string &s, int start, int num){
        if(start >= s.length() && num == 0){
            string IPstr = buildIP(IPnums);
            result.push_back(IPstr);
            return;
        }
        if(num <= 0){
            return;
        }
        
        for(int i = start; i < s.length(); i++){
            string piece = s.substr(start, i - start + 1);
            if(!isValidNum(piece)){
                continue;
            }
cout<<"pushing "<<piece<<" ["<<start<<"~"<<i<<"] num="<<num<<endl;            
            IPnums.push_back(piece);
            helper(result, IPnums, s, i+1, num-1);
            IPnums.pop_back();
        }
    }
public:
    /**
     * @param s the IP string
     * @return All possible valid IP addresses
     */
    vector<string> restoreIpAddresses(string& s) {
        // Write your code here
        vector<string> result;
        if(s.length() < 4){
            return result;
        }
        vector<string> path;
        helper(result, path, s, 0, 4);
        return result;
    }
};

int main(void){
	Solution sol;
	string IPstr = "1234";
	//cout<<"Please input IP:";
	//cin>>IPstr;
	vector<string> result = sol.restoreIpAddresses(IPstr);
	for(string str : result){
		cout<<str<<endl;
	}

	return 0;
}	
