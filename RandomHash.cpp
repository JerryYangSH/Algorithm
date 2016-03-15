#include <iostream>
#include <vector>
#include <unordered_map>
#include <time.h>

using namespace std;
// http://www.geeksforgeeks.org/design-a-data-structure-that-supports-insert-delete-search-and-getrandom-in-constant-time/
// Implement HashTable with get,set,delete,getRandom in O(1) Time
/* 
	a) Insert
	b) Delete
	c) Search
	d) getRandom */
	
class RandomHash{
private:
	vector<int> array; // store data value
	unordered_map<int, int> map;  // map from value -> array index
	void swap(vector<int> &A, int p, int q){
		int tmp = A[p];
		A[p] = A[q];
		A[q] = tmp;
	}
public:
	RandomHash(){}
	void add(int val){
		if(map.find(val) != map.end()){
			// if already exist, do nothing
			return;
		}
		array.push_back(val);
		map[val] = array.size()-1;		
	}
	void remove(int val){
		if(map.find(val) == map.end()){
			// do not exist
			return;
		}
		int index = map[val];
		swap(array, index, array.size()-1); //swap the one(to be deleted) with the last in array
		array.pop_back(); // delete the last element in the array
		map.erase(val); // remove the element in the hash table
		map[array[index]] = index; // update the index in the hash
	}
	// return the index
	int search(int val){
		if(map.find(val) == map.end()){
			return -1;// don't find
		}
		
		return map[val];
	}
	int getRandom(){
		srand((unsigned)time(NULL));
		int index = rand() % array.size();
		return array[index];
	}
	int size(){
		return array.size();
	}
};

int main(void){
	RandomHash hash;
	hash.add(2);
	hash.add(9);
	hash.add(10);
	hash.add(6);
	cout<<"Hash size : "<<hash.size()<<endl;
	hash.remove(10);
	cout<<"Hash size : "<<hash.size()<<endl;
	
	cout<<"Random test "<<endl;
	for(int i = 0; i < 5; i++){
	    int val = hash.getRandom();
		cout<<"Get Random index = "<< hash.search(val)<<", value =" << val <<endl;
	}
	
	for(int i = 0; i < 10; i++){
	    srand((unsigned)time(NULL));
		int val = rand() % 10;
		if(hash.search(val) == -1){
			cout<<"Not found : "<<val<<endl;
		}
		else {
			cout<<"We found : "<<val<<endl;
		}
	}
	return 0;	
}