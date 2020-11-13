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
#include <time.h>

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

void Grafo::larguraPrimeiraBusca(int vertice)
{
    queue<int> fila;
    vector<int> resultado;
    vector<int> verifica;
    for(int i =0; i < this->ordem; i++)
    {
        verifica.push_back(-1);
    }
    resultado.push_back(vertice);
    verifica[vertice] = 1;
    fila.push(vertice);
    while(!fila.empty())
    {
        for(list<No>::iterator it = vertices->begin(); it != vertices->end(); ++it)
        {
            if(it->getId() == fila.front())
            {
                cout<<"percorrendo os adjacentes não visitados do nó " << it->getId()<<" : ";
                No *aux = new No(it->getId());

                aux->setProximoNo(it->getProximoNo());

                while(aux->getProximoNo()!= 0)
                {
                    aux->setId(aux->getProximoNo()->getId());
                    if((aux->getProximoNo()->getProximoNo() == 0))
                    {
                        aux->setProximoNo(nullptr);
                    }
                    else
                    {
                        aux->setProximoNo(aux->getProximoNo()->getProximoNo());
                    }
                    if(verifica[aux->getId()] == -1)
                    {
                        fila.push(aux->getId());
                        resultado.push_back(aux->getId());
                        verifica[aux->getId()] = 1;
                        cout << aux->getId() << " ";
                    }
                }
            }
        }
        cout<<endl;
        fila.pop();
    }
}

void Grafo::floydMarshall()
{

    vector<No> vectorArestaOrdenada = retornaListaOrdenada();
    int i,j;
    int tam = this->ordem;
    float matriz[tam][tam];

    for(i = 0; i < tam; i++)
    {
        matriz[i][i] = 0;
        for(j = 0; j < tam; j++)
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
        cout<<id<< "  |  "<<x<<":  "<<custoVertices[x]<<endl;
        x++;
    }
}

