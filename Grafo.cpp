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

/*//retorna o número de arestas no Grafo
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





///////////////////////////////////////////////////////////////////////////////////////////////
void Grafo::insereGulosamente(int idNoFonte, int idNoAlvo)
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
                it->setGrau();
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
                checkNo = checkNo + 1;
                it->setGrau();
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
                it->setGrau();
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
                checkNo = checkNo + 1;
                it->setGrau();
                delete aux;
            }
        }

        //se os 2 nós ja foram inseridos, retorna
        else if (checkNo == 2)
        {
            break;
        }
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////
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


//Função recursiva que percorre o grafo, começando de nó raiz e indo o mais profundo possível em cada nó adjacente

vector<int> Grafo::profundidadePrimeiraBusca(vector<int> listaVertices, int ordemGrafo, int posicao, int *cont)
{
    //verifica se não foi digitado um nó invalido
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

            //verifica se o grafo ja foi visitado por completo
            if (*cont == ordemGrafo)
            {
                delete aux;
                return listaVertices;
            }
            int verticeAtual = it->getId();

            //enquanto o vértice tiver um nó adjancente caminha por ele
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

                    //chama a função recursivamente
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

//auxiliar para verificar se o nó ja foi visitado
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

//função de busca em largura, começando por um vértice raiz, exploramos todos os seus vizinho, e para desses vértices mais próximos, exploramos os seus vértices vizinhos inexplorados
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

    //continua percorrendo enquanto a fila de vértices não está vazia
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
                    //adiciona o nó a fila, caso ele ainda não tenha sido visitado
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

        //remove o primeiro elemento da fila
        fila.pop();
    }
}

//o algoritmo de Floyd resolve o problema de calcular a distancia mais curta entre todos os pares de vértices em um grafo, utilizando matriz de adjacência
void Grafo::floydMarshall()
{

    vector<No> vectorArestaOrdenada = retornaListaOrdenada();
    int i,j;
    int tam = this->ordem;
    float matriz[tam][tam];

    //inicializa a matriz com peso 0 ou infinito caso não haja adjacencia entre 2 nós
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

    // adiciona os pesos entre na matriz
    for(i = 0; i < vectorArestaOrdenada.size(); i++)
    {
        matriz[vectorArestaOrdenada[i].getAresta()->getIdAlvo()][vectorArestaOrdenada[i].getAresta()->getIdOrigem()] = vectorArestaOrdenada[i].getAresta()->getPeso();
        matriz[vectorArestaOrdenada[i].getAresta()->getIdOrigem()][vectorArestaOrdenada[i].getAresta()->getIdAlvo()] = vectorArestaOrdenada[i].getAresta()->getPeso();
    }

    //calcula o menor caminho entre os nós
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

    //imprime a matriz
    for(int i = 0; i < this->ordem; i++)
    {
        for(int j = 0; j < this->ordem; j++)
        {
            cout<<matriz[i][j]<<" ";
        }
        cout<<endl;
    }
}

//o algoritmo de Djikstra soluciona o problema do caminho mais curto em um grafo, passamos como parametro um Nó e ele imprime o caminho mais curto deste nó a todos os outros
void Grafo::dijkstra(int id)
{
    list<int> verticesVisitados;
    bool *verticesNaoVisitados;
    float *custoVertices;
    custoVertices = (float *)malloc(this->ordem * sizeof(int));
    verticesNaoVisitados = (bool *)malloc(this->ordem * sizeof(int));
    //inicializando os arrays
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
    //caminhando pelas adjacências
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
                //custo do Nó atual até seu adjacente é adicionado no vetor
                custoVertices[aux->getId()] = aux->getAresta()->getPeso();
            }
            delete aux;
        }
    }

    int i = id;

    //enquanto não visitar todos os vértices do grafo
    while(verticesVisitados.size() < this->ordem)
    {
        float menor = -1;
        for(int p = 0; p < this->ordem; p++)
        {
            //busca pelo menor peso
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

        //caminha até encontrar um nó não visitado
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

                    //calcula qual custo de peso é menor
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

    //imprime o custo dos pesos do nó raiz até todos os outros
    for(list<int>::iterator it = verticesVisitados.begin(); it != verticesVisitados.end(); ++it)
    {
        cout<<id<< "  |  "<<x<<":  caminho minimo: "<<custoVertices[x]<<endl;
        x++;
    }
}

//O algoritmo de Kruskal é um algoritmo que busca uma árvore geradora mínima para um grafo conexo com pesos
void Grafo::kruskal()
{
    clock_t timeStart, timeStop;
    timeStart = clock();
    vector<No> vectorArestaOrdenada = retornaListaOrdenada();
    list<No> listaArestaOrdenada(vectorArestaOrdenada.begin(),vectorArestaOrdenada.end());
    vector<No> solucao;
    int *subArvores;
    subArvores = (int *)malloc(this->ordem * sizeof(int));

    //inicializa sub-arvores
    for(int i = 0; i < this->ordem; i++)
    {
        subArvores[i]=i;
    }
    int cont = 0;
    int menor = 0;
    int maior = 0;
    int tamanho = listaArestaOrdenada.size();

    //roda enquanto não atingiu todos os vértices e a lista ordenada não estiver vazia
    while(cont < tamanho && (!listaArestaOrdenada.empty()))
    {
        //seleciona o maior e o menor entre 2 vértices
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

        //verifica se as sub-arvores são diferentes e faz a substituição necessária
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

    //imprime a árvore e peso total
    timeStop = clock();
    for(int i = 0; i < solucao.size(); i++)
    {
        cout<<solucao[i].getAresta()->getIdAlvo() << " | " << solucao[i].getAresta()->getIdOrigem()<<" Peso:";
        cout<< solucao[i].getAresta()->getPeso()<<endl;
        valor = valor + solucao[i].getAresta()->getPeso();
    }
    cout<<endl;
    cout<<endl;
    cout<<"o peso total foi: "<< valor<<endl;
    cout<<endl;
    double time = ((double)(timeStop - timeStart) / CLOCKS_PER_SEC);
    cout<<time;

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

// RETORNA DE FORMA ORDENADA E CRESCENTE , O CONJUNTO DE ARESTAS
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
    quickSort(vetorOrdenado,0,vetorOrdenado.size()-1); //quickSort funcao p reordenar o vetor
    for (int i = 0 ; i<vetorOrdenado.size(); i++) //Aqui reseta o valor da aresta para nao visitada (arestaA)
    {
        vetorOrdenado[i].getAresta()->setFalseAresta();
    }

    return vetorOrdenado;
}

void Grafo::algoritmoPrim()
{
    clock_t timeStart, timeStop;
    timeStart = clock();
    int contador,indiceMinimo,i,j;
    float pesoCandidato1,pesoCandidato2,pesototal=0;

    vector<No> vectorArestaOrdenada = retornaListaOrdenada();

    vector<Aresta>solucao;

    vector<int> vetProxId;
    vector<float>vetProxPeso;

    float matriz[ordem][ordem];

    for(i = 0; i < ordem; i++)
        for(j = 0; j < ordem; j++)
            matriz[i][j] = -1;

    for(i = 0; i < vectorArestaOrdenada.size(); i++)
    {
        matriz[vectorArestaOrdenada[i].getAresta()->getIdAlvo()][vectorArestaOrdenada[i].getAresta()->getIdOrigem()] = vectorArestaOrdenada[i].getAresta()->getPeso();
        matriz[vectorArestaOrdenada[i].getAresta()->getIdOrigem()][vectorArestaOrdenada[i].getAresta()->getIdAlvo()] = vectorArestaOrdenada[i].getAresta()->getPeso();
    }

    i = 0;
    solucao.push_back(*vectorArestaOrdenada[0].getAresta());

    for(list<No>::iterator it = vertices->begin(); it != vertices->end(); ++it)
    {
        pesoCandidato1 = matriz[i][solucao[0].getIdOrigem()];
        pesoCandidato2 = matriz[i][solucao[0].getIdAlvo()];

        if(pesoCandidato1!=-1 || pesoCandidato2!=-1)
        {
            if(pesoCandidato1!=-1 && pesoCandidato2!=-1 && pesoCandidato1<=pesoCandidato2 || pesoCandidato1!=-1 && pesoCandidato2==-1)
            {
                vetProxId.push_back(solucao[0].getIdOrigem());
                vetProxPeso.push_back(pesoCandidato1);
            }
            else
            {
                if(pesoCandidato1!=-1 && pesoCandidato2!=-1 && pesoCandidato1>pesoCandidato2 || pesoCandidato1==-1 && pesoCandidato2!=-1)
                {
                    vetProxId.push_back(solucao[0].getIdAlvo());
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

    vetProxId[solucao[0].getIdAlvo()] = vetProxId[solucao[0].getIdOrigem()] = -2;
    vetProxPeso[solucao[0].getIdAlvo()] = vetProxPeso[solucao[0].getIdOrigem()] = 9999999;
    contador = indiceMinimo = 0;

    while(contador<getOrdem()-2)
    {
        indiceMinimo = getIndiceMin(vetProxPeso);

        Aresta *aresta = new Aresta(indiceMinimo,vetProxId[indiceMinimo]);
        aresta->setPeso(vetProxPeso[indiceMinimo]);

        solucao.push_back( *aresta );
        delete aresta;

        vetProxId[indiceMinimo] = -2;
        vetProxPeso[indiceMinimo] = 9999999;

        for(int i=0; i<getOrdem(); i++)
            if(vetProxId[i] != -2)
            {
                pesoCandidato1 = matriz[i][indiceMinimo];
                if(pesoCandidato1 != -1)
                    if(vetProxPeso[i]>pesoCandidato1)
                    {
                        vetProxId[i] = indiceMinimo;
                        vetProxPeso[i] = pesoCandidato1;
                    }
            }
        contador ++;

    }
    timeStop = clock();
    for(int i=0; i<solucao.size(); i++)
    {
        cout<<solucao[i].getIdOrigem() <<" | "<< solucao[i].getIdAlvo() <<" Peso:"<<solucao[i].getPeso()<<endl;
        pesototal += solucao[i].getPeso();
    }
    cout<<"PESO DA ARVORE GERADORA DE PRIM : "<<pesototal<<endl;
    double time = ((double)(timeStop - timeStart) / CLOCKS_PER_SEC);
    cout<<time;
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



//Algoritmo guloso para o problema de subconjunto dominante Mínimo
void Grafo::guloso()
{
    clock_t timeStart, timeStop;
    timeStart = clock();
    vector<No> solucao;
    vector<int> graus;
    vector<No>candidatos;
    bool checkGrau = true;

    //inicializa a lista de candidatos e lista de Graus referente aos vértices
    for(list<No>::iterator it = vertices->begin(); it != vertices->end(); ++it)
    {
        candidatos.push_back(*it);
        graus.push_back(it->getGrau());
    }

    //ordena o a lista de candidatos e a lista de graus
    quickSortGuloso(candidatos, graus, 0, graus.size() - 1);

    //roda enquanto ainda houver candidatos e enquanto ainda não foi encontrado um subconjunto dominante
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

        //remove o candidato e seu grau das listas
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

            //caminha pela lista de candidatos buscando os adjacentes do nó removido
            for(int i = 0; i < candidatos.size(); i++)
            {
                if(candidatos[i].getId() == aux->getId())
                {
                    //diminui em 1 o grau do adjacente
                    graus[i] = graus[i] - 1;

                    //caso o adjacente esteja com grau 0, ele é removida da lista de candidatos e da lista de graus
                    if(graus[i] == 0)
                    {
                        candidatos.erase(candidatos.begin() + i);
                        graus.erase(graus.begin() + i);
                        break;
                    }
                }
            }
        }

        //percorre a lista de graus para ver se ja foi encontrado algum conjunto dominante, faz isso vendo se houve alterações em todos os graus dos vértices
        for(int i = 0; i< candidatos.size(); i++)
        {
            checkGrau = false;
            if(candidatos[i].getGrau() == graus[i])
            {
                checkGrau = true;
                break;
            }
        }

        //ordena as listas novamente
        quickSortGuloso(candidatos,graus,0, graus.size() - 1);
        delete aux;
    }
    timeStop = clock();
    cout<<"tempo gasto: " <<((double)(timeStop - timeStart) / CLOCKS_PER_SEC)<<endl;
    cout<<"solucao: "<<solucao.size()<<endl;

}

vector<int> Grafo::gulosoRandomizado(float alfa, int *iteracoes)
{
    vector<No> candidatos;
    vector<int> melhorSolucao;
    vector<int> graus;
    bool checkGrau = true;
    int iteracoesSemMudanca = 0;

    //inicializa a lista de candidatos e lista de Graus referente aos vértices
    for(list<No>::iterator it = vertices->begin(); it != vertices->end(); ++it)
    {
        graus.push_back(it->getGrau());
        candidatos.push_back(*it);
    }

    //ordena o a lista de candidatos e a lista de graus
    quickSortGuloso(candidatos, graus, 0, graus.size() - 1);

    //faz as 500 iterações maximas e até não que não haja uma melhor solução em 200 iterações
    while(*iteracoes < 500 && iteracoesSemMudanca < 200)
    {
        //listas para iteração atual
        vector<int> solucao;
        vector<No> candidato = candidatos;
        vector<int> grausIteracao = graus;
        checkGrau = true;

        //roda enquanto ainda houver candidatos e enquanto ainda não foi encontrado um subconjunto dominante
        while((!candidato.empty()) && checkGrau)
        {
            //randomiza a posição da lista de candidate pelo parâmetro alfa
            int x = randomizaValor(candidato.size(), alfa);
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

            //remove o candidato e seu grau das listas
            candidato.erase(candidato.begin() + 0);
            grausIteracao.erase(grausIteracao.begin() + 0);
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

                //caminha pela lista de candidatos buscando os adjacentes do nó removido
                for(int i = 0; i < candidato.size(); i++)
                {
                    if(candidato[i].getId() == aux->getId())
                    {
                        //diminui em 1 o grau do adjacente
                        grausIteracao[i] = grausIteracao[i] - 1;

                        //caso o adjacente esteja com grau 0, ele é removida da lista de candidatos e da lista de graus
                        if(grausIteracao[i] == 0)
                        {
                            candidato.erase(candidato.begin() + i);
                            grausIteracao.erase(grausIteracao.begin() + i);
                            break;
                        }
                    }
                }
            }

            //percorre a lista de graus para ver se ja foi encontrado algum conjunto dominante, faz isso vendo se houve alterações em todos os graus dos vértices
            for(int i = 0; i< candidato.size(); i++)
            {
                checkGrau = false;
                if(candidato[i].getGrau() == grausIteracao[i])
                {
                    checkGrau = true;
                    break;
                }
            }

            //ordena as listas novamente
            quickSortGuloso(candidato, grausIteracao, 0, grausIteracao.size() - 1);
            delete aux;
        }

        //verifica as condiçoes das iterações
        iteracoesSemMudanca = iteracoesSemMudanca + 1;
        if((melhorSolucao.size() > solucao.size()) || melhorSolucao.size() == 0)
        {
            melhorSolucao = solucao;
            iteracoesSemMudanca = 0;
        }
        *iteracoes = *iteracoes + 1;
    }
    return melhorSolucao;
}

//randomiza as posições no guloso randomizado
int Grafo::randomizaValor(int tamanho, float alfa)
{

    int value = ((tamanho - 1) * alfa);
    int x;
    if(value != 0)
    {
        return (rand()%value);
    }
    else
    {
        return 0;
    }
}

//quickSort para o algoritmo guloso
void Grafo::quickSortGuloso(vector<No>&candidatos, vector<int>&graus, int menorIndice, int maiorIndice)
{

    if(menorIndice<maiorIndice)
    {
        int pi = particaoGuloso(candidatos,graus,menorIndice,maiorIndice);
        quickSortGuloso(candidatos,graus,menorIndice,pi-1);
        quickSortGuloso(candidatos,graus,pi+1,maiorIndice);
    }

}

//auxiliar quickSortGuloso
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

