#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

bool mycompare(string& a, string& b){
    return a.length() > b.length();
}
class Solution {
public:
    int maxProduct(vector<string>& words) {
        int n = words.size();
        if(n == 0){
            return 0;
        }
        unordered_map<string, int> map;
        for(string word : words){
            int bitmap = 0;
            for(int i = 0; i < word.length(); i++){
                char c = word.at(i) - 'a';
                bitmap |= 1 << c;
            }
            map[word] = bitmap;
        }
        
        sort(words.begin(), words.end(), mycompare);
        int globalMax = -1;
        for(int i = 0; i < n; i++){
	    cout << globalMax <<" : ["<<i<<","<<"] words[i].length="<<words[i].length()<<endl;
            if((int)(words[i].length() * words[i].length()) <= globalMax){
                break;
            }
            for(int j = i+1; j < n; j++){
                int bitmap1 = map[words[i]];
                int bitmap2 = map[words[j]];
                
                if((bitmap1 & bitmap2) == 0){
                    globalMax = max(globalMax,
                                    (int)(words[i].length() * words[j].length()));
                }
            }
        }
                
        return globalMax == -1 ? 0 : globalMax;
        
    }
};

int main(void){
    Solution sol;
    vector<string> words = {"abcw","baz","foo","bar","xtfn","abcdef"};
    int n = sol.maxProduct(words);
	cout<<n<<endl;

	return 0;
}
