#!/bin/bash

FIRSTdomain=$1
LASTdomain=$2

CUR_DIR=$(pwd)
cd $CUR_DIR

echo "CUR_DIR $CUR_DIR"

 ##################################   
 if test -f "calib.dat" 
   then 
   	rm "calib.dat"   
   fi
################################## 

echo "#domain a0 a1 b0 b1 b2"> calib.dat 

domnb=$FIRSTdomain
echo "ecalmapId$domnb.dat" 
 if test -f "ecalmapId$domnb.dat" 
   then
   echo "yessssssssssss"
   else
   echo "nooooooooooooooooo"
 fi

echo "Will run the calib for domains $FIRSTdomain upto $LASTdomain "

domnb=$FIRSTdomain
while test $domnb -le $LASTdomain
do
 echo "Now starting calib for domain $domnb"	
 ##################################   
 if test -f "fit.log" 
   then 
   	rm "fit.log"   
   fi
################################## 
# gnuplot -e "PA=$domnb" calib_dt.p
 gnuplot -e "PA=$domnb" calib_dt.p
 less fit.log|grep +/- | awk '{print $3}' > test1.dat
 echo -n "$domnb     " >> calib.dat
 awk 'BEGIN { ORS = "     " } { print }' test1.dat >> calib.dat 
 echo " " >>calib.dat
 rm test1.dat
 domnb=$(($domnb + 1))
done 

