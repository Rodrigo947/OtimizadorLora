#ifndef MATRIX_DISTANCE_H
#define MATRIX_DISTANCE_H

#include "Instance.h"
#include "json-3.7.3/single_include/nlohmann/json.hpp" //leitor de json

using namespace std;
using json = nlohmann::json;

    void matrixDistance(Instance* instancia);
    long double toRadians(const long double degree);
    long double distance(long double lat1, long double long1, long double lat2, long double long2);
    long double getD(Instance* instancia,int idGateway,int idClient);
    void getAllDistG(Instance* instancia,int idGateway);

#endif