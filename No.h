/**************************************************************************************************
 * Implementation of the TAD No
**************************************************************************************************/

#ifndef NO_H_INCLUDED
#define NO_H_INCLUDED
#include "Aresta.h" // Include of the Aresta class

using namespace std;

// Definition of the No class
class No{

    // Attributes
    private:
        //Aresta* primeira_aresta;
        //Aresta* ultima_aresta;*/
        int id;
        int grau;
        /*unsigned int grau_entrada;
        unsigned int grau_saida;
        float peso;*/
        No* proximo_no;
        Aresta *aresta;

    public:
        // Construtor
        No(int id);
        // Destrutor
        ~No();
        // Getters
        Aresta* getPrimeiraAresta();
        Aresta* getUltimaAresta();
        void setId(int id);
        int getId();
        int getGrauEntrada();
        int getGrauSaida();


        float getPeso();
        No* getProximoNo();
        // Setters
        void setProximoNo(No* no);
        void setPeso(float peso);
        void setGrau();
        int getGrau();
        // Other methods
        bool buscarAresta(int id_alvo);
        Aresta *getAresta();

        void setAresta(Aresta *aresta);
        void removeTodasArestas();

        int  removeAresta(int id, bool direcao, No* no_alvo);
        void incrementaGrauSaida();
        void decrementaGrauSaida();
        void incrementaGrauEntrada();
        void decrementaGrauEntrada();
        Aresta* possuiArestaEntre(int id_alvo);
        // Auxiliar methods

};

#endif // NO_H_INCLUDED
