#include <iostream>
#include <fstream>
#include <TMath.h>
#include <TGraph2D.h>
#include <TCanvas.h>
#include <TF2.h>
#include <TH1.h>
#include <TRandom.h>
#include <TStyle.h>

using namespace std;

// ROOT library


int main()
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
	file.open("Cleaneddata", ios::in);

	//Calculating the number of rows in the file
	Int_t numLines = 0;
	ifstream in("Cleaneddata");
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
