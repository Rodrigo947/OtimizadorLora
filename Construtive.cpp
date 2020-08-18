#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>
#include "Construtive.h"
#include "Instance.h"
#include "linkCalculator.h"
#include "QuickSort.h"
#include "json.hpp" //leitor de json

using namespace std;
using json = nlohmann::json;

/**
 * @param inst informções da instancia
 * @param raio define o alcance(km) maximo do gateway
 * 
 */
Construtive::Construtive(Instance *inst, float raio)
{
    this->raio = raio;
    int totalAssignPoints = inst->getQuantAssignPoints();
    int totalClients = inst->getQuantClients();

    //incializando matriz de adjacencia
    long double d;
    for (int a = 0; a < totalAssignPoints; a++)
    {
        vector<int> row;
        json candidato;
        candidato["id"] = a;
        candidato["quant"] = 0;
        for (int c = 0; c < totalClients; c++)
        {
            d = inst->getDistance(a, c);
            if (d <= raio && d != -1)
            {
                row.push_back(1);
                candidato["quant"] = candidato["quant"].get<int>() + 1;
            }
            else
                row.push_back(0);
        }
        matrixAdjacencia.push_back(row);
        listaCandidatos.push_back(candidato);
    }

    //inicializando a matriz de solução
    for (int i = 0; i < totalAssignPoints; i++)
    {
        vector<long double> row;
        for (int j = 0; j < totalClients; j++)
            row.push_back(-1);
        matrixSolution.push_back(row);
    }
}

int Construtive::randomK(float alfa, int size)
{
    return alfa * (size - 1);
}

void Construtive::removeEscolhido(int idEscolhido)
{
    for (int i = 0; i < listaCandidatos.size(); i++)
    {
        if (listaCandidatos[i]["id"] == idEscolhido)
        {
            listaCandidatos.erase(listaCandidatos.begin() + i);
            break;
        }
    }
}

void Construtive::atualizaListaCadidato(vector<int> quantRemovida)
{
    int id;
    for (int i = 0; i < listaCandidatos.size(); i++)
    {
        id = listaCandidatos[i]["id"];
        listaCandidatos[i]["quant"] = listaCandidatos[i]["quant"].get<int>() - quantRemovida[id];
    }
}

void Construtive::removeNosAtendidos(int idEscolhido)
{
    vector<int> quantRemovida(matrixAdjacencia.size(), 0);

    for (int c = 0; c < matrixAdjacencia[idEscolhido].size(); c++)

        if (matrixAdjacencia[idEscolhido][c])

            for (int a = 0; a < matrixAdjacencia.size(); a++)

                if (matrixAdjacencia[a][c])
                {
                    matrixAdjacencia[a][c] = 0;
                    quantRemovida[a]++;
                }
    atualizaListaCadidato(quantRemovida);
}

long double Construtive::calcSNRMinimo(Instance *inst){
    long double somatorio,d;
    vector<long double> prClients;
    int qntClients  = inst->getQuantClients();
    int idG;
    long double SNRminima=999999,SNR;
    dispInoperantes = 0;
    dispOuvidos = 0;
    for (int g = 0; g < gatewaysEscolhidos.size(); g++)
    {
        somatorio = 0;
        prClients.clear();
        idG = gatewaysEscolhidos[g];
        for (int c = 0; c < qntClients ; c++)
        {
            d = inst->getDistance(idG,c);
            prClients.push_back(calcPr(25.118864315,2.15,2.15,d,915));      
            somatorio += prClients[c];
        }

        
        for (int c = 0; c < qntClients ; c++)
        {   
            if (matrixSolution[idG][c] != -1){
                SNR = snr(prClients[c], somatorio-prClients[c]);
                if(SNR>=-7.5) dispOuvidos++;
                else dispInoperantes++;
                if(SNR<SNRminima) SNRminima = SNR;
            }
            
        }
        
    }
    
    return SNRminima;
}

