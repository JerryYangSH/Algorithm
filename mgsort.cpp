#include <iostream>
#include <string.h>
using namespace std;
void merge(int number[], int start, int middle, int end)
{
  if(start == end)
  {
    return;
  }
  
  int len = end - start + 1;
  int * newNum = new int [len];
  int i = 0;
  int left = start, right = middle + 1;
  while(left <= middle && right <= end)
  {
    if(number[left] < number[right])
    {
      newNum[i++] = number[left++];
    }
    else
    {
      newNum[i++] = number[right++];
    }
  }
  if(left <= middle)
  {
    memcpy(&newNum[i], &number[left], (middle - left + 1)* sizeof(int));
  }
  else if(right <= end)
  {
    memcpy(&newNum[i], &number[right], (end - right + 1) * sizeof(int));
  }
  memcpy(number+start, newNum, len * sizeof(int));
 
  delete [] newNum;
  return;
}
void mgsort(int number[], int start, int end)
{
  if(start >= end)
  {
    return;
  }
  int middle = start + (end - start)/2;
  if(start <= middle)
  {
    mgsort(number, start, middle);
  }
  if(middle < end)
  {
    mgsort(number, middle+1, end);
  }
  
  merge(number, start, middle, end);
  return;
}
int main(void)
{
  int array[10] = {1,8, 5, 3, 8,2,7,4,6, 10};
  mgsort(array, 0, 9);
  
  for(int i = 0; i < 10; i++)
  {
    cout << array[i] << " ";
  }
  
}