#include <iostream>
#include <vector>
#include <math.h>
#include "Instance.h"
#include "linkCalculator.h"
#include "json.hpp" //leitor de json

using namespace std;
using json = nlohmann::json;

Instance::Instance(json* config, json* matrixSNRMin, json* sensibilidades, json* matrixAlcance, json* vGateways, json* vClients)
{
    
    this->config = config;
    this->matrixSNRMin = matrixSNRMin;
    this->sensibilidades = sensibilidades;
    this->matrixAlcance = matrixAlcance;
    this->vGateways = vGateways;
    this->vClients = vClients;
    populaMatrixDistance();
}

/*
    Calcula a distancia entre todos os Gateways e Dispositivos compativeis 
    e popula a matriz de distancia
*/
void Instance::populaMatrixDistance()
{
    long double lngG,latG,lngC,latC;
    
    for (int i = 0; i < vGateways->size(); i++){
        vector<long double> row;
        lngG = vGateways->at(i)["lng"];
        latG = vGateways->at(i)["lat"];
        
        for (int j = 0; j < vClients->size(); j++){
            if(vGateways->at(i)["sf"] == vClients->at(j)["sf"]){ //calcula a distancia do par Gateway e Client que possuem sf iguais
                lngC = vClients->at(j)["lng"];
                latC = vClients->at(j)["lat"];
        
                row.push_back( distance(latG,lngG,latC,lngC) );
            }
            else{
                row.push_back(-1);
            }
            
        }   
        matrixDistance.push_back(row);
    }
}

//GETERS
json* Instance::getConfig(){
    return this->config;
};
json* Instance::getmatrixSNRMin(){
    return this->matrixSNRMin;
};

long double Instance::getSNRMinimo(int sf){
    return this->matrixSNRMin->at(to_string(sf));
};

json* Instance::getSensibilidades(){
    return this->sensibilidades;
};
json* Instance::getmatrixAlcance(){
    return this->matrixAlcance;
};

long double Instance::getAlcanceMaximo(int dbm, int sf){
    return this->matrixAlcance->at(to_string(dbm))[to_string(sf)];
};

json* Instance::getvGateways(){
    return this->vGateways;
};
json* Instance::getvClients(){
    return this->vClients;
};

vector< vector<long double> >*  Instance::getmatrixDistance(){
    return &this->matrixDistance;
};

long double Instance::getDistance(int idGateway,int idClient){
    return matrixDistance[idGateway][idClient];
}
/*
    Retorna todas as distancias do gateway escolhido
*/
void Instance::getAllDistG(int idGateway){
    
    cout << "DISTANCE TABLE - GATEWAY ID " << idGateway << endl;

    for (int client = 0; client < matrixDistance[idGateway].size(); client++){
        long double dist = matrixDistance[idGateway][client];
        if(dist != -1)
            cout << client << " - " << dist << " | ";
    }
    cout << endl;
}