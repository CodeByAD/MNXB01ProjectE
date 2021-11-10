#include <iostream>
#include "tempTrender.h"

using namespace std;

// ROOT library objects
#include <TF1.h> // 1d function class
#include <TF2.h>
#include <TH1.h> // 1d histogram classes
#include <TStyle.h>  // style object
#include <TMath.h>   // math functions
#include <TCanvas.h> // canvas object
#include <fstream> // input/output file stream class
#include <TGraph2D.h>
#include <TRandom.h>
#include <TStyle.h>

tempTrender::tempTrender() = default;

void tempTrender::tempOnDay(int monthToCalculate, int dayToCalculate) const { //Make a histogram of the temperature on this day

	// open input file
	ifstream file ("Cleaneddata31");

	// create a histogram 
 	TH1D* dayhist = new TH1D("dayhist", "Average temperature of 1 day; Temperature [celsius]; counts", 60, -20, 40);

	//variable declaration 
	int tot_lines = 50300;
	int line = -1;
	int year;
	int month;
	int months[tot_lines];
	int day;
	int days[tot_lines];
	double temp;
	double temps[tot_lines];

	//reading in data file
	while(file >> year >> month >> day >> temp){
		line++;	
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
		}
			else {
				in_month = k;
				in_day = dateToCalculate - count + DaysPerMonth[k-1];
				//cout << in_month << " , " << in_day << endl; 
				break;
			}
	}

	// open input file
	ifstream file ("Cleaneddata31");

	// create a histogram 
 	TH1D* dayhist2 = new TH1D("dayhist2", "Average temperature of 1 day; Temperature [celsius]; counts", 60, -20, 40);

	//variable declaration 
	int tot_lines = 50300;
	int line = -1;
	int year;
	int month;
	int months[tot_lines];
	int day;
	int days[tot_lines];
	double temp;
	double temps[tot_lines];

	//reading in data file
	while(file >> year >> month >> day >> temp){
		line++;	
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
	cout << "The mean temperature is " << mean << " and the standard deviation is " << stdev << "." << endl;

	//filling color for dayhist
	dayhist2->SetFillColor(kRed +1);

  	// create canvas for dayhist
  	TCanvas* c2 = new TCanvas("c2", "day canvas", 900, 600);
  	dayhist2->Draw();

} 

double findtemp(Double_t daytemps[], Int_t samedaycount, string desire){
	Double_t hottest = -300;
	Double_t coldest = 1000000000000;	
	for(Int_t l = 0; l<samedaycount; l++){
	
		if(daytemps[l]>hottest){
			hottest = daytemps[l];			
		}
		if(daytemps[l]<coldest){
			coldest = daytemps[l];		
		}
	
	}

	if(desire == "hot"){
		return hottest;
	}
	if(desire == "cold"){
		return coldest;
	}

}


