#include <iostream>
#include <queue>
#include <unordered_map>
using namespace std;

class Node{
public:
    int value;
    int prio;
    Node(int v, int p){
        this->value = v;
        this->prio = p;
    }        
};

class myqueue{
public:
    queue<Node> q;
    myqueue(){
    }

//  Input arguement:  percentage :  key : priority, value : percentage with this priority
//  For example:      percentage[1] = 50; percentage[2] = 30; percentage[3] = 15    
//  Return a single node list with each priority has the expected percentage
    vector<Node> getNodes(unordered_map<int, int> percentage){
        vector<Node>  result;
        // Validate argument
	int sum = 0;
        for(auto it = percentage.begin(); it != percentage.end(); it++){
            if(it->second < 0 || it->second > 100){
                return result;
            }
            sum += it->second;
        }
        if(sum != 100){
            // invalid input;
            return result;
        }
        
        unordered_map<int, long> map; // key : priority,  value : count of Node with the priority
        long totalCount = 0;
        bool done = false;
        do{
            if(q.empty()){
                break;
            }
            Node nowNode = q.front();
	    q.pop();
            result.push_back(nowNode);
            long pr = nowNode.prio;
            if(map.find(pr) == map.end()){
                map[pr] = 1;
            }
            else{
                map[pr]++;
            }
            totalCount++;
            
            done = true;
            for(auto it = map.begin(); it != map.end(); it++){
                int prio = it->first;
                long count = it->second;
                if((count * 100 / totalCount) !=  percentage[prio]){
                    done = false;
                    break;
                }
            }
        }while(!done);
        
        return result;
    }
    
    void add(Node node){
        q.push(node);
    }
};

// 
void generateTestData(myqueue& q){

	for(int i = 0; i < 50; i++){
		q.add(Node(111, 1));
	}
	
	for(int i = 0; i < 30; i++){
		q.add(Node(222, 2));
	}

	for(int i = 0; i < 15; i++){
		q.add(Node(333, 3));
	}
	for(int i = 0; i < 5; i++){
		q.add(Node(444, 4));
	}
	return;
}
int main(void){
	myqueue mq;
	for(int i = 0; i < 10; i++){
		generateTestData(mq);
	}
	unordered_map<int, int> percent;
	percent[1] = 50;
	percent[2] = 30;
	percent[3] = 15;
	percent[4] = 5;
	vector<Node> nodeList = mq.getNodes(percent);
	cout<<"nodeList size is "<<nodeList.size()<<endl;
	for(auto x : nodeList){
		cout<<x.value <<" with prio"<<x.prio<<endl;
	}
	cout<<endl;
	return 0;

}
