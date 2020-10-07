#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <utility>
#include <tuple>
#include <iomanip>
#include <stdlib.h>
#include <chrono>
#include "Grafo.h"
#include "No.h"

using namespace std;

Grafo* leitura(ifstream& arquivo_entrada, int direcao, int aresta_ponderada, int no_ponderado){

    //Variáveis para auxiliar na criação dos nós no Grafo
    int idNoFonte;
    int idNoAlvo;
    int ordem;

    //Pegando a ordem do grafo
    arquivo_entrada >> ordem;

    //Criando objeto grafo
    Grafo* grafo = new Grafo(ordem, direcao, aresta_ponderada, no_ponderado);

    //Leitura de arquivo

    if(!grafo->getArestaPonderada() && !grafo->getNoPonderado()){

        while(arquivo_entrada >> idNoFonte >> idNoAlvo) {

            grafo->insereAresta(idNoFonte, idNoAlvo, 0);

        }

    }else if(grafo->getArestaPonderada() && !grafo->getNoPonderado() ){

        float pesoAresta;

        while(arquivo_entrada >> idNoFonte >> idNoAlvo >> pesoAresta) {

            grafo->insereAresta(idNoFonte, idNoAlvo, pesoAresta);

        }

    }else if(grafo->getNoPonderado() && !grafo->getArestaPonderada()){

        float pesoNoFonte, pesoNoAlvo;

        while(arquivo_entrada >> idNoFonte >> pesoNoFonte >> idNoAlvo >> pesoNoAlvo) {

            grafo->insereAresta(idNoFonte, idNoAlvo, 0);
            grafo->getNo(idNoFonte)->setPeso(pesoNoFonte);
            grafo->getNo(idNoAlvo)->setPeso(pesoNoAlvo);

        }

    }else if(grafo->getNoPonderado() && grafo->getArestaPonderada()){

        float pesoNoFonte, pesoNoAlvo, pesoAresta;

        while(arquivo_entrada >> idNoFonte >> pesoNoFonte >> idNoAlvo >> pesoNoAlvo) {

            grafo->insereAresta(idNoFonte, idNoAlvo, pesoAresta);
            grafo->getNo(idNoFonte)->setPeso(pesoNoFonte);
            grafo->getNo(idNoAlvo)->setPeso(pesoNoAlvo);

        }

    }

    return grafo;
}

Grafo* leituraInstancia(ifstream& arquivo_entrada, int direcao, int aresta_ponderada, int no_ponderado){

    //Variáveis para auxiliar na criação dos nós no Grafo
    int idNoFonte;
    int idNoAlvo;
    int ordem;
    int numeroArestas;

    //Pegando a ordem do grafo
    arquivo_entrada >> ordem >> numeroArestas;

    //Criando objeto grafo
    Grafo* grafo = new Grafo(ordem, direcao, aresta_ponderada, no_ponderado);

    //Leitura de arquivo
    while(arquivo_entrada >> idNoFonte >> idNoAlvo) {

        grafo->insereAresta(idNoFonte, idNoAlvo, 0);

    }

    return grafo;
}

int menu(){

    int selecao;

    cout << "MENU" << endl;
    cout << "----" << endl;
    cout << "[1] Complementar do grafo" << endl;
    cout << "[2] Imprimir caminhamento em largura" << endl;
    cout << "[3] Busca em profundidade" << endl;
    cout << "[4] Imprimir componentes conexas" << endl;
    cout << "[5] Imprimir componentes fortemente conexas" << endl;
    cout << "[6] Imprimir ordenacao topológica" << endl;
    cout << "[7] Guloso Randomizado Reativo" << endl;
    cout << "[8] Árvore Geradora Mínima de Prim" << endl;
    cout << "[9] Caminho Mínimo Dijkstra" << endl;
    cout << "[10] Caminho Mínimo Floyd" << endl;
    cout << "[0] Sair" << endl;

    cin >> selecao;

    return selecao;

}

void selecionar(int selecao, Grafo* grafo, ofstream& arquivo_saida){

    switch (selecao) {

        //Complementar
        case 1:{

            break;
        }

        //BFS
        case 2:{

            break;
        }

        //DFS
        case 3:{

            break;
        }

        //Componentes Conexas
        case 4:{



            break;
        }

        //Componentes Fortementes Conexas
        case 5:{

            break;
        }

        //Ordenação Topológica
        case 6:{

            break;
        }

        case 7:{


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

int mainMenu(ofstream& arquivo_saida, Grafo* grafo){

    int selecao = 1;

    while(selecao != 0){
        system("clear");
        selecao = menu();

        if(arquivo_saida.is_open())
            selecionar(selecao, grafo, arquivo_saida);

        else
            cout << "Unable to open the output_file" << endl;

        arquivo_saida << endl;

    }

    return 0;
}



int main(int argc, char const *argv[]) {

    //Verificação se todos os parâmetros do programa foram entrados
    if (argc != 6) {

        cout << "ERROR: Esperado: ./<nome_programa> <arquivo_entrada> <arquivo_saida> <direcao> <aresta_ponderada> <no_ponderado> " << endl;
        return 1;

    }

    string nome_programa(argv[0]);
    string nome_arquivo_entrada(argv[1]);

    string instancia;
    if(nome_arquivo_entrada.find("v") <= nome_arquivo_entrada.size()){
        instancia = nome_arquivo_entrada.substr(nome_arquivo_entrada.find("v"));
        cout << "Running " << nome_programa << " with instance " << instancia << " ... " << endl;
    }

    //Abrindo arquivo de entrada
    ifstream arquivo_entrada;
    ofstream arquivo_saida;
    arquivo_entrada.open(argv[1], ios::in);
    arquivo_saida.open(argv[2], ios::out | ios::trunc);



    Grafo* grafo;

    if(arquivo_entrada.is_open()){

        grafo = leituraInstancia(arquivo_entrada, atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));

    }else
        cout << "Unable to open " << argv[1];


    mainMenu(arquivo_saida, grafo);



    //Fechando arquivo de entrada
    arquivo_entrada.close();

    //Fechando arquivo de saída
    arquivo_saida.close();

    return 0;
}

