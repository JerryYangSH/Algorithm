#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;
const int MAX_ROW=3;
const int MAX_COL=3;
const int dx[8] = {-1, -1, -1, 0, 1, 1,  1,  0};
const int dy[8] = {-1,  0,  1, 1, 1, 0, -1, -1};
void helper(vector<string> &result, string &path, vector<bool> &used, int pos){
       path.push_back( (char)(pos)+'0');
       used[pos] = true;
       
	if(path.length() > 0){
	  result.push_back(path);
       }
       int x = (pos/MAX_COL)%MAX_ROW;
       int y = pos%MAX_COL;
       for(int k = 0; k < 8; k++){
            int nx = x + dx[k];
            int ny = y + dy[k];
            int npos = nx * MAX_COL + ny;
            if(nx < 0 || nx >= MAX_ROW || ny < 0 || ny >= MAX_COL || used[npos]) continue;
	    helper(result, path, used, npos);
        
       }
       used[pos] = false;
       path.pop_back();
}
int main()
{
    vector<string> result;
    string path="";
    for(int i = 0; i < MAX_ROW; i++){
	for(int j = 0; j < MAX_COL; j++){
		vector<bool> used(MAX_ROW*MAX_COL, false);
    		helper(result, path, used, i*MAX_COL + j);
	}
    }
    for(int i = 0; i < result.size(); i++){
        cout <<result[i]<<endl;
    }
  
  return 0;
  
}
