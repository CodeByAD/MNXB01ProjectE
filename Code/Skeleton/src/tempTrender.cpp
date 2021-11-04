#include <iostream>
#include "tempTrender.h"

using namespace std;

// ROOT library objects
#include <TF1.h> // 1d function class
#include <TH1.h> // 1d histogram classes
#include <TStyle.h>  // style object
#include <TMath.h>   // math functions
#include <TCanvas.h> // canvas object
#include <fstream> // input/output file stream class

tempTrender::tempTrender(const std::string& filePath) {
	std::cout << "The user supplied " << filePath <<" as the path to the data file.\n";
	std::cout << "You should probably store this information in a member variable of the class! Good luck with the project! :)\n";
}

void tempTrender::tempOnDay(int monthToCalculate, int dayToCalculate) const { //Make a histogram of the temperature on this day

	// open input file
	ifstream file ("Cleaneddata_3.1");

	// create a histogram 
 	TH1D* dayhist = new TH1D("dayhist", "Average temperature of 1 day; Temperature [celsius]; counts", 60, -20, 40);

	//variable declaration 
	int tot_lines = 50300; //defines size of arrays
	int line = -1; //counts lines while reading data
	int year;  // stores year when reading
	int month; // stores month when reading
	int months[tot_lines]; //collects month values
	int day; // stores day while reading
	int days[tot_lines]; //collects day values
	double temp; // stores temperature while reading
	double temps[tot_lines]; //collects temperature values

	//reading in data file
	while(file >> year >> month >> day >> temp){
		line++;	
		months[line] = month; //storing month, day and temperature values in seperate arrays
		days[line] = day;
		temps[line] = temp;
 		}
	tot_lines = line; // update total amount of lines to actual values

	//filling histogram
	for (Int_t i = 0; i < tot_lines; i++){

		if	(monthToCalculate == months[i]){  //checking for correct month
			if (dayToCalculate == days[i]){  //checking for correct day
				dayhist->Fill(temps[i]); //Filling histogram
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
  	TCanvas* c1 = new TCanvas("c1", "The temperature of a given day (month,day)", 900, 600);
  	dayhist->Draw();

} 

void tempTrender::tempOnDay(int dateToCalculate) const {  //Make a histogram of the temperature on this date

	//find date
	int DaysPerMonth[12] = {31,28,31,30,31,30,31,31,30,31,30,31}; //array with number of days per month
	int count = 0;  // variable for some of daynumbers for several months
	int in_month = 0; //variables to store date corresponding to requested day
	int in_day = 0;

	for (Int_t k = -1; k < 12; k++){ //loop to find date of day to calculate

		if (dateToCalculate > count){ 
			count = count + DaysPerMonth[k];
		}
			else {
				in_month = k; //storing value for month of requested day
				in_day = dateToCalculate - count + DaysPerMonth[k-1]; //storing value for day of requested day
				//cout << in_month << " , " << in_day << endl; 
				break;
			}
	}

	// open input file
	ifstream file ("Cleaneddata_3.1");

	// create a histogram 
 	TH1D* dayhist2 = new TH1D("dayhist2", "Average temperature of 1 day; Temperature [celsius]; counts", 60, -20, 40);

	int tot_lines = 50300; //defines size of arrays
	int line = -1; //counts lines while reading data
	int year;  // stores year when reading
	int month; // stores month when reading
	int months[tot_lines]; //collects month values
	int day; // stores day while reading
	int days[tot_lines]; //collects day values
	double temp; // stores temperature while reading
	double temps[tot_lines]; //collects temperature values


	//reading in data file
	while(file >> year >> month >> day >> temp){ 
		line++;	
		months[line] = month; //storing month, day and temperature values in seperate arrays
		days[line] = day;
		temps[line] = temp;
 		}
	tot_lines = line; // update total amount of lines to actual values

	//filling histogram
	for (Int_t i = 0; i < tot_lines; i++){

		if	(in_month == months[i]){  //checking for right month
			if (in_day == days[i]){   // checking for right day
				dayhist2->Fill(temps[i]);  //filling histogram
			}
		}
	
	}

	//Mean value and standart deviation
	double mean2 = dayhist2->GetMean();	
	double stdev2 = dayhist2->GetRMS();
	cout << "The mean temperature is " << mean2 << " and the standart deviation is " << stdev2 << "." << endl;

	//filling color for dayhist
	dayhist2->SetFillColor(kRed +1);

  	// create canvas for dayhist
  	TCanvas* c2 = new TCanvas("c2", "Average temperature of 1 day (1-355); Temperature [celsius]", 900, 600);
  	dayhist2->Draw();

} 

// void tempTrender::tempPerDay() const {} //Make a histogram of the average temperature of each day of the year
// void tempTrender::hotCold() const {} //Make a histogram of the hottest and coldest day of the year
// void tempTrender::tempPerYear(int yearToExtrapolate) const {} //Make a histogram of average temperature per year, then fit and extrapolate to the given year

