#include "tempTrender.h"
#include <string>
void Cleaner() //Runs the cleaners for each result.
{
	system("Cleaner31.sh");
	system("Cleaner33.sh");
	system("Cleaner3D.sh");
}

void temponday() //Calls the function temponday from skeleton.
{
	
	tempTrender t; //Instantiate your analysis object

	t.tempOnDay(8, 23); //Result3.1.1
	t.tempOnDay(235); //Result 3.1.2
}

void extremetemps() //Calls the function extremetemps from skeleton.
{
	tempTrender e;
	e.extremetemps("2020");
}

void Avgtemp3D() //Calls the function Avgtemp3D from skeleton.
{
	tempTrender d;
	d.Avgtemp3D();
}



