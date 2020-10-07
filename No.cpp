#include "No.h"
#include "Aresta.h"
#include <iostream>

using namespace std;

/**************************************************************************************************
 * Defining the No's methods
**************************************************************************************************/

// Constructor
No::No(int id){

    this->id = id;
    this->grau_entrada = 0;
    this->grau_saida = 0;
    this->peso = 0;
    this->primeira_aresta = nullptr;
    this->ultima_aresta = nullptr;
    this->proximo_no = nullptr;

};

// Destructor
No::~No(){

    Aresta* proxima_aresta = this->primeira_aresta;

    while(proxima_aresta != nullptr){

        Aresta* aresta_aux = proxima_aresta->getProximaAresta();
        delete proxima_aresta;
        proxima_aresta = aresta_aux;

    }

};

// Getters
Aresta* No::getPrimeiraAresta(){

    return this->primeira_aresta;

}

Aresta* No::getUltimaAresta(){

    return this->ultima_aresta;

}

int No::getId(){

    return this->id;

}

int No::getGrauEntrada(){

    return this->grau_entrada;

}

int No::getGrauSaida(){

    return this->grau_saida;

}

float No::getPeso(){

    return this->peso;

}

No* No::getProximoNo(){

    return this->proximo_no;

}

// Setters

void No::setProximoNo(No* proximo_no){

    this->proximo_no = proximo_no;

}

void No::setPeso(float peso){

    this->peso = peso;

}

// Other methods
void No::insereAresta(int id_alvo, float peso){
    // Verifies whether there are at least one Aresta in the No
    if(this->primeira_aresta != nullptr){
        // Allocating the new Aresta and keeping the integrity of the Aresta list
        Aresta* aresta = new Aresta(id_alvo);
        aresta->setPeso(peso);
        this->ultima_aresta->setProximaAresta(aresta);
        this->ultima_aresta = aresta;

    }
    else{
         // Allocating the new Aresta and keeping the integrity of the Aresta list
        this->primeira_aresta = new Aresta(id_alvo);
        this->primeira_aresta->setPeso(peso);
        this->ultima_aresta = this->primeira_aresta;

    }

}

void No::removeTodasArestas(){
    // Verifies whether there are at least one Aresta in the No
    if(this->primeira_aresta != nullptr){

        Aresta* proximo = nullptr;
        Aresta* aux = this->primeira_aresta;
        // Removing all Arestas of the No
        while(aux != nullptr){

            proximo = aux->getProximaAresta();
            delete aux;

        }

    }

    this->primeira_aresta = this->ultima_aresta = nullptr;

}

int No::removeAresta(int id, bool direcao, No* no_alvo){
    // Verifies whether the Aresta to remove is in the No
    if(this->buscarAresta(id)){

        Aresta* aux = this->primeira_aresta;
        Aresta* anterior = nullptr;
        // Searching for the Aresta to be removed
        while(aux->getIdAlvo() != id){

            anterior = aux;
            aux = aux->getProximaAresta();

        }
        // Keeping the integrity of the Aresta list
        if(anterior != nullptr)
            anterior->setProximaAresta(aux->getProximaAresta());

        else
            this->primeira_aresta = aux->getProximaAresta();

        if(aux == this->ultima_aresta)
            this->ultima_aresta = anterior;

        if(aux->getProximaAresta() == this->ultima_aresta)
            this->ultima_aresta= aux->getProximaAresta();

        delete aux;
        // Verifies whether the graph is directed
        if(direcao)
            this->decrementaGrauSaida();

        else{

            this->decrementaGrauEntrada();
            no_alvo->decrementaGrauEntrada();

        }

        return 1;

    }

    return 0;

}

bool No::buscarAresta(int id_alvo){
     // Verifies whether there are at least one Aresta in the No
    if(this->primeira_aresta != nullptr){
        // Searching for a specific Aresta of target id equal to target id
        for(Aresta* aux = this->primeira_aresta; aux != nullptr; aux = aux->getProximaAresta())
            if(aux->getIdAlvo() == id_alvo)
                return true;

    }

    return false;

}

void No::incrementaGrauEntrada(){

    this->grau_entrada++;

}

void No::incrementaGrauSaida(){

    this->grau_saida++;

}

void No::decrementaGrauEntrada(){

    this->grau_entrada--;

}

void No::decrementaGrauSaida(){

    this->grau_saida--;

}

Aresta* No::possuiArestaEntre(int id_alvo)
{

    for(Aresta *auxAresta = this->primeira_aresta; auxAresta != nullptr; auxAresta = auxAresta->getProximaAresta())
    {
        if(auxAresta->getIdAlvo() == id_alvo)
            return auxAresta;
    }
    return nullptr;
}
