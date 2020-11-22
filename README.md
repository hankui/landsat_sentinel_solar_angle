# landsat_sentinel_solar_angle

The modelled solar zenith for Landsat-8, Sentinel-2 and for a solar zenith half way between the L8 and S2 solar zeniths.

The modelled solar zenith can be used for NBAR solar zenith definition for the c-factor BRDF correction (Roy et al. 2016). 

The solar zenith is as a function of day of year and latitude for the sun-synchronous orbit and drived from an inter-intermediate variable local overpass time.

The local overpass time is derived using Eq. (4) in Li et al. 2019 based on an astronomical model parameterized by local overpass time at Equator, satellite inclination and latitude.

The codes have two versions (i) a C version and (ii) a R version. 

Li, Z., Zhang, H. K., & Roy, D. P. (2019). Investigation of Sentinel-2 bidirectional reflectance hot-spot sensing conditions. IEEE Transactions on Geoscience and Remote Sensing, 57(6), 3591-3598.
Roy, D. P., Zhang, H. K., Ju, J., Gomez-Dans, J. L., Lewis, P. E., Schaaf, C. B., ... & Kovalskyy, V. (2016). A general method to normalize Landsat reflectance data to nadir BRDF adjusted reflectance. Remote Sensing of Environment, 176, 255-271.
