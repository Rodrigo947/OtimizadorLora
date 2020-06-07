#include <iostream>
#include <stdio.h>
#include <math.h>
#include "linkCalculator.h"

using namespace std;

double freeSpace(float Pt, float Gt, float Gr, float d, int f);
double ricochet();

/*  @params: 
 *
 * Pt -> Tx power (dBm)
 * Gt -> Tx Antenna Gain (dBi)  
 * Gr -> Rx Antenna Gain (dBi)
 * d  -> Distance (meters)
 * f  -> Frequency (MHz)
*/
double freeSpace(float Pt, float Gt, float Gr, float d, int f) {
    return Pt + Gt + Gr - 32.44 - 20*log10(d/1000) - 20*log10(f);
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
double ricochet(float Pt, float Gt, float Gr, float Ht, float Hr, float d) {
    return Pt + Gt + Gr + 20*log10(Ht) + 20*log10(Hr) - 40*log10(d);
}