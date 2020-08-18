#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>
#include "Instance.h"
#include "linkCalculator.h"
#include "json.hpp" //leitor de json

using namespace std;
using json = nlohmann::json;

Instance::Instance(json *config, json *vAssignPoints, json *vClients, double maxRange)
{

    this->config = config;
    this->vAssignPoints = vAssignPoints;
    this->vClients = vClients;
    this->maxRange = maxRange;
    populaMatrix();
}

/*
    Calcula a distancia entre todos os clientes e os possiveis locais de gateways
    e popula a matriz de distancia
*/
void Instance::populaMatrix()
{
    int ptc, sf;
    long double lngA, latA, lngC, latC, d;

    for (int i = 0; i < vAssignPoints->size(); i++)
    {
        vector<long double> rowDistance;
        lngA = vAssignPoints->at(i)["lng"];
        latA = vAssignPoints->at(i)["lat"];

        for (int j = 0; j < vClients->size(); j++)
        {
            lngC = vClients->at(j)["lng"];
            latC = vClients->at(j)["lat"];

            d = distance(latA, lngA, latC, lngC);

            if (d <= maxRange)
                rowDistance.push_back(d);
            else
                rowDistance.push_back(-1);
        }

        matrixDistance.push_back(rowDistance);
    }
}

//GETERS

int Instance::getQuantClients()
{
    return this->config->at("clients").get<int>();
};
int Instance::getQuantGateways()
{
    return this->config->at("gateways").get<int>();
};
int Instance::getQuantAssignPoints()
{
    return this->config->at("assignPoints").get<int>();
};
double Instance::getMaxRange()
{
    return this->maxRange;
};

long double Instance::getDistance(int idAssignPoint, int idClient)
{
    return matrixDistance[idAssignPoint][idClient];
}

json *Instance::getClient(int id)
{
    return &vClients->at(id);
}

json *Instance::getAssignPoint(int id)
{
    return &vAssignPoints->at(id);
}

/*
    Imprime em um arquivo a matriz de distancias
*/
void Instance::getAllDist()
{
    ofstream myfile("resultados/matrixDistance.csv");

    for (int gateway = 0; gateway < matrixDistance.size(); gateway++)
    {
        for (int client = 0; client < matrixDistance[gateway].size(); client++)
        {
            long double dist = matrixDistance[gateway][client];
            myfile << dist << "\t";
        }
        myfile << "\n";
    }
}