//function producing histograms for the hottest and coldest days each year
void tempTrender::extremetemps(string year){ 

//Some variables
Int_t lines = 500000; //#lines in the data file
string date; // takes the read string yyyy-mm-dd
string dates[lines]; //An array for storing dates, as multiple measurements are done each day the size is greater than 365. Size can be increased by changing variable lines.
Double_t temp; //Stores the temp for a date and puts it into temps1d.
Double_t temps[lines]; //Stores all temperatures for later comparison.
Double_t daytemps[lines]; //Stores the temperatures of one day at a time, made at least big enough given #lines in the data file.
Double_t hottemps[400][366]; //year, day
Double_t coldtemps[400][366]; //year, day
Int_t linenr = -1; //Keeps track of which line in the data-file is being investigated. Begins at -1 due to loop-structures.
//The year to investigate, this can be changed. A string variable to be easily comparable to the data
Int_t yearindex; //To find the desired year in the 2D arrays to be produced.
Int_t daynr; //To have to #days for the desired year stored.

// open input file
ifstream file("Cleaneddata33");

//handles one line of the data-file at a time
while(file >> date >> temp){
	linenr++;	
	dates[linenr] = date;
	temps[linenr] = temp;
}

//Now filling the rest of dates and temps with a string and value respectively marking the end of data from the data-file. (This is probably not necessary)
for(Int_t k = linenr+1; k<lines; k++){
	dates[k] = "end"; //These strings will be sorted away
	temps[k] = -300; //These (impossible) temperatures will be sorted away
}

Int_t j = 0; 
Int_t day = 0;
string currentyear = "";
Int_t yearcount = -1;
//Finds the hottest and coldest temp of every day of every year
while(j<=linenr){
	Int_t samedaycount = 0;//the number of temperatures measurements during a day	
	string currentday; //the day that is being investigated 
	if(dates[j].substr(0, 4) == currentyear){//To find the correct year
		currentday = dates[j].substr(5,5);
		while(dates[j].substr(5,5) == currentday){//To only get temp. from one day
			daytemps[samedaycount] = temps[j];
			samedaycount++;
			j++;
			if(dates[j].substr(0, 4) != currentyear){
				break;	//breaks out of the loop if the year changed			
			}
		}

		hottemps[yearcount][day] = findtemp(daytemps, samedaycount, "hot");
		coldtemps[yearcount][day] = findtemp(daytemps, samedaycount, "cold");
		day++;

	}

	else{
		if(currentyear == year){
			yearindex = yearcount;		
			daynr = day;
		}
		currentyear = dates[j].substr(0, 4);
		yearcount++;
		day=0;
	}
}


//setting the styles for the histograms (code from suggested code for project)
gStyle->SetOptStat(0); //Get rid of the stat box
gStyle->SetOptTitle(0); //Get rid of the title 
gStyle->SetTitleSize(0.05, "x");//Bigger text on the axes
gStyle->SetTitleSize(0.05, "y");
gStyle->SetLabelSize(0.05, "x");//Bigger labels too
gStyle->SetLabelSize(0.05, "y");
gStyle->SetPadTopMargin(0.05); //Change the margins to fit
gStyle->SetPadRightMargin(0.05);
gStyle->SetPadBottomMargin(0.16);
gStyle->SetPadLeftMargin(0.16);
gStyle->SetErrorX(0); //To not have error bars

// create a histograms Hot_hist and Cold_hist
TH1D* Hot_hist = new TH1D("Hottest temperatures", "Hottest temperatures; Day of year; Temperature [celcius]", day, 0, day); //Using day to make sure the histogram is big enoug, this deals with jump years (366 days).
TH1D* Cold_hist = new TH1D("Coldest temperatures", "Coldest temperatures; Day of year; Temperature [celcius]", daynr, 0, daynr);
TH1D* Both_hist = new TH1D("Both hottest and coldest temperatures", "Both hottest and coldest temperatures; Day of year; Temperature [celcius]", daynr, 0, daynr);
TH1D* Mean_hist = new TH1D("Mean of hottest and coldest temperatures", "Mean of hottest and coldest temperatures; Day of year; Temperature [celcius]", daynr, 0, daynr);
TH1D* FixFill_hist = new TH1D("FixFill", "FixFill; Day of year; Temperature [celcius]", daynr, 0, daynr);


//Filling the histograms
for(Int_t n = 0; n<daynr; n++){
	Hot_hist->Fill(n,hottemps[yearindex][n]);
	Cold_hist->Fill(n,coldtemps[yearindex][n]);
	Mean_hist->Fill(n,(hottemps[yearindex][n]+coldtemps[yearindex][n])/2); //Not plotted, but could be interesting.
	if(coldtemps[yearindex][n]>=0){
		FixFill_hist->Fill(n,coldtemps[yearindex][n]);
	}	

	Both_hist->Fill(n,hottemps[yearindex][n]);//As coldtemps will be drawn on the same canvas
					//as Both_hist it is fine to fill it with hottemps only.
					//I use Both_hist instead of Hot_hist as the initial drawing
					//to get the correct title.
}

//Creating canvases
TCanvas* c_hot = new TCanvas("c_hot", "Hot_hist", 900, 600);
Hot_hist->Draw("HIST");
TCanvas* c_cold = new TCanvas("c_cold", "Cold_hist", 900, 600);
Cold_hist->Draw("HIST");
TCanvas* c_both = new TCanvas("c_both", "Both_hist", 900, 600);
//The y-axis would only be fit to the first Drawn histogram and not the second,
// therefore I am manually fitting them
Both_hist->SetMinimum(*min_element(coldtemps[yearindex], coldtemps[yearindex]+daynr)-3);
Both_hist->SetMaximum(*max_element(hottemps[yearindex], hottemps[yearindex]+daynr)+3);

Both_hist->SetFillColor(9);
Both_hist->Draw("HIST");

TH1D* Cold_hist2 = new TH1D();
*Cold_hist2 = *Cold_hist; //Making a deepcopy of Cold_hist so I can use SetFillColor
// without changing the histogram Cold_hist.
Cold_hist2->SetFillColor(9);
Cold_hist2->Draw("SAME HIST");

FixFill_hist->SetFillColor(10); //Using this to "paint over" the part between 0
// and the positive values of Cold_hist2, which would otherwise have also been
// "filled", not the most elegant solution, but it works.
FixFill_hist->Draw("SAME HIST");


//Now making a histogram with the coldest and the hottest temperatures of each year
TH1D* AHot_hist = new TH1D("All Hottest temperatures", "All Hottest temperatures; Day of year; Red: Hottest, Blue: Coldest", 366, 0, 366);
TH1D* ACold_hist = new TH1D("All Coldest temperatures", "All Coldest temperatures; Day of year; Temperature [celcius]", 366, 0, 366);

//Filling these histograms
Int_t Ahottest[366] = {0}; //no initializer is specified so all elements are zero
Int_t Acoldest[366] = {0};
for(Int_t i = 0; i<yearcount; i++){
	for(Int_t n = 0; n<366; n++){
		if(*min_element(coldtemps[i], coldtemps[i]+366) == coldtemps[i][n]){
			Acoldest[n]++;
		}
		if(*max_element(hottemps[i], hottemps[i]+366) == hottemps[i][n]){
			Ahottest[n]++;
		}
	}	
}

for(Int_t n = 0; n<366; n++){
//	cout << "Day " << n << " instances coldest: " << Acoldest[n] << endl;
//There seems to be too high values for the coldest temperatures days 0, 1 and 4, but
// the histogram looks ok.
	AHot_hist->Fill(n,Ahottest[n]);
	ACold_hist->Fill(n,Acoldest[n]);
}

TCanvas* c_Ahot = new TCanvas("c_Ahot", "All_years_hottest_and_coldest_day_hist", 900, 600);
AHot_hist->SetFillColor(2);
AHot_hist->Draw("HIST");
ACold_hist->SetFillColor(4);
ACold_hist->Draw("SAME HIST");

}

