#!/bin/bash
cd ../
cd Data

sed -e '1,12d' /home/an7384ho/Project/MNXB01-project/datasets/smhi-opendata_1_93250_20210926_100622_Karlstad.csv > Cleaneddata31 #Writes all but the first 12 lines to a new file
sed -i 's/;/ /g' Cleaneddata31 #Swaps all semi-colon for spaces
sed -i 's/Y.*//' Cleaneddata31 #Removes all Y
sed -i 's/G.*//' Cleaneddata31 #Removes all G

sed -i '/12:00\|13:00/!d' Cleaneddata31 #Special line where one can take out only specific wanted times.

sed -i 's/:/ /g' Cleaneddata31 #Swaps all colons for spaces
sed -i 's/  */ /g' Cleaneddata31 #Reduces all multiple spaces to only one
sed -i 's/^ //' Cleaneddata31 #removes the first character if its a space

#removes the times in the data
#if this is not wanted, Comment out the while loop
i=20
x=12
while [ $i -ge $x ]
do
	sed -i "s/.//$i" Cleaneddata31
	i=$(($i - 1));
done

#Cleanes the dashes separating the dates
sed -i 's/./ /5' Cleaneddata31
sed -i 's/./ /8' Cleaneddata31
sed -i 's/  */ /g' Cleaneddata31 #Reduces all multiple spaces to only one

mv Cleaneddata31 ../Skeleton
