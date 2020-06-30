#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>
#include "Construtive.h"
#include "Instance.h"
#include "Validator.h"
#include "linkCalculator.h"
#include "json.hpp" //leitor de json

using namespace std;
using json = nlohmann::json;

Construtive::Construtive(Instance* instance)
{
    //inicializando a matriz de solução
    int totalGateways = instance->getConfig()->at("totalGateways");
    int totalClients = instance->getConfig()->at("totalClients");

    for (int i = 0; i < totalGateways; i++){
        vector<long double> row;
        for (int j = 0; j < totalClients; j++)
            row.push_back(-1);
        matrixSolution.push_back(row);
    }

    escolhido["idG"] = -1;
    escolhido["idC"] = -1;
    escolhido["val"] = -1;

    //inicializando a lista de canditados
    for (int i = 0; i < totalClients; i++)
    {
        json canditado;
        canditado["idC"] = i;
        canditado["idG"] = -1;
        canditado["val"] = -1; 
        canditado["diferencaSNR"] = -1; 
        listaCanditados.push_back(canditado);
    }

    quantDispInv = 0;
    
}


void Construtive::Execute(Instance* instance){
    int idC,idG,val,quantDisp,Pt,indexNode=0,dispInvalidos=0;
    long double razao,d,SNRMin,Pr,N,SNR;
    json* vClients = instance->getvClients();
    json* vGateways = instance->getvGateways();
    float Gt = instance->getdBiGain();
    vector< vector<long double> >* matrixDistance = instance->getmatrixDistance();


    while (listaCanditados.size()!=0)
    {
        for (int i = 0; i < listaCanditados.size(); i++)
        {
            idC = listaCanditados[i]["idC"];
            idG = listaCanditados[i]["idG"];
            SNRMin = instance->getSNRMinimo(vClients->at(idC)["sf"].get<int>());
            if(idG == escolhido["idG"]){
                listaCanditados[i]["idG"] = -1;
                listaCanditados[i]["val"] = -1;
                listaCanditados[i]["diferencaSNR"] = -1;
                for (int j=0; j < vGateways->size(); j++)
                {
                    json* gateway = &vGateways->at(j);
                    int idG = gateway->at("id");
                    int quantDisp = gateway->at("quantDisp");
                    if( matrixDistance->at(j)[i] != -1){
                        Pr = instance->getPr(idG,idC);
                        N = vGateways->at(idG)["N"];
                        SNR = snr(Pr,N);
                        if(SNR >= SNRMin){
                            listaCanditados[i]["diferencaSNR"] = SNR-SNRMin;
                            razao = calcRazao(idG,idC,quantDisp,matrixDistance);
                            if(razao > listaCanditados[i]["val"]){
                                cout<<razao;
                                listaCanditados[i]["val"] = razao;
                                listaCanditados[i]["idG"] = idG;
                            }
                        }
                        
                    }
                }
                if( listaCanditados[i]["idG"] == -1){
                    dispInvalidos++;
                    removeNode(i);
                    i--;
                }
                    
            }
        }
        
        if(listaCanditados.size()!=0){
            indexNode = menorValor();
            escolhido = removeNode(indexNode);
            matrixSolution[escolhido["idG"]][escolhido["idC"]] = escolhido["diferencaSNR"].get<long double>();
            
            quantDisp = vGateways->at(escolhido["idG"].get<int>())["quantDisp"].get<int>()+1;
            vGateways->at(escolhido["idG"].get<int>())["quantDisp"] = quantDisp;
        }
       
    }
    imprimirResultado(dispInvalidos);
    
}



long double Construtive::calcRazao(int idG,int idC,int quantDisp, vector< vector<long double> >* matrixDistance){

    if(quantDisp==0)
        return matrixDistance->at(idG)[idC];
    else
        return matrixDistance->at(idG)[idC]/quantDisp;
}

/*
void swap(json* a, json* b)  
{  
    json t = *a;  
    *a = *b;  
    *b = t;  
}  
  
int partition (vector<json>* arr, int low, int high)  
{  
    json pivot = arr->at(high); 
    int i = (low - 1); 
  
    for (int j = low; j <= high - 1; j++)  
    {  
        if (arr->at(j)["val"] < pivot["val"])  
        {  
            i++; 
            swap(&arr->at(i), &arr->at(j));  
        }  
    }  
    swap(&arr->at(i+1), &arr->at(high));  
    return (i + 1);  
}  
  
void quickSort(vector<json>* arr, int low, int high)  
{  
    if (low < high)  
    {  
        int pi = partition(arr, low, high);  
  
        quickSort(arr, low, pi - 1);  
        quickSort(arr, pi + 1, high);  
    }  
} 

void Construtive::ordenarLista(){
    quickSort(&listaCanditados,0,listaCanditados.size()-1);
}
*/ 

int Construtive::menorValor(){
    int menorIndex = 0;
    cout << this->listaCanditados[0]["val"].get<long double>();
    long double menorVal = this->listaCanditados[0]["val"].get<long double>();
    long double valAtual;
    
    for (int i = 1; i < this->listaCanditados.size(); i++){
        valAtual = this->listaCanditados[i]["val"].get<long double>(); 
        if (valAtual < menorVal)
        {
        menorIndex = i;
        menorVal = valAtual;
        }
    }
    return menorIndex;
}
    

json Construtive::removeNode(int indexNode){
    json aux = listaCanditados[indexNode];
    listaCanditados.erase(listaCanditados.begin()+indexNode);
    return aux;
}


void Construtive::getCanditado(int index){
    cout<< "idC: "<< listaCanditados[index]["idC"] << " idG: "<< listaCanditados[index]["idG"] << " val: "<< listaCanditados[index]["val"] << endl;
}


void Construtive::imprimirResultado(int dispInvalidos){
    long double somatorio = 0;
    ofstream myfile ("resultado.txt");
    if (myfile.is_open())
    {
        for (int i = 0; i < matrixSolution.size(); i++)
        {   
            myfile << i << "-> ";
            for (int j = 0; j < matrixSolution[i].size(); j++)
                if( matrixSolution[i][j] != -1)
                    myfile << j << ":" << matrixSolution[i][j] << ", ";
            myfile << "\n";   
        }

        for (int i = 0; i < matrixSolution[0].size(); i++)
        {   
            myfile << i << "-> ";
            for (int j = 0; j < matrixSolution.size(); j++)
                if( matrixSolution[j][i] != -1){
                    myfile << j << ":" << matrixSolution[j][i];
                    somatorio += matrixSolution[j][i];
                    break;
                }
                    
            myfile << "\n";   
        }
        cout << "Dispositivos sem Gateway: " << dispInvalidos << endl;
        cout << "Total: " << somatorio;
    }
    else cout << "Unable to open file";
    
}
    
