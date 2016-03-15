#include <iostream>
#include <unordered_map>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Node{
public:
	char c;
	int count;
	Node(char c, int count){
		this->c = c;
		this->count = count;
	}
	bool operator<(const Node& obj) const{
		return this->count > obj.count;
	}
	bool operator()(const Node&a, const Node& b) const{
		return a.count > b.count;
	}
};
string minDistance(string s, int minDist){
	int len = s.length();
	unordered_map<char, int> count;
	for(int i = 0; i < s.length(); i++){
		char c = s.at(i);
		if(count.find(c) == count.end()){
			count[c] = 1;
		}
		else{
			count[c]++;
		}
	}
	
	vector<Node> v;
	for(auto itc = count.begin(); itc != count.end(); itc++){
		v.push_back(Node(itc->first, itc->second));
	}
	sort(v.begin(), v.end());

	if(v[0].count > (s.length()/minDist) + 1){
		return "No solution";
	}

	auto it = v.begin();
	string ans = s;
	for(int i = 0; i < (s.length() + minDist - 1)/minDist; i++){
		for(int k = 0; k < minDist; k++){
			int offset = k * minDist + i;
			if(offset >= s.length()){
				break;
			}
			if(it->count == 0){
				it++;
			}
			ans[offset] = it->c;
			it->count--;
		}
	}

	return ans;
}
int main(void){
	string s = "ABCDEAABB";
	cout<<  minDistance(s, 3) <<endl;
}
