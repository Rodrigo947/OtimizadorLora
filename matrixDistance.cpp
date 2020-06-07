#define _USE_MATH_DEFINES //Para usar a variavel de M_PI da biblioteca math.h
#include <iostream>
#include <vector>
#include <math.h>
#include "matrixDistance.h"
#include "Instance.h"
#include "json-3.7.3/single_include/nlohmann/json.hpp" //leitor de json

using namespace std;
using json = nlohmann::json;

void matrixDistance(Instance* instancia)
{
    long double lngG,latG,lngC,latC;
    json* vGateways = instancia->getvGateways();
    json* vClients = instancia->getvClients();
    
    for (int i = 0; i < vGateways->size(); i++)
    {
        vector<long double> row;
        lngG = vGateways->at(i)["lng"];
        latG = vGateways->at(i)["lat"];
        
        for (int j = 0; j < vClients->size(); j++)
        {
            if(vGateways->at(i)["sf"] == vClients->at(j)["sf"]){ //calcula a distancia do par Gateway e Client que possuem sf iguais
                lngC = vClients->at(j)["lng"];
                latC = vClients->at(j)["lat"];
        
                row.push_back( distance(latG,lngG,latC,lngC) );
            }
            else{
                row.push_back(-1);
            }
            
        }   
        instancia->setDistance(row);
    }
    
}

long double toRadians(const long double degree)
{
    long double one_deg = (M_PI) / 180;
    return (one_deg * degree);
}

long double distance(long double lat1, long double long1,
                     long double lat2, long double long2)
{

    lat1 = toRadians(lat1);
    long1 = toRadians(long1);
    lat2 = toRadians(lat2);
    long2 = toRadians(long2);

    // Haversine Formula
    long double dlong = long2 - long1;
    long double dlat = lat2 - lat1;

    long double ans = pow(sin(dlat / 2), 2) +
                      cos(lat1) * cos(lat2) *
                          pow(sin(dlong / 2), 2);

    ans = 2 * asin(sqrt(ans));

    // Radius of Earth in
    // Kilometers, R = 6371
    // Use R = 3956 for miles
    long double R = 6371;

    // Calculate the result
    ans = ans * R;

    return ans;
}


long double getD(Instance* instancia,int idGateway,int idClient){
    return instancia->getDistance(idGateway,idClient);
}
/*
    Retorna todas as distancias do gateway escolhido
*/
void getAllDistG(Instance* instancia,int idGateway){
    
    int size = instancia->getvClients()->size();
    cout << "DISTANCE TABLE - GATEWAY ID " << idGateway << endl;

    for (int client = 0; client < size; client++){
        long double dist = instancia->getDistance(idGateway,client);
        if(dist != -1)
            cout << client << " - " << dist << " | ";
    }
    cout << endl;
}
