// Example program
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

// class node
class node {
public:
    int id;   // index 
    int num; // count of val, in case duplicate numbers.
    node(node &now)
    {
        this->id = now.id;
        this->num = now.num;
    }
    node(int first, int second)
    {
        this->id = first;
        this->num = second;
    }
};
// class HashHeap
class HashHeap {
private:
    vector<int> heap;
    string mode;
    int size_t;
    unordered_map<int, node*> hash;

public:
    HashHeap(string mod)
    {
        mode = mod;
        size_t = 0;
    }
    HashHeap()
    {
        mode = "max";
        size_t = 0;
    }
    
    int peek()
    {
        return heap.at(0);
    }
    
    int size()
    {
        return size_t;
    }
    
    bool empty()
    {
        return (size_t == 0);
    }
    
    int parent(int id)
    {
        if(id == 0)
        {
            return -1;
        }
        return (id - 1)/2;
    }
    int lson(int id)
    {
        return (2 * id + 1);
    }
    int rson(int id)
    {
        return (2 * id + 2);
    }
    bool comparesmall(int a, int b)
    {
        if(a <= b)
        {
            if(mode.compare("min") == 0)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            if(mode.compare("min") == 0)
            {
                return false;
            }
            else
            {
                return true;
            }
        }
    }
    
    void swap(int idA, int idB)
    {
        int valA = heap[idA];
        int valB = heap[idB];
        
        hash[valB]->id = idA;
        hash[valA]->id = idB;
        
        heap[idA] = valB;
        heap[idB] = valA;
    }
    
    int poll()
    {
        size_t--;
        int now = heap[0];
        node* hashNow = hash[now];
        if(hashNow->num == 1)
        {
            swap(0, heap.size()-1);
            hash.erase(now);
            heap.pop_back();
            if(heap.size() > 0)
            {
                siftdown(0);
            }
        }
        else
        {
            hashNow->num--;
        }
        return now;
    }
    
    void add(int now)
    {
        size_t++;
        if(hash.find(now) != hash.end())
        {
            node* hashNow = hash[now];
            hashNow->num++;
        }
        else
        {
            heap.push_back(now);
            hash[now] = new node(heap.size()-1, 1);
			siftup(heap.size()-1);
        }
    }
    
    void remove(int now)
    {
        size_t --;
        node * hashNow = hash[now];
        int id = hashNow->id;
        int num = hashNow->num;
        if(num == 1)
        {
            swap(id, heap.size()-1);
            hash.erase(now);
            heap.pop_back();
            if(heap.size() > id)
            {
                siftup(id);
                siftdown(id);
            }
        }
        else
        {
            hashNow->num--;
        }
    }
    
    void siftup(int id)
    {
        while(parent(id) > -1)
        {
            int parentId = parent(id);
            if(comparesmall(heap[parentId], heap[id]) == true)
            {
                break;
            }
            else
            {
                swap(id, parentId);
            }
            id = parentId;
        }
    }
    
    void siftdown(int id)
    {
        while(lson(id) < heap.size())
        {
            int leftId = lson(id);
            int rightId = rson(id);
            int son;
            if (rightId >= heap.size() || 
                (comparesmall(heap[leftId], heap[rightId]) == true)) {
				son = leftId;
			} else {
				son = rightId;
			}
			
			if (comparesmall(heap[id], heap[son]) == true) {
				break;
			} else {
				swap(id, son);
			}
			id = son;
        }
    }
};

class Solution {
public:
    /**
     * @param nums: A list of integers.
     * @return: The median of the element inside the window at each moving
     */
    vector<int> medianSlidingWindow(vector<int> &nums, int k)  {
        // write your code here
        vector<int> result;
        if(nums.size() < k || k < 1)
        {
            return result;
        }
        
        int median = nums[0];
        HashHeap minheap("min");
        HashHeap maxheap("max");
        

        for(int i = 0; i < nums.size(); i++)
        {
            if(i != 0)
            {
                if(nums[i] > median)
                {
                    minheap.add(nums[i]);
                }
                else
                {
                    maxheap.add(nums[i]);
                }
            }
            
            if(i >= k)
            {
                // since num[i-k] is out of sliding window, we need to delete it
                if(median == nums[i-k])
                {
                    //it's median
                    if(maxheap.size() > 0)
                    {
                        median = maxheap.poll();
                    }
                    else if(minheap.size() > 0)
                    {
                        median = minheap.poll();
                    }
                }
                else if(median < nums[i-k])
                {
                    // must be in minheap
                    minheap.remove(nums[i-k]);
                }
                else
                {
                    // must be in maxheap
                    maxheap.remove(nums[i-k]);
                }			

            }
            
            // adjust heap size, ensure A = [B-1, B]
            // A: maxheap.size()
            // B: minheap.size()
            // 
            while (maxheap.size() > minheap.size()) {
			    minheap.add(median);
			    median = maxheap.poll();
		}
	    while (minheap.size() > (maxheap.size() + 1)) {
			maxheap.add(median);
			median = minheap.poll();
		}

	    if ((i + 1) >= k) {
			result.push_back(median);
		}
        }
        
        return result;
        
    }
};

int main()
{
    vector<int> input = {1,2,7,7,2};
    for(int i = 0; i < input.size(); i++)
  {
      cout << input[i] << " ";
  }
  cout <<endl;
  Solution sol;
  vector<int> result = sol.medianSlidingWindow(input, 3);
  for(int i = 0; i < result.size(); i++)
  {
      cout << result[i] << " ";
  }
  cout <<endl;
  
  return 0;
}

