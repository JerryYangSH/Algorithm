#include <iostream>
#include <vector>
#include <string>
#include <math.h>

using namespace std;
template <class T,class Integer>
T powerT(T x,Integer n)
{
    if(n == 0) return 1;
    if(n == 1) return x;
    while((n&1) == 0)
    {
        x = x*x;
        n >>= 1;
    }
    T result = x;
    n >>= 1;
    while(n != 0)
    {
        x = x*x;
        if((n&1) != 0)
            result *= x;
        n >>= 1;
    }
    return result;
}
float sqrt(float c, int p){
        double EPS = 0.1;
        while(--p > 0){
                EPS /= 10;
        }

        double x = c/2;
        double t = c;
        do {
                t = (x + c/x)/2.0;
        }while(fabs(t-x) > EPS);

        return t;
}

long long powern(long c, int p){
        if(c == 0){
                return 0;
        }

        if(p == 0){
                return 1;
        }
        else if(p < 0){
                c = 1/c;
        }
        long long product = powern(c, p/2);
        product = product * product;
        if(p%2 != 0){
                product = product * c;
        }
        return product;
}
double powerd(double base, int e){
                if(e == 0){
                        return 1.0;
                }
                else if(e < 0){
                        base = 1.0 / base;
                        e = -e;
                }
        double product = powerd(base, e/2);
        product = product * product;
        if(e%2 != 0){
                product = product * base;
        }
        return product;
}
///////////////////////////////////////////////////////
class BigNumber{
public:
	vector<int> integer;     // Integer part
	vector<int> decimal;//  decimal part
	bool negative;
	
	// Integer
	BigNumber(string str){
		if(str.length() == 0){
			negative = false;
			return;
		}
		
		// Check heading '+' or '-'
		negative = false;
		int i = 0;
		if(str.at(i) == '-'){
			negative = true;
			i++;
		}
		else if(str.at(i) == '+'){
			negative = false;
			i++;
		}
		// Integer part, LSB first
		while(i < str.length() &&
		      str.at(i) >= '0' && 
			  str.at(i) <= '9'){
			integer.insert(integer.begin(), str.at(i)-'0');
			i++;
		}
		
		// Deal with decimal if there is
		if(i < str.length() && str.at(i) == '.'){
			//now we got decimal part
			i++; // skip the dot
			while(i < str.length() &&
				str.at(i) >= '0' && str.at(i) <= '9'){
				decimal.insert(decimal.begin(), str.at(i)-'0');
				i++;
			}
		}
	}

	// Constructor for integer only
	BigNumber(bool neg, vector<int> &array){
		negative = neg;
		integer = array; 
	}
	BigNumber(){
		negative = false;
	}
	int size(void){
		return this->integer.size();
	}
	bool isNegative(){
		return this->negative;
	}
	
	BigNumber add(BigNumber &obj){
		bool flagA = this->isNegative();
		bool flagB = obj.isNegative();
		bool flagC = false; // result negative flag
		vector<int> C; // result
		add_helper(flagA, this->integer,
				   flagB, obj.integer,
				   flagC, C);

		return BigNumber(flagC, C);
	}

	BigNumber sub(BigNumber &obj){
		bool flagA = this->isNegative();
		bool flagB = obj.isNegative();
		bool flagC = false; // result negative flag
		vector<int> C; // result
		sub_helper(flagA, this->integer,
				   flagB, obj.integer,
				   flagC, C);

		return BigNumber(flagC, C);
	}

