#include <iostream>
using namespace std;
/*
*
* 用递归找一个字符串中 最长连续出现的字符的个数
* 例如：
* “abbbbbbc"返回的就是6
*/
int maxDupLen(string& str, int& count, int& maxCount, int pos)
{
	if(pos == str.length())
	{
		return maxCount;
	}
	if(str.at(pos) == str.at(pos-1))
	{
		count++;
		if(count > maxCount)
		{
			maxCount = count;
		}
	}
	else
	{
		count = 1;
	}
	
	return maxDupLen(str, count, maxCount, pos+1);
}

int main(void)
{
	string str("11aaaaaaaaabbbcccddeeeee");
	int count = 1;
	int maxCount = 1;
	cout << maxDupLen(str, count, maxCount, 1)<<endl;
	return 0;
}