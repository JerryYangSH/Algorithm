#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>
using namespace std;


class LRUCache{
private:
    struct cacheNode{
        int key;
        int value;
        cacheNode(int k, int v) : key(k), value(v){};
    };
    int capacity;
    list<cacheNode> cacheList;
    unordered_map<int, list<cacheNode>::iterator> cacheMap;
    
public:  
    LRUCache(int capacity) {
        this->capacity = capacity;
    }
  
    int get(int key) {
        if(cacheMap.find(key) == cacheMap.end()){
            return -1;
        }
        cacheList.splice(cacheList.begin(), cacheList, cacheMap[key]);
        cacheMap[key] = cacheList.begin();
        return cacheMap[key]->value;
    }
    
    void set(int key, int value) {
        if(cacheMap.find(key) == cacheMap.end()){
            cacheList.push_front(cacheNode(key, value));
            cacheMap[key] = cacheList.begin();
            if(cacheList.size() > capacity){
		cacheMap.erase(cacheList.back().key);
                cacheList.pop_back();
            }
        }
        else{
            cacheMap[key]->value = value;
            cacheList.splice(cacheList.begin(), cacheList, cacheMap[key]);
            cacheMap[key] = cacheList.begin();
        }
    }
};

int main(void){
	LRUCache lru(1);
	lru.set(2, 1);
	cout << lru.get(2)<<endl;
	lru.set(3, 2);
	cout << lru.get(2)<<endl;
	cout << lru.get(3)<<endl;
	return 0;
}
