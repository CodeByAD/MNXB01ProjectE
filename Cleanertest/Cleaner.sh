#!/bin/bash
sed -e '1,12d' DATA > Cleaneddata
sed -i 's/;/ /g' Cleaneddata 
sed -i 's/Y.*//' Cleaneddata
sed -i 's/G.*//' Cleaneddata
sed -i 's/:/ /g' Cleaneddata 
sed -i 's/  */ /g' Cleaneddata
sed -i 's/^ //' Cleaneddata

i=20
x=12
while [ $i -ge $x ]
do
	sed -i "s/.//$i" Cleaneddata
	i=$(($i - 1));
done









