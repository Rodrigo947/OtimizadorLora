#include <iostream>
#include <vector>
#include <math.h>
#include "Validator.h"
#include "Instance.h"
#include "linkCalculator.h"
#include "json.hpp" //leitor de json

using namespace std;
using json = nlohmann::json;

/*
    @return 
    0 -> Valido
    1 -> SF Diferente
    2 -> Distancia entre Gateway/Cliente > Alcance Maximo
    3 -> SNR do Gateway menor que o SNR Mínimo
*/
int validator(Instance* instance, int idG, int idC,vector< vector<long double> >* matrixSolution){
    json* vClients = instance->getvClients();
    json* vGateways = instance->getvGateways();
    int sfG = vGateways->at(idG)["sf"];
    int sfC = vClients->at(idC)["sf"];
    
    if(sfG != sfC)
        return 1;

    else{
        long double distance = instance->getDistance(idG,idC);
        int dbm = vClients->at(idC)["dbm"];
        long double alcanceMax = instance->getAlcanceMaximo(dbm,sfC);
        if(distance > alcanceMax)
            return 2;
        
        
        else{
            float SNRmin = instance->getSNRMinimo(sfG);
            long double SNR,somatorio=0,Pr;

            //Cliente a ser verificado
            json* config = instance->getConfig();
            float Gt = config->at("dBiGain").get<int>();
            float Pt = vClients->at(idC)["dbm"].get<int>();
            Pr = freeSpace(Pt,Gt,Gt,distance,915);
            
            //Somatorio dos Clientes que já estão no Gateway
            for (int i = 0; i < matrixSolution->at(idG).size(); i++)
            {
                if(matrixSolution->at(idG)[i] != -1)
                    somatorio += matrixSolution->at(idG)[i];
            }
            

            if(somatorio != 0)
                SNR = 10*log10(Pr/somatorio);
            else
                SNR = 10*log10(Pr);

            if(SNR < SNRmin)
                return 3;
            else 
                return 0;
        }
    }
    return 0;
};



