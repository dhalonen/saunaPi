#!/usr/bin/env bash
export myPlotFile=$1
export graphFile=$2
export highTemp=$3
export currentTemp=$4
plotDate=$(date +"%m/%d/%Y")
export plotDate
#echo "plotDate: $plotDate datafile: $myPlotFile, graphFile: $graphFile, highTemp: $highTemp currentTemp: $currentTemp"
gnuplot /home/pi/saunaPi/saunaPiPlotter/plot.gpl

