#include <iostream>
#include <vector>
#include <math.h>
#include "Instance.h"
#include "json-3.7.3/single_include/nlohmann/json.hpp" //leitor de json

using namespace std;
using json = nlohmann::json;

Instance::Instance(json* config, json* matrixSNRMin, json* matrixAlcance, json* vGateways, json* vClients)
{
    
    this->config = config;
    this->matrixSNRMin = matrixSNRMin;
    this->matrixAlcance = matrixAlcance;
    this->vGateways = vGateways;
    this->vClients = vClients;

}

json* Instance::getConfig(){
    return config;
};
json* Instance::getmatrixSNRMin(){
    return matrixSNRMin;
};
json* Instance::getmatrixAlcance(){
    return matrixAlcance;
};
json* Instance::getvGateways(){
    return vGateways;
};
json* Instance::getvClients(){
    return vClients;
};
long double Instance::getDistance(int idGateway, int idClient){
    return this->matrixDistance[idGateway][idClient];
};

void Instance::setDistance(vector<long double> row){
    this->matrixDistance.push_back(row);
};