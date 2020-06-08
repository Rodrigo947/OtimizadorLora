#include <iostream>
#include <vector>
#include <math.h>
#include "Construtive.h"
#include "Instance.h"
#include "Validator.h"
#include "json-3.7.3/single_include/nlohmann/json.hpp" //leitor de json

using namespace std;
using json = nlohmann::json;

Construtive::Construtive(Instance* instance)
{
    //inicializando a matriz de solução
    int totalGateways = instance->getConfig()->at("totalGateways");
    int totalClients = instance->getConfig()->at("totalClients");

    for (int i = 0; i < totalGateways; i++){
        vector<long double> row;
        for (int j = 0; j < totalClients; j++)
            row.push_back(-1);
        matrixSolution.push_back(row);
    }

    escolhido["idG"] = -1;
    escolhido["idD"] = -1;
    escolhido["val"] = -1;

    //inicializando a lista de canditados
    for (int i = 0; i < totalClients; i++)
    {
        json canditado;
        canditado["idD"] = i;
        canditado["idG"] = -1;
        canditado["val"] = -1; 
        listaCanditados.push_back(canditado);
    }
    
}

void Construtive::getCanditado(int index){
    cout<< "idD: "<< listaCanditados[index]["idD"] << " idG: "<< listaCanditados[index]["idG"] << " val: "<< listaCanditados[index]["val"] << endl;
}
    
