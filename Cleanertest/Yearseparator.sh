#!/bin/bash
#requires Cleaner.sh to have been run first
#if you do not wish to have separator at the top of the file
#yearstart should be set to one year above starting value in file
yearstart=1962
yearstop=1988

while [ $yearstart -le $yearstop ]
do
	sed -i "0,/.*$yearstart.*/s/.*$yearstart.*/;\n&/" Cleaneddata 
	#Change ";" to whatever delimiter you wish to have

	yearstart=$(($yearstart + 1));
done
