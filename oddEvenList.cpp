#include <iostream>
using namespace std;

  struct ListNode {
      int val;
      ListNode *next;
      ListNode(int x) : val(x), next(NULL) {}
  };
 
class Solution {
public:
    ListNode* oddEvenList(ListNode* head) {
        ListNode oddDummy(-1);
        ListNode evenDummy(-1);
        ListNode * odd = &oddDummy;
        ListNode * even = &evenDummy;
        bool toggle = true;
        while(head != NULL){
            if(toggle){
                odd->next = head;
                odd = odd->next;
            }
            else{
                even->next = head;
                even = even->next;
            }
            head = head->next;
            toggle = !toggle;
        }
	even->next = NULL;
        odd->next = evenDummy.next;
        
        return oddDummy.next;
    }
};

int main(void){
	ListNode a(1), b(2), c(3);
	a.next = &b;
	b.next = &c;
	cout<<"Original node list: "<<endl;
	ListNode * head = &a;
	while(head != NULL){
		cout<<head->val<<" ";
		head = head->next;
	}
	cout<<endl;
	
	cout<<"New node list: "<<endl;
	Solution sol;
	head = sol.oddEvenList(&a);
	while(head != NULL){
		cout<<head->val<<" ";
		head = head->next;
	}
	cout<<endl;
	return 0;
}