void Grafo::kruskal()
{
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


void Grafo::quickSort(vector<No>&vetorOrdenado,int menorIndice,int maiorIndice)
{



    if(menorIndice<maiorIndice)
    {

        int pi = particao(vetorOrdenado,menorIndice,maiorIndice);


        quickSort(vetorOrdenado,menorIndice,pi-1);
        quickSort(vetorOrdenado,pi+1,maiorIndice);
    }

}


int Grafo::particao(vector<No>&vetorOrdenado,int menorIndice,int maiorIndice)
{


    No pivo = vetorOrdenado[maiorIndice];
    int i = (menorIndice-1 );


    for(int j=menorIndice; j < maiorIndice; j++)
    {

        if(vetorOrdenado[j].getAresta()->getPeso() <  pivo.getAresta()->getPeso())
        {
            i++;
            swap(vetorOrdenado[i],vetorOrdenado[j]);
        }

    }
    swap(vetorOrdenado[i+1],vetorOrdenado[maiorIndice]);

    return i+1;


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
    quickSort(vetorOrdenado,0,vetorOrdenado.size()-1);
    for (int i = 0 ; i<vetorOrdenado.size(); i++)
    {
        vetorOrdenado[i].getAresta()->setFalseAresta();
    }

    return vetorOrdenado;
}

void Grafo::algoritmoPrim()
{
    float pesoAtual,pesoCandidato1,pesoCandidato2,pesototal=0;
    int contador,indiceMinimo,i=0;
    vector<No> vetArestaOrdenado = retornaListaOrdenada();
    vector<No> vetAdj;
    vector<int> vetProxId,PrimId,PrimIdAdj;
    vector<float>vetProxPeso,PrimPeso;
    No *aux = new No(1);

    PrimId.push_back(vetArestaOrdenado[0].getAresta()->getIdOrigem());
    PrimPeso.push_back(vetArestaOrdenado[0].getAresta()->getPeso());
    PrimIdAdj.push_back(vetArestaOrdenado[0].getAresta()->getIdAlvo());
    pesototal += vetArestaOrdenado[0].getAresta()->getPeso();

    for(list<No>::iterator it = vertices->begin(); it != vertices->end(); ++it)
    {
        vetAdj.push_back(*it);
        pesoCandidato1 = ehAdjacente(vetAdj,i,vetArestaOrdenado[0].getAresta()->getIdOrigem());
        pesoCandidato2 = ehAdjacente(vetAdj,i,vetArestaOrdenado[0].getAresta()->getIdAlvo());

        if(pesoCandidato1!=-2 || pesoCandidato2!=-2)
        {
            if(pesoCandidato1!=-2 && pesoCandidato2!=-2 && pesoCandidato1<=pesoCandidato2 || pesoCandidato1!=-2 && pesoCandidato2==-2)
            {
                vetProxId.push_back(vetArestaOrdenado[0].getAresta()->getIdOrigem());
                vetProxPeso.push_back(pesoCandidato1);
            }
            else
            {
                if(pesoCandidato1!=-2 && pesoCandidato2!=-2 && pesoCandidato1>pesoCandidato2 || pesoCandidato1==-2 && pesoCandidato2!=-2)
                {
                    vetProxId.push_back(vetArestaOrdenado[0].getAresta()->getIdAlvo());
                    vetProxPeso.push_back(pesoCandidato2);
                }
            }
        }
        else
        {
            vetProxId.push_back(-1);
            vetProxPeso.push_back(9999999);
        }
        i++;
    }
    delete aux;

    vetProxId[vetArestaOrdenado[0].getAresta()->getIdAlvo()] = -2;
    vetProxId[vetArestaOrdenado[0].getAresta()->getIdOrigem()] = -2;
    vetProxPeso[vetArestaOrdenado[0].getAresta()->getIdAlvo()] = 9999999;
    vetProxPeso[vetArestaOrdenado[0].getAresta()->getIdOrigem()] = 9999999;

    contador = indiceMinimo = 0;

    while(contador<getOrdem()-2)
    {
        indiceMinimo = getIndiceMin(vetProxPeso);

        PrimId.push_back(vetProxId[indiceMinimo]);
        PrimIdAdj.push_back(indiceMinimo);
        PrimPeso.push_back(vetProxPeso[indiceMinimo]);

        pesototal += vetProxPeso[indiceMinimo];
        vetProxId[indiceMinimo] = -2;
        vetProxPeso[indiceMinimo] = 9999999;

        for(int i=0; i<getOrdem(); i++)
            if(vetProxId[i] != -2)
            {
                pesoAtual = ehAdjacente(vetAdj,i,indiceMinimo);
                if(pesoAtual != -2)
                    if(vetProxPeso[i]>pesoAtual)
                    {
                        vetProxId[i] = indiceMinimo;
                        vetProxPeso[i] = pesoAtual;
                    }
            }
        contador ++;

    }
    for(int i=0; i<PrimId.size(); i++)
    {
        cout<<PrimId[i]<<" | "<< PrimIdAdj[i]<<" Peso: "<<PrimPeso[i]<<endl;
    }
    cout<<"PESO DA ARVORE GERADORA DE PRIM : "<<pesototal<<endl;
}

int Grafo::getIndiceMin(vector<float>vetProxPeso)
{
    int indiceMin;
    int pesoMin;
    for(int i=0; i<vetProxPeso.size(); i++)
    {
        if(vetProxPeso[i]!= 9999999)
        {
            indiceMin = i;
            pesoMin = vetProxPeso[i];
            break;
        }
    }
    for(int i=indiceMin; i<vetProxPeso.size(); i++)
    {
        if( vetProxPeso[i]!=9999999)
        {
            if(pesoMin > vetProxPeso[i])
            {
                indiceMin = i;
                pesoMin = vetProxPeso[i];
            }
        }
    }
    return indiceMin;
}
float Grafo::ehAdjacente(vector<No> vetAdj,int idOrigem,int idAlvo)
{
    No *aux;
    float peso;
    if(vetAdj[idOrigem].getProximoNo()!=0)
    {
        if(vetAdj[idOrigem].getProximoNo()->getId()== idAlvo)
        {
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
    delete aux;
    return -2;
}




void Grafo::guloso()
{
    clock_t timeStart, timeStop;
    timeStart = clock();
    vector<No> solucao;
    vector<int> graus;
    vector<No>candidatos;
    bool checkGrau = true;
    for(list<No>::iterator it = vertices->begin(); it != vertices->end(); ++it)
    {
        candidatos.push_back(*it);
        graus.push_back(it->getGrau());
    }
    quickSortGuloso(candidatos, graus, 0, graus.size() - 1);
    while((!candidatos.empty()) && (checkGrau))
    {
        solucao.push_back(candidatos.front());
        No *aux = new No(candidatos.front().getId());
        if(candidatos.front().getProximoNo() == 0)
        {
            aux->setProximoNo(nullptr);
        }
        else
        {
            aux->setProximoNo(candidatos.front().getProximoNo());
        }
        aux->setProximoNo(candidatos.front().getProximoNo());
        candidatos.erase(candidatos.begin() + 0);
        graus.erase(graus.begin() + 0);
        while(aux->getProximoNo()!=0)
        {
            aux->setId(aux->getProximoNo()->getId());
            if(aux->getProximoNo()->getProximoNo() != 0)
            {
                aux->setProximoNo(aux->getProximoNo()->getProximoNo());
            }
            else
            {
                aux->setProximoNo(aux->getProximoNo()->getProximoNo());
            }

            for(int i = 0; i < candidatos.size(); i++)
            {
                if(candidatos[i].getId() == aux->getId())
                {
                    graus[i] = graus[i] - 1;
                    if(graus[i] == 0)
                    {
                        candidatos.erase(candidatos.begin() + i);
                        graus.erase(graus.begin() + i);
                        break;
                    }
                }
            }
        }
        for(int i = 0; i< candidatos.size(); i++)
        {
            checkGrau = false;
            if(candidatos[i].getGrau() == graus[i])
            {
                checkGrau = true;
                break;
            }
        }
        quickSortGuloso(candidatos,graus,0, graus.size() - 1);
        delete aux;
    }
    timeStop = clock();
    cout<<"tempo gasto: " <<((double)(timeStop - timeStart) / CLOCKS_PER_SEC)<<endl;
    cout<<"solucao: "<<solucao.size();

}


vector<int> Grafo::gulosoRandomizado(float alfa, int *interacoes)
{
    vector<No> candidatos;
    vector<int> melhorSolucao;
    vector<int> graus;
    bool checkGrau = true;
    int interacoesSemMudanca = 0;
    for(list<No>::iterator it = vertices->begin(); it != vertices->end(); ++it)
    {
        graus.push_back(it->getGrau());
        candidatos.push_back(*it);
    }
    quickSortGuloso(candidatos, graus, 0, graus.size() - 1);
    while(*interacoes < 500 && interacoesSemMudanca < 200)
    {
        vector<int> solucao;
        vector<No> candidato = candidatos;
        vector<int> grausInteracao = graus;
        checkGrau = true;
        while((!candidato.empty()) && checkGrau)
        {

            int value = ((candidato.size()) * alfa) + 1;
            int x = (rand()%value);
            solucao.push_back(candidato[x].getId());
            No *aux = new No(candidato[x].getId());
            if(candidato[x].getProximoNo() == 0)
            {
                aux->setProximoNo(nullptr);
            }
            else
            {
                aux->setProximoNo(candidato[x].getProximoNo());
            }
            aux->setProximoNo(candidato[x].getProximoNo());
            candidato.erase(candidato.begin() + 0);
            grausInteracao.erase(grausInteracao.begin() + 0);
            while(aux->getProximoNo()!=0)
            {
                aux->setId(aux->getProximoNo()->getId());
                if(aux->getProximoNo()->getProximoNo() != 0)
                {
                    aux->setProximoNo(aux->getProximoNo()->getProximoNo());
                }
                else
                {
                    aux->setProximoNo(aux->getProximoNo()->getProximoNo());
                }

                for(int i = 0; i < candidato.size(); i++)
                {
                    if(candidato[i].getId() == aux->getId())
                    {
                        grausInteracao[i] = grausInteracao[i] - 1;
                        if(grausInteracao[i] == 0)
                        {
                            candidato.erase(candidato.begin() + i);
                            grausInteracao.erase(grausInteracao.begin() + i);
                            break;
                        }
                    }
                }
            }
            for(int i = 0; i< candidato.size(); i++)
            {
                checkGrau = false;
                if(candidato[i].getGrau() == grausInteracao[i])
                {
                    checkGrau = true;
                    break;
                }
            }
            quickSortGuloso(candidato, grausInteracao, 0, grausInteracao.size() - 1);
            delete aux;
        }
        interacoesSemMudanca = interacoesSemMudanca + 1;
        if((melhorSolucao.size() > solucao.size()) || melhorSolucao.size() == 0)
        {
            melhorSolucao = solucao;
            interacoesSemMudanca = 0;
        }
        *interacoes = *interacoes + 1;
    }
    return melhorSolucao;
}

void Grafo::quickSortGuloso(vector<No>&candidatos, vector<int>&graus, int menorIndice, int maiorIndice)
{

    if(menorIndice<maiorIndice)
    {
        int pi = particaoGuloso(candidatos,graus,menorIndice,maiorIndice);
        quickSortGuloso(candidatos,graus,menorIndice,pi-1);
        quickSortGuloso(candidatos,graus,pi+1,maiorIndice);
    }

}

int Grafo::particaoGuloso(vector<No>&candidatos, vector<int>&graus, int menorIndice, int maiorIndice)
{
    int pivo = graus[maiorIndice];
    int i = (menorIndice -1);


    for(int j = menorIndice; j < maiorIndice; j++)
    {

        if( graus[j] > pivo)
        {
            i++;
            swap(candidatos[i],candidatos[j]);
            swap(graus[i],graus[j]);
        }

    }
    swap(candidatos[i+1], candidatos[maiorIndice]);
    swap(graus[i+1], graus[maiorIndice]);

    return i+1;
}

