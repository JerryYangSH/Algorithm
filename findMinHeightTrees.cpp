#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <limits>
using namespace std;

class Node{
public:
    int label;
    vector<Node*> neighbor;
    Node(int l){
        this->label = l;
    }
};
class Solution {
public:
    int bfs(Node* root){
        int distance = 0;
        queue<Node*> q;
        unordered_map<int, bool> visited;
        q.push(root);
        visited[root->label] = true;
        while(!q.empty()){
	    int size= q.size();
	    while(size-- > 0){
            Node* node = q.front();
            q.pop();
            
            for(auto nb : node->neighbor){
                if(visited.find(nb->label) == visited.end()){
                    q.push(nb);
                    visited[nb->label] = true;
                }
            }
	    }
            distance++;
        }
        return distance;
    }
    vector<int> findMinHeightTrees(int n, vector<pair<int, int>>& edges) {
        unordered_map<int, Node*> map;
        //vector<Node*> nList;
        for(auto p : edges){
            int first = p.first;
            int second = p.second;
            if(map.find(first) == map.end()){
                map[first] = new Node(first);
            }
            if(map.find(second) == map.end()){
                map[second] = new Node(second);
            } 
            map[first]->neighbor.push_back(map[second]);
            map[second]->neighbor.push_back(map[first]);
        }
        
        int minLen = numeric_limits<int>::max();
        unordered_map<int, vector<int>> distanceToNodes;
        for(auto it = map.begin(); it != map.end(); it++){
            Node* node = it->second;
            int len = bfs(node);
    cout<<">"<<node->label<<": len = "<<len<<endl;       
	 distanceToNodes[len].push_back(node->label);
            minLen = min(minLen, len);
        }
        

        return distanceToNodes[minLen];
    }
};

int main(void){

	int n = 4;
	vector<pair<int, int>> edges;
	edges.push_back(make_pair<int,int>(1,0));
	edges.push_back(make_pair<int,int>(1,2));
	edges.push_back(make_pair<int,int>(1,3));
	Solution sol;
	auto res = sol.findMinHeightTrees(n, edges);
	for(int x: res){
		cout<<x<<" ";
	}
	cout<<endl;

	return 0;
}
