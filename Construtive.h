#ifndef CONSTRUTIVE_H
#define CONSTRUTIVE_H
#include <iostream>
#include <vector>
#include "Instance.h"
#include "json-3.7.3/single_include/nlohmann/json.hpp" //leitor de json

using namespace std;
using json = nlohmann::json;

class Construtive
{
    private:
        vector< vector<long double> > matrixSolution;
        json escolhido;
        vector<json> listaCanditados;
    public:
       Construtive(Instance* instance);
       void getCanditado(int index);
};


#endif