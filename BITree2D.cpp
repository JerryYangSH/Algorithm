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
                        index -= (index & -index);
                }
                return sum;
        }
		//
		// Return single value of array[index]. 
		int readSingle(int index){
			index = index+1;
			int sum = BIT[index]; // sum will be decreased
			while(index > 0){
				int z = index - (index & -index);//parent
				index--;
				while(index != z){ // at some iteration index (y) will become z
					sum -= BIT[index];
					index -= (index & -index);
				}
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
                        index += (index & -index); // ancestors, 1, 2, 4, 8, 16 ...
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

// https://www.topcoder.com/community/data-science/data-science-tutorials/binary-indexed-trees/#2d
// Binary Index Tree 2D
class BinaryIndexTree2D{
private:
		int n, m; // 2D BIT size (n * m)
        vector<vector<int>> BIT;
		
		//The function getSumY is the “same” as function getSum, called by getSum (2D)
		// Make it independent so easier to read.
		int getSumY(int x, int y){
			int sum = 0;
			y = y + 1;
			while(y > 0){
				sum += BIT[x][y];
				y -= (y & -y);
			}
			return sum;
		}
		//The function updateY is the “same” as function update, called by update (2D)
		// Make it independent so easier to read.
		void updateY(int x, int y, int value){
			y = y + 1;
			while(y < m){
				 BIT[x][y] += value;
				 y += (y & -y);
			}
		}
public:
        // Returns sum of [arr[0][0], arr[x][y] ]. This function assumes
        // that the array is preprocessed and partial sums of
        // array elements are stored in BIT[][].
        int getSum(int x, int y){
                int sum = 0;
                x = x + 1;
                while(x > 0){
                        sum += getSumY(x, y);
                        x = x - (x & -x);
                }
                return sum;
        }
        // Updates a node in Binary Index Tree (BIT) at given point(x, y)
        // in BIT.  The given value 'val' is added to BIT[x][y] and
        // all of its ancestors in tree.
        void updateBIT(int x,  int y, int value){
                // index in BIT[][] is 1 more than the index in arr[][]
                x = x + 1;
                int n = BIT.size();
                while(x < n){
                        updateY(x, y, value);
                        x += (x & -x); // ancestors, 1, 2, 4, 8, 16 ...
                }
        }

        // Constructs and returns a Binary Indexed Tree for given array of size n.
        BinaryIndexTree2D(vector<vector<int>> arr){
				n = arr.size() + 1;
				m = arr[0].size() + 1;
                BIT.assign(n, vector<int>(m, 0));
                for(int i = 0; i < arr.size(); i++){
					for(int j = 0; j < arr[i].size(); j++){
                        updateBIT(i, j, arr[i][j]);
					}
                }
        }
};

int main(void){
	cout<<"--- Binary Index Tree ---"<<endl;
        vector<int> arr = {2, 1, 1, 3, 2, 3, 4, 5, 6, 7, 8, 9};
        BinaryIndexTree BITree(arr);
		cout<<"Original array:"<<endl;
		for(int x: arr){
                cout<< x <<" ";
        }
		cout<<"Sum:"<<endl;
        for(int i = 0; i < arr.size(); i++){
                cout<< BITree.getSum(i) <<" ";
        }
        cout<<endl;
        cout << "Sum of elements in arr[0..5] is " << BITree.getSum(5)<<endl;
		
	
	//////////////////// 2D ////////////////////////////////
	cout<<endl<<"--- 2D Binary Index Tree ---"<<endl;
	vector<vector<int>> arr2 = {{1,2, 3},
			            {40,50,60},
                                    {10,11,12}};
	BinaryIndexTree2D BITree2D(arr2);
	cout<<"2D Sum: X\\Y"<<endl;
	for(int i = 0; i < arr2.size(); i++){
		cout<<"["<<i<<"]: ";
		for(int j = 0; j < arr2[i].size(); j++){
			cout<< BITree2D.getSum(i, j) <<" ";
		}
		cout<<endl;
	}
	cout<<endl;
        
	return 0;
}

