//http://traceformula.blogspot.com/2015/12/count-of-smaller-numbers-after-self.html
//不明白
class Node{
public:
    Node * left;
    Node * right;
    int val;
    int count;// count of smaller
    int dup;
    Node(int v){
        this->val = v;
        this->count = 0;
        this->dup = 1;
        this->left = NULL;
        this->right = NULL;
    }
};

class Solution1 {
private:
    int insert(Node* root, int val) {
        int smallCount = 0;

        Node* cur = root;
        //不明白
        while (true) {
            if (cur->val < val) {
                smallCount += cur->count + cur->dup;
                if (cur->right == NULL) {
                    cur->right = new Node(val);
                    return smallCount;
                }
                else {
                    cur = cur->right;
                }
            }
            else if (cur->val > val) {
                cur->count++;
                if (cur->left == NULL) {
                    cur->left = new Node(val);
                    return smallCount;
                }
                else {
                    cur = cur->left;
                }
            }
            // equal
            else {
                smallCount += cur->count;
                cur->dup++;
                return smallCount;
            }
        }
        return smallCount;
    }
public:
    vector<int> countSmaller(vector<int>& nums) {
        vector<int> result;
        int n = nums.size();
        if(n == 0){
            return result;
        }
        Node * root = new Node(nums[n-1]);
        result.push_back(0);
        for(int i = nums.size()-2; i >= 0; i--){
            int count = insert(root, nums[i]);
            result.push_back(count);
        }

        // reverse result
        reverse(result.begin(), result.end());
        return result;
    }
};
////////////////////////////
// V2 : BIT(Binary Index Tree)

class Solution {
private:
	int makePositive(vector<int>& nums){
		int minValue = nums[0];
		int maxValue = nums[0];
		for(int x : nums){
			minValue = min(minValue, x);
			maxValue = max(maxValue, x);
		}
		if(minValue <= 0){
			minValue = -minValue + 1;
			maxValue += minValue;
			for(int i = 0; i < nums.size(); i++){
				nums[i] += minValue;
			}
		}
		return maxValue;
	}
	
	vector<int> bit;
	void build(int n){
		bit.assign(n+1, 0);
	}
	int get(int index){
		index = index+1;
		int sum = 0;
		while(index > 0){
			sum += bit[index];
			index -= index & -index;
		}
		return sum;
	}
	void set(int index, int value){
		index = index+1;
		while(index < bit.size()){
			bit[index] += value;
			index += (index & -index);
		}
	}
public:
    vector<int> countSmaller(vector<int>& nums) {
		vector<int> result;
        if(nums.size() == 0){
			return result;
		}
		
		// use nums[i] as index!!!
		int maxn = makePositive(nums);
		build(maxn+1);
		for(int i = nums.size()-1; i >= 0; i--){
			int count = get(nums[i]-1);
			result.push_back(count);
			set(nums[i], 1);
		}
		reverse(result.begin(), result.end());
		return result;
    }
};

