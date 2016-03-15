/*
判断整数序列是不是二元查找树的后序遍历结果
题目：输入一个整数数组，判断该数组是不是某二元查找树的后序遍历的结果。
如果是返回true，否则返回false。
例如输入5、7、6、9、11、10、8，由于这一整数序列是如下树的后序遍历结果：
8
/ \
6 10
/ \ / \
5 7 9 11
因此返回true。
如果输入7、4、6、5，没有哪棵树的后序遍历的结果是这个序列，因此返回false。
*/
bool isValidPost(int array[], int len)
{
	int rootVal = array[len-1];

	int i, j;
	for(i = 0; i < len-1; i++)
	{
		if(array[i] > rootVal)
		{
			break;
		}
	}
	for(j = i; j < len-1; j++)
	{
		if(array[j] < rootVal)
		{
			return false;
		}
	}
	
	bool leftValid = true;
	bool rightValid = true;
	if(i > 0)
		leftValid = isValidPost(array, i);
	if(i < len-1)
		leftValid = isValidPost(array+i, len-1-i);
	
	return leftValid&&rightValid;
}