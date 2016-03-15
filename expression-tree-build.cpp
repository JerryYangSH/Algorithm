#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <limits>
using namespace std;
//////////////////////////////////////////////////////////////////////////////////
//Definition of ExpressionTreeNode:
class ExpressionTreeNode {
public:
     string symbol;
     ExpressionTreeNode *left, *right;
     ExpressionTreeNode(string symbol) {
         this->symbol = symbol;
         this->left = this->right = NULL;
     }
};
/* V2 : Build directly expression tree from expression
 *    1). Leaf node is number
 *    2). Non-leaf is operator
 *    3). top level node has lower priority
 *    4). The subtree of each node is a complete expression 
 */
class TNode{
public:
    int priority;
    ExpressionTreeNode* root;
    TNode(int p, string ss){
        this->priority = p;
        this->root = new ExpressionTreeNode(ss);
        
    }
};
class Solution {
private:
    int getPriority(string a, int base){
        if((a.compare("+") == 0) || (a.compare("-") == 0)){
            return base + 1;
        }
        else if((a.compare("*") == 0) || (a.compare("/") == 0)){
            return base + 2;
        }
        return numeric_limits<int>::max();
    }
public:
    /**
     * @param expression: A string array
     * @return: The root of expression tree
     */
    ExpressionTreeNode* build(vector<string> &expression) {
        if(expression.size() == 0){
            return NULL;
        }
        
        // stack keeps tree nodes with increasing priority sequence.
        stack<TNode*> s;
        int priority = 0;
        int base = 0;
        for(int i = 0; i <= expression.size(); i++){
            if(i != expression.size()){
                if(expression[i].compare("(") == 0){
                    base += 10;
                    continue;
                }
                else if(expression[i].compare(")") == 0){
                    base -= 10;
                    continue;
                }
                priority = getPriority(expression[i], base);
            }
            TNode * rightNode = NULL;
            if(i == expression.size()) {
                rightNode = new TNode(numeric_limits<int>::min(), "");
            }
            else{
                rightNode = new TNode(priority, expression[i]);
            }
            
            //top level node has low priority
            while(!s.empty() && rightNode->priority <= s.top()->priority){
                TNode * nowNode = s.top();
                s.pop();
                if(s.empty()){
                    rightNode->root->left = nowNode->root;
                }
                else{
                    TNode * leftNode = s.top();
                    if(leftNode->priority < rightNode->priority){
                        rightNode->root->left = nowNode->root;
                    }
                    else{
                        leftNode->root->right = nowNode->root;
                    }
                }
            }
            s.push(rightNode);
        }
        return (s.top())->root->left;
    }
};

int main(void){
	Solution sol;
	vector<string> exp = {"2","*","6","-","(","23","+","7",")","/","(","1","+","2",")"};
        ExpressionTreeNode* node = sol.build(exp);
	queue<ExpressionTreeNode*> q;
	if(node != NULL){
		q.push(node);
	}	
	while(!q.empty()){
		ExpressionTreeNode* node = q.front();
		q.pop();
		cout<<node->symbol<<" ";
		if(node->left != NULL){
			q.push(node->left);
		}
		if(node->right != NULL){
			q.push(node->right);
		}
	}
	return 0;
}
