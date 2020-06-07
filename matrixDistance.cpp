#define _USE_MATH_DEFINES //Para usar a variavel de M_PI da biblioteca math.h
#include <iostream>
#include <vector>
#include <math.h>
#include "matrixDistance.h"
#include "json-3.7.3/single_include/nlohmann/json.hpp" //leitor de json

using namespace std;
using json = nlohmann::json;

matrixDistance::matrixDistance(json vGateways, json vClients)
{
    
    long double lngG,latG,lngC,latC;
    
    for (int i = 0; i < vGateways.size(); i++)
    {
        vector<long double> row;
        lngG = vGateways[i]["lng"];
        latG = vGateways[i]["lat"];
        
        for (int j = 0; j < vClients.size(); j++)
        {
            if(vGateways[i]["sf"] == vClients[j]["sf"]){ //calcula a distancia do par Gateway e Client que possuem sf iguais
                lngC = vClients[j]["lng"];
                latC = vClients[j]["lat"];
        
                row.push_back( distance(latG,lngG,latC,lngC) );
            }
            else{
                row.push_back(-1);
            }
            
        }   
        this->matrix.push_back(row);
    }
    
}

long double matrixDistance::toRadians(const long double degree)
{
    long double one_deg = (M_PI) / 180;
    return (one_deg * degree);
}

long double matrixDistance::distance(long double lat1, long double long1,
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


long double matrixDistance::getD(int idGateway,int idClient){
    return this->matrix[idGateway][idClient];
}
/*
    Retorna todas as distancias do gateway escolhido
*/
void matrixDistance::getAllDistG(int idGateway){
    cout << "DISTANCE TABLE - GATEWAY ID " << idGateway << endl;
    for (int client = 0; client < this->matrix[idGateway].size(); client++)
        if(this->matrix[idGateway][client] != -1)
            cout << client << " - " << this->matrix[idGateway][client] << " | ";
    cout << endl;
}
