#include "tempTrender.h"
#include <string>
void Cleaner(){
	system("Cleaner31.sh");
	system("Cleaner33.sh");
	system("Cleaner3D.sh");
}

void project() {
	
	tempTrender t; //Instantiate your analysis object
	//One must currently comment out the results one does not want to produce since only one can be done at once.
	//t.tempOnDay(8, 23); //Result3.1.1
	//t.tempOnDay(235); //Result 3.1.2
	//t.extremetemps("2020"); //Result 3.3 Call with a single year to investigate
				//Also plots for all available years in the dataset
	t.Avgtemp3D();//3D average plot
}
