#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED

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
