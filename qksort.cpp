#include <iostream>
using namespace std;
void swap(int * a, int * b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}
int partition(int number[], int start, int end)
{
  if(start == end)
  {
    return start;
  }
  
  int pivotIndex = start + (end - start) / 2;
  int pivot = number[pivotIndex];
  
  int oldEnd = end;
  swap(&number[pivotIndex], &number[end]);
  
  while(start <= end)
  {
    if(start <= end && number[start] < pivot)
    {
      start++;
    }
    while(start <= end && pivot <= number[end])
    {
      end--;
    }
    if(start < end)
    {
      swap(&number[start], &number[end]);
    }
    
  }
  swap(&number[start], &number[oldEnd]);
  
  return start;
}
void  qksort(int number[], int start, int end)
{
  int index = partition(number, start, end);
  if(index > start)
  {
    qksort(number, start, index - 1);
  }
  if(index < end)
  {
    qksort(number, index + 1, end);
  }
  return;
}
int main(void)
{
  int array[10] = {1,8, 5, 3, 8,2,7,4,6, 10};
  qksort(array, 0, 9);
  for(int i = 0; i < 10; i++)
  {
    cout << array[i] << " ";
  }
  
}