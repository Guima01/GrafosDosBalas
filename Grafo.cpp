#include "Grafo.h"
#include "No.h"
#include "Aresta.h"
#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <list>
#include <vector>
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
Grafo::Grafo(int ordem)
{

    this->vertices = new list<No>[ordem];
    this->ordem = ordem;
//    this->direcao = direcao;
//    this->aresta_ponderada = aresta_ponderada;
//    this->no_ponderado = no_ponderado;
    this->primeiro_no = this->ultimo_no = nullptr;
    this->numero_arestas = 0;
}

// Destructor
Grafo::~Grafo()
{

//    while (proximo_no != nullptr)
//    {
//
//        proximo_no->removeTodasArestas();
//        No *no_aux = proximo_no->getProximoNo();
//        delete proximo_no;
//        proximo_no = no_aux;
//    }
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

//bool Grafo::getDirecao()
//{
//
//    return this->direcao;
//}

//bool Grafo::getArestaPonderada()
//{
//
//    return this->aresta_ponderada;
//}

//bool Grafo::getNoPonderado()
//{
//
//    return this->no_ponderado;
//}

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

void Grafo::criaLista(int ordem)
{

    for(int vertice = 0;  vertice < ordem; vertice ++)
    {
        int x = vertice;
        No *no = new No(vertice);
        this->vertices->push_back(*no);
    }

    cout<<endl;
    cout<<vertices->size()<<endl;



}

void Grafo::insereNo(int idNoFonte, int idNoAlvo)
{
    int checkNo = 0;
    for (list<No>::iterator it = vertices->begin(); it != vertices->end(); ++it)
    {
//        cout<<it->getId();
//        cout<<" ";
//        cout<<idNoFonte;
//        cout<<" ";
//        cout<<idNoAlvo<<endl;
        if(idNoFonte == it->getId())
        {
            if(!it->getProximoNo())
            {
                No *proximoNo = new No(idNoAlvo);
                it->setProximoNo(proximoNo);
            }
            else if(it->getProximoNo())
            {
                No *proximoNo = new No(idNoAlvo);
                No *aux = new No(it->getId());
                aux->setProximoNo(it->getProximoNo());
                while(aux->getProximoNo()->getProximoNo())
                {
                    aux->setId(aux->getProximoNo()->getId());
                    aux->setProximoNo(aux->getProximoNo()->getProximoNo());

                }
                aux->getProximoNo()->setProximoNo(proximoNo);
                checkNo = checkNo + 1;
                delete aux;
            }
        }
        else if(idNoAlvo == it->getId())
        {
//            cout<<it->getId();
//            cout<<" ";
//            cout<<idNoAlvo;
//            cout<<" ";
//            cout<<idNoFonte<<endl;

            if(!it->getProximoNo())
            {
                No *proximoNo = new No(idNoFonte);
                it->setProximoNo(proximoNo);
            }
            else if(it->getProximoNo())
            {
                No *proximoNo = new No(idNoFonte);
                No *aux = new No(it->getId());
                aux->setProximoNo(it->getProximoNo());
                while(aux->getProximoNo()->getProximoNo())
                {
                    aux->setId(aux->getProximoNo()->getId());
                    aux->setProximoNo(aux->getProximoNo()->getProximoNo());
                }
                aux->getProximoNo()->setProximoNo(proximoNo);
                checkNo = checkNo + 1;
                delete aux;
            }
        }
        else if(checkNo == 2)
        {
            break;
        }
    }
}


void Grafo::insereAresta(int id, int id_alvo, float peso)
{


}

void Grafo::removeNo(int id)
{

}

bool Grafo::buscaNo(int id)
{

}

No *Grafo::getNo(int id)
{


}


//Function that verifies if there is a path between two nodes
bool Grafo::profundidadePrimeiraBusca(int initialId, int targetId)
{

}


void Grafo::amplitudePrimeiraBusca(ofstream &output_file)
{

}


Grafo *Grafo::getComplemento()
{

}


//A function that returns a subjacent of a directed Grafo, which is a Grafo which the arcs have opposite directions to the original Grafo
Grafo* Grafo::getSubjacente()
{

}

bool Grafo::GrafoConectado()
{

}



bool Grafo::PossuiCiclo()
{

}



float** Grafo::floydMarshall()
{

}



float* Grafo::dijkstra(int id)
{

}
