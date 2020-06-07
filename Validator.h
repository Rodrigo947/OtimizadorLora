#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <vector>
#include "Instance.h"
#include "json-3.7.3/single_include/nlohmann/json.hpp" //leitor de json

using namespace std;
using json = nlohmann::json;

    int validator(Instance* instance, int idGateway, int idClient);

#endif