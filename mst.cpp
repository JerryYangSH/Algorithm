#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

// Start UnionFind (for Kruskal)
class UnionFind{
public:
	unordered_map<int, int> father;
	UnionFind(int n){
		for(int i = 0; i < n; i++){
			father[i] = i;
		}
	}
	int find(int x){
		int parent = father[x];
		while(parent != father[parent]){
			parent = father[parent];
		}
		return parent;
	}
	void union_both(int x, int y){
		int fa_x = find(x);
		int fa_y = find(y);
		if(fa_x != fa_y){
			father[fa_x] = father[fa_y];
		}
 	}
};
// End UnionFind
class Edge{
public:
	int weight;
	char start; // 'A' ~ 'Z'
	char end;  // 'A' ~ 'Z'
	Edge(): weight(0), start(0), end(0){}
	Edge(int w, int s, int e){
		this->weight = w;
		this->start = s;
		this->end = e;
	}
	
	bool operator<(const Edge& obj) const {
		return this->weight < obj.weight; //从小到大排序
	}
	bool operator()(const Edge& A, const Edge& B) const {
		return A.weight < B.weight;
	}
};

// Prime Algorithm - Minimum Spanning Tree
// Input : Edges
// Output : Total minimal weights and result that contains the set of edges in MST
int prime(vector<Edge>& result, vector<Edge>& edges){
}

// Kruskal Algorithm - Minimum Spanning Tree
// Input : Edges
// Output : Total minimal weights and result that contains the set of edges in MST
int kruskal(vector<Edge>& result, vector<Edge>& edges){
	int totalWeight = 0;
	sort(edges.begin(), edges.end());
	UnionFind uf(128);
	for(int i = 0; i < edges.size(); i++){
		Edge edge = edges[i];
		if(uf.find(edge.start) != uf.find(edge.end)){
			uf.union_both(edge.start, edge.end);
			result.push_back(edge);
			totalWeight += edge.weight;
		}
	}
	return totalWeight;
}

void printedges(vector<Edge>& edges){
	for(auto edge : edges){
		cout<<edge.start <<" -> "<<edge.end<<" ";
	}
}
// test Minimum Spanning Tree
int main(void){
	//data from http://www.cnblogs.com/adforce/p/3247437.html
	vector<Edge> edges;
	edges.push_back(Edge(4, 'A', 'B'));
	edges.push_back(Edge(8, 'B', 'C'));
	edges.push_back(Edge(7, 'C', 'D'));
	edges.push_back(Edge(9, 'D', 'E'));
	edges.push_back(Edge(10, 'E', 'F'));
	edges.push_back(Edge(2, 'F', 'G'));
	edges.push_back(Edge(1, 'G', 'H'));
	edges.push_back(Edge(8, 'H', 'A'));
	edges.push_back(Edge(11, 'B', 'H'));
	edges.push_back(Edge(2, 'C', 'I'));
	edges.push_back(Edge(7, 'I', 'H'));
	edges.push_back(Edge(6, 'I', 'G'));
	edges.push_back(Edge(4, 'C', 'F'));
	edges.push_back(Edge(14, 'D', 'F'));

	// Kruskal Algorithm	
	vector<Edge> mst;
	int total = kruskal(mst, edges);
	cout<<"Total minimal weight is "<<total<<endl;
	printedges(mst);
	
	return 0;
}
