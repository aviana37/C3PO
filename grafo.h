#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED

#include <stddef.h>
#include <stdio.h>

struct Grafo
{
    struct Aresta
    {
        int a, b;
        bool operator==(Aresta &outro);
    };

    bool** matriz_adj;
    int** matriz_inc;

    int n_vertices;
    int n_arestas;

    Grafo(int n_vertices, Aresta* vetor, int n_arestas);
    ~Grafo();
};

Grafo* CarregarArquivo(const char* arquivo);

#endif // GRAFO_H_INCLUDED
