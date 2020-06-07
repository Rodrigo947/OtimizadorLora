#ifndef INSTANCE_H
#define INSTANCE_H

#include <vector>
#include "json-3.7.3/single_include/nlohmann/json.hpp" //leitor de json

using namespace std;
using json = nlohmann::json;

class Instance
{
    private:
        json* config;
        json* matrixSNRMin;
        json* matrixAlcance;
        json* vGateways;
        json* vClients;
        vector< vector<long double> > matrixDistance;

    public:
       Instance(json* config, json* matrizSNRMin, json* matrizAlcance, json* vGateways, json* vClients);
       json* getConfig();
       json* getmatrixSNRMin();
       json* getmatrixAlcance();
       json* getvGateways();
       json* getvClients();
       long double getDistance(int idGateway, int idClient);
       void setDistance(vector<long double> row);
};


#endif