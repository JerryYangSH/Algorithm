#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

/* Build a special tree heap
 * A rooted binary tree with keys in its nodes has the binary search property(BST) 
 * and Heap property. Each tree node contain an integer i and an integer j. 
 * If you pay attention only to the first key i in each node, it looks like a binary
 * search tree. If you pay attention only to the second key j in each node, it looks
 * like a heap.
 */
// http://www.1point3acres.com/bbs/thread-13292-1-1.html 
// Note: This is NOT a Treap, Treap 并不是二叉堆Heap，二叉堆必须是完全二叉树，而Treap可以并不一定是。

class Node{
public:
	int i, j;
	Node* left, *right;
	Node(int _i_, int _j_){
		this->i = _i_;
		this->j = _j_;
	}
};

bool compareByBST(const Node* a, const Node* b){
	return a->i < b->i;
}
class BstHeapTree{
private:
#if 0
	bool compare(int a, int b){
		return a < b;//min heap
	}
	void siftdown(vector<int>& nums, int i){
		while(i < nums.size()){
			int left = i * 2 + 1;
			int right = i * 2 + 2;
			int smallest = i;
			if(left < nums.size() && compare(left, smallest)){
				smallest = left;
			}
			if(right < nums.size() && compare(right, smallest)){
				smallest = right;
			}
			if(smallest == i){
				break;
			}
			int tmp = nums[i];
			nums[i] = nums[smallest];
			nums[smallest] = tmp;
			i = smallest;
		}
	}
	void heapify(vector<int> nums){
		if(nums.size() == 0){
			return;
		}
		for(int i = nums.size() / 2; i >= 0; i--){
			siftdown(nums, i);
		}
	}
#endif	
	Node* _inner_build(vector<Node*>& nodes, int start, int end){
		if(start > end){
			return NULL;
		}
		// find min index
		int minIndex = start;
		for(int i = start; i <= end; i++){
			if(nodes[i]->j < nodes[minIndex]->j){
				minIndex = i;
			}
		}
		Node* root = nodes[minIndex];
		root->left  = _inner_build(nodes, start, minIndex-1);
		root->right = _inner_build(nodes, minIndex+1, end);
		return root;
	}
public:
	Node* root;
	BstHeapTree(vector<Node*>& nodes){
		root = build(nodes);
	}
	
	Node* build(vector<Node*>& nodes){
		if(nodes.size() == 0){
			return NULL;
		}
		sort(nodes.begin(), nodes.end(), compareByBST);// sort by first value i
		return _inner_build(nodes, 0, nodes.size()-1);
	}
};

/////////////////////////////////////////////
// Below is for test purpose
/////////////////////////////////////////////
void printLevel(Node * root){
	if(root == NULL){
		return;
	}
	queue<Node*> q;
	q.push(root);
	while(!q.empty()){
		int size = q.size();
		while(size-- > 0){
			Node* node = q.front();
			q.pop();
			std::cout<<"["<<node->i<<","<<node->j<<"] ";
			if(node->left != NULL){
				q.push(node->left);
			}
			if(node->right != NULL){
				q.push(node->right);
			}
		}
		std::cout<<std::endl;
	}
}

int main(void){
	vector<Node*> nodes;
	nodes.push_back(new Node(6,30));
	nodes.push_back(new Node(5,35));
	nodes.push_back(new Node(4,10));
	nodes.push_back(new Node(1,40));
	nodes.push_back(new Node(2,20));
	nodes.push_back(new Node(3,25));
	
	BstHeapTree bhtree(nodes);
	printLevel(bhtree.root);
	
	for(auto node : nodes){
		delete node;
	}
	
	return 0;
}
