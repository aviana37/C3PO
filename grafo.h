#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED

/*André Viana Sena de Souza - 25037
**Projeto e Análise de Algoritmos - ECO027
**Projeto #3 - C3PO - 10/11/2014
**Arquivo: grafo.h
**Descrição: Define o tipo Grafo, seus subtipos, métodos de iteração, e uma função para carregamento de arquivos.
*/

/** \file grafo.h
    \brief Definições do tipo Grafo e seus métodos auxiliares.
    \details Implementação em grafo.cpp

    \struct Grafo::Aresta
    \brief Estrutura de aresta.
    \details Útil durante a construção dos objetos Grafo.

    \var Grafo::Aresta::a
    Vértice inicial.
    \var Grafo::Aresta::b
    Vértice final.
    \fn bool Grafo::Aresta::operator==(Aresta &outro)
    \brief Overload do operador de igualidade.
    \return Retorna true somente caso as arestas sejam iguais ou opostas.


    \struct Grafo::Vertice
    \brief Estrutura de vértice.
    \details Útil quando é necessário percorrer vértices do Grafo.\n
    É altamente recomendado utilizar os métodos AdicionarVerticeAdj(int v) e ProximoVerticeAdj(int *adj),
     pois eles simplificam o acesso à lista de vértices adjacentes drasticamente.

    \enum Grafo::Vertice::Cor
    \brief Cores dos vértices.
    \details Métodos de percurso em profundidade e largura se utilizam
     deste sistema de cores para evitar self-loops e outros problemas de otimização em sua execução.

    \var Grafo::Vertice::ant
    Aponta para o vértice anterior, de acordo com o último percurso utilizado. Se o valor dessa variável for -1,
     o vértice não possui antecessores.
    \var Grafo::Vertice::descoberta
    Guarda o valor do tempo de descoberta, de acordo com o último percurso realizado.
    \var Grafo::Vertice::termino
    Guarda o valor do tempo em que todos os vértices adjacentes à este foram processados durante o último percurso.
    \var Grafo::Vertice::cor
    A cor do vértice.
    \var Grafo::Vertice::v_adj
    Estrutura dinâmica que armazena todos os vértices adjacentes à este.

    \fn void Grafo::Vertice::AdicionarVerticeAdj(int v)
    \brief Adiciona um vértice v à lista de vértices adjacentes.
    \details Instancia v_adj* caso seja nulo.
    \param v Vértice a ser adicionado.

    \fn bool Grafo::Vertice::ProximoVerticeAdj(int* adj)
    \brief Permite iterar pela lista de vértices adjacentes através de um while.
    \details Chamadas com adj NULL zeram o iterador interno. Quando adj é não-nulo,
     ele passa a apontar para o próximo vértice adjacente da lista. Enquanto for possível fazer essas atribuições,
     o método retorna true, se não, false.
    \param adj Ponteiro a ser atribuído valor.
    \return TRUE caso adj recebeu um vértice.\nFALSE caso a lista tenha terminado.

    \struct Grafo
    \brief Estrutura base do grafo.
    \details Dispõe de todos os métodos, variáveis, e subtipos necessários para manipulação de grafos.

    \var Grafo::aciclico
    Armazena se o grafo é acíclico ou não. O valor default é true, mas também é atualizado durante o percurso de profundidade,
     quando arestas de retorno são descobertas.
    \var Grafo::matriz_adj
    Matriz de adjacências n_vertices x n_vertices. Instanciada no construtor.
    \var Grafo::matriz_inc
    Matriz de incidência n_vertices x n_arestas. Instanciada no construtor.
    \var Grafo::vertices
    Vetor de vértices do grafo.
    \var Grafo::n_vertices
    Quantidade de vértices no grafo.
    \var Grafo::n_arestas
    Quantidade de arestas no grafo.

    \fn Grafo::Grafo(int n_vertices, Aresta* vetor, int n_arestas)
    \brief Inicializa o grafo a partir do número de vertices e um vetor de arestas.
    \details Caso o ponteiro do vetor seja nulo, todos os componentes do grafo apontarão para NULL.\n
    Se n_vertices ou n_arestas terem valor zero,

    \fn Grafo::~Grafo()
    \brief Desaloca todos os recursos utilizados.
    \details Ignora ponteiros nulos.

    \fn void Grafo::_Profundidade_R(int vertice)
    \brief Função recursiva utilizada no método Grafo::PercursoProfundidade.
    \details Percorre os vértices em profundidade, recursivamente, a partir do parâmetro vértice.
    Determina os valores internos de cada vértice para interpretação posterior.\n
    A recursão para quando todos os vértices brancos de vértice foram processados.\n
    Se durante sua execução arestas de retorno forem encontradas, acíclico recebe valor FALSE.

    \fn int Grafo::PercursoProfundidade(int raiz)
    \brief Inicia o percurso em profundidade a partir da raiz especificada.
    \details Inicializa todos os vértices para branco, e seus antecessores para -1.\n
    Caso raiz tenha sido especificada, somente o componente raiz será processado.\n
    Se a raiz for 0, todos os componentes serão processados.\n
    \param raiz Tem como valor default 0.
    \return Retorna a quantidade de componentes encontrados.

    \fn void Grafo::PercursoLargura(int raiz)
    \brief Inicia o percurso em largura a partir da raiz especificada.
    \details Inicializa todos os vértices para branco, e seus antecessores para -1.\n
    Começa o percurso a partir de raiz, enfileirando cada vértice encontrado e, logo após,
     processando-os.
    \param raiz Tem como valor default 0.

    \fn Grafo* CarregarArquivo(const char* arquivo)
    \brief Carrega um grafo a partir de arquivo.
    \param arquivo Endereço do arquivo.
    \return Ponteiro para um objeto Grafo ou NULL caso o arquivo seja inválido.

*/

#include <stddef.h>
#include <stdio.h>
#include <vector>
#include <queue>

struct Grafo
{
    struct Aresta
    {
        int a, b;
        bool operator==(Aresta &outro);
    };

    struct Vertice
    {
        enum Cor
        {
            BRANCO,
            CINZA,
            PRETO,
        };

        int ant;
        int descoberta;
        int termino;
        Cor cor;
        std::vector<int>* v_adj;

        void AdicionarVerticeAdj(int v);
        bool ProximoVerticeAdj(int* adj);

        Vertice();
        ~Vertice();
    };

    bool aciclico;
    bool** matriz_adj;
    int** matriz_inc;
    Vertice* vertices;

    int n_vertices;
    int n_arestas;

    Grafo(int n_vertices, Aresta* vetor, int n_arestas);
    ~Grafo();

    void _Profundidade_R(int vertice);
    int PercursoProfundidade(int raiz=0);

    void PercursoLargura(int raiz=0);
};

Grafo* CarregarArquivo(const char* arquivo);

#endif // GRAFO_H_INCLUDED
