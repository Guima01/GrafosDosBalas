/**************************************************************************************************
 * Implementation of the TAD Graph
**************************************************************************************************/

#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED
#include "No.h"
#include <fstream>
#include <stack>
#include <list>
#include <vector>
#include <queue>

using namespace std;

class Grafo{

    //Atributes
    private:
//        list<No> *vertices;
        int ordem;
        int numero_arestas;
        float grau_medio_grafo;
//        bool direcao;
//        bool aresta_ponderada;
//        bool no_ponderado;
        No* primeiro_no;
        No* ultimo_no;


    public:
        list<No> *vertices;
        //Constructor
        Grafo(int ordem);
        //Destructor
        ~Grafo();
        //Getters
        int getOrdem();
        int getNumeroArestas();
        float getGrauMedioGrafo();
        bool getDirecao();
        bool getArestaPonderada();
        bool getNoPonderado();
        No* getPrimeiroNo();
        No* getUltimoNo();
        void getFrequenciaRelativa(ofstream &arquivo_saida, int ordem);
        //Other methods
        void criaLista(int ordem);
        void insereNo(int idNoFonte, int idNoAlvo, float peso);
        void insereAresta(int id, int id_alvo, float peso);
        void removeNo(int id);
        bool buscaNo(int id);
        No* getNo(int id);

        void insereGulosamente(int idNoFonte, int idNoAlvo);

        vector<int> profundidadePrimeiraBusca(vector<int> listaVertices ,int ordemGrafo,int posicao,int *cont);
        vector<int> auxBusca(vector<int> listaVertices,int idNo,int *cont);
        void larguraPrimeiraBusca(int vertice);

        No alteraVetProx(vector<No>vetProx,int noAtual,int noAlvo);
        void algoritmoPrim();
        int getIndiceMin(vector<float>vetProx);
        float ehAdjacente(vector<No>vetAdj,int noOrigem,int noAlvo);

        vector<No> retornaListaOrdenadaGrau();
        void ordenaLista(vector<No> candidatos, vector<int> graus);

        void quickSort(vector<No> &vetorOrdenado,int menorIndice,int maiorIndice);
        int particao(vector<No>&vetorOrdenado,int menorIndice,int maiorIndice);
        vector<No> retornaListaOrdenada();

        void quickSortGuloso(vector<No>&candidatos, vector<int>&graus, int menorIndice, int maiorIndice);
        int particaoGuloso(vector<No>&candidatos, vector<int>&graus, int menorIndice, int maiorIndice);

        int randomizaValor(int tamanho, float alfa);

        bool GrafoConectado();
        void floydMarshall();
        void kruskal();
        void dijkstra(int id);
        void guloso();
        vector<int> gulosoRandomizado(float alfa, int *iteracoes);

    private:
        //Auxiliar methods

};

#endif // GRAPH_H_INCLUDED
