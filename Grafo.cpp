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
#include <queue>

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
        if(vertice == 0)
        {
            primeiro_no = no;
        }
    }

}

void Grafo::insereNo(int idNoFonte, int idNoAlvo)
{
    Aresta *aresta = new Aresta(idNoAlvo,idNoFonte);
    int checkNo = 0;
    bool checkNoRepetido = false;
    for (list<No>::iterator it = vertices->begin(); it != vertices->end(); ++it)
    {
        if(idNoFonte == it->getId())
        {
            if(!it->getProximoNo())
            {

                No *proximoNo = new No(idNoAlvo);
                it->setProximoNo(proximoNo);
                it->insereAresta(aresta);
                numero_arestas = numero_arestas + 1;
            }
            else if(it->getProximoNo())
            {
                if(it->getProximoNo()->getId() == idNoAlvo)
                {
                    break;
                }
                No *proximoNo = new No(idNoAlvo);
                No *aux = new No(it->getId());
                aux->setProximoNo(it->getProximoNo());
                while(aux->getProximoNo()->getProximoNo())
                {
                    if(aux->getProximoNo()->getProximoNo()->getId() == idNoAlvo)
                    {
                        checkNoRepetido = true;
                        break;
                    }
                    aux->setId(aux->getProximoNo()->getId());
                    aux->setProximoNo(aux->getProximoNo()->getProximoNo());

                }
                if(checkNoRepetido == true)
                {
                    break;
                }
                aux->getProximoNo()->setProximoNo(proximoNo);
                aux->getProximoNo()->insereAresta(aresta);
                checkNo = checkNo + 1;
                numero_arestas = numero_arestas + 1;
                delete aux;
            }
        }
        else if(idNoAlvo == it->getId())
        {
            if(!it->getProximoNo())
            {
                No *proximoNo = new No(idNoFonte);
                it->setProximoNo(proximoNo);
                it->insereAresta(aresta);

            }
            else if(it->getProximoNo())
            {
                if(it->getProximoNo()->getId() == idNoFonte)
                {
                    break;
                }
                No *proximoNo = new No(idNoFonte);
                No *aux = new No(it->getId());
                aux->setProximoNo(it->getProximoNo());
                while(aux->getProximoNo()->getProximoNo())
                {
                    if(aux->getProximoNo()->getProximoNo()->getId() == idNoFonte)
                    {
                        checkNoRepetido = true;
                        break;
                    }
                    aux->setId(aux->getProximoNo()->getId());
                    aux->setProximoNo(aux->getProximoNo()->getProximoNo());
                }
                if(checkNoRepetido == true)
                {
                    break;
                }
                aux->getProximoNo()->setProximoNo(proximoNo);
                aux->getProximoNo()->insereAresta(aresta);
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
vector<int> Grafo::profundidadePrimeiraBusca(vector<int> listaVertices,int ordemGrafo, int posicao,int *cont)
{
    if(posicao >= ordemGrafo)
    {
        cout<<endl;
        cout<<"No invalido"<<endl<<endl;
        return listaVertices;
    }
    for (list<No>::iterator it = vertices->begin(); it != vertices->end(); ++it)
    {
        if(it->getId()==posicao)
        {
            cout<<"Vertice atual "<<it->getId()<<endl;
            listaVertices = auxBusca(listaVertices,it->getId(),cont);
            No *aux;
            if(it->getProximoNo() != 0)  //existe o no;
            {
                aux = new No(it->getProximoNo()->getId());
                if(it->getProximoNo()->getProximoNo() != 0)
                {
                    aux->setProximoNo(it->getProximoNo()->getProximoNo());
                }
            }
            if(*cont == ordemGrafo)
            {
                delete aux;
                return listaVertices;
            }
            int verticeAtual = it->getId();
            while(true)
            {
                int i=0;
                for (vector<int>::iterator it = listaVertices.begin(); it != listaVertices.end(); ++it)
                {

                    if(aux->getId()==listaVertices[i])
                    {
                        if(aux->getProximoNo()==0)
                        {
                            return listaVertices;
                        }
                        aux->setId(aux->getProximoNo()->getId());

                        if(aux->getProximoNo()->getProximoNo() != 0)
                        {
                            aux->setProximoNo(aux->getProximoNo()->getProximoNo());
                        }
                        else
                        {
                            aux->setProximoNo(nullptr);
                        }
                        break;
                    }
                    i++;

                    if(i == listaVertices.size())
                    {
                        listaVertices = profundidadePrimeiraBusca(listaVertices,ordemGrafo,aux->getId(),cont);
                        cout<<"retornou para o vertice: "<<verticeAtual<<endl;

                        if(*cont == ordemGrafo)
                        {
                            delete aux;
                            return listaVertices;
                        }
                        break;
                    }
                }
            }

        }
    }
}


vector<int> Grafo::auxBusca(vector<int>listaVertices,int idNo,int *cont)
{

    int i=0;

    for (vector<int>::iterator it = listaVertices.begin(); it != listaVertices.end(); ++it)
    {
        if(idNo == listaVertices[i])
        {
            if(*cont == 0)
            {
                *cont = *cont + 1;
            }
            return listaVertices;
        }
        i++;
    }
    listaVertices[*cont]=idNo;
    *cont = *cont +1;
    return listaVertices;
}


vector<int> Grafo::amplitudePrimeiraBusca(queue<int>*filaVertices,int idNo, vector<int>verticesVisitados, int *cont)
{
    if(idNo >= ordem)
    {
        cout<<endl;
        cout<<"No invalido"<<endl<<endl;
        return verticesVisitados;
    }
    for (list<No>::iterator it = vertices->begin(); it != vertices->end(); ++it)
    {
        if(it->getId() == idNo)
        {
            //cout<<"Visitando vertice"<<it->getId()<<endl;
            filaVertices->pop();
            verticesVisitados = auxBusca(verticesVisitados,it->getId(),cont);
            No *aux;
            if(it->getProximoNo() != 0)  //existe o no;
            {
                aux = new No(it->getProximoNo()->getId());
                if(it->getProximoNo()->getProximoNo() != 0)
                {
                    aux->setProximoNo(it->getProximoNo()->getProximoNo());
                }
            }
            if(*cont == ordem)
            {
                delete aux;
                return verticesVisitados;
            }

            int verticeAtual = it->getId();

            do
            {
                int i = 0;
                for (vector<int>::iterator it = verticesVisitados.begin(); it != verticesVisitados.end(); ++it)
                {

                    if(aux->getId() == verticesVisitados[i])
                    {
                        break;
                    }
                    i++;
                    if(i == verticesVisitados.size())
                    {
                        filaVertices->push(aux->getId());
                        verticesVisitados = auxBusca(verticesVisitados,aux->getId(),cont);
                        cout<<"Visitando vertice "<<aux->getId()<<endl;
                        break;
                    }
                }
                if(aux->getProximoNo() == 0)
                {
                    break;
                }
                else
                {
                    aux->setId(aux->getProximoNo()->getId());
                    if(aux->getProximoNo()->getProximoNo() != 0)
                    {
                        aux->setProximoNo(aux->getProximoNo()->getProximoNo());
                    }
                    else
                    {
                        aux->setProximoNo(nullptr);
                    }
                }
            }
            while(true);

            bool check = false;
            while(!filaVertices->empty())
            {
                int atual = filaVertices->front();
                verticesVisitados = amplitudePrimeiraBusca(filaVertices, filaVertices->front(), verticesVisitados, cont);
            }
            delete aux;
            return verticesVisitados;
        }
    }

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
