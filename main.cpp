#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>
#include "linkCalculator.h"
#include "Instance.h"
#include "json-3.7.3/single_include/nlohmann/json.hpp" //leitor de json

using namespace std;
using json = nlohmann::json;



int main()
{
    /*double freespaceModel = freeSpace(17, 5, 5, 5000, 915);
    double ricochetModel = ricochet(17, 5, 5, 20, 20, 5000);
    cout << "\nFreeSpace " << freespaceModel << "\n";
    cout << "Ricochet " << ricochetModel << "\n\n";*/
    ifstream file("instancias/instancia_200_800.txt");
    string line;

    getline(file, line, ';');
    json config = json::parse(line);

    getline(file, line, ';');
    json matrizSNRMin = json::parse(line);

    getline(file, line, ';');
    json matrizAlcance = json::parse(line);

    getline(file, line, ';');
    json vGateways = json::parse(line);

    getline(file, line, ';');
    json vClients = json::parse(line);

    Instance* instance = new Instance(&config, &matrizSNRMin, &matrizAlcance, &vGateways, &vClients);
    instance->getAllDistG(5);
    file.close();

}