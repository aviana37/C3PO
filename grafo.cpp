#include "grafo.h"

bool Grafo::Aresta::operator==(Grafo::Aresta &outro)
{
    if(a == outro.a)
    {
        if(b==outro.b)
            return true;
    }
    else if(b==outro.a)
    {
        if(a==outro.b)
            return true;
    }
    return false;
}

Grafo::Grafo(int n_vertices, Aresta* vetor, int n_conexoes)
{
    if(vetor)
    {
        this->n_vertices = n_vertices;
        this->n_arestas = n_conexoes;
        matriz_inc = NULL;

        //Inicializando matriz de adjacencias
        matriz_adj = new bool*[n_vertices];
        for(int c=0; c<n_vertices; c++)
        {
            matriz_adj[c]=new bool[n_vertices];

            for(int d=0; d<n_vertices; d++)
                matriz_adj[c][d] = false;

        }

        for(int e=0;e<n_conexoes; e++)
            matriz_adj[vetor[e].a][vetor[e].b] = true;

        matriz_inc = new int*[n_arestas];

        for(int h=0;h<n_arestas;h++)
        {
            matriz_inc[h] = new int[n_vertices];
            for(int i=0;i<n_vertices;i++)
                matriz_inc[h][i]=0;
        }

        int linha=0;
        for(int f=0;f<n_arestas;f++)
        {
            matriz_inc[linha][vetor[f].b]++;
            matriz_inc[linha][vetor[f].a]++;
            linha++;
        }

    }
    else
    {
        matriz_adj = NULL;
        matriz_inc = NULL;
        n_vertices = 0;
        n_arestas = 0;
    }
}
Grafo::~Grafo()
{
    if(matriz_adj)
    {
        for(int f=0;f<n_vertices;f++)
            delete [] matriz_adj[f];
        delete [] matriz_adj;
    }
    if(matriz_inc)
    {
        for(int e=0;e<n_vertices;e++)
            delete [] matriz_inc[e];
        delete [] matriz_inc;
    }
}

Grafo* CarregarArquivo(const char* arquivo)
{
    FILE* file = fopen(arquivo, "r");
    if(!file)
        return NULL;

    int n_vertices;
    int vertice_atual;
    int adj;
    int c=0;
    fscanf(file, "%d", &n_vertices);

    while(fscanf(file, "%d", &vertice_atual)!=EOF)
        c++;
    c=c/2;
    Grafo::Aresta* Aresta = new Grafo::Aresta[c];
    c=0;

    rewind(file);
    fscanf(file, "%d", &n_vertices);

    while(fscanf(file, "%d", &vertice_atual)!=EOF)
    {
        fscanf(file, "%d", &adj);
        Aresta[c]= {vertice_atual, adj};
        c++;
    }

    fclose(file);

    Grafo* ret = new Grafo(n_vertices, Aresta, c);
    return ret;
}
