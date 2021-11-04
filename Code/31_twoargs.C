#include <iostream>

using namespace std;

// ROOT library obejcts
#include <TF1.h> // 1d function class
#include <TH1.h> // 1d histogram classes
#include <TStyle.h>  // style object
#include <TMath.h>   // math functions
#include <TCanvas.h> // canvas object
#include <fstream> // input/output file stream class

void tempOnDay(Int_t in_day, Int_t in_month);

//-----------------------------------------

void tempOnDay(Int_t monthToCalculate, Int_t dayToCalculate){

	// open input file
	fstream file;
	file.open("Cleaneddata", ios::in);

	// create a histogram 
 	TH1D* dayhist = new TH1D("dayhist", "Average temperature of 1 day; Temperature [celsius]; counts", 60, -20, 40);

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
  	TCanvas* c1 = new TCanvas("c1", "The temperature of a given day (month/year)", 900, 600);
  	dayhist->Draw();

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
  	c1->SaveAs("31_twoargs.jpg");
	
}
