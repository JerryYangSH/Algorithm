/**
 * Definition for Directed graph.
 * struct DirectedGraphNode {
 *     int label;
 *     vector<DirectedGraphNode *> neighbors;
 *     DirectedGraphNode(int x) : label(x) {};
 * };
 */
class Solution {
public:
    /**
     * @param graph: A list of Directed graph node
     * @return: Any topological order for the given graph.
     */
    vector<DirectedGraphNode*> topSort(vector<DirectedGraphNode*> graph) {
        // write your code here
		vector<DirectedGraphNode*> result;
		int n = graph.size();
		if(n <= 0)
		{
			return result;
		}
		
		// walk thru each node, and setup the 入度
		unordered_map<DirectedGraphNode*, int> hashmap;
		for(int i = 0; i < n; i++)
		{
			vector<DirectedGraphNode *> &neighbors = graph[i]->neighbors;
			for(int j = 0; j < neighbors.size(); j++)
			{
				DirectedGraphNode * node = neighbors[j];
				if(hashmap.find(node) == hashmap.end())
				{
					hashmap[node] = 1;
				}
				else
				{
					hashmap[node] = hashmap[node] + 1;
				}
			}
			
		}
		
		// find the heading node(s) that with positive reference count
		queue<DirectedGraphNode*> q;
		for(int i = 0; i < n; i++)
		{
			DirectedGraphNode * node = graph[i];
			if(hashmap.find(node) == hashmap.end())
			{
				q.push(node);
				result.push_back(node);
			}		
		}
		while(!q.empty())
		{
			DirectedGraphNode * head = q.front();
			q.pop();
			vector<DirectedGraphNode *> &neighbors = head->neighbors;
			for(int j = 0; j < neighbors.size(); j++)
			{
				DirectedGraphNode * node = neighbors[j];
				hashmap[node] = hashmap[node] - 1;
				if(hashmap[node] == 0)
				{
					q.push(node);
					result.push_back(node);
				}
			}
		}
		
		return result;
    }
};
