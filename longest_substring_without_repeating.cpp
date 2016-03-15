#include <string>
#include <string.h>
#include <iostream>
using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int i, j;
        int strLen = s.length();
        int len;
        int maxlen = 0;
        char maxkey = 0;
        char key;
        char count[128]={0};
        for(i=0; i < strLen; i++)
        {
            len = 0;
            memset(count, 0, sizeof(count));
            for(j=i; j < strLen; j++)
            {
                key = s.at(j);
                if(count[key] >= 1)
                {
                    break;
                }
                len++;
                count[key]++;
            }
            if(len > maxlen)
            {
                maxlen = len;
                maxkey = key;
            }
        }
        
        return maxlen;
        
    }
};
int main(void)
{
	Solution myobj;
	string mystr="abcabcaaa";
	int mylen;
	mylen = myobj.lengthOfLongestSubstring(mystr);

	cout<<"mylen is"<<mylen<<endl;
}
