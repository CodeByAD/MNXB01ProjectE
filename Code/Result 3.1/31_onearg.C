#include <iostream>

using namespace std;

// ROOT library obejcts
#include <TF1.h> // 1d function class
#include <TH1.h> // 1d histogram classes
#include <TStyle.h>  // style object
#include <TMath.h>   // math functions
#include <TCanvas.h> // canvas object
#include <fstream> // input/output file stream class

void tempOnDay(Int_t dateToCalculate);

//-----------------------------------------

void tempOnDay(Int_t dateToCalculate){

	//find date
	Int_t DaysPerMonth[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
	Int_t count = 0;
	Int_t in_month = 0;
	Int_t in_day = 0;

	for (Int_t k = -1; k < 12; k++){

		if (dateToCalculate > count){
			count = count + DaysPerMonth[k];
			//cout << count << endl;
		}
			else {
				in_month = k;
				in_day = dateToCalculate - count + DaysPerMonth[k-1];
				//cout << in_month << " , " << in_day << endl; 
				break;
			}
	}


	// create a histogram 
 	TH1D* day2hist = new TH1D("day2hist", "Average temperature of 1 day; Temperature [celsius]; counts", 60, -20, 40);

	//variable declaration 
	Int_t tot_lines = 50300;
	Int_t line = -1;
	Int_t year;
	Int_t years[tot_lines];
	Int_t month;
	Int_t months[tot_lines];
	Int_t day;
	Int_t days[tot_lines];
	Double_t temp;
	Double_t temps[tot_lines];

	// open input file
	fstream file;
	file.open("Cleaneddata_3.1", ios::in);

	//reading in data file
	while(file >> year >> month >> day >> temp){
		line++;	
		years[line] = year ;
		months[line] = month;
		days[line] = day;
		temps[line] = temp;
 		}
	tot_lines = line;
	//filling histogram
	for (Int_t i = 0; i < tot_lines; i++){

		if (in_month == months[i]){
			if (in_day == days[i]){
				day2hist->Fill(temps[i]);
			}
		}
	
	}

	//Mean value and standart deviation
	double mean = day2hist->GetMean();	
	double stdev = day2hist->GetRMS();
	cout << "The mean temperature is " << mean << " and the standart deviation is " << stdev << "." << endl;

	//filling color for dayhist
	day2hist->SetFillColor(kRed +1);

  	// create canvas for dayhist
  	TCanvas* c2 = new TCanvas("c1", "The temperature of a given day (1-355)", 900, 600);
  	day2hist->Draw();

	//ROOT formatting
	gStyle->SetOptStat(0); //Let's make our plots look a bit better. Get rid of the stat box
 	gStyle->SetOptTitle(0); //Get rid of the title (good plots use legends instead)
  	gStyle->SetTitleSize(0.05, "x"); //Use bigger text on the axes
  	gStyle->SetTitleSize(0.05, "y");
  	gStyle->SetLabelSize(0.05, "x"); //Use bigger labels too
  	gStyle->SetLabelSize(0.05, "y");
  	gStyle->SetPadTopMargin(0.05); //Change the margins to fit our new sizes
  	gStyle->SetPadRightMargin(0.05);
  	gStyle->SetPadBottomMargin(0.16);
  	gStyle->SetPadLeftMargin(0.16);

	// Save the canvas as a picture
  	c2->SaveAs("31_onearg.jpg");
	
	
}
