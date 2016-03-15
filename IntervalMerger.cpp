#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Interval {
public:
	int start;
	int len;
	Interval(int _start, int _len){
		this->start = _start;
		this->len = _len;
	}
public:
	bool operator <(const Interval &b) const{
		return this->start < b.start;
	}
};
class Merger {
public:
	vector<Interval> merge(vector<Interval> &requests){
		int n = requests.size();
		vector<Interval> result;
		if(n == 0){
			return result;
		}
		if(n == 1){
			result.push_back(requests[0]);
			return result;
		}
		// sort
		sort(requests.begin(), requests.end());
		
		int start = requests[0].start;
		int len = requests[0].len;
		for(int i = 1; i < requests.size(); i++){
			Interval now = requests[i];
			if((start + len) == now.start){
				len = len + now.len;
			}
			else{
				result.push_back(Interval(start, len));
				start = now.start;
				len = now.len;
			}
		}
		result.push_back(Interval(start, len));
		return result;
	}
};

int main(void){
	Merger mg;
	vector<Interval> reqs, result;
	reqs.push_back(Interval(0, 1024));
	reqs.push_back(Interval(1024, 512));
	reqs.push_back(Interval(2048, 1024));
	reqs.push_back(Interval(4096, 512));
	reqs.push_back(Interval(512, 1024));
	reqs.push_back(Interval(768, 512));
	
	result = mg.merge(reqs);
	for(Interval req : result){
		cout<<req.start<<" : + "<<req.len<<endl;
	}
	return 0;
}
