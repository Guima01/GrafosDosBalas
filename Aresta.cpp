#include "Aresta.h"
#include <iostream>

using namespace std;

/**************************************************************************************************
 * Defining the Aresta's methods
**************************************************************************************************/

// Constructor
Aresta::Aresta(int target_id){

    this->id_alvo = id_alvo;
    this->proxima_aresta = nullptr;
    this->peso = 0;

}

// Destructor
Aresta::~Aresta(){

    if (this->proxima_aresta != nullptr){
        delete this->proxima_aresta;
        this->proxima_aresta = nullptr;
    }

}

// Getters
int Aresta::getIdAlvo(){

    return this->id_alvo;

}

Aresta* Aresta::getProximaAresta(){

    return this->proxima_aresta;

}

float Aresta::getPeso(){

    return this->peso;

}

// Setters
void Aresta::setProximaAresta(Aresta* aresta){

    this->proxima_aresta = aresta;

}

void Aresta::setPeso(float peso){

    this->peso = peso;

}
