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

        vector<int> profundidadePrimeiraBusca(vector<int> listaVertices ,int ordemGrafo,int posicao,int *cont);
        vector<int> auxBusca(vector<int> listaVertices,int idNo,int *cont);
        vector<int> amplitudePrimeiraBusca(queue<int> *filaVertices, int idNo, vector<int>verticesVisitados,int *cont);
        vector<No> retornaListaOrdenada();
        vector<No>algoritmoPrim();
        vector<No>auxAlgoritmoPrim(vector<No>Prim,No noAtual,No noAlvo);
        int ehAdjacente(int idOrigem,int idAlvo);
         Grafo* getComplemento();
        Grafo* getSubjacente();
        bool PossuiCiclo();
        bool GrafoConectado();
        float** floydMarshall();
        void dijkstra(int id);

    private:
        //Auxiliar methods

};

#endif // GRAPH_H_INCLUDED
