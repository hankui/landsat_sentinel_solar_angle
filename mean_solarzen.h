#ifndef MEAN_SOLARZEN_H
#define MEAN_SOLARZEN_H

#include "hls_projection.h"

/* Compute the annual mean solar zenith angle for the given UTM location (at the 
 * time of satellite overpass.
 */

double mean_solarzen(char *utm_numhem, double ux, double uy); 
double sdsu_solarzen(char *utm_numhem, double ux, double uy, int iYear, int mdoy1);
double Li_solarzen(double inclination, double Local_Time_at_Descending_Node, char *utm_numhem, double ux, double uy, int iYear, int mdoy1);

#endif

