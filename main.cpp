#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <list>
#include <utility>
#include <tuple>
#include <iomanip>
#include <stdlib.h>
#include <chrono>
#include "Grafo.h"
#include "No.h"

using namespace std;

Grafo* leituraInstancia(ifstream& arquivo_entrada)
{

    //Vari�veis para auxiliar na cria��o dos n�s no Grafo
    int idNoFonte;
    int idNoAlvo;
    int ordem;
    int numeroArestas;
    int peso;

    //Pegando a ordem do grafo
    arquivo_entrada >> ordem;

    //Criando objeto grafo
    Grafo* grafo = new Grafo(ordem);

    grafo->criaLista(ordem);

    cout<<endl;

    //Leitura de arquivo
    while(arquivo_entrada >> idNoFonte >> idNoAlvo >> peso)
    {

        grafo->insereNo(idNoFonte,idNoAlvo);

    }

    for(list<No>::iterator it = grafo->vertices->begin(); it != grafo->vertices->end(); ++it)
    {
        No *aux = new No(it->getId());
        aux->setProximoNo(it->getProximoNo());
        cout<<aux->getId();
        cout<<" "<<endl;

        while(aux->getProximoNo())
        {
            aux->setId(aux->getProximoNo()->getId());
            aux->setProximoNo((aux->getProximoNo()->getProximoNo()));
            cout<<aux->getId();
            cout<<" ";
        }
        cout<<endl;
        cout<<endl;

    }

    cout<<endl;
    cout<<"Numero de Arestas: ";
    cout<<grafo->getNumeroArestas();
    cout<<endl;

    return grafo;
}

int menu()
{

    int selecao;

    cout << "MENU" << endl;
    cout << "----" << endl;
    cout << "[1] Complementar do grafo" << endl;
    cout << "[2] Imprimir caminhamento em largura" << endl;
    cout << "[3] Busca em profundidade" << endl;
    cout << "[4] Imprimir componentes conexas" << endl;
    cout << "[5] Imprimir componentes fortemente conexas" << endl;
    cout << "[6] Imprimir ordenacao topol�gica" << endl;
    cout << "[7] Guloso Randomizado Reativo" << endl;
    cout << "[8] �rvore Geradora M�nima de Prim" << endl;
    cout << "[9] Caminho M�nimo Dijkstra" << endl;
    cout << "[10] Caminho M�nimo Floyd" << endl;
    cout << "[0] Sair" << endl;

    cin >> selecao;

    return selecao;

}

void selecionar(int selecao, Grafo* grafo, ofstream& arquivo_saida)
{

    switch (selecao)
    {

    //Complementar
    case 1:
    {

        break;
    }

    //BFS
    case 2:
    {

        break;
    }

    //DFS
    case 3:
    {
        vector<int>listaVertices(grafo->getOrdem());
        int cont=1;
        listaVertices = grafo->profundidadePrimeiraBusca(listaVertices,grafo->getOrdem(),0,&cont);

        int i = 0;

       /*  for (vector<int>::iterator it = listaVertices.begin(); it != listaVertices.end(); ++it)
        {
            cout<<"imprimindo IT: "<<listaVertices[i]<<endl;

            i++;

        }
        */

        break;
    }

    //Componentes Conexas
    case 4:
    {



        break;
    }

    //Componentes Fortementes Conexas
    case 5:
    {

        break;
    }

    //Ordena��o Topol�gica
    case 6:
    {

        break;
    }

    case 7:
    {


        break;
    }

    //Algoritmo de Prim
    case 8:
    {

        break;
    }

    //Algoritmo de Dijkstra
    case 9:
    {

        break;
    }

    //Algoritmo de Floyd
    case 10:
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



int main(int argc, char const *argv[])
{

    //Verifica��o se todos os par�metros do programa foram entrados
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



    Grafo* grafo;

    if(arquivo_entrada.is_open())
    {

        grafo = leituraInstancia(arquivo_entrada);

    }
    else
        cout << "Unable to open " << argv[1];


    mainMenu(arquivo_saida, grafo);



    //Fechando arquivo de entrada
    arquivo_entrada.close();

    //Fechando arquivo de sa�da
    arquivo_saida.close();

    return 0;
}

