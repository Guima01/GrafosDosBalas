#include "Grafo.h"
#include "No.h"
#include "Aresta.h"
#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <list>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <float.h>
#include <iomanip>

using namespace std;

/**************************************************************************************************
 * Defining the Grafo's methods
**************************************************************************************************/

// Constructor
Grafo::Grafo(int ordem, bool direcao, bool aresta_ponderada, bool no_ponderado)
{

    this->ordem = ordem;
    this->direcao = direcao;
    this->aresta_ponderada = aresta_ponderada;
    this->no_ponderado = no_ponderado;
    this->primeiro_no = this->ultimo_no = nullptr;
    this->numero_arestas = 0;
}

// Destructor
Grafo::~Grafo()
{

    No *proximo_no = this->primeiro_no;

    while (proximo_no != nullptr)
    {

        proximo_no->removeTodasArestas();
        No *no_aux = proximo_no->getProximoNo();
        delete proximo_no;
        proximo_no = no_aux;
    }
}

// Getters
int Grafo::getOrdem()
{

    return this->ordem;
}
int Grafo::getNumeroArestas()
{

    return this->numero_arestas;
}

bool Grafo::getDirecao()
{

    return this->direcao;
}

bool Grafo::getArestaPonderada()
{

    return this->aresta_ponderada;
}

bool Grafo::getNoPonderado()
{

    return this->no_ponderado;
}

No *Grafo::getPrimeiroNo()
{

    return this->primeiro_no;
}

No *Grafo::getUltimoNo()
{

    return this->ultimo_no;
}

// Other methods
/*
    The outdegree attribute of nodes is used as a counter for the number of edges in the Grafo.
    This allows the correct updating of the numbers of edges in the Grafo being directed or not.
*/
void Grafo::insereNo(int id)
{

}

void Grafo::insereAresta(int id, int id_alvo, float peso)
{


}

void Grafo::removeNo(int id){

}

bool Grafo::buscaNo(int id)
{

}

No *Grafo::getNo(int id)
{


}


//Function that verifies if there is a path between two nodes
bool Grafo::profundidadePrimeiraBusca(int initialId, int targetId){

}


void Grafo::amplitudePrimeiraBusca(ofstream &output_file){

}


Grafo *Grafo::getComplemento(){

}


//A function that returns a subjacent of a directed Grafo, which is a Grafo which the arcs have opposite directions to the original Grafo
Grafo* Grafo::getSubjacente(){

}

bool Grafo::GrafoConectado(){

}



bool Grafo::PossuiCiclo(){

}



float** Grafo::floydMarshall(){

}



float* Grafo::dijkstra(int id){

}