	BigNumber mul(BigNumber &obj){
		bool flagA = this->isNegative();
		bool flagB = obj.isNegative();
		bool flagC = (flagA != flagB); // result negative flag
		vector<int> &A = this->integer;
		vector<int> &B = obj.integer;
		vector<int> C(A.size()+B.size(), 0); // result
		for(int i = 0; i < A.size(); i++){
			int carry = 0;
			for(int j = 0; j < B.size(); j++){
				int newValue = A[i] * B[j] + carry;
				carry = newValue/10;
				newValue = newValue%10;
				C[i+j] += newValue;
				C[i+j+1] += C[i+j]/10;
				C[i+j] = C[i+j]%10;
			}
			if(carry != 0){
				C[i+B.size()] += carry;
				if(C[i+B.size()] >= 10){
					C[i+B.size() + 1]  += C[i+B.size()] / 10;
					C[i+B.size()] = C[i+B.size()]%10;
				}
			}
		}
		
		// Remove the heading zeros
		int last = C.size() - 1;
		while(C[last] == 0 && last > 0){
			C.pop_back();
			last--;
		}

		return BigNumber(flagC, C);
	}
	
	// 高精度幂, base^n,  n 可能很大
	BigNumber power(int n){
		BigNumber &base = *this;
		if(n == 0){
			return BigNumber("1");
		}
		if(n == 1){
			return base;
		}
		BigNumber result = power(n>>1);
		result = result.mul(result);
		if(n%2 != 0){
			result = result.mul(base);
		}
		return result;		
	}
	
	// 高精度浮点数乘法
	BigNumber fmul(BigNumber &obj){
		if(this->decimal.size() == 0 && 
		   obj.decimal.size() == 0){
			// corner case
			return mul(obj);;
		}
		int len = this->decimal.size() + obj.decimal.size();
		BigNumber A = *this;
		BigNumber B = obj;
		A.integer.insert(A.integer.begin(), this->decimal.begin(), this->decimal.end());
		B.integer.insert(B.integer.begin(), obj.decimal.begin(), obj.decimal.end());
		BigNumber C = A.mul(B);
		
		C.decimal.assign(C.integer.begin(), C.integer.begin() + len);
		C.integer.assign(C.integer.begin() + len, C.integer.end());
		return C;	
	}
	//////////////// Below is Utility ////////////////////////////////
	void add_helper(bool flagA, vector<int> A, 
					bool flagB, vector<int> B,
					bool &flagC, vector<int> &C){
		if(flagA == flagB){
			int len = max(A.size(), B.size());
			int carry = 0;
			for(int i = 0; i < len; i++){
				int value1 = (i >= A.size()) ? 0 :A[i];
				int value2 = (i >= B.size()) ? 0 :B[i];
				int newValue = value1 + value2 + carry;
				carry = newValue/10;
				newValue = newValue%10;
				C.push_back(newValue);
			}
			if(carry != 0){
				C.push_back(carry);
			}
			flagC = flagA;
		}
		else{
			if(flagA){
				sub_helper(flagB, B, 
						   !flagA, A, 
						   flagC, C);
			}
			else{
				sub_helper(flagA, A, 
						   !flagB, B, 
						   flagC, C);
			}
		}
	}
	
	void sub_helper(bool flagA, vector<int> A, 
					bool flagB, vector<int> B,
					bool &flagC, vector<int> &C){
		if(compareBigNum(A, B) == 0){
			// equal
			C.push_back(0);
			flagC = false;
			return;
		}
		
		if(flagA == flagB){
			flagC = flagA;
			if(compareBigNum(A, B) < 0){
				flagC = !flagC;// toggle this flag
				// swap A and B, make sure A is bigger than B
				auto tmp = A;
				A = B;
				B = tmp;
			}
			int len = max(A.size(), B.size());
			int borrowIn = 0;
			int borrowOut = 0;
			for(int i = 0; i < len; i++){
				int value1 = (i >= A.size()) ? 0 :A[i];
				int value2 = (i >= B.size()) ? 0 :B[i];
				if((value1-borrowOut) < value2) {
					borrowIn = 10;
				}
				else {
					borrowIn = 0;
				}
				int newValue = value1 + borrowIn - borrowOut - value2;
				borrowOut = (borrowIn == 10) ? 1 : 0;
				C.push_back(newValue);				
			}
		}
		else{
			add_helper(false, A, 
     				   false, B, 
					   flagC, C);
			flagC = flagA;
		}
	}
	
