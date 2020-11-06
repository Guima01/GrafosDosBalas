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

void Grafo::floydMarshall()
{
    vector<No> vectorArestaOrdenada = retornaListaOrdenada();
    int i,j;
    int tam = this->ordem;
    int matriz[ordem][ordem];
    int matrizAux[ordem][ordem];

    for(i = 0; i < this->ordem; i++)
    {
        matriz[i][i] = 0;
        for(j = 0; j < this->ordem; j++)
        {
            if(i != j)
            {
                matriz[i][j] = 99999;
            }
        }
    }
    for(i = 0; i < vectorArestaOrdenada.size(); i++)
    {
        matriz[vectorArestaOrdenada[i].getAresta()->getIdAlvo()][vectorArestaOrdenada[i].getAresta()->getIdOrigem()] = vectorArestaOrdenada[i].getAresta()->getPeso();
        matriz[vectorArestaOrdenada[i].getAresta()->getIdOrigem()][vectorArestaOrdenada[i].getAresta()->getIdAlvo()] = vectorArestaOrdenada[i].getAresta()->getPeso();
    }

    for(int k = 0; k < this->ordem; k++)
    {
        for(int i = 0; i < this->ordem; i++)
        {
            for(int j = 0; j < this->ordem; j++)
            {
                if(i != j && i!= k && j != k)
                {
                    if(matriz[i][j] > matriz[i][k] + matriz[k][j])
                    {
                        matriz[i][j] = matriz[i][k] + matriz[k][j];
                    }
                }
            }
        }

    }
    for(int i = 0; i < this->ordem; i++)
    {
        for(int j = 0; j < this->ordem; j++)
        {
            cout<<matriz[i][j]<<" ";
        }
        cout<<endl;
    }
}

void Grafo::dijkstra(int id)
{
    list<int> verticesVisitados;
    bool *verticesNaoVisitados;
    float *custoVertices;
    custoVertices = (float *)malloc(this->ordem * sizeof(int));
    verticesNaoVisitados = (bool *)malloc(this->ordem * sizeof(int));
    for (int i = 0; i < this->ordem; i++)
    {
        if(i == id)
        {
            verticesNaoVisitados[i] = true;
            custoVertices[i] = 0;
            verticesVisitados.push_back(id);

        }
        else
        {
            custoVertices[i] = -1;
            verticesNaoVisitados[i] = false;
        }
    }
    for(list<No>::iterator it = vertices->begin(); it != vertices->end(); ++it)
    {
        if(it->getId() == id)
        {
            No *aux = new No(it->getId());
            aux->setProximoNo(it->getProximoNo());
            aux->setAresta(it->getAresta());
            while(aux->getProximoNo() !=0)
            {
                aux->setId(aux->getProximoNo()->getId());
                aux->setAresta(aux->getProximoNo()->getAresta());
                if(aux->getProximoNo()->getProximoNo() !=0 )
                {
                    aux->setProximoNo(aux->getProximoNo()->getProximoNo());
                }
                else
                {
                    aux->setProximoNo(nullptr);
                }
                custoVertices[aux->getId()] = aux->getAresta()->getPeso();
            }
            delete aux;
        }
    }

    int i = id;
    while(verticesVisitados.size() < this->ordem)
    {
        float menor = -1;
        for(int p = 0; p < this->ordem; p++)
        {
            if(verticesNaoVisitados[p] == false)
            {
                if(menor == -1 && custoVertices[p]!= -1)
                {
                    menor = custoVertices[p];
                    i = p;
                }
                else if(menor > custoVertices[p] && (custoVertices[p]!= -1))
                {
                    menor = custoVertices[p];
                    i = p;
                }
            }
        }
        verticesNaoVisitados[i] = true;
        verticesVisitados.push_back(i);
        cout<<i;
        int k = 0;
        for(list<No>::iterator it = vertices->begin(); it != vertices->end(); ++it)
        {

            if(verticesNaoVisitados[k] == false)
            {

                No *aux = new No(it->getId());
                aux->setProximoNo(it->getProximoNo());
                aux->setAresta(it->getAresta());
                while(aux->getProximoNo() !=0)
                {
                    aux->setId(aux->getProximoNo()->getId());
                    aux->setAresta(aux->getProximoNo()->getAresta());
                    if(aux->getProximoNo()->getProximoNo() !=0 )
                    {
                        aux->setProximoNo(aux->getProximoNo()->getProximoNo());
                    }
                    else
                    {
                        aux->setProximoNo(nullptr);
                    }
                    if(aux->getId() == i)
                    {
                        if(custoVertices[it->getId()] == -1 || (custoVertices[it->getId()] > aux->getAresta()->getPeso() + custoVertices[i]))
                        {
                            custoVertices[it->getId()] = aux->getAresta()->getPeso() + custoVertices[i];

                        }
                        else if(custoVertices[aux->getId()] > aux->getAresta()->getPeso() + custoVertices[i])
                        {
                            custoVertices[aux->getId()] = aux->getAresta()->getPeso() + custoVertices[i];

                        }
                    }
                }
                delete aux;
            }
            k++;
        }
    }
    int x = 0;
    cout<<endl;
    for(list<int>::iterator it = verticesVisitados.begin(); it != verticesVisitados.end(); ++it)
    {
        cout<<custoVertices[x]<<endl;
        x++;
    }
}

