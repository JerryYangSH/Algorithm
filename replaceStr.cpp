#include <iostream>
#include <string>
using namespace std;

// replace foo with bar in source string s.
string replaceStr(string s, string foo, string bar){
	string ans("");
	for(int i = 0; i < s.length(); i++){
		int j = 0;
		for(j = 0; j < foo.length(); j++){
			if((i+j) >= s.length() || s.at(i+j) != foo.at(j)){
				break;
			}
		}
		if(j == foo.length()){
			ans += bar;
			i = i + j - 1;
		}
		else{
			ans += s.at(i);
		}
	}
	return ans;
}

int main(void){
	string s = "hello foolish man";
	cout<<"Original string is : "<<s<<endl;
	cout<<"     New string is : "<<replaceStr(s, "foolish", "bar")<<endl;
	return 0;
}
