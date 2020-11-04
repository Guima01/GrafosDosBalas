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
 * Definindo os métodos do Grafo
**************************************************************************************************/

// Construtor
Grafo::Grafo(int ordem)
{

    this->vertices = new list<No>[ordem];
    this->ordem = ordem;
    //    this->direcao = direcao;
    //    this->aresta_ponderada = aresta_ponderada;
    //    this->no_ponderado = no_ponderado;
    this->primeiro_no = this->ultimo_no = nullptr;
    this->numero_arestas = 0;
    this->grau_medio_grafo = 0;
}

// Destrutor
Grafo::~Grafo()
{
    for (list<No>::iterator it = vertices->begin(); it != vertices->end(); ++it)
    {
        No *aux;
        No *auxDelete;
        aux->setProximoNo(it->getProximoNo());
        auxDelete->setProximoNo(it->getProximoNo());
        while (aux->getProximoNo()->getProximoNo() != 0)
        {
            aux->setProximoNo(aux->getProximoNo()->getProximoNo());
            delete auxDelete->getProximoNo();
            auxDelete->setProximoNo(aux->getProximoNo());
        }
        delete aux->getProximoNo();
        delete aux;
        delete auxDelete;
    }
}

// Getters

//retorna a ordem do Grafo
int Grafo::getOrdem()
{

    return this->ordem;
}

//retorna o número de arestas no Grafo
int Grafo::getNumeroArestas()
{

    return this->numero_arestas;
}

//retorna o Grau médio do Grafo

float Grafo::getGrauMedioGrafo()
{

    float grau = 0;
    for (list<No>::iterator it = vertices->begin(); it != vertices->end(); ++it)
    {
        grau = grau + it->getGrau();
    }
    this->grau_medio_grafo = grau / this->getOrdem();
    return this->grau_medio_grafo;
}

//calcula a frequência relativa para os graus presentes no grafo
//parâmetros: arquivo de saída e ordem do Grafo

