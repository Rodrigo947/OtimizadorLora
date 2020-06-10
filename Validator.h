#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <vector>
#include "Instance.h"
#include "json.hpp" //leitor de json

using namespace std;
using json = nlohmann::json;

    int validator(Instance* instance, int idG, int idC,vector< vector<long double> >* matrixSolution);

#endif