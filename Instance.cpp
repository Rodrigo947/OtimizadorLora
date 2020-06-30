#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>
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
    populaMatrix();
}

/*
    Calcula a distancia entre todos os Gateways e Dispositivos com sf iguais 
    e popula a matriz de distancia
*/
void Instance::populaMatrix()
{
    int ptc,sf;
    long double lngG,latG,lngC,latC,d,alcanceMax,Pr;
    float Gt = getdBiGain();
    float Pt;

    for (int i = 0; i < vGateways->size(); i++){
        vector<long double> rowDistance;
        vector<long double> rowPr;
        lngG = vGateways->at(i)["lng"];
        latG = vGateways->at(i)["lat"];
        vGateways->at(i)["quantDisp"] = 0;
        vGateways->at(i)["N"] = 0;
        
        for (int j = 0; j < vClients->size(); j++){
            if(vGateways->at(i)["sf"] == vClients->at(j)["sf"]){ //Apenas se o par Gateway e Client possuirem sf iguais
                lngC = vClients->at(j)["lng"];
                latC = vClients->at(j)["lat"];
                
                ptc = vClients->at(j)["ptc"];
                sf = vClients->at(j)["sf"];
                alcanceMax = getAlcanceMaximo(ptc,sf);
                d = distance(latG,lngG,latC,lngC);
                
                if( d < alcanceMax){ //Apenas se o par Gateway e Client possuem uma distancia menor do que definida na tabela de alcance
                    rowDistance.push_back(d);
                    Pt = vClients->at(i)["ptc"].get<int>();
                    Pr = freeSpace(Pt,Gt,Gt,d,915);
                    vGateways->at(i)["N"] = Pr + vGateways->at(i)["N"].get<long double>();
                    rowPr.push_back( Pr );
                }
                else{
                    rowPr.push_back(-1);
                    rowDistance.push_back(-1);
                }
               
            }
            else{
                rowPr.push_back(-1);
                rowDistance.push_back(-1);
            }
            
        }   
        matrixPr.push_back(rowPr);
        matrixDistance.push_back(rowDistance);
    }
}

//GETERS
json* Instance::getConfig(){
    return this->config;
};
float Instance::getdBiGain(){
    return this->config->at("dBiGain").get<float>();
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

long double Instance::getPr(int idGateway,int idClient){
    return matrixPr[idGateway][idClient];
}
/*
    Imprime em um arquivo a matriz de distancias
*/
void Instance::getAllDist(){
    ofstream myfile ("distanceTable.txt");
    myfile << "DISTANCE TABLE" << "\n";

    for (int gateway = 0; gateway < matrixDistance.size(); gateway++)
    {
        for (int client = 0; client < matrixDistance[gateway].size(); client++){
            long double dist = matrixDistance[gateway][client];
            myfile << dist << " ";
        }
        myfile << "\n";   
    }
    
}

/*
    Imprime em um arquivo a matriz de Prs
*/
void Instance::getAllPrs(){
    ofstream myfile ("PrTable.txt");
    myfile << "Pr TABLE" << "\n";

    for (int gateway = 0; gateway < matrixPr.size(); gateway++)
    {
        for (int client = 0; client < matrixPr[gateway].size(); client++){
            long double dist = matrixPr[gateway][client];
            myfile << dist << " ";
        }
        myfile << "\n";   
    }
    
}
