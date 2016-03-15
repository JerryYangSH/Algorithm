/**
 * Definition for undirected graph.
 * struct UndirectedGraphNode {
 *     int label;
 *     vector<UndirectedGraphNode *> neighbors;
 *     UndirectedGraphNode(int x) : label(x) {};
 * };
 */
class Solution {
public:
    /**
     * @param node: A undirected graph node
     * @return: A undirected graph node
     */
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
        // write your code here
		if(node == NULL)
		{
			return NULL;
		}
		int start = 0;
		//UndirectedGraphNode * nodes;
		vector<UndirectedGraphNode *> list;
		unordered_map<UndirectedGraphNode *, UndirectedGraphNode *> hashmap;
		list.push_back(node);
		hashmap[node] = new UndirectedGraphNode(node->label);
		
		// clone nodes
		while(start < list.size())
		{
			vector<UndirectedGraphNode *> neighbor = list[start++]->neighbors;
			for(vector<UndirectedGraphNode *>::iterator it = neighbor.begin(); 
				it != neighbor.end();
				it++)
			{
				if(hashmap.find(*it) != hashmap.end())
				{
					// alreay exists. ignore
					continue;
				}
				list.push_back(*it);
				//hashmap[*it] = new UndirectedGraphNode((*it)->label);
				UndirectedGraphNode * k = *it;
				UndirectedGraphNode * v = new UndirectedGraphNode(k->label);
				hashmap.insert(std::make_pair<UndirectedGraphNode *, UndirectedGraphNode *> (k,v));
			}
		}
		
		//clone neighbors
		start = 0;
		while(start < list.size())
		{
			vector<UndirectedGraphNode *> neighbor = list[start]->neighbors;
			UndirectedGraphNode * nodes = hashmap[list[start]];
			for(vector<UndirectedGraphNode *>::iterator it = neighbor.begin(); 
				it != neighbor.end();
				it++)
			{
				nodes->neighbors.push_back(hashmap[(*it)]);
			}		
			start++;		
		}
		
		return hashmap[(node)];
    }
};
