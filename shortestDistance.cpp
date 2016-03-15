#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

// http://segmentfault.com/a/1190000004187914
// [LeetCode]Shortest Distance from All Buildings

class Solution {
private:
	void bfs(vector<vector<int>>& grid, int x, int y, vector<vector<int>>& dist, vector<vector<int>>& num){
		int n = grid.size();
		int m = grid[0].size();
		vector<vector<bool> > visited(n, vector<bool>(m, false));
		queue<int> q;
		int id = x * m + y;
		q.push(id);
		visited[x][y] = true;
		int level = 0;
		int dx[4] = {-1, 1, 0, 0};
		int dy[4] = {0, 0, -1, 1};
		while(!q.empty()){
			level++;
			int size = q.size();
			while(size-- > 0){
				id = q.front();
				q.pop();
				x = id / m;
				y = id % m;
				for(int k = 0; k < 4; k++){
					int nx = x + dx[k];
					int ny = y + dy[k];
					if(nx >= 0 && nx < n && ny >= 0 && ny < m && 
						!visited[nx][ny] && grid[nx][ny] == 0){
						dist[nx][ny] += level;
						num[nx][ny]++;
						q.push(nx * m + ny);
						visited[nx][ny] = true;
					}
				}
			}
		}
	}
public:
    int shortestDistance(vector<vector<int> > grid) {
		int n = grid.size();
		if(n == 0){
			return -1;
		}
		int m = grid[0].size();
		// dist[i][j]: shortest distance from point [i,j] to all buildings
		vector<vector<int> > dist(n, vector<int>(m, 0));
		// number of build that can be achieved 
		vector<vector<int> > num(n, vector<int>(m, 0));
		int totalNum = 0; // total building number
		
		for(int i = 0; i < n; i++){
			for(int j = 0; j < m; j++){
				if(grid[i][j] == 1){
					totalNum++;
					bfs(grid, i, j, dist, num);
				}
			}
		}
		int shortest = numeric_limits<int>::max();
		for(int i = 0; i < n; i++){
			for(int j = 0; j < m; j++){
				if(grid[i][j] == 0 && dist[i][j] > 0 && num[i][j] == totalNum){
					shortest = min(shortest, dist[i][j]);
				}
			}
		}
		return shortest == numeric_limits<int>::max() ? -1 : shortest;
	}
};

int main(void){
	Solution sol;
	vector<vector<int> > grid = {{1, 0, 2, 0, 1},
				     {0, 0, 0, 0, 0},
				     {0, 0, 1, 0, 0}};
	cout << sol.shortestDistance(grid)<<endl;
	return 0;
}
