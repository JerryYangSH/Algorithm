#include <iostream>
using namespace std;

class base {
public:
	virtual void f(void){
		cout <<"f in base"<<endl;
	}
	void g(void){
		cout <<"g in base"<<endl;
	}
	~base(){
		cout<<"destructor in base"<<endl;
	}
};

class derive:base{
public:
	void f(void){
		cout <<"f in derive"<<endl;
	}
	void g(void){
		cout <<"g in derive"<<endl;
	}
	~derive(){
		cout <<"destructor in derive"<<endl;
	}
};

void myprint (base * obj){
	obj->f();
	obj->g();
}
int main(void){
	base * b = new base;
	derive * d = new derive;
	base * b2 = (base *) d;
	myprint(b2);
	myprint((base*)d);
	delete b;
	delete d;
	return 0;
}
