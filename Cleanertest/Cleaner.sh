#!/bin/bash
sed -e '1,12d' DATA > Cleaneddata
sed -i 's/;/ /g' Cleaneddata 
sed -i 's/Y.*//' Cleaneddata
sed -i 's/G.*//' Cleaneddata