	// 比较大数， 返回 1， 0， -1
	int compareBigNum(vector<int> &A, vector<int> &B){
		if(A.size() > B.size()){
			return 1;
		}
		else if(B.size() > A.size()){
			return -1;
		}
		// 从最高位到最低位开始比较
		for(int i = A.size()-1; i >= 0; i--){
			if(A[i] > B[i]){
				return 1;
			}
			else if(A[i] < B[i]){
				return -1;
			}
		}
		return 0;
	}
	void print(void){
		if(isNegative()){
			cout<<"-";
		}
		// 整数部分
		if(integer.size() > 0){
			for(int i = integer.size()-1; i >= 0; i--){
				cout<<integer[i];
			}
		}
		
		//小数部分
		if(decimal.size() > 0){
			cout<<".";
			for(int i = decimal.size()-1; i >= 0; i--){
				cout<<decimal[i];
			}
		}
	}
	
};
int main()
{
    /*
  cout <<"sqrt test"<<endl;
  cout << sqrt(1)<<endl;
  cout << sqrt(2)<<endl;
  cout << sqrt(5)<<endl;
  cout << sqrt(100)<<endl;
  cout << sqrt(99999)<<endl;

  cout <<"powern (long) test"<<endl;
  cout <<"10^0 = "<< powern(10, 0)<<endl;
  cout <<"10^1 = "<< powern(10, 1)<<endl;
  cout <<"10^4 = "<< powern(10, 4)<<endl;
  cout <<"10^7 = "<< powern(10, 7)<<endl;
  cout <<"10^-2 = "<< powern(10, -2)<<endl;

  cout <<"powerd (double) test"<<endl;
  cout.precision(5);
  cout <<"2.5^0 = "<<std::fixed<< powerd(2.5, 0)<<endl;
  cout <<"2.5^1 = "<<std::fixed<< powerd(2.5, 1)<<endl;
  cout <<"2.5^-1 = "<<std::fixed<< powerd(2.5, -1)<<endl;
  cout <<"2.5^5 = "<<std::fixed<< powerd(2.5, 5)<<endl;
  cout <<"2.5^-5 = "<<std::fixed<< powerd(2.5, -5)<<endl;
  */
  ///////////////////////
  BigNumber C;
  vector<vector<string> > ints1 = { 
									{"0", "0"},
									{"11","89"},
									{"10", "1000"},
									{"10", "-999"},
									{"123", "456"},
									{"+123", "-456"},
									{"-123", "456"},
									{"-123", "-456"},
									{"999", "8888888888"},
									{"999", "-8888888888"},
									{"-999", "8888888888"},
									{"-999", "-8888888888"},
									{"98765432109876543210", "9876543210"},
									{"+98765432109876543210", "-9876543210"},
									{"-98765432109876543210", "9876543210"},
									{"-98765432109876543210", "-9876543210"}
	};

  for(int k = 0; k < ints1.size(); k++){
	BigNumber A(ints1[k][0]);
    BigNumber B(ints1[k][1]);
	
	C = A.add(B);
	cout<<ints1[k][0]<<" + "<<ints1[k][1]<<" = "; C.print(); cout<<endl;
	
    C = A.sub(B);
	cout<<ints1[k][0]<<" - "<<ints1[k][1]<<" = "; C.print(); cout<<endl;
        
	C = A.mul(B);
	cout<<ints1[k][0]<<" * "<<ints1[k][1]<<" = "; C.print(); cout<<endl;
  }		
  
  vector<vector<string> > floats2 = { {"1.1", "2.0"},
									  {"11111111.111111", "2222222.2222222"},
									  {"-9999.4567890123", "8901.987654321"}
  };
  for(int k = 0; k < floats2.size(); k++){
	BigNumber A(floats2[k][0]);
    BigNumber B(floats2[k][1]);       
	C = A.fmul(B);
	cout<<floats2[k][0]<<" * "<<floats2[k][1]<<" = "; C.print(); cout<<endl;
  }
	
	
    BigNumber base("10");
	int n = 100;
	BigNumber X = base.power(n);
	base.print(); cout<<" ^ "<<n <<" = "; X.print(); cout<<endl;
	
  return 0;
}