void tempTrender::Avgtemp3D()
{


	//Declaring starting variables and arrays.
	Int_t year;
	Int_t month;
	Double_t temp;
	Int_t linenumber = 0;
	Int_t div = 0; //used to take the avrage temperature of each month.
	Int_t n = 0;
	Double_t Avgtemp = 0; 
	Double_t Avgtemparray[888]; //The array for the values of the avrage temperature.
	Double_t Avgmontharray[888]; //The array for the months of the year used to plot the avarage temperature.
	Double_t Avgyeararray[888]; //The array for the years used to plot the avarage temperature.
	
	//Opening the Data file with fstream.
	fstream file;
	file.open("Cleaneddata3D", ios::in);

	//Calculating the number of rows in the file
	Int_t numLines = 0;
	ifstream in("Cleaneddata3D");
	string unused;
	while (getline(in, unused))
	   ++numLines;
	
	//Setsup the arrays used to gather the data from the datafile.
	Int_t yeararray[numLines];
	Int_t montharray[numLines];
	Double_t temparray[numLines];
	
	//Collecting the data from the files into arrays and after closing the file.
	while (!file.eof()){
		file >> year >> month >> temp;
		yeararray[linenumber] = year;
		montharray[linenumber] = month;
		temparray[linenumber] = temp;
		linenumber++;
	}
	file.close();
	
	//declaring the starting year for the loop used to calculate the avrage temperature of each month
	Int_t currentyear = yeararray[0];
	while (currentyear < 2021){
		for (int i=1;i<=12;i++){
			for(int j = 0;j<numLines;j++){
				if (montharray[j] == i && yeararray[j] == currentyear){
					Avgtemp = Avgtemp + temparray[j];
					div++;
				}
			}
			Avgtemp = Avgtemp / div;
			Avgtemparray[n] = Avgtemp;
			Avgmontharray[n] = i;
			Avgyeararray[n] = currentyear;
			n++;
			div = 0;
			Avgtemp = 0;
			}
		currentyear++;
	}
	//Plotting with the help of TGraph2D.
	TCanvas *c = new TCanvas("c", "Graph2D");
	TGraph2D *dt = new TGraph2D(1);
	dt->SetTitle("Avarage temperature each month over the years in Karlstad; Year; Month; Temperature(C)");
	for (int f = 0; f<888; f++)
		dt->SetPoint(f, Avgyeararray[f], Avgmontharray[f], Avgtemparray[f]);
	dt->Draw("surf1");
	
}



