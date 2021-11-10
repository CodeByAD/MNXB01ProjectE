#ifndef TEMPTRENDER_H
#define TEMPTRENDER_H

#include <string>
class tempTrender {
	public:
	tempTrender(); //Construct using the specified file
	~tempTrender() {} //Destructor

	 void tempOnDay(int monthToCalculate, int dayToCalculate) const; //Make a histogram of the temperature on this day
	 void tempOnDay(int dateToCalculate) const; //Make a histogram of the temperature on this date
	 void extremetemps(string year);//Make a histograms for the hottest and coldest days of each year, as well 
					//as the hottest and coldest temperature for every day of one year (the argument)
	 void Avgtemp3D();
	private:
	
};
#endif
