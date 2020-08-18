#ifndef LINK_CALCULATOR_H
#define LINK_CALCULATOR_H

#include <iostream>
#include <stdio.h>
#include <math.h>

using namespace std;
long double snr(long double P, long double N);
long double dBm2mW(long double P);
long double mW2dBm(long double PdB);
long double Pr_dBm(long double Pt, long double Gt, long double Gr, long double d, long double f);
long double calcPr(float Pt, float Gt, float Gr, long double d, int f);

long double ricochet(float Pt, float Gt, float Gr, float Ht, float Hr, float d);

long double toRadians(const long double degree);
long double distance(long double lat1, long double long1, long double lat2, long double long2);


#endif

