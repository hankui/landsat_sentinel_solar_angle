# This is used to calculate the nadir point solar geometry of Landsat-8 and Sentinel-2 
# The modelled solar zenith is defined as a function of latitude and day of the year (Li et al. 2019; Zhang et al. 2016), 
# and is calculated through a sensor overpass time model (Eq. 4 in Li et al. 2019).  
# This model only needs two satellite relevant parameters: the local overpass time at the Equator and the satellite inclination angle used in the sensor overpass time model (Eq. 4 in Li et al. 2019) take the average of the values for Landsat-8 and Sentinel-2. 

# Li, Z., Zhang, H.K., Roy, D.P., 2019. Investigation of Sentinel-2 bidirectional reflectance hot-spot sensing conditions. IEEE Transactions on Geoscience and Remote Sensing, 57(6), 3591-3598.

# Zhang, H. K., Roy, D.P., Kovalskyy, V., 2016. Optimal solar geometry definition for global long term Landsat time series bi-directional reflectance normalization. IEEE Transactions on Geoscience and Remote Sensing, 54(3), 1410-1418.

# Hank on Oct 15 2019  

# source("Pro.Landsat.Sentinel-2.sz.r")

require(insol)


## **********************************************************************************************
## calculate sun position all the days in year 'year'
## method = 0; using time specified in hour & mins
## method = 2; using modelled Landsat-8
## method = 3; using modelled Sentinel-2
## method = 4; using modelled Sentinel-2 and Landsat-8 average 
get_sun_position_a_year <- function(lat, year=2018, method=0, hour=12, mins=0) {

	# local noon time
	hour <- 12; mins <- 0;

	if (method==2) { ## Landsat-8
		inclination <- 98.2248*pi/180;
		Local_Time_at_Descending_Node <- 10.18333333333;
		model.time <- Local_Time_at_Descending_Node-asin(tan(lat*pi/180)/tan(inclination))*180/pi/15;
		hour <- floor(model.time); mins <- as.integer((model.time-hour)*60);
	} else if (method==3) { ## Sentinel-2
		# inclination <- 98.5613*pi/180;
		inclination <- 98.62*pi/180;
		Local_Time_at_Descending_Node <- 10.5;
		model.time <- Local_Time_at_Descending_Node-asin(tan(lat*pi/180)/tan(inclination))*180/pi/15;
		hour <- floor(model.time); mins <- as.integer((model.time-hour)*60);
	} else if (method==4) { ## Landsat-8 & Sentinel-2 average
		inclination <- (98.62*pi/180+98.2248*pi/180)/2;
		Local_Time_at_Descending_Node <- (10.5+10.18333333333)/2;
		model.time <- Local_Time_at_Descending_Node-asin(tan(lat*pi/180)/tan(inclination))*180/pi/15;
		hour <- floor(model.time); mins <- as.integer((model.time-hour)*60);
	} 

	## **********************************************************************************************
	## calculating sz
	days <- seq(ISOdate(year=year,month=1,day=1,hour=hour,min=mins),ISOdate(year=year,month=12,day=31,hour=hour,min=mins),by='24 hour');
	juneday=JD(days);
	lon <- 0;
	sp <- sunpos(sunvector(juneday, latitude=lat, longitude=lon, 0));
	sz <- sp[,2];
	sa <- sp[,1];
	# j <- -1*asin(cos(inclination*pi/180)/cos(lat*pi/180))*180/pi;
	dayofyear <- as.numeric(strftime(days, format = "%j"));

	list("dayofyear"=dayofyear, "sz"=sz, "sa"=sa); 
	
} 


## invoking example 
year <- 2019
lat <- -32.58 ## somewhere in south Africa
lat <- 44.3114 ## Brookings SD
Landsat.sz <- get_sun_position_a_year(lat, year, method=2)$sz 
Sentinel.sz <- get_sun_position_a_year(lat, year, method=3)$sz 
doys <- get_sun_position_a_year(lat, year, method=2)$dayofyear
plot(doys, Landsat.sz)
points(doys, Sentinel.sz, col="red")

