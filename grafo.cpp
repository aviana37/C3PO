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

Grafo::Vertice::Vertice()
{
    v_adj = NULL;
    cor=BRANCO;
    ant=-1;
    descoberta=0;
    termino=0;
}
Grafo::Vertice::~Vertice()
{
    if(v_adj)delete v_adj;
}
void Grafo::Vertice::AdicionarVerticeAdj(int v)
{
    if(!v_adj)
        v_adj=new std::vector<int>;
    v_adj->push_back(v);
}
bool Grafo::Vertice::ProximoVerticeAdj(int* adj)
{
    static int atual=-1;
    if(v_adj && adj)
    {
        atual++;
        if(atual>=v_adj->size())
            return false;
        *adj=v_adj->at(atual);
        return true;
    }
    if(!adj)
        atual=-1;
    return false;
}


Grafo::Grafo(int n_vertices, Aresta* vetor, int n_conexoes)
{
    if(vetor)
    {
        this->aciclico = true;
        this->n_vertices = n_vertices;
        this->n_arestas = n_conexoes;

        //Instanciando vetor de vértices
        vertices = new Vertice[n_vertices];
        for(int v=0; v<n_conexoes; v++)
            vertices[vetor[v].a].AdicionarVerticeAdj(vetor[v].b);

        //Inicializando matriz de adjacencias
        matriz_adj = new bool*[n_vertices];
        for(int c=0; c<n_vertices; c++)
        {
            matriz_adj[c]=new bool[n_vertices];

            for(int d=0; d<n_vertices; d++)
                matriz_adj[c][d] = false;

        }

        for(int e=0; e<n_conexoes; e++)
            matriz_adj[vetor[e].a][vetor[e].b] = true;

        matriz_inc = new int*[n_arestas];

        for(int h=0; h<n_arestas; h++)
        {
            matriz_inc[h] = new int[n_vertices];
            for(int i=0; i<n_vertices; i++)
                matriz_inc[h][i]=0;
        }

        int linha=0;
        for(int f=0; f<n_arestas; f++)
        {
            matriz_inc[linha][vetor[f].b]++;
            matriz_inc[linha][vetor[f].a]++;
            linha++;
        }

    }
    else
    {
        vertices = NULL;
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
        for(int f=0; f<n_vertices; f++)
            delete [] matriz_adj[f];
        delete [] matriz_adj;
    }
    if(matriz_inc)
    {
        for(int e=0; e<n_vertices; e++)
            delete [] matriz_inc[e];
        delete [] matriz_inc;
    }
    if(vertices)
        delete [] vertices;
}

void Grafo::_Profundidade_R(int v)
{
    static int tempo=0;
    if(vertices[v].cor == Vertice::BRANCO)
    {
        tempo++;
        vertices[v].descoberta=tempo;
        vertices[v].cor=Vertice::CINZA;
    }

    int atual;
    vertices[v].ProximoVerticeAdj(NULL);
    while(vertices[v].ProximoVerticeAdj(&atual))
    {
        if(vertices[atual].ant==-1)
            vertices[atual].ant=v;

        if(vertices[atual].cor == Vertice::CINZA)
            aciclico=false;
        if(vertices[atual].cor == Vertice::BRANCO)
            _Profundidade_R(atual);
    }

    tempo++;
    vertices[v].termino=tempo;
    vertices[v].cor=Vertice::PRETO;
}

int Grafo::PercursoProfundidade(int raiz)
{
    int comp=0;
    for(int c=0; c<n_vertices; c++)
    {
        vertices[c].cor = Vertice::BRANCO;
        vertices[c].ant = -1;
    }

    if(raiz)
    {
        comp++;
        _Profundidade_R(raiz);
    }

    for(int c=0; c<n_vertices; c++)
    {
        if(vertices[c].cor == Vertice::BRANCO)
        {
            comp++;
            _Profundidade_R(c);
        }
    }
    return comp;
}

void Grafo::PercursoLargura(int raiz)
{
    for(int c=0; c<n_vertices; c++)
    {
        vertices[c].cor = Vertice::BRANCO;
        vertices[c].ant = -1;
    }
    if(!raiz)
    {
        for(int c=0; c<n_vertices; c++)
        {
            if(vertices[c].cor == Vertice::BRANCO)
            {
                vertices[c].cor=Vertice::CINZA;
                vertices[c].descoberta=0;
                std::queue<int>* fila=new std::queue<int>;
                fila->push(c);

                int atual, v;
                while(!fila->empty())
                {
                    atual = fila->front();
                    fila->pop();
                    vertices[atual].ProximoVerticeAdj(NULL);
                    while(vertices[atual].ProximoVerticeAdj(&v))
                    {
                        if(vertices[v].cor==Vertice::BRANCO)
                        {
                            vertices[v].cor = Vertice::CINZA;
                            vertices[v].descoberta = vertices[atual].descoberta+1;
                            vertices[v].ant = atual;
                            fila->push(v);
                        }
                    }
                }

                vertices[c].cor = Vertice::PRETO;
                delete fila;
            }
        }
    }
    else
    {
        vertices[raiz].cor=Vertice::CINZA;
        vertices[raiz].descoberta=0;
        std::queue<int>* fila=new std::queue<int>;
        fila->push(raiz);

        int atual, v;
        while(!fila->empty())
        {
            atual = fila->front();
            fila->pop();
            vertices[atual].ProximoVerticeAdj(NULL);
            while(vertices[atual].ProximoVerticeAdj(&v))
            {
                if(vertices[v].cor==Vertice::BRANCO)
                {
                    vertices[v].cor = Vertice::CINZA;
                    vertices[v].descoberta = vertices[atual].descoberta+1;
                    vertices[v].ant = atual;
                    fila->push(v);
                }
            }
        }

        vertices[raiz].cor = Vertice::PRETO;
        delete fila;
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
