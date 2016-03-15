#include <iostream>
using namespace std;

class singleton{
public:
  static singleton * getInstance();
private:
  singleton();
  singleton(const singleton&);
  singleton& operator=(const singleton&);
  static singleton * instance;
};

singleton::singleton()
{
}
singleton::singleton(const singleton&)
{
}

singleton& singleton::operator=(const singleton&)
{
}

///////////////////////////////////////////////////
singleton * singleton::instance = new singleton();
singleton * singleton::getInstance()
{
  return instance;
}




int main() {
  singleton * pInstance1 = singleton::getInstance();
  singleton * pInstance2 = singleton::getInstance();
  if(pInstance1 == pInstance2)
  {
    cout << "Good singleton example!\n";
  }
  return 0;
}

