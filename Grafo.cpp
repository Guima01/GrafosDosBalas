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
    for (list<No>::iterator it = vertices->begin(); it != vertices->end(); ++it)
    {
        if(it->getId()==posicao)
        {
            listaVertices = auxProfundidade(listaVertices,it->getId(),cont);
            No *aux;
            if(it->getProximoNo() != 0)  //existe o no;
            {
                aux = new No(it->getProximoNo()->getId());
                if(it->getProximoNo()->getProximoNo() != 0){
                    aux->setProximoNo(it->getProximoNo()->getProximoNo());
                }
                cout<<"AA"<<aux->getId()<<endl;
                if(aux->getProximoNo() != 0){
                cout<<"BB"<<aux->getProximoNo()->getId()<<endl;
                }
            }
            if(*cont == ordemGrafo)
            {
                break;
            }
            while(true)
            {
                int i=0;
                for (vector<int>::iterator it = listaVertices.begin(); it != listaVertices.end(); ++it)
                {
                    cout<<i<<endl;
                    if(aux->getId()==it[i])
                    {
                        if(aux->getProximoNo()==0)
                        {
                            return listaVertices;
                        }
                        aux->setId(aux->getProximoNo()->getId());
                        cout<<"CC"<<aux->getId()<<endl;
                        if(aux->getProximoNo()->getProximoNo() != 0){
                            aux->setProximoNo(aux->getProximoNo()->getProximoNo());
                            cout<<"DD"<<aux->getProximoNo()->getId()<<endl;
                        }
                        else{
                            aux->setProximoNo(nullptr);
                        }
                        break;
                    }
                    i++;

                    if(i == listaVertices.size()-1)
                    {
                        listaVertices = profundidadePrimeiraBusca(listaVertices,ordemGrafo,aux->getId(),cont);
                        break;
                    }
                }
            }
            //cout<<"A"<<aux->getId()<<endl;
         //   listaVertices = profundidadePrimeiraBusca(listaVertices,ordemGrafo,aux->getId(),cont);
        }
    }


    return listaVertices;
}


vector<int> Grafo::auxProfundidade(vector<int>listaVertices,int idNo,int *cont)
{

    int i=0;

    for (vector<int>::iterator it = listaVertices.begin(); it != listaVertices.end(); ++it)
    {
        if(idNo == it[i])
        {
            return listaVertices;
        }
        i++;
    }
    //cout<<idNo<<endl;

    listaVertices[*cont]=idNo;
    *cont = *cont +1;
    return listaVertices;
}
/*        cout<<it->getId()<<endl;
        aux->setId(it->getProximoNo()->getId());
        aux->setProximoNo(it->getProximoNo());
        cout<<aux->getId()<<endl;
        // cout<<it->getId()<<endl;

        while(aux->getProximoNo()->getProximoNo() )
        {
            //cout<<"AAAA"<<aux->getId()<<endl;
            aux->setId(aux->getProximoNo()->getId());
            aux->setProximoNo(aux->getProximoNo()->getProximoNo());
            cout<<aux->getProximoNo()->getId()<<endl;
        }

        /* if(it->getId() == targetId)
         {
             cout<<"No encontrado"<<endl;
             //delete aux;
             //return true;
         }
         else
         {
             aux = it->getProximoNo();
             while( aux )
             {
                 /*if(aux->getId() == targetId)
                 {
                     cout<<"No encontrado"<<endl;
                     //delete aux;
                     //return true;
                 }
                 else{/
                     cout<<aux->getId()<<endl;
                     aux = aux->getProximoNo();
                 }

             }
    }
    delete aux;
    return true;*/




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
