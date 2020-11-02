
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

<<<<<<< HEAD
=======
int Aresta::getIdOrigem(){

    return this->id_origem;

}

/*Aresta* Aresta::getProximaAresta(){

    return this->proxima_aresta;

}*/

>>>>>>> c10c15b326210e5ecee24c26ffb9bbdc2c481bdb
float Aresta::getPeso(){

    return this->peso;

}

bool Aresta::getVerificaAresta(){
    return this->verificaA;
}

/*Aresta* Aresta::getProximaAresta(){

    return this->proxima_aresta;

}*/


// Setters

void Aresta::setPeso(float peso){

    this->peso = peso;

}

void Aresta::setVerificaAresta(){
    this->verificaA = true;
}


