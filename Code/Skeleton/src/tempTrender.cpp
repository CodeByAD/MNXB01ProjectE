#include <iostream>
#include "tempTrender.h"

tempTrender::tempTrender(const std::string& filePath) {
	std::cout << "The user supplied " << filePath <<" as the path to the data file.\n";
	std::cout << "You should probably store this information in a member variable of the class! Good luck with the project! :)\n";
}

void tempTrender::tempOnDay(int monthToCalculate, int dayToCalculate) const { //Make a histogram of the temperature on this day

	// open input file
	ifstream file ("Cleaneddata");

	// create a histogram 
 	TH1D* dayhist = new TH1D("dayhist", "Average temperature of 1 day; Temperature [celsius]; counts", 60, -20, 40);

	//variable declaration 
	int tot_lines = 50300;
	int line = -1;
	int year;
	int years[tot_lines];
	int month;
	int months[tot_lines];
	int day;
	int days[tot_lines];
	double temp;
	double temps[tot_lines];

	//reading in data file
	while(file >> year >> month >> day >> temp){
		line++;	
		//years[line] = year ;
		months[line] = month;
		days[line] = day;
		temps[line] = temp;
 		}
	tot_lines = line;

	//filling histogram
	for (Int_t i = 0; i < tot_lines; i++){

		if	(monthToCalculate == months[i]){
			if (dayToCalculate == days[i]){
				dayhist->Fill(temps[i]);
			}
		}
	
	}

	//Mean value and standart deviation
	double mean = dayhist->GetMean();	
	double stdev = dayhist->GetRMS();
	cout << "The mean temperature is " << mean << " and the standart deviation is " << stdev << "." << endl;

	//filling color for dayhist
	dayhist->SetFillColor(kRed +1);

  	// create canvas for dayhist
  	TCanvas* c1 = new TCanvas("c1", "day canvas", 900, 600);
  	dayhist->Draw();

} 

void tempTrender::tempOnDay(int dateToCalculate) const {  //Make a histogram of the temperature on this date

	//find date
	Int_t DaysPerMonth[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
	Int_t count = 0;
	Int_t in_month = 0;
	Int_t in_day = 0;

	for (Int_t k = -1; k < 12; k++){

		if (dateToCalculate > count){
			count = count + DaysPerMonth[k];
			cout << count << endl;
		}
			else {
				in_month = k;
				in_day = dateToCalculate - count + DaysPerMonth[k-1];
				cout << in_month << " , " << in_day << endl; 
				break;
			}
	}

	// open input file
	ifstream file ("Cleaneddata");

	// create a histogram 
 	TH1D* dayhist2 = new TH1D("dayhist2", "Average temperature of 1 day; Temperature [celsius]; counts", 60, -20, 40);

	//variable declaration 
	int tot_lines = 50300;
	int line = -1;
	int year;
	int years[tot_lines];
	int month;
	int months[tot_lines];
	int day;
	int days[tot_lines];
	double temp;
	double temps[tot_lines];

	//reading in data file
	while(file >> year >> month >> day >> temp){
		line++;	
		//years[line] = year ;
		months[line] = month;
		days[line] = day;
		temps[line] = temp;
 		}
	tot_lines = line;

	//filling histogram
	for (Int_t i = 0; i < tot_lines; i++){

		if	(in_month == months[i]){
			if (in_day == days[i]){
				dayhist2->Fill(temps[i]);
			}
		}
	
	}

	//Mean value and standart deviation
	double mean = dayhist2->GetMean();	
	double stdev = dayhist2->GetRMS();
	cout << "The mean temperature is " << mean << " and the standart deviation is " << stdev << "." << endl;

	//filling color for dayhist
	dayhist2->SetFillColor(kRed +1);

  	// create canvas for dayhist
  	TCanvas* c1 = new TCanvas("c1", "day canvas", 900, 600);
  	dayhist2->Draw();

} 

// void tempTrender::tempPerDay() const {} //Make a histogram of the average temperature of each day of the year
// void tempTrender::hotCold() const {} //Make a histogram of the hottest and coldest day of the year
// void tempTrender::tempPerYear(int yearToExtrapolate) const {} //Make a histogram of average temperature per year, then fit and extrapolate to the given year
