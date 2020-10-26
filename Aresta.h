/**************************************************************************************************
 * Implementation of the TAD Edge
**************************************************************************************************/

#ifndef ARESTA_H_INCLUDED
#define ARESTA_H_INCLUDED
using namespace std;

// Definição da classe Aresta
class Aresta{

    // Attributes
    private:
        int id_origem;
        int id_alvo;
        Aresta* proxima_aresta;
        float peso;
        bool verificaA;

    public:
        // Construtor
        Aresta(int id_origem, int id_alvo);
        // Destrutor
        ~Aresta();
        // Getters
        int getIdAlvo();
        Aresta* getProximaAresta();
        float getPeso();
        // Setters
        void setProximaAresta(Aresta* aresta);
        void setPeso(float peso);
        bool getVerificaAresta();
        void setVerificaAresta();
};

#endif // EDGE_H_INCLUDED
