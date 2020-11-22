/******************
Hankui Apr 17, 2019
// calculate the modelled Landsat-8, Sentinel-2 & the average of Landsat-8 and Sentinel-2 solar zenith angles 
// ref to Eq. 4 in 
Li, Z., Zhang, H.K., Roy, D.P., 2019, Investigation of Sentinel-2 bidirectional reflectance hot-spot sensing conditions. IEEE Transactions on Geoscience and Remote Sensing. ​DOI: 10.1109/TGRS.2018.2885967
// input parameters: utm zone number, utmx, utmy, day of year, year
// e.g., ".exe zonehem ux uy year doy"
// ./solar.zenith.exe 36 454860.000 -554880.000 1 2016
 * ******************/
 
#include <stdio.h>
#include <stdlib.h>
#include "mean_solarzen.h"
#define MAX_FILE_LENGTH 1024


int main(int argc,char **argv)
{
	/********************************************************************************
	//parse the input parameters
	********************************************************************************/
	char usage[MAX_FILE_LENGTH];
	sprintf(usage, "%s zonehem ux uy year doy", argv[0]);
	if (argc < 5){
		printf("%s\n", usage);
		return 1;
	}
	double l8_inclination = 98.2;
	double l8_Local_Time_at_Descending_Node=10.18333333333;
	double s2_inclination = 98.62;
	double s2_Local_Time_at_Descending_Node=10.5;
	
	double l8_li_sz;	// L8 modelled solar zenith
	double s2_li_sz;		// S2 modelled solar zenith
	double s2_l8_average_li_sz;		// L8 & S2 average modelled solar zenith
	
	char* zonehem=argv[1]; 
	double ux=atof(argv[2]); 
	double uy=atof(argv[3]);
	int doy =atoi(argv[4]);	
	int year=atoi(argv[5]);	
	
	// printf("%s %f %f %d %d\n", zonehem, ux, uy, doy, year); 
	// L8 modelled solar zenith
	l8_li_sz = Li_solarzen(l8_inclination, l8_Local_Time_at_Descending_Node, zonehem, ux, uy, year, doy); 
                                                                                            
	// S2 modelled solar zenith
	s2_li_sz = Li_solarzen(s2_inclination, s2_Local_Time_at_Descending_Node, zonehem, ux, uy, year, doy); 
	
	// L8 & S2 average modelled solar zenith
	s2_l8_average_li_sz = Li_solarzen((s2_inclination+l8_inclination)/2, (s2_Local_Time_at_Descending_Node+l8_Local_Time_at_Descending_Node)/2, zonehem, ux, uy, year, doy); 

	printf("%f, %f, %f",l8_li_sz, s2_li_sz, s2_l8_average_li_sz);


	return 0;
}
