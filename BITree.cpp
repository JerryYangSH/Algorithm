#include <iostream>
#include <vector>
using namespace std;

// Binary Index Tree
class BinaryIndexTree{
private:
	vector<int> BIT;
public:
	// Returns sum of arr[0..index]. This function assumes
	// that the array is preprocessed and partial sums of
	// array elements are stored in BIT[].
	int getSum(int index){
		int sum = 0;
		index = index+1;
		while(index > 0){
			sum += BIT[index];
			index = index - (index & -index);
		}
		return sum;
	}
	// Updates a node in Binary Index Tree (BIT) at given index
	// in BIT.  The given value 'val' is added to BIT[i] and 
	// all of its ancestors in tree.
	void updateBIT(int index, int value){
		// index in BIT[] is 1 more than the index in arr[]
		index = index + 1;
		int n = BIT.size();
		while(index < n){
			BIT[index] += value;
			index = index + (index & -index); // ancestors, 1, 2, 4, 8, 16 ...
		}
	}
	
	// Constructs and returns a Binary Indexed Tree for given array of size n.
	BinaryIndexTree(vector<int> arr){
		BIT.assign(arr.size()+1, 0);
		for(int i = 0; i < arr.size(); i++){
			updateBIT(i, arr[i]);
		}
	}
};

int main(void){
	vector<int> arr = {2, 1, 1, 3, 2, 3, 4, 5, 6, 7, 8, 9};
	BinaryIndexTree BITree(arr);
	for(int i = 0; i <= arr.size(); i++){
		cout<< BITree.getSum(i) <<" ";
	}
	cout<<endl;
	cout << "Sum of elements in arr[0..5] is " << BITree.getSum(5)<<endl;
	return 0;
}
