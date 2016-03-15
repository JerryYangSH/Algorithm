/**
 * Definition of Interval:
 * classs Interval {
 *     int start, end;
 *     Interval(int start, int end) {
 *         this->start = start;
 *         this->end = end;
 *     }
 */
class myPoint {
public:
    int startTime;
    int isStart;
    myPoint(int _startTime, bool _isStart){
        this->startTime = _startTime;
        this->isStart = _isStart;
    }
    
    // writing sort compare funtion is a pain!!!!
    // const ... const is must! or else compile error
    #if 0
    bool operator ()(const myPoint &a, const myPoint &b) const{
        if(a.startTime == b.startTime){
            return a.isStart < b.isStart;
        }
        else{
            return a.startTime < b.startTime;
        }
    }
    #endif
    
    // const ... const is must! or else compile error
    bool operator <(const myPoint &obj) const{
        if(startTime == obj.startTime){
            return isStart < obj.isStart;
        }
        else{
            return startTime < obj.startTime; // 从小到大排序
        }
    }
    bool operator >(const myPoint &obj) const{
        if(startTime == obj.startTime){
            return isStart > obj.isStart;
        }
        else{
            return startTime > obj.startTime;
        }
    }
};

// 注意此处定义myPoint 与 sort对象vector<myPoint>参数类型要一致
bool mycompare(const myPoint &a, const myPoint &b){
    if(a.startTime == b.startTime){
        return a.isStart < b.isStart;
    }
    else{
        return a.startTime < b.startTime;
    }
}
class Solution {
public:
    /**
     * @param intervals: An interval array
     * @return: Count of airplanes are in the sky.
     */
    int countOfAirplanes(vector<Interval> &airplanes) {
        // write your code here
        // 注意此处定义myPoint 与 mycompare 函数参数类型要一致
        vector<myPoint> points; 
        for(Interval itv : airplanes){
            points.push_back(myPoint(itv.start, 1)); 
            points.push_back(myPoint(itv.end, 0)); 
        }
        
        sort(points.begin(), points.end());
        //sort(points.begin(), points.end(), mycompare);
        
        int count = 0;
        int maxCount = 0;
        for(int i = 0; i < points.size(); i++){
            if(points[i].isStart){
                count++;
            }
            else{
                count--;
            }
            maxCount = max(maxCount, count);
        }
        return maxCount;
    }
};
