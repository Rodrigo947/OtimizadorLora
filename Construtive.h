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
    vector<vector<long double>> matrixSolution;
    vector<vector<int>> matrixAdjacencia; //Quais clientes estão no range dos pontos candidatos
    vector<json> listaCandidatos;         // ids e quantidade de clientes atendidos
    vector<int> gatewaysEscolhidos;
    float raio;
    int dispOuvidos;
    int dispInoperantes;

    int randomK(float alfa, int size);
    void removeEscolhido(int idEscolhido);
    void atualizaListaCadidato(vector<int> quantRemovida);
    void removeNosAtendidos(int idEscolhido);
    long double calcSNRMinimo(Instance *inst);

public:
    Construtive(Instance *inst, float raio);
    void Execute(Instance *instance, float alfa1, float alfa2);
    void imprimirResultado(Instance *inst);
    void printMatrixAdjacencia();
    void printListaCandidatos();
};

#endif