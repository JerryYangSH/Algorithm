// Example program
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

void permu(vector<string> &result, string &path, string str, vector<int> &visited)
{
    if(path.size() == str.size())
    {
        result.push_back(path);
        return;
    }
    
    for(int i = 0; i < str.size(); i++){
        if(visited[i] == 1 ||
          (i > 0 && visited[i-1] == 0 && str.at(i)==str.at(i-1) )) {
              continue;
        }
        visited[i] = 1;
        path.push_back(str.at(i));
        permu(result, path, str, visited);
        path.pop_back();
        visited[i] = 0;
    }
}
int main()
{
  std::string name = "331";
  vector<string> result;
  string path;
  vector<int> visited(name.length(), 0);

  sort(name.begin(), name.end());
  permu(result, path, name, visited);
  
  for(int i = 0; i < result.size(); i++){
    cout <<result[i]<<endl;
  }
  return 0;
}
