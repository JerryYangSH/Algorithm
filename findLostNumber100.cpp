#include <iostream>
using namespace std;

int main(void)
{
	int a[99];
	int tmp=0;
	for(int i = 0; i < 99; i++)
	{
		a[i] = i+1;
	}

	a[30] = 0;
	for(int i = 0; i < 99; i++)
	{
		tmp  = tmp ^ a[i];
	}

	cout << "Lost number is "<<tmp<<endl;
}
