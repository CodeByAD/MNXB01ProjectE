#!/bin/bash
cd ../
cd Data

sed -e '1,12d' smhi-opendata_1_93250_20210926_100622_Karlstad.csv > Cleaneddata33 #Writes all but the first 12 lines to a new file
sed -i 's/;/ /g' Cleaneddata33 #Swaps all semi-colon for spaces
sed -i 's/Y.*//' Cleaneddata33 #Removes all Y
sed -i 's/G.*//' Cleaneddata33 #Removes all G

sed -i 's/:/ /g' Cleaneddata33 #Swaps all colons for spaces
sed -i 's/  */ /g' Cleaneddata33 #Reduces all multiple spaces to only one
sed -i 's/^ //' Cleaneddata33 #removes the first character if its a space

#removes the times in the data
#if this is not wanted, Comment out the while loop
i=20
x=12
while [ $i -ge $x ]
do
	sed -i "s/.//$i" Cleaneddata33
	i=$(($i - 1));
done

mv Cleaneddata33 ../Skeleton
