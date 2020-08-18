#ifndef INSTANCE_H
#define INSTANCE_H

#include <vector>
#include "json.hpp" //leitor de json

using namespace std;
using json = nlohmann::json;

class Instance
{
private:
    json *config;
    json *vAssignPoints;
    json *vClients;
    double maxRange;
    vector<vector<long double>> matrixDistance; //Distancia entre os clientes e os possiveis locais de gateways

public:
    Instance(json *config, json *vAssignPoints, json *vClients, double maxRange);
    void populaMatrix();

    //Configs
    int getQuantClients();
    int getQuantGateways();
    int getQuantAssignPoints();
    double getMaxRange();
    //--
    json *getClient(int id);
    json *getAssignPoint(int id);
    long double getDistance(int idAssignPoint, int idClient);
    void getAllDist();
};

#endif