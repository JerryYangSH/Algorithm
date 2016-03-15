// Example program
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

void helper(vector<string> &result, string &path, string &src, vector<int> &visited){
        if(path.length() == src.length()){
            result.push_back(path);
            return;
        }
        for(int i = 0; i < src.length(); i++){
            if(visited[i] != 0) continue;
            if(i > 0 && visited[i-1] == 0 && src.at(i) == src.at(i-1)) continue;
            
            path.push_back(src.at(i));
            visited[i] = 1;
            helper(result, path, src, visited);
            visited[i] = 0;
            path.pop_back();
        }
    }
    /**
     * @param str a string
     * @return all permutations
     */
    vector<string> stringPermutation2(string& str) {
        // Write your code here
        sort(str.begin(), str.end());
        vector<string> result;
        string path;
        vector<int> visited(str.length(), 0);
        helper(result, path, str, visited);
        return result;
    }
    
int main()
{
  std::string name = "abb";
  vector<string> result = stringPermutation2(name);
  for(string str : result){
    cout << str<<endl;
  }
  cout << "END"<<endl;
  return 0;
}

