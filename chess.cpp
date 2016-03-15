#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

#define ROW 5 
#define COL 5

bool traverse(vector<vector<int> > &result, vector<vector<int> > &board, int x, int y, int count)
{
	
	board[x][y] = count;
	if(count >= ROW * COL)
	{
	    result = board;
            return true;
	}
	
	int dy[8] = {2,  2, 1, -1, -2, -2, -1, 1}; //
	int dx[8] = {-1, 1, 2, 2, 1,  -1, -2, -2}; //
	for(int i = 0; i < 8; i++)
	{
		int nx = x + dx[i];
		int ny = y + dy[i];
		if(nx <0 || nx >= COL || ny < 0 || ny >= ROW)
		{
			continue;
		}
		
		if(board[nx][ny] != 0) // already traversed
		{
			continue;
		}
		
		//go next
		traverse(result, board, nx, ny, count+1);
	}
	cout<<"Test:["<<count<<"]" << x << " "<<y<<endl;
	board[x][y] = 0;
	return true;
}
void printBoard(vector<vector<int> > &board)
{
	for(int i = 0; i < board.size(); i++)
	{
		for(int j = 0; j < board[i].size(); j++)
		{
			cout<<setw(4)<<board[i][j]<< " ";
		}
		cout<<endl;
	}
}
int main(void)
{
	vector<vector<int> > board(ROW, vector<int>(COL, 0));
	vector<vector<int> > result(ROW, vector<int>(COL, 0));
	int start_x = 0;
	int start_y = 0;
	cout<<"Please input start point:"<<endl;  
	cin>>start_x>>start_y; 
	cout<<"start from ["<<start_x<<","<<start_y<<"]"<<endl;
	bool ok = traverse(result, board, start_x, start_y, 1);
	if(ok)
	{
	    printBoard(result);
	}
	else
	{
	   cout<<"Unable to traverse all cells"<<endl;
	}
	return 0;	
}
