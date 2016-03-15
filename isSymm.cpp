#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

bool isPalind(string& str){
	if(str.length() == 0){
		return true;
	}
	int i = 0, j = str.length()-1;
	while(i < j){	
		if(str.at(i) != str.at(j)){
			return false;
		}
		i++;
		j--;
	}
	return true;
}
void helper(vector<string>& result, string& path, unordered_map<char, char>& map, int len){
	if(len == 0){
		if(isPalind(path)){
			result.push_back(path);
		}
		return;
	}
	for(char c = '0'; c <= '9'; c++){
		char mc = map[c];
		if(mc == 'x'){
			continue;
		}
		path.push_back(mc);
		helper(result, path, map, len-1);
		path.pop_back();
	}
}
int main(void){
	unordered_map<char, char> map;
	map['0'] = '0';
	map['1'] = '1';
	map['2'] = '5';
	map['3'] = 'x';
	map['4'] = 'x';
	map['5'] = '2';
	map['6'] = '9';
	map['7'] = 'x';
	map['8'] = '8';
	map['9'] = '6';
	vector<string> result;
	string src;
	int n = 3;
	helper(result, src, map, n);
	for(string str : result){
		cout<<str<<endl;
	}
	return 0;
}
