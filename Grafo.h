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

using namespace std;

class Grafo{

    //Atributes
    private:
//        list<No> *vertices;
        int ordem;
        int numero_arestas;
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
        bool getDirecao();
        bool getArestaPonderada();
        bool getNoPonderado();
        No* getPrimeiroNo();
        No* getUltimoNo();
        //Other methods
        void criaLista(int ordem);
        void insereNo(int idNoFonte, int idNoAlvo);
        void insereAresta(int id, int id_alvo, float peso);
        void removeNo(int id);
        bool buscaNo(int id);
        No* getNo(int id);
        bool profundidadePrimeiraBusca(int idInicial,int idAlvo);
        void amplitudePrimeiraBusca(ofstream& arquivo_saida);
        Grafo* getComplemento();
        Grafo* getSubjacente();
        bool PossuiCiclo();
        bool GrafoConectado();
        float** floydMarshall();
        float* dijkstra(int id);

    private:
        //Auxiliar methods

};

#endif // GRAPH_H_INCLUDED
