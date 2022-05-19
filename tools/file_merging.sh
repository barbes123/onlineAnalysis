#!/bin/bash


FIRSTrun=$1
volume1=$2
volume2=$3
Ncores=${4:-1}

echo "Will run the selector for runs $FIRSTrun upto $LASTrun "
echo "Will run the selector for volumes $volume1 upto $volume2 "		


space=" "

runnb=$FIRSTrun
volnb=$volume1

fileout="sum_selected_run_$runnb""_$volume1""_$volume2"."root"
#command="hadd sum_selected_run_$runnb""_$volume1""_$volume2"."root "
command="hadd $fileout -j$Ncores"
echo "Output file : $command"

if test -f "$fileout"
   then
   rm "$fileout"
fi

while test $volnb -le $volume2
 do 
 echo "selected_run_$runnb""_$volnb.root"
   if test -f "selected_run_$runnb""_$volnb.root"
   then
     command="$command""selected_run_$runnb""_$volnb.root""$space"
     echo "$command"
     volnb=$(($volnb + 1))
     else 
     break  
   fi  
done

echo "$command"
$command
