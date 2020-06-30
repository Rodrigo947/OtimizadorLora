#ifndef LINK_CALCULATOR_H
#define LINK_CALCULATOR_H

#include <iostream>
#include <stdio.h>
#include <math.h>

using namespace std;

double Pr_dBm(float Pt, float Gt, float Gr, float d, int f);
double Pr(float Pt, float Gt, float Gr, float d, int f);
double ricochet(float Pt, float Gt, float Gr, float Ht, float Hr, float d);

long double snr(float P, float N);
long double dBm2mW(float P);
long double mW2dBm(float PdB);

#endif

