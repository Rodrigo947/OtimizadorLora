#include <iostream>
#include <vector>
#include <math.h>
#include "Construtive.h"
#include "Instance.h"
#include "Validator.h"
#include "linkCalculator.h"
#include "json-3.7.3/single_include/nlohmann/json.hpp" //leitor de json

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
        listaCanditados.push_back(canditado);
    }

    quantDispInv = 0;
    
}


void Construtive::Execute(Instance* instance){
    int idC,idG,val,quantDisp,Pt,indexNode=0;
    long double razao,d;
    json* vClients = instance->getvClients();
    json* vGateways = instance->getvGateways();
    json* config = instance->getConfig();
    float Gt = config->at("dbiGain").get<int>();
    vector< vector<long double> >* matrixDistance = instance->getmatrixDistance();

    //while (listaCanditados.size()!=0)
    //{
        for (int i = 0; i < listaCanditados.size(); i++)
        {
            idC = listaCanditados[i]["idC"];
            idG = listaCanditados[i]["idG"];
            if(idG == escolhido["idG"]){
                listaCanditados[i]["idG"] = -1;
                listaCanditados[i]["val"] = -1;
                for (int j=0; j < vGateways->size(); j++)
                {
                    json* gateway = &vGateways->at(j);
                    int idG = gateway->at("id");
                    int quantDisp = gateway->at("quantDisp");
                    if(validator(instance,idG,idC,&matrixSolution)==0){
                        razao = calcRazao(idG,idC,quantDisp,matrixDistance);
                        if(razao > listaCanditados[i]["val"]){
                            listaCanditados[i]["val"] = razao;
                            listaCanditados[i]["idG"] = idG;
                        }
                    }
                }
                
            }
        }
        removeCandInv();
        ordenarLista();
        //indexNode=randomRang(0,α×|listaCandidatos|);
        escolhido = removeNode(indexNode);

        Pt = vClients->at(escolhido["idD"].get<int>())["dbm"].get<int>();
        d = matrixDistance->at(idG)[idC];
        //Gr = ??
        matrixSolution[escolhido["idG"]][escolhido["idC"]] = 0;//freeSpace(Pt,Gt,Gr,d,915);
        
        quantDisp = vGateways->at(escolhido["idG"].get<int>())["quantDisp"].get<int>()+1;
        vGateways->at(escolhido["idG"].get<int>())["quantDisp"] = quantDisp;

    //}
    
}

long double Construtive::calcRazao(int idG,int idC,int quantDisp, vector< vector<long double> >* matrixDistance){

    if(quantDisp==0)
        return matrixDistance->at(idG)[idC];
    else
        return matrixDistance->at(idG)[idC]/quantDisp;
}

/*
    Remove todos os canditados que não estão ligados a um Gateway
*/
void Construtive::removeCandInv(){
    for (int i = 0; i < listaCanditados.size(); i++)
        if(listaCanditados[i]["idG"]==-1)
            listaCanditados.erase(listaCanditados.begin()+i);
}



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

json Construtive::removeNode(int indexNode){
    json aux = listaCanditados[indexNode];
    listaCanditados.erase(listaCanditados.begin()+indexNode);
    return aux;
}


void Construtive::getCanditado(int index){
    cout<< "idC: "<< listaCanditados[index]["idC"] << " idG: "<< listaCanditados[index]["idG"] << " val: "<< listaCanditados[index]["val"] << endl;
}



    
