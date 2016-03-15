// Example program
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

int lengthOfLongestSubstringKDistinct(string s, int k) {
        // write your code here
		if(k <= 0 || s.length() == 0 || k > s.length()){
			return 0;
		}
		int slow = 0;
		int maxLen = 0;

		// Key: letter; value: the number of occurrences.
		unordered_map<char, int> map;
		int fast;
		for (fast = 0; fast < s.length(); ++fast) {
			char c = s.at(fast);
			if (map.find(c) != map.end()) {
				map[c] += 1;
			} else {
				map[c] = 1;
				while (map.size() > k) {
					char slowChar = s.at(slow++);
					int count = map[slowChar];
					if (count > 1) {
						map[slowChar] = count - 1;
					} else {
						map.erase(slowChar);
					}
				}
			}

			maxLen = max(maxLen, fast - slow + 1);
		}

		return maxLen;
    }
    
int main()
{
  std::string name = "nfhiexxjrtvpfhkrxcutexxcodfioburrtjefrgwrnqtyzelvtpvwdvvpsbudwtiryqzzy";
  std::cout << name.length()<<std::endl;
  std::cout<< lengthOfLongestSubstringKDistinct(name, 25)<<std::endl;
  return 0;
}

