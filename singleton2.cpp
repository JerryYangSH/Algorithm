#include <iostream>
#include <pthread.h>
using namespace std;

class singleton{
public:
  static singleton * getInstance();
private:
  singleton();
  singleton(const singleton&);
  singleton& operator=(const singleton&);
  static singleton * instance;
  static pthread_mutex_t mutex;
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
singleton * singleton::instance = NULL;
pthread_mutex_t singleton::mutex;
singleton * singleton::getInstance()
{
  if(instance == NULL)
  {
	pthread_mutex_lock(&mutex);
	if(instance == NULL)
	{
		instance = new singleton();
	}
	pthread_mutex_unlock(&mutex);
  }
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

