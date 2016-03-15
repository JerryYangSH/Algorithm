#include <iostream>
using namespace std;

/* .... ..
* http://www.cnblogs.com/miloyip/archive/2010/02/25/1673114.html
*/
struct NODE
{
    NODE *pLeft;
    NODE *pRight;
};
 
struct RESULT
{
    int nMaxDistance;
    int nMaxDepth;
};
 
RESULT GetMaximumDistance(NODE* root)
{
    if (!root)
    {
        RESULT empty = { 0, -1 };   // trick: nMaxDepth is -1 and then caller will plus 1 to balance it as zero.
        return empty;
    }
 
    RESULT lhs = GetMaximumDistance(root->pLeft);
    RESULT rhs = GetMaximumDistance(root->pRight);
 
    RESULT result;
    result.nMaxDepth = max(lhs.nMaxDepth + 1, rhs.nMaxDepth + 1);
    result.nMaxDistance = max(max(lhs.nMaxDistance, rhs.nMaxDistance), lhs.nMaxDepth + rhs.nMaxDepth + 2);
    return result;
}
//////////Test code ////////
int main(void)
{
	NODE * nodeA;
	nodeA  = new  NODE [10];

	nodeA[0].pLeft = &nodeA[1];nodeA[0].pRight = &nodeA[2];
	nodeA[1].pLeft = &nodeA[3]; nodeA[1].pRight = &nodeA[4];
	nodeA[3].pLeft = &nodeA[5]; nodeA[4].pRight = &nodeA[6];
	
	RESULT ans = GetMaximumDistance(&nodeA[0]);
	cout<<"nMaxDistance : "<< ans.nMaxDistance << "" << endl;
	cout<<"nMaxDepth : "<< ans.nMaxDepth << "" << endl;
	delete [] nodeA;

	return 0;
}


