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
        int quantDispInv; //Dispositivos sem ligaçao com um Gateway
    public:
       Construtive(Instance* instance);
       void getCanditado(int index);
       void Execute(Instance* instance);
       long double calcRazao(int idG,int idD,int quantDisp,vector< vector<long double> >* matrixDistance);
       void removeCandInv(); //Remove todos os canditados que não estão ligados a um Gateway
       void ordenarLista();
       json removeNode(int indexNode); //Remove da lista de canditados o canditado passado como parametro e o retorna
       long double calcInterferencia();
       
       void ImprimirResultado();
};


#endif