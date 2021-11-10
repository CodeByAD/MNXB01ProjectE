#!/bin/bash
cd ../
cd Data

sed -e '1,12d' smhi-opendata_1_93250_20210926_100622_Karlstad.csv > Cleaneddata3D #Writes all but the first 12 lines to a new file
sed -i 's/;/ /g' Cleaneddata3D #Swaps all semi-colon for spaces
sed -i 's/Y.*//' Cleaneddata3D #Removes all Y
sed -i 's/G.*//' Cleaneddata3D #Removes all G

sed -i '/12:00/!d' Cleaneddata3D #Special line where one can take out only specific wanted times.

sed -i 's/:/ /g' Cleaneddata3D #Swaps all colons for spaces
sed -i 's/  */ /g' Cleaneddata3D #Reduces all multiple spaces to only one
sed -i 's/^ //' Cleaneddata3D #removes the first character if its a space

#removes the times in the data
#if this is not wanted, Comment out the while loop
i=20
x=12
while [ $i -ge $x ]
do
	sed -i "s/.//$i" Cleaneddata3D
	i=$(($i - 1));
done

#Cleanes the dashes separating the dates
sed -i 's/./ /5' Cleaneddata3D
sed -i 's/./ /8' Cleaneddata3D
sed -i 's/./ /9' Cleaneddata3D
sed -i 's/./ /10' Cleaneddata3D
sed -i 's/  */ /g' Cleaneddata3D #Reduces all multiple spaces to only one

mv Cleaneddata3D ../Skeleton
