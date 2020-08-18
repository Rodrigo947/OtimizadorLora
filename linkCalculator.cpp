#include <iostream>
#include <stdio.h>
#include <math.h>
#include "linkCalculator.h"

# define PI           3.14159265358979323846  /* pi */

using namespace std;

/*  @params: 
 *
 * P -> Power (mW)
 * N -> Noise (mW)
*/
long double snr(long double P, long double N) {
    return 20*log10(P/N);
}

/*  @params: 
 *
 * P -> Power (dBm)
*/
long double dBm2mW(long double P) {
    return pow(10, P/10);
}

/*  @params: 
 *
 * P -> Power (mW )
*/
long double mW2dBm(long double PdB) {
    return 10*log10(PdB);
}

/*  @params: 
 *
 * Pt -> Tx power (dBm)
 * Gt -> Tx Antenna Gain (dBi)  
 * Gr -> Rx Antenna Gain (dBi)
 * d  -> Distance (meters)
 * f  -> Frequency (MHz)
*/
double Pr_dBm(float Pt, float Gt, float Gr, float d, int f) {
    return Pt + Gt + Gr - 32.44 - 20*log10(d/1000) - 20*log10(f);
}

/*  @params: 
 *
 * Pt -> Tx power (mW)
 * Gt -> Tx Antenna Gain (dBi)  
 * Gr -> Rx Antenna Gain (dBi)
 * d  -> Distance (meters)
 * f  -> Frequency (MHz)
*/
long double calcPr(float Pt, float Gt, float Gr, long double d, int f) {
    return Pt*Gt*Gr*pow(300/(4*PI*d*f), 2); // Pt + Gt + Gr - 32.44 - 20*log10(d/1000) - 20*log10(f);
}

/*  @params: 
 *
 * Pt -> Tx power (dBm)
 * Gt -> Tx Antenna Gain (dBi)  
 * Gr -> Rx Antenna Gain (dBi)
 * Ht -> Tx antenna height (meters)
 * Hr -> Rx antenna height (meters)
 * d  -> Distance (meters)
*/
long double ricochet(float Pt, float Gt, float Gr, float Ht, float Hr, float d) {
    return Pt + Gt + Gr + 20*log10(Ht) + 20*log10(Hr) - 40*log10(d);
}

long double toRadians(const long double degree)
{
    long double one_deg = PI / 180;
    return (one_deg * degree);
}

long double distance(long double lat1, long double long1,
                     long double lat2, long double long2)
{

    lat1 = toRadians(lat1);
    long1 = toRadians(long1);
    lat2 = toRadians(lat2);
    long2 = toRadians(long2);

    // Haversine Formula
    long double dlong = long2 - long1;
    long double dlat = lat2 - lat1;

    long double ans = pow(sin(dlat / 2), 2) +
                      cos(lat1) * cos(lat2) *
                          pow(sin(dlong / 2), 2);

    ans = 2 * asin(sqrt(ans));

    // Radius of Earth in
    // Kilometers, R = 6371
    // Use R = 3956 for miles
    long double R = 6371;

    // Calculate the result
    ans = ans * R;

    return ans;
}


