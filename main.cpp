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
    /*double freespaceModel = freeSpace(17, 5, 5, 5000, 915);
    double ricochetModel = ricochet(17, 5, 5, 20, 20, 5000);
    cout << "\nFreeSpace " << freespaceModel << "\n";
    cout << "Ricochet " << ricochetModel << "\n\n";*/
    ifstream file("instancias/instancia_200_800_7.txt");
    string line;

    // getline(file, line, ';');
    // json config = json::parse(line);

    // getline(file, line, ';');
    // json matrizSNRMin = json::parse(line);

    // getline(file, line, ';');
    // json sensibilidades = json::parse(line);

    // getline(file, line, ';');
    // json matrizAlcance = json::parse(line);

    // getline(file, line, ';');
    // json vGateways = json::parse(line);

    // getline(file, line, ';');
    // json vClients = json::parse(line);


    Instance* instance = new Instance(&config, &matrizSNRMin, &sensibilidades, &matrizAlcance, &vGateways, &vClients);
    //instance->getAllDist();
    //instance->getAllPrs();
    Construtive* c = new Construtive(instance);
    c->Execute(instance);
    

    // file.close();
    float G_dBi = 2.15;
    float G = pow(10, G_dBi/10);

    double P_dBm = Pr_dBm(14, G_dBi, G_dBi, 5000, 915);
    double P_mW = Pr(14, G, G, 5000, 915);
    // double ricochetModel = ricochet(17, 5, 5, 20, 20, 5000);
    cout << "\nP1_dBm = " << P_dBm << " dBm\n";
    cout << "P2_mW  = " << P_mW << " mW\n";
    cout << "P2_dBm = " << mW2dBm(P_mW) << " dBm\n";
    // cout << "Ricochet " << ricochetModel << "\n\n";

    double P = dBm2mW(20);
    double N = dBm2mW(14);
    double N_dBm = mW2dBm(N);
    double SNR_dB = snr(P, N);
       
    cout << "\nPower " << P << "mW\n";
    cout << "\nNoise " << N << "mW\n";
    cout << "\nNoise dBm " << N_dBm << "dBm\n";
    cout << "SNR " << SNR_dB << "\n\n";


}