/**************************************************************************************************
 * Implementation of the TAD Edge
**************************************************************************************************/

#ifndef ARESTA_H_INCLUDED
#define ARESTA_H_INCLUDED

using namespace std;

// Definition of the Edge class
class Aresta{

    // Attributes
    private:
        int id_alvo;
        Aresta* proxima_aresta;
        float peso;

    public:
        // Constructor
        Aresta(int id_alvo);
        // Destructor
        ~Aresta();
        // Getters
        int getIdAlvo();
        Aresta* getProximaAresta();
        float getPeso();
        // Setters
        void setProximaAresta(Aresta* aresta);
        void setPeso(float peso);

};

#endif // EDGE_H_INCLUDED