void Grafo::kruskal()
{
    cout<<"teste";
    vector<No> vectorArestaOrdenada = retornaListaOrdenada();
    list<No> listaArestaOrdenada(vectorArestaOrdenada.begin(),vectorArestaOrdenada.end());
    vector<No> solucao;
    int *subArvores;
    subArvores = (int *)malloc(this->ordem * sizeof(int));
    for(int i = 0; i < this->ordem; i++)
    {
        subArvores[i]=i;
    }
    int cont = 0;
    int menor = 0;
    int maior = 0;
    int tamanho = listaArestaOrdenada.size();
    while(cont < tamanho && (!listaArestaOrdenada.empty()))
    {
        No *aux = new No(listaArestaOrdenada.begin()->getId());
        aux->setAresta(listaArestaOrdenada.begin()->getAresta());
        listaArestaOrdenada.pop_front();
        if(aux->getAresta()->getIdAlvo() > aux->getAresta()->getIdOrigem())
        {
            menor = aux->getAresta()->getIdOrigem();
            maior = aux->getAresta()->getIdAlvo();
        }
        else
        {
            menor = aux->getAresta()->getIdAlvo();
            maior = aux->getAresta()->getIdOrigem();
        }
        if(subArvores[maior] != subArvores[menor])
        {
            solucao.push_back(*aux);
            for(int i = 0; i < this->ordem; i++)
            {
                if(subArvores[i] == subArvores[maior] && (i!= maior))
                {
                    subArvores[i] = subArvores[menor];
                }
            }
            subArvores[maior] = subArvores[menor];
            for(int i = 0; i < this->ordem; i++)
            {
            }
            cont = cont + 1;
        }
        delete aux;
    }
    cout<<endl;
    cout<<endl;
    cout<<endl;
    int valor = 0;
    for(int i = 0; i < solucao.size(); i++)
    {
        cout<<solucao[i].getAresta()->getIdAlvo() << " | " << solucao[i].getAresta()->getIdOrigem()<<" Peso:";
        cout<< solucao[i].getAresta()->getPeso()<<endl;
        valor = valor + solucao[i].getAresta()->getPeso();
    }

    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<"o peso total foi: "<< valor<<endl;


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
    return vetorOrdenado;
}

