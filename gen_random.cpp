#include <stdlib.h>
#include <vector>
#include <iostream>
using namespace std;

vector<int> gen_vector_int(int size, int range_max)
{
	vector<int> v;
	int key;
	for(int i = 0; i < size; i++)
	{
		key = random() % range_max;
		v.push_back(key);
	}
	return v;
}
vector<int> gen_vector_int(int size, int range_min, int range_max)
{
	vector<int> v;
	int key;
	for(int i = 0; i < size; i++)
	{
		key = random() % (range_max - range_min) + range_min;
		v.push_back(key);
	}
	return v;
}
int main(void)
{
	for(int i = 0; i < 100; i++)
	{
		cout << random()%100<<" ";
		if(i%16 == 15) 
		{
			cout <<endl;
		}
	}

	cout << endl;
	vector<int> v = gen_vector_int(128, 30,100);
	for(int i = 0; i < 128; i++)
	{
		cout << v[i]<<" ";
		if(i%16 == 15)
		{
			cout << endl;
		}
	}
}
