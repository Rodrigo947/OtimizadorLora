#ifndef CONSTRUTIVE_H
#define CONSTRUTIVE_H
#include <iostream>
#include <vector>
#include "Instance.h"
#include "json.hpp" //leitor de json

using namespace std;
using json = nlohmann::json;

class Construtive
{
    private:
        vector< vector<long double> > matrixSolution;
        json escolhido;
        vector<json> listaCanditados;
        int quantDispInv; //Dispositivos sem ligaçao com um Gateway
    public:
       Construtive(Instance* instance);
       void getCanditado(int index);
       void Execute(Instance* instance);
       long double calcRazao(int idG,int idD,int quantDisp,vector< vector<long double> >* matrixDistance);
       
       //void ordenarLista();
       int menorValor();
       json removeNode(int indexNode); 
       long double calcInterferencia();
       
       void imprimirResultado(int dispInvalidos);
};


#endif