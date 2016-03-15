#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
	bool **palindrome;
	int N;
    /**
     * @param s: A string
     * @return: A list of lists of string
     */
	 
	bool isPalindrome(string &s, int start, int end)
	{
			return palindrome[start][end];
	}
	bool ** getIsPalindrome(string &s)
	{
		int n = s.length();
		
		palindrome = new bool * [n]();
		N = n;
		
		for(int i = 0; i < n; i++)
		{
			palindrome[i] = new int [n]();
		}
		
		for(int i = 0; i < n; i++)
		{
			palindrome[i][i] = true;
		}
		for(int i = 0; i < n-1; i++)
		{
			palindrome[i][i+1] = (s.at(i) == s.at(i+1));
		}
		for(int start = 0; start < n; start++)
		{
			for(int length = 2; 
					length < n && (start+length) < n; 
					length++)
			{
				palindrome[start][start+length] = palindrome[start+1][start+length-1] && 
												  (s.at(start) == s.at(start+length));
			}
		}
		
		return palindrome;
	
	}
	void destoryPalindrome(void)
	{
		for(int i = 0; i < N; i++)
		{
			delete palindrome[i];
		}
		delete [] palindrome;
	}
    vector<vector<string>> partition(string s) {
        // write your code here
		vector<vector<string>> vv;
		
		getIsPalindrome(s);
		
		
		for(int len = 1; len <= s.length(); len++)
		{
			vector<string> v = cutPalindrome(s, len, 0, s.length()-1);
			if(v.size() > 0)
			{
				vv.push_back(v);
			}
		}
		
		destoryPalindrome();
		
		return vv;
    }
	
	vector<string> cutPalindrome(string &s, int firstCutLen, int start, int end)
	{
			vector<string> v;
			if(start > end)
			{
				return v;
			}
			if((firstCutLen == 0) || 
			   (firstCutLen > (end - start + 1)))
			{
				return v;
			}
			
			if(start == end)
			{
				v.push_back(s.substr(start, 1));
				return v;
			}
			
			if(isPalindrome(s, start, start + firstCutLen-1))
			{
				v.push_back(s.substr(start, firstCutLen));
				vector<string> remaining = cutPalindrome(s, start + firstCutLen, end);
				v.insert(v.end(), remaining.begin(), remaining.end());
			}
			
			return v;
	}
};

int main(void)
{
	Solution mysol;
	vector<vector<string> > myvv;
	string str = "aabcb";
	myvv = mysol.partition(str);
	for(int i = 0; i < myvv.size(); i++)
	{
		vector<string> v = myvv[i];
		for(int j=0; j < v.size(); j++)
		{
			cout <<v[j] <<" ";
		}
		cout << endl;
	}

	return 0;
}
