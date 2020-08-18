#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>
#include "linkCalculator.h"
#include "Instance.h"
#include "Construtive.h"
#include "json.hpp" //leitor de json

using namespace std;
using json = nlohmann::json;

int main()
{

    ifstream file("instancias/instancia_100_1000.txt");
    string line;

    getline(file, line, ';');
    json config = json::parse(line);

    getline(file, line, ';');
    json vAssignPoints = json::parse(line);

    getline(file, line, ';');
    json vClients = json::parse(line);

    file.close();

    //BW = 500 / SF=7 / Potencia=14 / dbi=2.15 /

    Instance *instance = new Instance(&config, &vAssignPoints, &vClients, 135.39);
    Construtive *cons = new Construtive(instance, 10);
    cons->Execute(instance, 1, 1);

}