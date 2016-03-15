class Solution {
public:
	bool isOp(string op){
		if(op.compare("+") == 0 || 
		   op.compare("-") == 0 || 
		   op.compare("*") == 0 || 
		   op.compare("/") == 0 ){
			return true;
		}
		
		return false;
	}
	
	// greater: 1
	// equal: 0
	// less: -1
	int compareOrder(string op1, string op2) {
		int prio1 = 0, prio2 = 0;
		if(op1.compare("*") == 0 || 
		   op1.compare("/") == 0){
			prio1 = 1;
		}
		if(op2.compare("*") == 0 || 
		   op2.compare("/") == 0){
			prio2 = 1;
		}
		return prio1 - prio2;
	}
	vector<string> convertToRPN(vector<string> &expression) {
		vector<string> rpnList;
		stack<string> opStack;
		for(int i = 0; i < expression.size(); i++){
			string now = expression[i];
			if(now.compare("(") == 0){
				opStack.push(now);
			}
			else if(now.compare(")") == 0){
				while(opStack.top().compare("(") != 0){
					rpnList.push_back(opStack.top());
					opStack.pop();
				}
				opStack.pop();
			}
			else if(isOp(now)){
				if(!opStack.empty() &&
					isOp(opStack.top()) &&
					compareOrder(opStack.top(), now) >= 0){
					// pop out those ops with higher or equal order 
					rpnList.push_back(opStack.top());
					opStack.pop();
				}
				opStack.push(now);
			}
			else {
				rpnList.push_back(now);
			}
		}
		while(!opStack.empty()) {
			rpnList.push_back(opStack.top());
			opStack.pop();
		}
		return rpnList;
	}
	int calculate(int a, int b, string op){
		if(op.compare("+") == 0){
			return a+b;
		}
		else if(op.compare("-") == 0){
			return a-b;
		}
		else if(op.compare("*") == 0){
			return a*b;
		}
		else if(op.compare("/") == 0){
			return a/b;
		}
		return -1; // should never happen
	}
	int calculateRPN(vector<string> &expression) {
		stack<int> s;
		int number = 0;
		for(int i = 0; i < expression.size(); i++){
			string now = expression[i];
			if(isOp(now)){
				int b = s.top();
				s.pop();
				int a = s.top();
				s.pop();
				number = calculate(a, b, now);
				s.push(number );
			}
			else {
				number = stoi(now);
				s.push(number);
			}
		}
		return s.top();
	}
    /**
     * @param expression: a vector of strings;
     * @return: an integer
     */
    int evaluateExpression(vector<string> &expression) {
        // write your code here
        if(expression.size() == 0){
            return 0;
        }
		// 1. converted to reversed polish expression 
		vector<string> rpe = convertToRPN(expression);
		
		// 2. caculate the reversed polish expression
		return calculateRPN(rpe);
    }
};
