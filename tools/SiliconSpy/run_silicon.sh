#!/bin/bash

RUNNO=$1
VOL1=${2:-0}
VOL2=${3:-$VOL1}
EVTN=${4:-1}

# Usage
if [ $# -le 0 ]; then
    echo "Usage: ./run_calib.sh (runno) (vol1) (vol2) (event# to analyze)"
    echo ""
    exit -1
fi

# Version: skip event numver
if [ $# -le 4 ]; then
    RUNNO=$1
    VOL1=$2
    VOL2=$3
    EVTN=-1
fi

# Versin: skip volume
if [ $# -le 2 ]; then
    RUNNO=$1
    VOL1=0
    VOL2=0
    EVTN=-1
fi




echo "  Run Number        : " $RUNNO
echo "  Volume from       : " $VOL1
echo "  Volume to         : " $VOL2
echo "  Analysis Event No.: " $EVTN

root -b -l<<EOF
.x chain.C($RUNNO,$VOL1,$VOL2);
.x calib.C($RUNNO,$VOL1,$VOL2,$EVTN);
EOF
