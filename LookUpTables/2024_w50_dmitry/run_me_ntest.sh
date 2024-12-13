#!/bin/bash

runnb=$1
runnb1=${2:-$runnb}
volume1=${3:-0}
volume2=${4:-$volume1}
nevents=${5:-0}
AddBack=${6:-1}
server=${7:-1}


echo "Put Parameters: AddBack (0 - if none); server_nbr (0 - if none); run_nbr; volume_from; volume_to;"

echo "RUNfirst      $runnb"
echo "RUNlast       $runnb1"
echo "VOLUMEfirst   $volume1"
echo "VOLUMElast    $volume2"
echo "N EVENTS      $events"
echo "AddBack       $AddBack"
echo "SERVER ID     $server"


lut_path="$HOME/onlineAnalysis/LookUpTables/2024_w50_dmitry/"
lut_link="$HOME/EliadeSorting/"


#lut_file="LUT_ELIADE_S9_20230523_DT.dat"
lut_file=""
lut_ta=""
lut_conf="LUT_CONF_NTEST.dat" #LaBr
lut_json="LUT_NTEST_20241203.json"
lut_cut=""


while test $runnb -le $runnb1
do

    volnb=$volume1
    while test $volnb -le $volume2
    do


unlink "$lut_link""LUT_ELIADE.dat"
unlink "$lut_link""LUT_ELIADE.json"
unlink "$lut_link""LUT_TA.dat"
unlink "$lut_link""LUT_CONF.dat"


if [ "$runnb" -ge "49" ]; then #for 10 MeV protons
	lut_conf="LUT_CONF_NTEST_RF.dat"
	lut_cut="neutron_cuts_run_56_64.root"
	lut_ta="LUT_TA_RUN59.conf"
fi


if [ "$runnb" -ge "65" ]; then #for 10 MeV protons
	lut_conf="LUT_CONF_NTEST_RF.dat"
	lut_cut="neutron_cuts_run_56_64.root"
	lut_ta="LUT_TA_RUN65.conf"
fi

if [ "$runnb" -ge "79" ]; then #for 10 MeV protons
	lut_conf="LUT_CONF_NTEST_RF.dat"
	lut_cut="neutron_cuts_run_56_64.root"
	lut_ta="LUT_TA_RUN79.conf"
fi


      
###########################LUT_ELIADE###s#####################
if [ -z "$lut_file" ]
then
      echo "LUT_ELIADE.dat is missing"
else
      unlink "$lut_link""LUT_ELIADE.dat"
      ln -s "$lut_path$lut_file" "$lut_link""LUT_ELIADE.dat"
fi

###########################LUT_ELIADE.json####################
if [ -z "$lut_json" ]
then
      echo "LUT_ELIADE.json is missing"
else
      unlink "$lut_link""LUT_ELIADE.json"
      ln -s "$lut_path$lut_json" "$lut_link""LUT_ELIADE.json"
      unlink "$lut_link""LUT_ELIADE.dat"     
fi

###########################LUT_TA############################
if [ -z "$lut_ta" ]
then
      echo "LUT_TA.dat is missing"
else
      unlink "$lut_link""LUT_TA.dat"
      ln -s "$lut_path$lut_ta" "$lut_link""LUT_TA.dat"
fi

###########################LUT_CONF##########################
if [ -z "$lut_conf" ]
then
      echo "LUT_CONF.dat is missing"
else
      unlink "$lut_link""LUT_CONF.dat"
      ln -s "$lut_path$lut_conf" "$lut_link""LUT_CONF.dat"
fi
#############################################################

echo "--------------------------------------------------------"
echo "Setting of LUT(s)"
echo "--------------------------------------------------------"	
echo -ne "LUT_ELIADE file	: "; tput setaf 2; echo " $lut_file";tput sgr0;
echo -ne "LUT_ELIADE json	: "; tput setaf 2; echo " $lut_json";tput sgr0;
echo -ne "LUT_CONF file	: "; tput setaf 2; echo " $lut_conf";tput sgr0;
echo -ne "LUT_TA file	: "; tput setaf 2; echo " $lut_ta";tput sgr0;
echo -ne "LUT_CUT file  : "; tput setaf 2; echo " $lut_cut";tput sgr0;
echo "--------------------------------------------------------"
   
    echo "Now I am starting run the selector run$runnb"_"$volnb.root"	
    rootcommand=start_me.C+"($AddBack,$server,$runnb,$volnb,$nevents)"    
    root -l -b -q $rootcommand    
    echo "I finished run$runnb"_"$volnb.root"
    volnb=$(($volnb + 1))      
    done
    runnb=$(($runnb + 1))  
done 
