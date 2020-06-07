#ifndef MATRIX_DISTANCE_H
#define MATRIX_DISTANCE_H

#include <vector>
#include "json-3.7.3/single_include/nlohmann/json.hpp" //leitor de json

using namespace std;
using json = nlohmann::json;

class matrixDistance
{
    private:
        vector< vector<long double> > matrix;

    public:
        matrixDistance(json vGateway, json vClients);
        long double toRadians(const long double degree);
        long double distance(long double lat1, long double long1, long double lat2, long double long2);
        long double getD(int idGateway,int idClient);
        void getAllDistG(int idGateway);
};


#endif