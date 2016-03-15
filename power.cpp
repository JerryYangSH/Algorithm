#include <iostream>
#include <math.h>
using namespace std;

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

double powerd2(double base, int e){
	
}
int main()
{
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

  return 0;
}