void Construtive::Execute(Instance *inst, float alfa1, float alfa2)
{
    int k, idEscolhido;

    // 1º Fase - Selecionando os locais dos Gateways
    int qntGateways = inst->getQuantGateways();

    for (int i = 0; i < qntGateways; i++)
    {
        quickSort(&listaCandidatos, 0, listaCandidatos.size() - 1);
        k = randomK(1, listaCandidatos.size());
        idEscolhido = listaCandidatos[k]["id"];
        gatewaysEscolhidos.push_back(idEscolhido);
        removeEscolhido(idEscolhido);
        removeNosAtendidos(idEscolhido);
    }

    // 2º Fase - Atribuindo os Clientes aos Gateways
    int qntClients = inst->getQuantClients();
    int idGateway;
    long double distancia;
    for (int c = 0; c < qntClients; c++)
    {
        listaCandidatos.clear();
        for (int g = 0; g < gatewaysEscolhidos.size(); g++)
        {
            json candidato;
            idGateway = gatewaysEscolhidos[g];
            candidato["id"] = idGateway;
            candidato["quant"] = inst->getDistance(idGateway, c);
            listaCandidatos.push_back(candidato);
        }
        quickSort(&listaCandidatos, 0, listaCandidatos.size() - 1);
        k = randomK(0, listaCandidatos.size());
        idEscolhido = listaCandidatos[k]["id"];
        distancia = listaCandidatos[k]["quant"];
        matrixSolution[idEscolhido][c] = distancia;
    }
    imprimirResultado(inst);
}

void Construtive::imprimirResultado(Instance *inst)
{
    //long double somatorio = 0;
    int qntClients = inst->getQuantClients();
    int qntGateways = inst->getQuantGateways();

    ofstream myfile("resultados/resultadoJSON_"+to_string(qntGateways)+"_"+to_string(qntClients)+"_"+to_string(raio)+".txt");
    if (myfile.is_open())
    {
        json resultado, *client;
        int idG;
        json geral;
        geral["SNRminimo"] = calcSNRMinimo(inst);
        geral["dispOuvidos"] = dispOuvidos;
        geral["dispInoperantes"] = dispInoperantes;
        geral["raio"] = raio;
        resultado.push_back(geral);
        for (int g = 0; g < gatewaysEscolhidos.size(); g++)
        {
            json gateway;
            idG = gatewaysEscolhidos[g];
            gateway["id"] = idG;
            gateway["lat"] = inst->getAssignPoint(idG)->at("lat");
            gateway["lng"] = inst->getAssignPoint(idG)->at("lng");
            gateway["clients"];
            for (int c = 0; c < matrixSolution[idG].size(); c++)
                if (matrixSolution[idG][c] != -1)
                {
                    client = inst->getClient(c);
                    gateway["clients"].push_back({{"id", client->at("id")},
                                                  {"lat", client->at("lat")},
                                                  {"lng", client->at("lng")}});
                }
            resultado.push_back(gateway);
        }
        myfile << resultado.dump(2) << endl;

        /*
        for (int i = 0; i < matrixSolution.size(); i++)
        {
            myfile << i << "-> ";
            for (int j = 0; j < matrixSolution[i].size(); j++)
                if (matrixSolution[i][j] != -1)
                    myfile << j << ":" << matrixSolution[i][j] << ", ";
            myfile << "\n";
        }
        
        for (int i = 0; i < matrixSolution[0].size(); i++)
        {
            myfile << i << "-> ";
            for (int j = 0; j < matrixSolution.size(); j++)
                if (matrixSolution[j][i] != -1)
                {
                    myfile << j << ":" << matrixSolution[j][i];
                    //somatorio += matrixSolution[j][i];
                    break;
                }

            myfile << "\n";
        };
        */
        //cout << "Total: " << somatorio;
    }
    else
        cout << "Unable to open file";
}

void Construtive::printMatrixAdjacencia()
{
    ofstream myfile("resultados/matrixAdjacencia.csv");
    if (myfile.is_open())
    {
        for (int i = 0; i < matrixAdjacencia.size(); i++)
        {
            myfile << i << "->";
            for (int j = 0; j < matrixAdjacencia[i].size(); j++)
                myfile << "\t" << matrixAdjacencia[i][j];
            myfile << "\n";
        }
    }
    else
        cout << "Unable to open file";
}

void Construtive::printListaCandidatos()
{
    ofstream myfile("resultados/listaCandidatos.csv");
    if (myfile.is_open())
    {
        for (int i = 0; i < listaCandidatos.size(); i++)
            myfile << listaCandidatos[i]["id"] << " -> " << listaCandidatos[i]["quant"] << "\n";
    }
    else
        cout << "Unable to open file";
}