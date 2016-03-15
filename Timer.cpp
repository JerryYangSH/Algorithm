#include <iostream>
#include <vector>
#include <list>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>
using namespace std;

class Request{
public:
                int id;
                int timeout;
                int interval;
                void (*callback)(void* arg);

                Request():timeout(0), callback(NULL){};
                Request(int t, int intvl, void(*fn) (void* arg)):timeout(t), interval(intvl), callback(fn)
                {};
};
enum STATUS{
        INIT = 0,
        RUNNING = 1,
        STOPPED = 2,
};
class TimerProcess{
private:
        int status;
        list<Request> timerList;
        pthread_mutex_t     mutex = PTHREAD_MUTEX_INITIALIZER;
        bool exitFlag;
        const int DEFAULT_TIME = 1;

        time_t getNowTime(){ // get current time in seconds
                struct timeval tv;
                gettimeofday(&tv, NULL);
                return tv.tv_sec;
        }
        int insert(Request& req){
//                pthread_mutex_lock(&mutex);
                if(timerList.empty()){
                        timerList.push_back(req);
                }
                else{
                        long now = getNowTime();
                        for(auto it = timerList.begin();
                                 it != timerList.end();
                                 it++){
                                 if((*it).timeout > now){
                                       timerList.insert(it, req);
                                        break;
                                }
                        }
                }
  //              pthread_mutex_unlock(&mutex);
        }
public:
            TimerProcess(){
                status = INIT;
                exitFlag = false;
        }
        void start(void){
                cout<<"START timer thread"<<endl;
                status = RUNNING;
                while(!exitFlag){
                        int sleepTime = DEFAULT_TIME;
                        int now = getNowTime();
                        pthread_mutex_lock(&mutex);
                        for(auto it = timerList.begin();
                                 it != timerList.end();
                                 it++){
                                time_t timeout = (*it).timeout;
                                if(timeout > now){
                                        sleepTime = timeout - now;
                                        break;
                                }
                                int interval = (*it).interval;
                                void (*fn)(void*) = (*it).callback;
                                if(fn != NULL)  fn((void *)interval);
                                //timerList.erase(it);
                                //Request newReq(now+interval, interval, fn);
                                //insert(newReq);
                        }
                        pthread_mutex_unlock(&mutex);
                        cout<<"Sleeping "<<sleepTime<<" s..."<<endl;
                        sleep(sleepTime);
                }
                status = STOPPED;
                cout<<"EXIT timer thread"<<endl;
        }

        void stop(void){
                exitFlag = true;
                cout<<"STOPPING timer"<<endl;
        }
        int addTimer(int interval, void (*fn)(void * arg)){
                long now = getNowTime();
                int timeout = now + interval;
                Request req(timeout, interval, fn);
                insert(req);
        }
        int cancelTimer(int id){
        }

};

//
void test_callback(void *arg){
        cout<<"Call back is called "<<(int)arg<<endl;
}

void test_callback2(void *arg){
        cout<<"Call back is called "<<(int)arg<<endl;
}
int main(void){
        TimerProcess t;

        void (*fn)(void*) = test_callback;
        t.addTimer(1, fn);
        t.addTimer(3, test_callback2);
        t.start();
        return 0;
}

