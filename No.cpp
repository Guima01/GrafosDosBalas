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
No::~No()
{

//    Aresta* proxima_aresta = this->primeira_aresta;

//    while(proxima_aresta != nullptr)
//    {
//
//        Aresta* aresta_aux = proxima_aresta->getProximaAresta();
//        delete proxima_aresta;
//        proxima_aresta = aresta_aux;
//
//    }

};

// Getters
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

void No::setId(int id)
{
    this->id = id;
}

int No::getId()
{

    return id;

}

void No::setGrau(){
    this->grau = grau + 1;
}

int No::getGrau(){
    return this->grau;
}
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

No* No::getProximoNo()
{
//    cout<<this->proximo_no<<endl;
//    cout<<&this->proximo_no<<endl;
    return this->proximo_no;

}

// Setters

void No::setProximoNo(No* proximo_no)
{

    this->proximo_no = proximo_no;

}

//void No::setPeso(float peso)
//{
//
//    this->peso = peso;
//
//}

// Other methods
void No::insereAresta(Aresta *aresta)
{
        this->aresta = aresta;
}

Aresta* No::getAresta(){
    return this->aresta;
}
//bool No::buscarAresta(int id_alvo)
//{
//    // Verifies whether there are at least one Aresta in the No
//    if(this->primeira_aresta != nullptr)
//    {
//        // Searching for a specific Aresta of target id equal to target id
//        for(Aresta* aux = this->primeira_aresta; aux != nullptr; aux = aux->getProximaAresta())
//            if(aux->getIdAlvo() == id_alvo)
//                return true;
//
//    }
//
//    return false;
//
//}
//
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
