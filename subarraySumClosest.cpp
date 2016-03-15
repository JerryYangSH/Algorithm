struct mypaircompare {
    bool operator ()(pair<int, int> &a, pair<int, int> &b) 
    {
        return (a.first < b.first) ? true : false;
    }
};

class Solution {
public:
    
    /**
     * @param nums: A list of integers
     * @return: A list of integers includes the index of the first number 
     *          and the index of the last number
     */
    vector<int> subarraySumClosest(vector<int> nums){
        // write your code here
        vector<int> result;
        int n = nums.size();
        if(n == 0)
        {
            return result;
        }
        
        vector<pair<int, int> > sum;
        sum.resize(n);
        pair<int,int> a(nums[0], 0);
        sum[0] = a;
        for(int i = 1; i < n; i++)
        {
            pair<int,int> b(sum[i-1].first + nums[i], i); 
            sum[i] = b;
        }
        
        sort(sum.begin(), sum.end());
        
        pair<int,int> maxSum(0, -1);
        int minDiff = numeric_limits<int>::max();
        int start = -1, end = 0;
        int diff = sum[0].first;
        for(int i = 1; i < n; i++)
        {
            int diff = sum[i].first - sum[i-1].first;
            if(diff < minDiff)
            {
                minDiff = diff;
                start = sum[i].second;
                end = sum[i-1].second;
            }
        }
        
        if(start > end)
        {
            int tmp = start;
            start = end;
            end = tmp;
        }
        

        result.push_back(start+1);
        result.push_back(end);
        return result;
        
    }
};