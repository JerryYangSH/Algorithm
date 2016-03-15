#include <iostream>
#include <vector>
using namespace std;

void findPrimes(int n){
	vector<bool> isPrime(n, true);
	for(int i = 2; i*i < n; i++){
		for(int j = i*i; j < n; j += i){
			isPrime[j] = false;
		}
	}
	for(int i = 2; i < n; i++){
		if(isPrime[i]){
			cout<<i<<" ";
			
		}
	}
}
int main(void){
	int n = 100;
	findPrimes(n);
	return 0;
}
