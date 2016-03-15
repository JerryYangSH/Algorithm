#include <iostream>
#include <limits>
#include <string>
#include <unordered_map>
#include <list>
using namespace std;

int main(void)
{
	int n1;
	int n2;
	char str[20];
	char str2[20];
	
	cout <<"input two numbers;"<<endl;
	cin>>n1>>n2;
	cin.getline(str2, 5);
	cout<<n1<<n2<<endl;
	cout<<"STR1 :"<<str<<endl;
	cout<<"STR2 :"<<str2<<endl;	

	const volatile int aaa = 10;
	cout <<">>>>>>"<<endl;
	int * p = (int *) &aaa;
	*p = 20;
	cout << *p <<endl;
	cout << aaa<<endl;

	cout<<"Test List"<<endl;
	list<int> lst;
	if(lst.begin() == lst.end()){
		cout<<"Empty"<<endl;
	}
	lst.insert(lst.begin(), 12);
	auto it = lst.begin();
	it = it++;
	return 0;
}
