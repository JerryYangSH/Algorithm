#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
#include <algorithm>
using namespace std;

// http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=133915&extra=page%3D2%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3046%5D%5Bvalue%5D%3D1%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311
void helper(vector<string>& result, string& path, string& word, vector<bool>& visited, unordered_set<string>& dict){
	if(path.length() > 0 && dict.find(path) != dict.end() && 
	    find(result.begin(), result.end(), path) == result.end()){ // dedup
		result.push_back(path);
		return;
	}
	for(int i = 0; i < word.length(); i++){
		if(visited[i]){
			continue;
		}
		char c = word.at(i);
		path.push_back(c);
		visited[i] = true;
		helper(result, path, word, visited, dict);
		visited[i] = false;
		path.pop_back();
	}

}

int main(void){
	string word = "WEDNESDAY";
	vector<bool> visited(word.length(), false);
	unordered_set<string> dict = {"SAY", "SEDEN", "DAY", "EDN", "WE"};
	vector<string> result;
	string path;
	helper(result, path, word, visited, dict);
	for(string str : result){
		cout<<str<<endl;
	}
	return 0;
}