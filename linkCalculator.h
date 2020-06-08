#ifndef LINK_CALCULATOR_H
#define LINK_CALCULATOR_H

#include <iostream>
#include <stdio.h>
#include <math.h>

using namespace std;

double freeSpace(float Pt, float Gt, float Gr, float d, int f);
double ricochet(float Pt, float Gt, float Gr, float Ht, float Hr, float d);
long double toRadians(const long double degree);
long double distance(long double lat1, long double long1, long double lat2, long double long2);

#endif

