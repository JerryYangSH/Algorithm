// Example program
#include <iostream>
#include <unordered_map>
using namespace std;
struct RandomListNode {
      int label;
      RandomListNode *next, *random;
      RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
};
RandomListNode *copyRandomList(RandomListNode *head) {
        // write your code here
        if(head == NULL){
            return NULL;
        }
        unordered_map<RandomListNode*, RandomListNode*> map;
        RandomListNode dummy(-1);
        dummy.next = head;
        RandomListNode * prev = &dummy;
        RandomListNode * node = head;
        while(node != NULL){
	    prev->next = new RandomListNode(node->label);
            map[node] = prev->next;
            prev = prev->next;
            node = node->next;
        }
        
        node = head;
        while(node != NULL){
           RandomListNode * newNode = map[node];
           newNode->random = map[node->random];
           node = node->next;
        }
        return map[head];
    }
    
int main()
{
  RandomListNode A(-1);
  RandomListNode B(1);
  A.next = &B;
  
  RandomListNode * X = copyRandomList(&A);
  cout << X->label<<endl;
  return 0;
}

