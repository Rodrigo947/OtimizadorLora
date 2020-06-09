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
        json* sensibilidades;
        json* matrixAlcance;
        json* vGateways;
        json* vClients;
        vector< vector<long double> > matrixDistance;

    public:
       Instance(json* config, json* matrizSNRMin, json* sensibilidades, json* matrizAlcance, json* vGateways, json* vClients);
       void populaMatrixDistance();
       void getAllDistG(int idG);
       json* getConfig();
       json* getmatrixSNRMin();
       json* getSensibilidades();
       json* getmatrixAlcance();
       json* getvGateways();
       json* getvClients();
       vector< vector<long double> >* getmatrixDistance();
       long double getDistance(int idG, int idC);
};


#endif