vector<No>Grafo::algoritmoPrim()
{
    vector<No> vetArestaOrdenado = retornaListaOrdenada();
    vector<No> vetPrim,vetProx;
    vector<No> vetAdj;
    No *flag = new No(-2);
    int contador,indiceMinimo;
    float pesoAlvo,pesoOrigem,peso1,peso2;
    vetPrim.push_back(vetArestaOrdenado[0]);
    for(list<No>::iterator it = vertices->begin(); it != vertices->end(); ++it)
    {
        vetAdj.push_back(*it);
    }
    for(list<No>::iterator it = vertices->begin(); it != vertices->end(); ++it)
    {
        while(true)
        {
            pesoOrigem = ehAdjacente(vetAdj,vetPrim[0].getAresta()->getIdOrigem(),it->getId());
            pesoAlvo = ehAdjacente(vetAdj,vetPrim[0].getAresta()->getIdAlvo(),it->getId());
            if(pesoOrigem==-2 && pesoAlvo==-2)
            {
                vetProx = addVetProx(vetAdj,vetProx, it->getId(),-1);
                break;
            }
            else
            {
                if(pesoOrigem!=-2 && pesoAlvo==-2 || pesoOrigem!=-2 && pesoAlvo!=0 && pesoOrigem<=pesoAlvo )
                {
                    vetProx = addVetProx(vetAdj,vetProx,it->getId(),vetPrim[0].getAresta()->getIdOrigem());
                    break;
                }
                else
                {
                    vetProx = addVetProx(vetAdj,vetProx,it->getId(),vetPrim[0].getAresta()->getIdAlvo());
                    break;
                }
            }
        }
    }
    vetProx[vetArestaOrdenado[0].getAresta()->getIdAlvo()] = *flag;
    vetProx[vetArestaOrdenado[0].getAresta()->getIdOrigem()] = *flag;
    contador = indiceMinimo = 0;
    while(contador<getOrdem()-2)
    {
        indiceMinimo = getIndiceMin(vetProx);
        vetPrim.push_back(vetProx[indiceMinimo]);
        vetProx[indiceMinimo] = *flag;
        for(int i=0; i<getOrdem(); i++)
        {
            if(vetProx[i].getId() != -2)
            {
                if(!(vetProx[i].getAresta() != 0))
                {
                    pesoOrigem = ehAdjacente(vetAdj,vetProx[i].getId(),vetPrim.back().getAresta()->getIdOrigem());
                    pesoAlvo = ehAdjacente(vetAdj,vetProx[i].getId(),vetPrim.back().getAresta()->getIdAlvo());

                    if(pesoOrigem != -2 && pesoAlvo == -2 || pesoOrigem !=-2 && pesoAlvo!=-2 && pesoOrigem<=pesoAlvo)
                    {
                        vetProx[i] = alteraVetProx(vetAdj,vetProx[i].getId(),vetPrim.back().getAresta()->getIdOrigem());
                    }
                    else
                    {
                        if(pesoAlvo != -2 && pesoOrigem == -2 || pesoAlvo != -2 && pesoOrigem != -2 && pesoOrigem>pesoAlvo)
                        {
                            vetProx[i] = alteraVetProx(vetAdj,vetProx[i].getId(),vetPrim.back().getAresta()->getIdAlvo());
                        }
                    }
                }
                else
                {
                    pesoOrigem = vetProx[i].getAresta()->getPeso();
                    peso1 = ehAdjacente(vetAdj,vetProx[i].getId(),vetPrim.back().getAresta()->getIdOrigem());
                    peso2 = ehAdjacente(vetAdj,vetProx[i].getId(),vetPrim.back().getAresta()->getIdAlvo());
                    if(peso1!=-2 && peso2==-2 || peso1!=-2 && peso2!=-2 && peso1<=peso2)
                    {
                        if(peso1<pesoOrigem)
                        {
                            vetProx[i] = alteraVetProx(vetAdj,vetProx[i].getId(),vetPrim.back().getAresta()->getIdOrigem());
                        }
                    }
                    else
                    {
                        if(peso1==-2 &&peso2!=-2 || peso1!=-2 && peso2!=-2 && peso1>peso2)
                        {
                            if(peso2<pesoOrigem)
                            {
                                vetProx[i] = alteraVetProx(vetAdj,vetProx[i].getId(),vetPrim.back().getAresta()->getIdAlvo());
                            }
                        }
                    }
                }
            }
        }
        contador = contador+1;
    }
    delete flag;
    return vetPrim;
}

