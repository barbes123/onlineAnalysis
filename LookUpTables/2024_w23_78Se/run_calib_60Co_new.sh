#!/bin/bash

FIRSTdomain=$1
LASTdomain=${2:-$1}
activityCo60=${3:-1}
#$activityCs137=$3


CUR_DIR=$(pwd)
cd $CUR_DIR

echo "CUR_DIR $CUR_DIR"


domnb=$FIRSTdomain
echo "mDelila_raw_py_$domnb.spe" 
 if test -f "mDelila_raw_py_$domnb.spe" 
   then
   echo "yessssssssssss"
   else
   echo "nooooooooooooooooo"
 fi

echo "Will run the calib for domains $FIRSTdomain upto $LASTdomain "

##################################   
 if test -f "eliade.calib" 
   then 
   	rm "eliade.calib"   
   fi
##################################   
    if test -f "res.temp" 
   then 
   	rm "res.temp"   
   fi
##################################      
    if test -f "Co60.temp" 
   then 
   	rm "Co60.temp"   
   fi
##################################      
    if test -f "temp.calib" 
   then 
   	rm "temp.calib"   
   fi
##################################
    if test -f "resolution.txt" 
   then 
   	rm "resolution.txt"   
   fi
##################################
    if test -f "resolution_1332.txt" 
   then 
   	rm "resolution_1332.txt"   
   fi
##################################
   if test -f "resolution_1173.txt" 
   then 
   	rm "resolution_1173.txt"   
   fi
##################################
    if test -f "fulldata.calib" 
   then 
   	rm "fulldata.calib"   
   fi
##################################      
      
lim1=1600 lim2=4000 fwhm=4 ampl=100

domnb=$FIRSTdomain
while test $domnb -le $LASTdomain
do
 echo "Now starting calib for domain $domnb"
 
 
case "$domnb" in
"500") lim1=4000 lim2=6000 fwhm=4  ampl=100 ;;
"501") lim1=2000 lim2=4000 fwhm=4  ampl=100 ;;
"502") lim1=2000 lim2=4000 fwhm=4  ampl=100 ;;
"503") lim1=2000 lim2=4000 fwhm=4  ampl=100 ;;
"504") lim1=1600 lim2=2000 fwhm=4  ampl=100 ;;
"506") lim1=1600 lim2=2000 fwhm=4  ampl=100 ;;
"508") lim1=1600 lim2=2000 fwhm=4  ampl=100 ;;
"509") lim1=1600 lim2=2000 fwhm=4  ampl=100 ;;
"511") lim1=2400 lim2=3600 fwhm=4  ampl=100 ;;
"512") lim1=3000 lim2=4000 fwhm=4  ampl=100 ;;
"513") lim1=3000 lim2=4000 fwhm=4  ampl=10 ;;
"514") lim1=1600 lim2=2000 fwhm=4  ampl=100 ;;
"516") lim1=2000 lim2=4000 fwhm=4  ampl=100 ;;
"518") lim1=1500 lim2=2500 fwhm=4  ampl=100 ;;
"520") lim1=3000 lim2=4500 fwhm=4  ampl=100 ;;
"521") lim1=3000 lim2=4500 fwhm=4  ampl=100 ;;
"522") lim1=3000 lim2=4500 fwhm=4  ampl=100 ;;
"523") lim1=3000 lim2=4500 fwhm=3  ampl=100 ;;
"524") lim1=5000 lim2=7000 fwhm=3  ampl=100 ;;
*) echo "$domnb - default" ;;
esac 
 
 
 if test -f "mDelila_raw_py_$domnb.spe" 
   then
      ~/EliadeSorting/EliadeTools/RecalEnergy -spe mDelila_raw_py_$domnb.spe -fmt A 16384 -lim $lim1 $lim2 -dwa $fwhm $ampl -60Co -40K -v 2 -poly1
      ~/EliadeSorting/EliadeTools/RecalEnergy -spe mDelila_raw_py_$domnb.spe -fmt A 16384 -lim $lim1 $lim2 -dwa $fwhm $ampl -60Co -40K -v 2 -poly1 > fulldata.calib
      #delete first 14 lines
      awk 'NR > 14 { print }' fulldata.calib >  temp.calib
      
      echo -n "domain $domnb " >> eliade.calib      
      if grep 'Cal1' temp.calib
	then
 	   grep 'Cal1'  temp.calib >> eliade.calib      
 	   echo "Found Cal1"
 	else echo " ">> eliade.calib #if domain is emtry add a new line
	fi 	
	##################################      
	if grep '1173.238' temp.calib
	then
           #echo -n "domain $domnb " >> Co60.calib    
 	  #grep '1173.238'  temp.calib >> Co60.calib
 	   grep '1173.238'  temp.calib >> res.temp
 	   grep '1173.238'  temp.calib >> Co60.temp      
 	   echo "Found 1173.238"
	fi
	if grep '1332.513' temp.calib	    
	then
           #echo -n "domain $domnb " >> Co60.calib 
 	   grep '1332.513'  temp.calib >> res.temp
 	   grep '1332.513'  temp.calib >> Co60.temp      
 	   echo "Found"
	fi	
	if grep '1460.81' temp.calib	    
	then
           #echo -n "domain $domnb " >> Co60.calib 
 	   grep '1460.81'  temp.calib >> res.temp      
 	   echo "Found"
	fi
	if grep '#2' res.temp
	then
 	   grep '#2'  res.temp >> data.calib      
 	   echo "Found"
	fi            
   else 
     echo no file "mDelila_raw_py_$domnb.spe" 
     echo "domain $domnb #2     0  Slope = 0.000000    Cal1=[ -0.0000  1.000000 ]" >> eliade.calib       
     #echo "#2" >> eliade.calib 
     #sed -i "s/#2/$domnb/" eliade.calib
   fi  

sed -i "s/#2/$domnb/" data.calib
sed -i "s/#2/$domnb/" Co60.temp

 rm res.temp
 rm temp.calib	
 domnb=$(($domnb + 1))
done 
 
cat eliade.calib | sed 's/|/ /' | awk '{print $2, $9, $10}' >  eliade.coeff

awk -F " " '{ print $1 " " $5 " " $9 " " $6 " " $7 " " $7/$6*$9 " keV" }' data.calib > resolution.txt 
awk -F " " '{ print $1 " " $5 " " $9 " " $6 " " $7 " " $7/$6*$9 " [keV]; eff [%]: " $5/'$activityCo60'*100}' Co60.temp > eff_60Co.txt

rm Co60.temp
rm data.calib

grep '1332.513' resolution.txt >> resolution_1332.txt
grep '1173.238' resolution.txt >> resolution_1173.txt

