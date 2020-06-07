#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>
#include "linkCalculator.h"
#include "matrixDistance.h"
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

    file.close();

    matrixDistance* MD = new matrixDistance(vGateways,vClients);
    MD->getAllDistG(5);
}