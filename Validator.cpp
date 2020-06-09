#include <iostream>
#include <vector>
#include <math.h>
#include "Validator.h"
#include "Instance.h"
#include "json-3.7.3/single_include/nlohmann/json.hpp" //leitor de json

using namespace std;
using json = nlohmann::json;

/*
    @return 0 -> valido
    1 -> sf diferente
*/
int validator(Instance* instance, int idG, int idC,vector< vector<long double> >* matrixSolution){
    json* vClients = instance->getvClients();
    json* vGateways = instance->getvGateways();
    int sfG = vGateways->at(idG)["sf"];
    int sfC = vClients->at(idC)["sf"];

    if(sfG != sfC){
        return 1;
    }
    else{
        json* matrixSNRMin = instance->getmatrixSNRMin();
        json* sensibilidades = instance->getSensibilidades();
        json* matrixAlcance = instance->getmatrixAlcance();
        float SNRmin = matrixSNRMin->at(sfG);
        float sensibilidade = sensibilidades->at(sfC);
        float dbm = vClients->at(idC)["dbm"];
        float alcanceMax = matrixAlcance->at(dbm)[sfC];
    }
    return 0;
};



