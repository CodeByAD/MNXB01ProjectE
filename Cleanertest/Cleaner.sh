#!/bin/bash
sed -e '1,12d' DATA > Cleaneddata
sed -i 's/;/ /g' Cleaneddata 
sed -i 's/Y.*//' Cleaneddata
sed -i 's/G.*//' Cleaneddata
sed -i 's/:/ /g' Cleaneddata 
sed -i 's/  */ /g' Cleaneddata
sed -i 's/^ //' Cleaneddata

#removes the times in the data, if this is not wanted.
#Comment out the while loop
i=20
x=12
while [ $i -ge $x ]
do
	sed -i "s/.//$i" Cleaneddata
	i=$(($i - 1));
done

#if you only want one specific year: Change year underneath do desired year.
#if you do not want this feature, comment it out.

year=1988

sed -i "/$year/!d" Cleaneddata







