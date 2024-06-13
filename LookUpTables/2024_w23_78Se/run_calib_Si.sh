#!/bin/bash

#echo "MASS first last"

# DIST=$1
FIRSTdomain=$1
LASTdomain=$2
activityCo60=$3
#activityCs137=$3

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
    if test -f "fulldata.calib" 
   then 
   	rm "fulldata.calib"   
   fi
##################################
    if test -f "res.temp" 
   then 
   	rm "res.temp"   
   fi
##################################          
    if test -f "data.calib" 
   then 
   	rm "data.calib"   
   fi
##################################
   
   

lim1=800
lim2=1600
fwhm=20
ampl=20

domnb=$FIRSTdomain
while test $domnb -le $LASTdomain
do
 echo "Now starting calib for domain $domnb"	
 
 # lim1=2500
#  lim2=3500
  #fwhm=20
  #ampl=20

 if test -f "mDelila_raw_py_$domnb.spe" 
   then
      #get full data on calibration
      ~/onlineAnalysis/tools/RecalEnergy -spe mDelila_raw_py_$domnb.spe -fmt A 16384 -lim $lim1 $lim2 -dwa $fwhm $ampl -ener 5155 -ener 5486 -ener 5805  -poly1 -v 2
      ~/onlineAnalysis/tools/RecalEnergy -spe mDelila_raw_py_$domnb.spe -fmt A 16384 -lim $lim1 $lim2 -dwa $fwhm $ampl -ener 5155 -ener 5486 -ener 5805  -poly1 -v 2 > fulldata.calib
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
	if grep '5155.000' temp.calib
	then
 	   cp -p temp.calib  calib1.temp
 	   sed -i "s/ /$domnb/" calib1.temp
 	   grep '5155.000'  calib1.temp >> res.temp 	   
 	   rm calib1.temp
 	   echo "Found 5155.00" 	   
	fi
	##################################      
	if grep '5486.000' temp.calib
	then
	   cp -p temp.calib  calib2.temp
 	   sed -i "s/ /$domnb/" calib2.temp
 	   grep '5486.000'  calib2.temp >> res.temp 	   
 	   rm calib2.temp
 	   echo "Found 5486.00"
	fi
	##################################      
	if grep '5805.000' temp.calib
	then
   	   cp -p temp.calib  calib3.temp
 	   sed -i "s/ /$domnb/" calib3.temp
 	   grep '5805.000'  calib3.temp >> res.temp 	   
 	   rm calib3.temp
 	   echo "Found 5805.00"
	fi
	##################################      
	if grep '#2' res.temp
	then	
 	   grep '#2'  res.temp >> data.calib      
 	   echo "Found"
	fi            
   else 
     echo no file "mDelila_raw_py_$domnb.spe" 
     echo "domain $domnb #2     0  Slope = 0.000000    Cal1=[ -0.0000  1.000000 ]" >> eliade.calib       
   fi  

 rm temp.calib
 domnb=$(($domnb + 1))
done

awk -F " " '{ print $1 " " $6 " " $7 " " $9 " "  $7/$6*$9 " keV" }' res.temp > resolution.txt
sed -i 's/#2/ /g' resolution.txt
awk -F " " '{ print $2 " " $9 " " $10 }' eliade.calib > coeff.dat



