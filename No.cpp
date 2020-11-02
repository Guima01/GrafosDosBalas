#include "No.h"
#include "Aresta.h"
#include "Grafo.h"
#include <iostream>

using namespace std;

/**************************************************************************************************
 * Defining the No's methods
**************************************************************************************************/

// Constructor
No::No(int id)
{

    this->id = id;
    this->grau = 0;
    /*this->grau_saida = 0;
    this->peso = 0;
    this->primeira_aresta = nullptr;
    this->ultima_aresta = nullptr;*/
    this->proximo_no = nullptr;
    this->aresta = nullptr;
};

// Destructor
No::~No(){

};

// Getters

Aresta *No::getAresta()
{
    return this->aresta;
}

No *No::getProximoNo()
{

    return this->proximo_no;
}

int No::getId()
{

    return id;
}

int No::getGrau()
{
    return this->grau;
}

//setters

void No::setId(int id)
{
    this->id = id;
}

void No::setGrau()
{
    this->grau = grau + 1;
}

void No::setProximoNo(No *proximo_no)
{

    this->proximo_no = proximo_no;
}
//Aresta* No::getPrimeiraAresta()
//{
//
//    return this->primeira_aresta;
//
//}

//Aresta* No::getUltimaAresta()
//{
//
//    return this->ultima_aresta;
//
//}

//int No::getGrauEntrada()
//{
//
//    return this->grau_entrada;
//
//}

//int No::getGrauSaida()
//{
//
//    return this->grau_saida;
//
//}

//float No::getPeso()
//{
//
//    return this->peso;
//
//}

//void No::setPeso(float peso)
//{
//
//    this->peso = peso;
//
//}

// Other methods
void No::setAresta(Aresta *aresta)
{
        this->aresta = aresta;
}

//void No::incrementaGrauEntrada()
//{
//
//    this->grau_entrada++;
//
//}
//
//void No::incrementaGrauSaida()
//{
//
//    this->grau_saida++;
//
//}
//
//void No::decrementaGrauEntrada()
//{
//
//    this->grau_entrada--;
//
//}
//
//void No::decrementaGrauSaida()
//{
//
//    this->grau_saida--;
//
//}
//
//Aresta* No::possuiArestaEntre(int id_alvo)
//{
//
//    for(Aresta *auxAresta = this->primeira_aresta; auxAresta != nullptr; auxAresta = auxAresta->getProximaAresta())
//    {
//        if(auxAresta->getIdAlvo() == id_alvo)
//            return auxAresta;
//    }
//    return nullptr;
//}