void Grafo::getFrequenciaRelativa(ofstream &arquivo_saida, int ordem)
{
    int *vetorGraus;
    vetorGraus = (int *)malloc(ordem * sizeof(int));
    int grau = 0;
    float freqRel = 0;
    for (int i = 0; i < ordem; i++)
    {
        vetorGraus[i] = 0;
    }
    for (list<No>::iterator it = vertices->begin(); it != vertices->end(); ++it)
    {
        vetorGraus[it->getGrau()] = vetorGraus[it->getGrau()] + 1;
    }
    for(int i = 0; i < ordem; i++)
    {
        if(vetorGraus[i] != 0)
        {
            arquivo_saida << "Frequencia Relativa de grau " << i << " : " << (float)vetorGraus[i]/this->getOrdem() << "\n";
        }
    }
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

/*No *Grafo::getPrimeiroNo()
{

    return this->primeiro_no;
}

No *Grafo::getUltimoNo()
{

    return this->ultimo_no;
}*/


//cria a lista com o tamanho de vértices do grafo
//parâmetro: ordem do Grafo
void Grafo::criaLista(int ordem)
{

    for (int vertice = 0; vertice < ordem; vertice++)
    {
        int x = vertice;
        No *no = new No(vertice);
        this->vertices->push_back(*no);
        if (vertice == 0)
        {
            primeiro_no = no;
        }
    }
}

// insere os nós adjacentes a lista de vértice
void Grafo::insereNo(int idNoFonte, int idNoAlvo,float peso)
{
    bool checkAresta = false;
    Aresta *aresta = new Aresta(idNoAlvo, idNoFonte);
    int checkNo = 0;
    bool checkNoRepetido = false;
    for (list<No>::iterator it = vertices->begin(); it != vertices->end(); ++it)
    {

        // insere o nó na lista de adjacência
        if (idNoFonte == it->getId())
        {
            if (!it->getProximoNo())
            {
                No *proximoNo = new No(idNoAlvo);
                it->setProximoNo(proximoNo);
                it->getProximoNo()->setAresta(aresta);
                it->getProximoNo()->getAresta()->setPeso(peso);
                it->setGrau();
                if (checkAresta == false)
                {
                    numero_arestas = numero_arestas + 1;
                    checkAresta = true;
                }
            }
            else if (it->getProximoNo())
            {
                if (it->getProximoNo()->getId() == idNoAlvo)
                {
                    break;
                }
                No *proximoNo = new No(idNoAlvo);
                No *aux = new No(it->getId());
                aux->setProximoNo(it->getProximoNo());
                while (aux->getProximoNo()->getProximoNo())
                {
                    if (aux->getProximoNo()->getProximoNo()->getId() == idNoAlvo)
                    {
                        checkNoRepetido = true;
                        break;
                    }
                    aux->setId(aux->getProximoNo()->getId());
                    aux->setProximoNo(aux->getProximoNo()->getProximoNo());
                }
                if (checkNoRepetido == true)
                {
                    break;
                }
                aux->getProximoNo()->setProximoNo(proximoNo);
                aux->getProximoNo()->getProximoNo()->setAresta(aresta);
                aux->getProximoNo()->getProximoNo()->getAresta()->setPeso(peso);
                checkNo = checkNo + 1;
                it->setGrau();
                if (checkAresta == false)
                {
                    numero_arestas = numero_arestas + 1;
                    checkAresta = true;
                }
                delete aux;
            }
        }

        //também insere o nó na lista de adjacência, porém na posição do outro ID

        else if (idNoAlvo == it->getId())
        {
            if (!it->getProximoNo())
            {
                No *proximoNo = new No(idNoFonte);
                it->setProximoNo(proximoNo);
                it->getProximoNo()->setAresta(aresta);
                it->getProximoNo()->getAresta()->setPeso(peso);
                it->setGrau();

                if (checkAresta == false)
                {
                    numero_arestas = numero_arestas + 1;
                    checkAresta = true;
                }
            }
            else if (it->getProximoNo())
            {
                if (it->getProximoNo()->getId() == idNoFonte)
                {
                    break;
                }
                No *proximoNo = new No(idNoFonte);
                No *aux = new No(it->getId());
                aux->setProximoNo(it->getProximoNo());
                while (aux->getProximoNo()->getProximoNo())
                {
                    if (aux->getProximoNo()->getProximoNo()->getId() == idNoFonte)
                    {
                        checkNoRepetido = true;
                        break;
                    }
                    aux->setId(aux->getProximoNo()->getId());
                    aux->setProximoNo(aux->getProximoNo()->getProximoNo());
                }
                if (checkNoRepetido == true)
                {
                    break;
                }
                aux->getProximoNo()->setProximoNo(proximoNo);
                aux->getProximoNo()->getProximoNo()->setAresta(aresta);
                aux->getProximoNo()->getProximoNo()->getAresta()->setPeso(peso);
                checkNo = checkNo + 1;
                it->setGrau();
                if (checkAresta == false)
                {
                    numero_arestas = numero_arestas + 1;
                    checkAresta = true;
                }
                delete aux;
            }
        }
        else if (checkNo == 2)
        {
            break;
        }
    }
}
/*
void Grafo::insereAresta(int id, int id_alvo, float peso)
{
}
*/
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
vector<int> Grafo::profundidadePrimeiraBusca(vector<int> listaVertices, int ordemGrafo, int posicao, int *cont)
{
    if (posicao >= ordemGrafo)
    {
        cout << endl;
        cout << "No invalido" << endl
             << endl;
        return listaVertices;
    }
    for (list<No>::iterator it = vertices->begin(); it != vertices->end(); ++it)
    {
        if (it->getId() == posicao)
        {
            cout << "Vertice atual " << it->getId() << endl;
            listaVertices = auxBusca(listaVertices, it->getId(), cont);
            No *aux;
            if (it->getProximoNo() != 0) //existe o no;
            {
                aux = new No(it->getProximoNo()->getId());
                if (it->getProximoNo()->getProximoNo() != 0)
                {
                    aux->setProximoNo(it->getProximoNo()->getProximoNo());
                }
            }
            if (*cont == ordemGrafo)
            {
                delete aux;
                return listaVertices;
            }
            int verticeAtual = it->getId();
            while (true)
            {
                int i = 0;
                for (vector<int>::iterator it = listaVertices.begin(); it != listaVertices.end(); ++it)
                {

                    if (aux->getId() == listaVertices[i])
                    {
                        if (aux->getProximoNo() == 0)
                        {
                            return listaVertices;
                        }
                        aux->setId(aux->getProximoNo()->getId());

                        if (aux->getProximoNo()->getProximoNo() != 0)
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

                    if (i == listaVertices.size())
                    {
                        listaVertices = profundidadePrimeiraBusca(listaVertices, ordemGrafo, aux->getId(), cont);
                        cout << "retornou para o vertice: " << verticeAtual << endl;

                        if (*cont == ordemGrafo)
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

vector<int> Grafo::auxBusca(vector<int> listaVertices, int idNo, int *cont)
{

    int i = 0;

    for (vector<int>::iterator it = listaVertices.begin(); it != listaVertices.end(); ++it)
    {
        if (idNo == listaVertices[i])
        {
            if (*cont == 0)
            {
                *cont = *cont + 1;
            }
            return listaVertices;
        }
        i++;
    }
    listaVertices[*cont] = idNo;
    *cont = *cont + 1;
    return listaVertices;
}

vector<int> Grafo::amplitudePrimeiraBusca(queue<int> *filaVertices, int idNo, vector<int> verticesVisitados, int *cont)
{
    if (idNo >= ordem)
    {
        cout << endl;
        cout << "No invalido" << endl
             << endl;
        return verticesVisitados;
    }
    for (list<No>::iterator it = vertices->begin(); it != vertices->end(); ++it)
    {
        if (it->getId() == idNo)
        {
            //cout<<"Visitando vertice"<<it->getId()<<endl;
            filaVertices->pop();
            verticesVisitados = auxBusca(verticesVisitados, it->getId(), cont);
            No *aux;
            if (it->getProximoNo() != 0) //existe o no;
            {
                aux = new No(it->getProximoNo()->getId());
                if (it->getProximoNo()->getProximoNo() != 0)
                {
                    aux->setProximoNo(it->getProximoNo()->getProximoNo());
                }
            }
            if (*cont == ordem)
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

                    if (aux->getId() == verticesVisitados[i])
                    {
                        break;
                    }
                    i++;
                    if (i == verticesVisitados.size())
                    {
                        filaVertices->push(aux->getId());
                        verticesVisitados = auxBusca(verticesVisitados, aux->getId(), cont);
                        cout << "Visitando vertice " << aux->getId() << endl;
                        break;
                    }
                }
                if (aux->getProximoNo() == 0)
                {
                    break;
                }
                else
                {
                    aux->setId(aux->getProximoNo()->getId());
                    if (aux->getProximoNo()->getProximoNo() != 0)
                    {
                        aux->setProximoNo(aux->getProximoNo()->getProximoNo());
                    }
                    else
                    {
                        aux->setProximoNo(nullptr);
                    }
                }
            }
            while (true);

            bool check = false;
            while (!filaVertices->empty())
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
Grafo *Grafo::getSubjacente()
{
}

bool Grafo::GrafoConectado()
{
}

bool Grafo::PossuiCiclo()
{
}

float **Grafo::floydMarshall()
{
}

float *Grafo::dijkstra(int id)
{
}



vector<No>Grafo::retornaListaOrdenada()
{

    vector<No> vetorOrdenado;
    No *aux;

    for(list<No>::iterator it = vertices->begin(); it != vertices->end(); ++it)
    {
        if(it->getProximoNo()!=0)
        {

            if(it->getProximoNo()->getAresta()->getVerificaAresta()!=true)
            {
                vetorOrdenado.push_back(*it->getProximoNo());
                it->getProximoNo()->getAresta()->setVerificaAresta();
            }

            aux = new No(it->getProximoNo()->getId());
            aux->setAresta(it->getProximoNo()->getAresta());
            aux->setProximoNo(it->getProximoNo()->getProximoNo());

            while(aux->getProximoNo()!= 0)
            {

                if(aux->getAresta()->getVerificaAresta()!=true)
                {
                    aux->getAresta()->setVerificaAresta();
                    vetorOrdenado.push_back(*aux);
                }

                aux->setId(aux->getProximoNo()->getId());
                aux->setAresta(aux->getProximoNo()->getAresta());
                if(!(aux->getProximoNo()->getProximoNo() !=0))
                {

                    if(aux->getProximoNo()->getAresta()->getVerificaAresta()!=true)
                    {
                        aux->getProximoNo()->getAresta()->setVerificaAresta();
                        vetorOrdenado.push_back(*aux->getProximoNo());
                    }
                }
                aux->setProximoNo(aux->getProximoNo()->getProximoNo());
            }
        }
    }

    No ordenar = 0;
    for(int i = 0 ; i< vetorOrdenado.size()-1; i++)
    {
        for(int j = i + 1; j < vetorOrdenado.size(); j++)
        {
            if(vetorOrdenado[i].getAresta()->getPeso() > vetorOrdenado[j].getAresta()->getPeso())
            {
                ordenar = vetorOrdenado[i];
                vetorOrdenado[i] = vetorOrdenado[j];
                vetorOrdenado[j] = ordenar;
            }
        }
    }

    for(int i=0; i<vetorOrdenado.size() ; i++)
    {
        cout<<vetorOrdenado[i].getAresta()->getIdAlvo() << " | " << vetorOrdenado[i].getAresta()->getIdOrigem()<<" Peso:";
        cout<< vetorOrdenado[i].getAresta()->getPeso()<<endl;
    }
    cout<<endl;
    return vetorOrdenado;
}
vector<No>Grafo::algoritmoPrim()
{
    vector<No> vetArestaOrdenado = retornaListaOrdenada();
    vector<No> vetPrim;
    vector<No> vetProx;
    No *flag = new No(-2);
    int contador;
    vetPrim.push_back(vetArestaOrdenado[0]);

    float peso1,peso2,peso3;
    for(list<No>::iterator it = vertices->begin(); it != vertices->end(); ++it)
    {

        while(true)
        {
            peso1 = ehAdjacente(vetPrim[0].getAresta()->getIdOrigem(),it->getId());
            peso2 = ehAdjacente(vetPrim[0].getAresta()->getIdAlvo(),it->getId());
            cout<<vetPrim[0].getAresta()->getIdOrigem()<<" " << it->getId()<<" Peso1:"<<peso1<<endl;
            cout<<vetPrim[0].getAresta()->getIdAlvo()<<" " << it->getId()<<" Peso2:"<<peso2<<endl;

            if(peso1!=0)
            {
                if(peso2==0)
                {
                    vetProx = auxAlgoritmoPrim(vetProx,it->getId(),vetPrim[0].getAresta()->getIdOrigem());

                    cout<<"Peso1M:"<<vetProx.back().getAresta()->getIdAlvo();
                    cout<<" "<<vetProx.back().getAresta()->getIdOrigem()<<endl;
                    break;
                }
                else
                {
                    if(peso1<=peso2)
                    {
                        vetProx = auxAlgoritmoPrim(vetProx,it->getId(),vetPrim[0].getAresta()->getIdOrigem());

                        cout<<"Peso1MM:"<<vetProx.back().getAresta()->getIdAlvo();
                        cout<<" "<<vetProx.back().getAresta()->getIdOrigem()<<endl;
                        break;
                    }
                    else
                    {
                        vetProx = auxAlgoritmoPrim(vetProx,it->getId(),vetPrim[0].getAresta()->getIdAlvo());

                        cout<<"Peso2M:"<<vetProx.back().getAresta()->getIdAlvo();
                        cout<<" "<<vetProx.back().getAresta()->getIdOrigem()<<endl;
                        break;
                    }
                }
            }
            else
            {
                if(peso2!=0)
                {
                    vetProx = auxAlgoritmoPrim(vetProx,it->getId(),vetPrim[0].getAresta()->getIdAlvo());

                    cout<<"Peso2MM:"<<vetProx.back().getAresta()->getIdAlvo();
                    cout<<" "<<vetProx.back().getAresta()->getIdOrigem()<<endl;
                    break;
                }
                else
                {
                    vetProx = auxAlgoritmoPrim(vetProx, -1,-1);
                    cout<<vetProx.back().getId()<<endl;
                    break;
                }
            }

        }
        cout<<endl;
        cout<<endl;

    }

    vetProx[vetArestaOrdenado[0].getAresta()->getIdAlvo()] = *flag;
    vetProx[vetArestaOrdenado[0].getAresta()->getIdOrigem()] = *flag;
    contador =0;

    /*  for(int i=0; i<vetProx.size(); i++)
      {
          if(vetProx[i].getId() != -1 && vetProx[i].getId()!= -2)
              cout<<vetProx[i].getAresta()->getIdAlvo() << " | " << vetProx[i].getAresta()->getIdOrigem()<<endl;
          else
          {
              if(vetProx[i].getId() == -1)
              {
                  cout<<"Custo infinito"<<endl;
              }
              else
              {
                  cout<<"Ja visitado"<<endl;
              }
          }

      }
    */
    int indiceMinimo=0;
    while(contador<getOrdem()-2)
    {
        cout<<endl<<"CONTADOR"<<contador<<endl;

        indiceMinimo = getIndiceMin(vetProx);
        if(indiceMinimo>=0)
        {
            vetPrim.push_back(vetProx[indiceMinimo]);
            vetProx[indiceMinimo] = *flag;
        }
        for(int i=0; i < vetProx.size(); i++)
        {

            if(vetProx[i].getId() != -2)
            {
                if(vetProx[i].getId()== -1)
                {

                    peso1 = ehAdjacente(i,vetPrim.back().getAresta()->getIdAlvo());
                    peso2 = ehAdjacente(i,vetPrim.back().getAresta()->getIdOrigem());
                    cout<<"OK AMIGO"<<peso1<<" "<<peso2<<endl;

                    if(peso1 == 0)
                    {
                        if(peso2!=0)
                        {
                            vetProx[i] = getNoListaOrdenada(vetArestaOrdenado,vetProx[i].getId(),vetPrim.back().getAresta()->getIdOrigem(),i);
                            cout<<"ESTA1 "<< vetProx[i].getAresta()->getIdAlvo() << " " << vetProx[i].getAresta()->getIdOrigem()<<endl;
                        }
                    }
                    else
                    {
                        if(peso2==0)
                        {

                            vetProx[i] = getNoListaOrdenada(vetArestaOrdenado,vetProx[i].getId(),vetPrim.back().getAresta()->getIdAlvo(),i);
                            cout<<"ESTA2 "<< vetProx[i].getAresta()->getIdAlvo() << " " << vetProx[i].getAresta()->getIdOrigem()<<endl;
                            break;
                        }
                        else
                        {
                            if(peso1<=peso2)
                            {
                                vetProx[i] = getNoListaOrdenada(vetArestaOrdenado,vetProx[i].getId(),vetPrim.back().getAresta()->getIdAlvo(),i);
                                cout<<"ESTA3 "<< vetProx[i].getAresta()->getIdAlvo() << " " << vetProx[i].getAresta()->getIdOrigem()<<endl;
                            }
                            else{
                                vetProx[i] = getNoListaOrdenada(vetArestaOrdenado,vetProx[i].getId(),vetPrim.back().getAresta()->getIdOrigem(),i);
                            }
                        }
                    }

                }
                else
                {
                    cout<<"SJASIODJASODSAJDJSADIOSAJDIOJSADIOJSA ";
                    cout<<i<<endl<<endl;
                    cout<<"VETPROXIMO "<<vetProx[i].getAresta()->getIdAlvo()<<" "<<vetProx[i].getAresta()->getIdOrigem()<<endl;

                    cout<<vetPrim.back().getAresta()->getIdAlvo()<<endl;
                    cout<<vetPrim.back().getAresta()->getIdOrigem()<<endl;
                    cout<<vetPrim.back().getId()<<endl<<endl;


                    peso1 = ehAdjacente(i,vetPrim.back().getAresta()->getIdAlvo());
                    peso2 = vetProx[i].getAresta()->getPeso();
                    cout<<peso1<<" "<<peso2<<endl;
                    if(peso1 == 0)
                    {
                        if(peso2!=0)
                        {
                            vetProx[i] = getNoListaOrdenada(vetArestaOrdenado,vetProx[i].getAresta()->getIdAlvo(),vetPrim.back().getAresta()->getIdOrigem(),i);

                        }
                    }
                    else
                    {
                        if(peso2==0)
                        {
                            vetProx[i] = getNoListaOrdenada(vetArestaOrdenado,vetProx[i].getAresta()->getIdAlvo(),vetPrim.back().getAresta()->getIdAlvo(),i);

                        }
                        else
                        {
                            if(peso1<=peso2)
                            {
                                vetProx[i] = getNoListaOrdenada(vetArestaOrdenado,vetProx[i].getAresta()->getIdAlvo(),vetPrim.back().getAresta()->getIdAlvo(),i);

                            }
                            else
                            {
                                vetProx[i] = getNoListaOrdenada(vetArestaOrdenado,vetProx[i].getAresta()->getIdAlvo(),vetPrim.back().getAresta()->getIdOrigem(),i);

                            }
                        }
                    }

                }
            }


        }
        contador = contador+1;
    }
    cout<<endl<<endl;
    cout<<"IRMAO SE DEU CERTO NOIS É BALA"<<endl;
    for(int i=0; i<vetPrim.size(); i++)
    {
        cout<<vetPrim[i].getAresta()->getIdAlvo() << " | " << vetPrim[i].getAresta()->getIdOrigem()<<endl;

    }


}
//-1 = INFINITO , -2 = VISITADO

No Grafo::getNoListaOrdenada(vector<No>vetOrdenado,No noAtual, No noAlvo,float peso)
{
    cout<<"================="<<endl;
    cout<<"NO ATUAL:"<<noAtual.getId() << " NO ALVO :"<<noAlvo.getId()<<" PESO:"<<peso<<endl;
    cout<<"================="<<endl;
    for(int i=0; i<vetOrdenado.size() ; i++)
    {
        cout<<vetOrdenado[i].getAresta()->getIdAlvo() << " | " << vetOrdenado[i].getAresta()->getIdOrigem()<<" Peso:";
        cout<< vetOrdenado[i].getAresta()->getPeso()<<endl;
    }
    cout<<"===========-=-=-=--=-=-=-=-=-=-=--="<<endl;
    for(int i=0; i< vetOrdenado.size(); i++)
    {
        if(noAtual.getId() == -1)
        {

            if(peso == vetOrdenado[i].getAresta()->getIdOrigem())
            {
                if(vetOrdenado[i].getAresta()->getIdAlvo() == noAlvo.getId())
                {

                    return vetOrdenado[i];
                }
            }


        }
        else
        {

            if(vetOrdenado[i].getAresta()->getIdOrigem() == peso )
            {

                if(vetOrdenado[i].getAresta()->getIdOrigem() == noAlvo.getId() || vetOrdenado[i].getAresta()->getIdAlvo() == noAlvo.getId())
                {
                    cout<<vetOrdenado[i].getAresta()->getIdAlvo() << " " << vetOrdenado[i].getAresta()->getIdOrigem()<<endl;
                    return vetOrdenado[i];
                }
            }
            else
            {
                if(vetOrdenado[i].getAresta()->getIdAlvo() == peso)
                {
                    if(vetOrdenado[i].getAresta()->getIdOrigem() == noAlvo.getId() || vetOrdenado[i].getAresta()->getIdAlvo() == noAlvo.getId())
                    {
                        cout<<vetOrdenado[i].getAresta()->getIdAlvo() << " " << vetOrdenado[i].getAresta()->getIdOrigem()<<endl;
                        return vetOrdenado[i];
                    }
                }
            }
        }

    }



}
int Grafo::getIndiceMin(vector<No>Prim)
{

    for(int i=0; i<Prim.size(); i++)
    {
        if(Prim[i].getId() != -1 && Prim[i].getId()!=-2)
            cout<<Prim[i].getAresta()->getIdAlvo() << " | " << Prim[i].getAresta()->getIdOrigem()<<endl;
        else
        {
            if(Prim[i].getId()== -2)
            {
                cout<<"ja visitado"<<endl;
            }
            else
            {
                cout<<"infinito"<<endl;
            }
        }

    }
    cout<<"------------------------------------------------------------------------"<<endl;




    int indiceMin;
    for(int i=0; i<Prim.size(); i++)
    {
        if(Prim[i].getId() != -1 && Prim[i].getId()!= -2)
        {
            indiceMin = i;
        }

    }

    for(int i=0; i<Prim.size()-1; i++)
    {

        if(Prim[i].getId() != -1 && Prim[i].getId()!= -2)
        {
            for(int j=i+1; j<Prim.size(); j++)
            {

                if(Prim[j].getId() != -1 && Prim[j].getId()!= -2)
                {

                    if(Prim[i].getAresta()->getPeso() <= Prim[j].getAresta()->getPeso())
                    {
                        indiceMin = i;
                    }
                    else
                    {
                        indiceMin = j;
                    }
                }
            }

        }

    }

    return indiceMin;
}

vector<No>Grafo::auxAlgoritmoPrim(vector<No>vetProx,No noAtual,No noAlvo)
{
    No *aux;
    No *flag = new No(-1);

    if(noAtual.getId() == -1 || noAlvo.getId()== -1)
    {
        vetProx.push_back(*flag);
        return vetProx;
    }

    for(list<No>::iterator it = vertices->begin(); it != vertices->end(); ++it)
    {
        if(it->getId() == noAtual.getId())
        {
            aux = new No(it->getProximoNo()->getId());
            aux->setAresta(it->getProximoNo()->getAresta());
            aux->setProximoNo(it->getProximoNo()->getProximoNo());


            if(it->getProximoNo()->getId() == noAlvo.getId())
            {

                vetProx.push_back(*it->getProximoNo());
                return vetProx;
            }
            while(true)
            {
                if(aux->getProximoNo()->getId() == noAlvo.getId())
                {
                    vetProx.push_back(*aux->getProximoNo());
                    return vetProx;
                }
                aux->setId(aux->getProximoNo()->getId());
                aux->setAresta(aux->getProximoNo()->getAresta());
                aux->setProximoNo(aux->getProximoNo()->getProximoNo());
            }
        }
    }

}

int Grafo:: ehAdjacente(int idOrigem,int idAlvo)
{
    No *aux ;
    for(list<No>::iterator it = vertices->begin(); it != vertices->end(); ++it)
    {
        if(it->getId() == idOrigem)
        {

            if(it->getProximoNo()!=0)
            {
                if(it->getProximoNo()->getId() == idAlvo)
                {
                    return it->getProximoNo()->getAresta()->getPeso();
                }
                aux = new No(it->getProximoNo()->getId());
                aux->setAresta(it->getProximoNo()->getAresta());
                aux->setProximoNo(it->getProximoNo()->getProximoNo());

            }
            while(aux->getProximoNo()!=0)
            {

                aux->setId(aux->getProximoNo()->getId());
                aux->setAresta(aux->getProximoNo()->getAresta());
                aux->setProximoNo(aux->getProximoNo()->getProximoNo());

                if(aux->getId() == idAlvo)
                {

                    return aux->getAresta()->getPeso();
                }
            }
        }
    }
    return 0;
}
