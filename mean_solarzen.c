#include "mean_solarzen.h"
#include "local_solar.h"

double mean_solarzen(char *utm_numhem, double ux, double uy) 
{
	int utmzone;
	double lon, lat;
	double msz;
	double k_0, k_1, k_2, k_3, k_4, k_5, k_6;	

	utmzone = atoi(utm_numhem);
	if (strstr(utm_numhem, "S") && uy > 0)  /* Sentinel 2 */ 
		uy -= 10000000;		/* accommodate GCTP */

	utm2lonlat(utmzone, ux, uy, &lon, &lat);

	//lat = fabs(lat);  ??? Apr 9, 2016.

	/* From Martin:
	thes = k_6 x lat^6 + k_5 x lat^5 + k_4 x lat^4 + k_3 x lat^3 + k_2 x lat^2 + k_1 x lat + k_0
	*/
	k_0 =  31.0076;
	k_1 = -0.1272;
	k_2 =  0.01187;
	k_3 =  2.4025e-05;
	k_4 = -9.482e-07;
	k_5 = -1.9523e-09;
	k_6 =  6.1486e-11;

	msz = k_6 * pow(lat,6) + k_5 * pow(lat,5) + k_4 * pow(lat,4) + 
	      k_3 * pow(lat,3) + k_2 * pow(lat,2) + k_1 * lat + k_0;

	return msz;
}


/*********************************************************************************
time of mean overpass
********************************************************************************/
double get_poly_time(double lat){
	double x0coef, x1coef, x2coef, x3coef, x4coef, x5coef;
	double mhours;
	mhours=10.7833333;//initially average;
	x0coef=10.06;
	x1coef=0.01240604786763;
	x2coef=0.00006526856543;
	x3coef=-0.00000315819614;
	x4coef=-0.00000003154030;
	x5coef=0.00000000136292;
	mhours=x0coef+(x1coef*lat)+(x2coef*pow(lat, 2))+(x3coef*pow(lat, 3))+(x4coef*pow(lat, 4))+(x5coef*pow(lat, 5));
	return mhours;
}

double sdsu_solarzen(char *utm_numhem, double ux, double uy, int iYear, int mdoy1) 
{
	int utmzone;
	double lon, lat;
	double msz, msa;

	utmzone = atoi(utm_numhem);
	if (strstr(utm_numhem, "S") && uy > 0)  /* Sentinel 2 */ 
		uy -= 10000000;		/* accommodate GCTP */

	utm2lonlat(utmzone, ux, uy, &lon, &lat);

	// Zhang, H. K., Roy, D.P., Kovalskyy, V., 2016. Optimal solar geometry definition for global long term Landsat time series bi-directional reflectance normalization. IEEE Transactions on Geoscience and Remote Sensing, 54(3), 1410-1418. 
	double Mlat_hours; /* mean latitudinal overpass time*/
	Mlat_hours=get_poly_time(lat);
	// first for mday1
	int iMonth_gmt, iDay_gmt;
	double dHours_gmt, dMinutes_gmt, dSecondsint_gmt;
	getGMTtime(lon,mdoy1,Mlat_hours,
		&iDay_gmt,&dHours_gmt, &dMinutes_gmt, &dSecondsint_gmt);

	getDate(iDay_gmt,iYear,&iMonth_gmt,&iDay_gmt);

	SolarGeometry(iYear, iMonth_gmt, iDay_gmt,
		dHours_gmt, dMinutes_gmt, dSecondsint_gmt,
		lat, lon, &msa, &msz);

	return msz;
}

double Li_solarzen(double inclination, double Local_Time_at_Descending_Node, char *utm_numhem, double ux, double uy, int iYear, int mdoy1) 
{
	int utmzone;
	double lon, lat;
	double msz, msa;

	utmzone = atoi(utm_numhem);
	if (strstr(utm_numhem, "S") && uy > 0)  /* Sentinel 2 */ 
		uy -= 10000000;		/* accommodate GCTP */
	utm2lonlat(utmzone, ux, uy, &lon, &lat);

	// Li, Z., Zhang, H.K., Roy, D.P., Investigation of Sentinel-2 bidirectional reflectance hot-spot sensing conditions. IEEE Transactions on Geoscience and Remote Sensing. ​In press.	double Mlat_hours; /* mean latitudinal overpass time*/
	double Mlat_hours; /* mean latitudinal overpass time*/
	// double inclination = 98.62*PI/180;
	inclination = inclination*PI/180;
	// double Local_Time_at_Descending_Node = 10.5;
	Mlat_hours = Local_Time_at_Descending_Node-asin(tan(lat*PI/180)/tan(inclination))*180/PI/15;
	// printf("Mlat_hours%f %f\n", Mlat_hours, lat);

	int iMonth_gmt, iDay_gmt;
	double dHours_gmt, dMinutes_gmt, dSecondsint_gmt;
	getGMTtime(lon,mdoy1,Mlat_hours,
		&iDay_gmt,&dHours_gmt, &dMinutes_gmt, &dSecondsint_gmt);

	getDate(iDay_gmt,iYear,&iMonth_gmt,&iDay_gmt);

	SolarGeometry(iYear, iMonth_gmt, iDay_gmt,
		dHours_gmt, dMinutes_gmt, dSecondsint_gmt,
		lat, lon, &msa, &msz);

	return msz;
}
