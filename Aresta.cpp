
#include "Aresta.h"
#include <iostream>

using namespace std;

/**************************************************************************************************
 * Definindo métodos de Aresta
**************************************************************************************************/

// Construtor
Aresta::Aresta(int id_origem,int id_alvo){

    this->id_origem = id_origem;
    this->id_alvo = id_alvo;
    //this->proxima_aresta = nullptr;
    this->peso = 0;
    this->verificaA=false;
}

// Destrutor
Aresta::~Aresta(){

    /*if (this->proxima_aresta != nullptr){
        delete this->proxima_aresta;
        this->proxima_aresta = nullptr;
    }*/

}

// Getters
int Aresta::getIdAlvo(){

    return this->id_alvo;

}

/*Aresta* Aresta::getProximaAresta(){

    return this->proxima_aresta;

}*/

float Aresta::getPeso(){

    return this->peso;

}

// Setters
/*void Aresta::setProximaAresta(Aresta* aresta){

    this->proxima_aresta = aresta;

}*/

void Aresta::setPeso(float peso){

    this->peso = peso;

}
bool Aresta::getVerificaAresta(){
    return this->verificaA;
}

void Aresta::setVerificaAresta(){
    this->verificaA = true;
}
