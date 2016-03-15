#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <queue>
using namespace std;

class Node{
public:
	string word;
	int count;
public:	
	Node(string word, int count){
		this->word = word;
		this->count = count;
	}
	bool operator<(const Node& obj) const{
		return this->count > obj.count; // min heap
	}
};

class TopN{
private:
	vector<string> words;
public:
	void insert(string query){
		words.push_back(query);
	}
	
	// V1 hash + heap 找top N
	vector<string> getTopN(int n){
		vector<string> result;
		if(n > words.size()){
			return words;
		}
	
		unordered_map<string, int> map;
		for(string word : words){
			if(map.find(word) == map.end()){
				map[word] = 1;
			}
			else {
				map[word] = map[word] + 1;
			}
		}
		
		priority_queue<Node> pq;
		vector<Node> nodeList;
		int index = 0;
		for(auto it = map.begin(); 
			it != map.end(); 
			it++, index++){
			Node node(it->first, it->second);
			if(index < n){
				pq.push(node);
			}
			else {
				Node topone = pq.top();
				if(node.count > topone.count){
					pq.pop();
					pq.push(node);
				}
			}
		}
		
		while(!pq.empty()){
			result.push_back(pq.top().word);
			pq.pop();
		}
		
		return result;
	}
	
	// hash + vector + quick select 找 TOP N
	vector<string> selectTopN(int n){
		vector<string> result;
		if(n > words.size()){
			return words;
		}
	
		unordered_map<string, int> map;
		for(string word : words){
			if(map.find(word) == map.end()){
				map[word] = 1;
			}
			else {
				map[word] = map[word] + 1;
			}
		}
		
		vector<Node> wordList;
		for(auto it = map.begin(); it != map.end(); it++){
			wordList.push_back(Node(it->first, it->second));
		}
		// quick select 
		int j = quickSelect(wordList, 0, wordList.size()-1, n);
		for(int i = 0; i <= j; i++){
			result.push_back(wordList[i].word);
		}
		return result;
	}
	int quickSelect(vector<Node>& wordList, int start, int end, int n){
		if(start >= end){
			return start;
		}
		int j = partition(wordList, start, end);
		if(j == n-1){
			return j;
		}
		else if ( j > n-1){
			return quickSelect(wordList, start, j - 1, n);
		}
		else {
			return quickSelect(wordList, j+1, end, n-j-1);
		}
	}
	int partition(vector<Node>& wordList, int start, int end){
		if(start >= end){
			return start;
		}
		
		int pivot = end;
		end--;
		while(start <= end){
			while(start <= end && wordList[start].count >= wordList[pivot].count){
				start++;
			}
			while(start <= end && wordList[end].count < wordList[pivot].count){
				end--;
			}
			if(start < end){
				swap(wordList[start], wordList[end]);
			}
		}
		swap(wordList[start], wordList[pivot]);
		return start;
	}
	void swap(Node& a, Node& b){
		Node tmp = a;
		a = b;
		b = tmp;
	}
};

int main(void){
	vector<string> words = {"bob", "joe", "bob", "jane", "bob", "joe", "jack", "steven", "jerry", "jerry", "Marsha", "jerry", "jerry"};
	TopN topn;
	for(string str : words){
		topn.insert(str);
	}
	
	cout <<"Hash Map + Heap :"<<endl;
	vector<string> result = topn.getTopN(2);
	for(string str : result){
		cout<<str<<endl;
	}
	
	cout <<"Hash Map + Quick Select :"<<endl;
	result = topn.selectTopN(2);
	for(string str : result){
		cout<<str<<endl;
	}
	
	return 0;
}
