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
#include "time.h"



using namespace std;

Grafo* leituraGulosa(ifstream& arquivo_entrada)
{
    int ordem;
    string aux = "";
    arquivo_entrada >> aux;
    arquivo_entrada >> ordem;

    Grafo* grafo = new Grafo(ordem);
    grafo->criaLista(ordem);
    arquivo_entrada >> aux;
    while (aux != "*****************CONNECTIONS****************")
    {
        arquivo_entrada >> aux;
    }
    string delimiter = " ";
    size_t pos = 0;
    string token;
    int leitura = -1;
    arquivo_entrada >> leitura;
    for (int i = 0; i < ordem; i++)
    {
        for (int j = 0; j < ordem; j++, arquivo_entrada >> leitura)
        {
            if (leitura == 1 && i != j)
            {
                //cout << i << " - " << cont << endl;
                grafo->insereGulosamente(i, j);
            }
        }
    }

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




Grafo* leituraInstancia(ifstream& arquivo_entrada)
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
    cout << "[1] caminhamento em largura" << endl;
    cout << "[2] Busca em profundidade" << endl;
    cout << "[3] Arvore Geradora minima de Kruskal" << endl;
    cout << "[4] arvore Geradora Minima de Prim" << endl;
    cout << "[5] Caminho Minimo Dijkstra" << endl;
    cout << "[6] Caminho Minimo Floyd" << endl;
    cout << "[7] Guloso" << endl;
    cout << "[8] Guloso randomizado" << endl;
    cout << "[0] Sair" << endl;

    cin >> selecao;

    return selecao;

}

void selecionar(int selecao, Grafo* grafo, ofstream& arquivo_saida)
{

    switch (selecao)
    {

    //Busca em largura
    case 1:
    {
        int no;
        cout<<"digite o No origem: ";
        cin>>no;
        grafo->larguraPrimeiraBusca(no);
        break;
    }

    //busca em profundidade
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

        grafo->algoritmoPrim();

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

    //Algoritmo Guloso
    case 7:
    {
        grafo->guloso();
        break;
    }
    //Algoritmo Guloso Randomizado
    case 8:
    {
        vector<float> alfas = {0.1,0.2,0.3,0.5,0.7};
        for(int i = 0; i < alfas.size(); i++)
        {
            vector<int> solucoes;
            vector<int> solucao;
            double desvioPadrao = 0;
            double mediaQualidade = 0;
            double time = 0;
            int mediaInteracoes = 0;
            for(int j = 0; j < 10; j++)
            {
                int interacoes = 0;
                clock_t timeStart, timeStop;
                timeStart = clock();
                solucao = grafo->gulosoRandomizado(alfas[i], &interacoes);
                timeStop = clock();
                time = ((double)(timeStop - timeStart) / CLOCKS_PER_SEC) + time;
                solucoes.push_back(solucao.size());
                mediaQualidade = solucao.size() + mediaQualidade;
                mediaInteracoes = mediaInteracoes + interacoes;
            }
            mediaInteracoes = mediaInteracoes/10;
            mediaQualidade = mediaQualidade/10;
            time = time/10;
            for(int i = 0; i < solucoes.size(); i++)
            {
                desvioPadrao = ((pow((solucoes[i] - mediaQualidade),2)) / 10) + desvioPadrao;
            }
            desvioPadrao = sqrt(desvioPadrao);
            cout<<"tempo médio de Alfa ["<<alfas[i]<<"] : "<< time<<endl;
            cout<<"media de solucoes Alfa: ["<<alfas[i]<<"] : "<< mediaQualidade <<endl;
            cout<<"media de Interacoes ["<<alfas[i]<<"] : "<< mediaInteracoes <<endl;
            cout<<"Desvio padrão da qualidade ["<<alfas[i]<<"] : "<< desvioPadrao << endl<<endl;
        }
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

    srand(time(NULL));

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

    //verifica o formato do arquivo

    if(arquivo_entrada.is_open() )
    {
        if(nome_arquivo_entrada.find("Problem.dat") != string::npos)
        {
            grafo = leituraGulosa(arquivo_entrada);
        }
        else if(nome_arquivo_entrada.find("grafo") != string::npos)
        {
            grafo = leituraInstancia(arquivo_entrada);
        }
    }
    else
    {
        cout << "Unable to open " << argv[1];
        return 0;
    }

    //chamando funções para escrever no arquivo de texto
    //arquivo_saida << grafo->getOrdem()<<"\n";
    //arquivo_saida << grafo->getNumeroArestas()<<"\n";
    //arquivo_saida << grafo->getGrauMedioGrafo()<<"\n";
    //grafo->getFrequenciaRelativa(arquivo_saida, grafo->getOrdem());


    mainMenu(arquivo_saida, grafo);



    //Fechando arquivo de entrada
    arquivo_entrada.close();

    //Fechando arquivo de sa�da
    arquivo_saida.close();

    return 0;
}

