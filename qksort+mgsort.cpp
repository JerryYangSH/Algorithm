// Example program
#include <iostream>
#include <string>
#include <vector>
#include <string.h>
using namespace std;


void merge(int A[], int start, int mid, int end)
{
	int len = end - start + 1;
	if(len == 0)
	{
		return;
	}
	int * array = new int[len];
	int i = 0;
	int left = start;
	int right = mid + 1;
	while(left <= (mid) && right <= end)
	{
		if(A[left] < A[right])
		{
			array[i++] = A[left++];
		}
		else 
		{
			array[i++] = A[right++];
		}
	}
	
	if(left <= mid)
    {
        memcpy(&array[i], &A[left], (mid - left + 1)* sizeof(int));
    }
    else if(right <= end)
    {
        memcpy(&array[i], &A[right], (end - right + 1) * sizeof(int));
    }
    memcpy(A+start, array, len * sizeof(int));
	
	delete [] array;
	
}
void mgsort(int A[], int start, int end)
{
	if(start == end)
	{
		return;
	}

	int mid = (start + end) / 2;
	if(start < mid)
	{
	    mgsort(A, start, mid);
	}
	if(mid + 1 < end)
	{
	    mgsort(A, mid+1, end);
	}
	merge(A, start, mid, end);
	return;
}

void swap(int A[], int x, int y)
{
	int tmp = A[x];
	A[x] = A[y];
	A[y] = tmp;
}
int partition(int A[], int start, int end)
{
	if(start == end)
	{
		return start;
	}
	int pivot = A[end];
	int left = start;
	int right = end-1;
	while(left <= right)
	{
		while(left <= right && A[left] <= pivot)
		{
			left++;
		}
		while(left <= right && A[right] > pivot)
		{
			right--;
		}
		if(left < right)
		{
			swap(A, left, right);
		}
	}
	swap(A, left, end);
	return left;
}
void qksort(int A[], int start, int end)
{
	if(start >= end)
	{
		return;
	}
	int j = partition(A, start, end);
	qksort(A, start, j-1);
	qksort(A, j+1, end);

	return;
}

int main()
{
  cout<<"hello"<<endl;
  int A[] = {1, 3, 10, 9, 8, 7, 6, 4, 5,20};
  qksort(A, 0, sizeof(A)/sizeof(int)-1);
  for(int i = 0; i < 10; i++)
  {
        cout << A[i] << " ";
  }
  cout <<endl;
      
}