No Grafo::alteraVetProx(vector<No> vetAdj,int noAtual,int noAlvo)
{
    No *aux = new No(vetAdj[noAlvo].getProximoNo()->getId());
    aux->setAresta(vetAdj[noAlvo].getProximoNo()->getAresta());
    aux->setProximoNo(vetAdj[noAlvo].getProximoNo()->getProximoNo());
    if(aux->getId() == noAtual)
    {
        return *aux;
    }
    while(true)
    {
        if(aux->getId() == noAtual)
        {
            return *aux;
        }
        aux->setId(aux->getProximoNo()->getId());
        aux->setAresta(aux->getProximoNo()->getAresta());
        aux->setProximoNo(aux->getProximoNo()->getProximoNo());
    }
}


int Grafo::getIndiceMin(vector<No>vetProx)
{
    int indiceMin=-1;
    int pesoMin=-1;
    for(int i=0; i<vetProx.size(); i++)
    {
        if(vetProx[i].getAresta()!= 0 && vetProx[i].getId() != -2)
        {
            indiceMin = i;
            pesoMin = vetProx[i].getAresta()->getPeso();
            break;
        }
    }
    for(int i=0; i<vetProx.size()-1; i++)
    {
        if(vetProx[i].getAresta() != 0 && vetProx[i].getId()!= -2)
        {
            for(int j=i+1; j<vetProx.size(); j++)
            {
                if(vetProx[j].getAresta() != 0 && vetProx[j].getId()!= -2)
                {
                    if(vetProx[i].getAresta()->getPeso() <= vetProx[j].getAresta()->getPeso())
                    {
                        if(indiceMin!=i && pesoMin>vetProx[i].getAresta()->getPeso())
                        {
                            indiceMin = i;
                            pesoMin = vetProx[i].getAresta()->getPeso();
                        }
                    }
                    else
                    {
                        if(indiceMin!=j&& pesoMin>vetProx[j].getAresta()->getPeso())
                        {
                            indiceMin = j;
                            pesoMin = vetProx[j].getAresta()->getPeso();
                        }
                    }
                }
            }
        }
    }
    return indiceMin;
}

vector<No>Grafo::addVetProx(vector<No>vetAdj,vector<No>vetProx,No noAtual,No noAlvo)
{
    No *aux;
    No *flag = new No(noAtual.getId());
    flag->setAresta(nullptr);
    if( noAlvo.getId()== -1)
    {
        vetProx.push_back(*flag);
        delete flag;
        return vetProx;
    }
    aux = new No(vetAdj[noAlvo.getId()].getProximoNo()->getId());
    aux->setAresta(vetAdj[noAlvo.getId()].getProximoNo()->getAresta());
    aux->setProximoNo(vetAdj[noAlvo.getId()].getProximoNo()->getProximoNo());
    if(aux->getId()==noAtual.getId())
    {
        vetProx.push_back(*aux);
        return vetProx;
    }

    while(true)
    {
        if(aux->getId() == noAtual.getId())
        {
            vetProx.push_back(*aux);
            delete aux;
            return vetProx;
        }
        aux->setId(aux->getProximoNo()->getId());
        aux->setAresta(aux->getProximoNo()->getAresta());
        aux->setProximoNo(aux->getProximoNo()->getProximoNo());
    }
}

float Grafo::ehAdjacente(vector<No> vetAdj,int idOrigem,int idAlvo)
{
    No *aux;
    float peso;
    if(vetAdj[idOrigem].getProximoNo()!=0){
        if(vetAdj[idOrigem].getProximoNo()->getId()== idAlvo){
            return vetAdj[idOrigem].getProximoNo()->getAresta()->getPeso();
        }
    }
    aux = new No(vetAdj[idOrigem].getProximoNo()->getId()) ;
    aux->setAresta(vetAdj[idOrigem].getProximoNo()->getAresta());
    aux->setProximoNo(vetAdj[idOrigem].getProximoNo()->getProximoNo());
    while(aux->getProximoNo()!=0)
            {
                aux->setId(aux->getProximoNo()->getId());
                aux->setAresta(aux->getProximoNo()->getAresta());
                aux->setProximoNo(aux->getProximoNo()->getProximoNo());

                if(aux->getId() == idAlvo)
                {
                    peso = aux->getAresta()->getPeso();
                    delete aux;
                    return peso;
                }
            }

    return -2;

}

