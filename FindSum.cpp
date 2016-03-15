#include <stdlib.h>
#include <vector>
#include <iostream>
using namespace std;

/*

输入两个数m和n ，从数列1,2,3,4,.....n这些数中挑选几个

使得和为m，找出所有的这样的组合

*/

void FindSum(int m,int n,vector<int>& vec)

{

    if(m < 0 || n < 0)
     return ;

    if(m == 0)
    {
        vector<int>::iterator itr = vec.begin();
        for(;itr != vec.end();itr++)
        {
		cout<<*itr<<" ";
	}
        cout<<endl;
        return ;
    }

    vec.push_back(n); // 典型的背包问题

    FindSum(m-n,n-1,vec); //放入一个元素 在剩下的元素满足剩下的要求

    vec.pop_back();//不放入当期的元素  在剩下的元素满足所有的要求

    FindSum(m,n-1,vec);

}

int main()
{
   int sum = 9;
   int n = 10;
   vector<int> vec;
   FindSum(sum, n, vec);
   return 0;
}
