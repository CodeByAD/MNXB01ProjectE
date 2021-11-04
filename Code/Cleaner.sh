#!/bin/bash
sed -e '1,12d' smhi-opendata_1_93250_20210926_100622_Karlstad.csv > Cleaneddata #Writes all but the first 12 lines to a new file
sed -i 's/;/ /g' Cleaneddata #Swaps all semi-colon for spaces
sed -i 's/Y.*//' Cleaneddata #Removes all Y
sed -i 's/G.*//' Cleaneddata #Removes all G

#sed -i '0,/^1955 12 31$/d' Cleaneddata Removes everything 

sed -i '/12:00\|13:00/!d' Cleaneddata #Special line where one can take out only specific wanted times.

sed -i 's/:/ /g' Cleaneddata #Swaps all colons for spaces
sed -i 's/  */ /g' Cleaneddata #Reduces all multiple spaces to only one
sed -i 's/^ //' Cleaneddata #removes the first character if its a space

#removes the times in the data
#if this is not wanted, Comment out the while loop
i=20
x=12
while [ $i -ge $x ]
do
	sed -i "s/.//$i" Cleaneddata
	i=$(($i - 1));
done

#if you only want one specific year: Change year underneath do desired year.
#if you do not want this feature, comment it out.

#year=1988

#sed -i "/$year/!d" Cleaneddata

#Cleanes the dashes separating the dates
sed -i 's/./ /5' Cleaneddata
sed -i 's/./ /8' Cleaneddata
sed -i 's/./ /9' Cleaneddata
sed -i 's/./ /10' Cleaneddata
sed -i 's/  */ /g' Cleaneddata #Reduces all multiple spaces to only one





