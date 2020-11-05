#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <list>
#include <queue>
#include <utility>
#include <tuple>
#include <iomanip>
#include <stdlib.h>
#include <chrono>
#include <string>
#include "Grafo.h"
#include "No.h"



using namespace std;

Grafo* leituraInstancia(ifstream& arquivo_entrada,ofstream *arquivo_saida)
{

    //Variaveis para auxiliar na criação dos nós no Grafo
    int idNoFonte;
    int idNoAlvo;
    int ordem;
    int peso;

    //Pegando a ordem do grafo
    arquivo_entrada >> ordem;

    //Criando objeto grafo
    Grafo* grafo = new Grafo(ordem);

    grafo->criaLista(ordem);

    cout<<endl;

    //Leitura dos nós
    while(arquivo_entrada >> idNoFonte >> idNoAlvo >> peso)
    {
        //verifica se é um self-loop
        if(idNoFonte != idNoAlvo)
        {
            grafo->insereNo(idNoFonte,idNoAlvo,peso);
        }

    }

    //impressão do grafo

    for(list<No>::iterator it = grafo->vertices->begin(); it != grafo->vertices->end(); ++it)
    {
        No *aux = new No(it->getId());
        aux->setProximoNo(it->getProximoNo());
        cout<<aux->getId();
        cout<<" "<<endl;

        while(aux->getProximoNo() !=0)
        {
            aux->setId(aux->getProximoNo()->getId());
            aux->setAresta(aux->getProximoNo()->getAresta());
            aux->setProximoNo((aux->getProximoNo()->getProximoNo()));
            cout<<aux->getId();
            cout<<" ";

        }
        cout<<endl;
        cout<<endl;

    }

    return grafo;
}


int menu()
{

    int selecao;

    cout << "MENU" << endl;
    cout << "----" << endl;
    cout << "[1] Imprimir caminhamento em largura" << endl;
    cout << "[2] Busca em profundidade" << endl;
    cout << "[3] Arvore Geradora minima de Kruskal" << endl;
    cout << "[4] arvore Geradora Minima de Prim" << endl;
    cout << "[5] Caminho Minimo Dijkstra" << endl;
    cout << "[6] Caminho Minimo Floyd" << endl;
    cout << "[7] Guloso Randomizado Reativo" << endl;
    cout << "[0] Sair" << endl;

    cin >> selecao;

    return selecao;

}

void selecionar(int selecao, Grafo* grafo, ofstream& arquivo_saida)
{

    switch (selecao)
    {

    //BFS
    case 1:
    {

        queue<int>filaVertices;
        filaVertices.push(0);
        vector<int>verticesVisitados(grafo->getOrdem());
        int i = 0;
        for (vector<int>::iterator it = verticesVisitados.begin(); it != verticesVisitados.end(); ++it)
        {
            verticesVisitados[i] = -1;
            i++;
        }
        int cont = 0;
        int No = 0;
        cout<<"digite o No origem: ";
        cin>>No;
        verticesVisitados = grafo->amplitudePrimeiraBusca(&filaVertices, No, verticesVisitados, &cont);
        i = 0;
        for (vector<int>::iterator it = verticesVisitados.begin(); it != verticesVisitados.end(); ++it)
        {
            cout<<"imprimindo vertices visitados na busca por amplitude: "<<verticesVisitados[i]<<endl;

            i++;

        }

        break;
    }

    case 2:
    {
        vector<int>listaVertices(grafo->getOrdem());
        int cont=0;
        int No = 0;
        int i = 0;
        for (vector<int>::iterator it = listaVertices.begin(); it != listaVertices.end(); ++it)
        {
            listaVertices[i] = -1;
            i++;
        }
        cout<<"digite o No origem: ";
        cin>>No;
        listaVertices = grafo->profundidadePrimeiraBusca(listaVertices,grafo->getOrdem(),No,&cont);

        i = 0;

        for (vector<int>::iterator it = listaVertices.begin(); it != listaVertices.end(); ++it)
        {
            cout<<"imprimindo vertices visitados na busca por profundidade: "<<listaVertices[i]<<endl;

            i++;

        }


        break;
    }

    //Algoritmo de Kruskal
    case 3:
    {
        grafo->kruskal();

        break;
    }

    //Algoritmo de Prim
    case 4:
    {

        vector<No> Prim = grafo->algoritmoPrim();
        int cont=0;
        for(int i=0; i<Prim.size(); i++)
        {
            cout<<Prim[i].getAresta()->getIdOrigem() << " | " <<Prim[i].getAresta()->getIdAlvo();
            cout<< " Peso:" << Prim[i].getAresta()->getPeso()<<endl;
            cont += Prim[i].getAresta()->getPeso();
        }
        cout<<"PESO RESULTANTE:" << cont<<endl;
        Prim.clear();
        break;
    }

    //Caminho minimo de djikstra
    case 5:
    {
        int id;
        cout<<"digite o vertice inicial: ";
        cin>>id;
        grafo->dijkstra(id);
        break;
    }

    //Algoritmo de Floyd
    case 6:
    {
        grafo->floydMarshall();
        break;
    }

    case 7:
    {
        break;
    }
    }
}

int mainMenu(ofstream& arquivo_saida, Grafo* grafo)
{

    int selecao = 1;

    while(selecao != 0)
    {
        //system("cls");
        selecao = menu();

        if(arquivo_saida.is_open())
            selecionar(selecao, grafo, arquivo_saida);

        else
            cout << "Unable to open the output_file" << endl;

        arquivo_saida << endl;

    }

    return 0;
}


/*
XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
X                                                                                                                                                               X
X   Alunos: Guilherme Marques, Gabriel Bronte, Daniel Machado, Giovane Nilmer, Marcos Mateus, Anthony Lima                                                      X                                                                                                     X                                                                                                                                                              X
X                                                                                                                                                               X
XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
 */


int main(int argc, char const *argv[])
{



    //Verificando se todos os parametros do programa foram inseridos
    if (argc != 3)
    {

        cout << "ERROR: Esperado: ./<nome_programa> <arquivo_entrada> <arquivo_saida>" << endl;
        return 1;

    }

    string nome_programa(argv[0]);
    string nome_arquivo_entrada(argv[1]);

    string instancia;
    if(nome_arquivo_entrada.find("v") <= nome_arquivo_entrada.size())
    {
        instancia = nome_arquivo_entrada.substr(nome_arquivo_entrada.find("v"));
        cout << "Running " << nome_programa << " with instance " << instancia << " ... " << endl;
    }

    //Abrindo arquivo de entrada
    ifstream arquivo_entrada;
    ofstream arquivo_saida;
    arquivo_entrada.open(argv[1], ios::in);
    arquivo_saida.open(argv[2], ios::out | ios::trunc);


    //criando grafo
    Grafo* grafo;

    if(arquivo_entrada.is_open())
    {

        grafo = leituraInstancia(arquivo_entrada, &arquivo_saida);

    }
    else
    {
        cout << "Unable to open " << argv[1];
        return 0;
    }

    //chamando funções para escrever no arquivo de texto
    arquivo_saida << grafo->getOrdem()<<"\n";
    arquivo_saida << grafo->getNumeroArestas()<<"\n";
    arquivo_saida << grafo->getGrauMedioGrafo()<<"\n";
    grafo->getFrequenciaRelativa(arquivo_saida, grafo->getOrdem());


    mainMenu(arquivo_saida, grafo);



    //Fechando arquivo de entrada
    arquivo_entrada.close();

    //Fechando arquivo de sa�da
    arquivo_saida.close();

    return 0;
}

