#include <iostream>
using namespace std;

bool isLeapYear(int year){
	if(year%100 == 0){
		if(year%400 == 0){
			return true;
		}
	}
	else{
		if(year%4 == 0){
			return true;
		}
	}
	return false;
}

// Input :
//        year - xxxx (>= 1970)
//        month - [1-12]
//        day   - [1-31]
//        hour:min:second
// return seconds since 1970Jan1 00:00:00
long long epochTime(int year, int month, int day, int hour, int minute, int second){
	int daysOfMonth[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if(isLeapYear(year)){
		daysOfMonth[2] = 29;
	}
	
	// Validate date input
	if(year < 1970 || 
	   month <= 0 || month > 12 || 
	   day <= 0 || day > daysOfMonth[month] ||
	   hour < 0 || hour >= 24 ||
	   minute < 0 || minute >= 60 ||
	   second < 0 || second >= 60){
		return -1;
	}
	
	long long numOfDays = 0;
	// days of last years
	for(int i = 1970; i < year; i++){
		numOfDays += isLeapYear(i) ? 366 : 365;
	}
	// days since this year
	for(int i = 1; i < month; i++){
		numOfDays += daysOfMonth[i];
	}
	numOfDays += day-1;

	long long numOfSeconds = (24 * 60 * 60) * numOfDays + (60 * 60) * hour + 60 * minute + second;
	return numOfSeconds;
}

// Test program
int main(void){
	//              year, month, day, hour, minute, second	
	cout<<epochTime(1970,    2,   28,    1,    0,    0)<<endl;
	cout<<epochTime(1972,    3,    1,    0,    0,    0)<<endl;
	cout<<epochTime(2015,   12,   25,    23,   59,   59)<<endl;
	cout<<epochTime(2016,    1,   1,    0,    0,   0)<<endl;
	cout<<epochTime(2016,    3,   1,    0,    0,   0)<<endl;
	return 0;
}
