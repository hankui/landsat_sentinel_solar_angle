#!/bin/bash
#
# Hankui Jan 27, 2015
# dump a year of modelled Landsat-8, Sentinel-2 and the average of Landsat-8 and Sentinel-2 into a text file 
# for a test location, i.e., the tile centre of T35HME
# chmod a+x ./run_solar.sh
# bash ./run_solar.sh
#

# ./solar.zenith.exe 36 454860.000 -554880.000 1 2016
# ./solar.zenith.exe 35 454860.000 -3554880.000 1 2016

utmzone=36;
ux=454860.000;
uy=-554880.000;
year=2018;

# utmzone=35;
# ux=454860.000;
# uy=-3554880.000;
# year=2018;

filename_out=temp.utm${utmzone}.txt
lines_n=0
echo -e "l8_model, s2_model, l8_s2_average_model" > $filename_out

for doy in `seq 1 365`; do
	angles=`./solar.zenith.exe ${utmzone} ${ux} ${uy}  ${doy} ${year}`;
	echo $angles >> $filename_out; 
done 
