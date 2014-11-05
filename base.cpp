#include "base.h"

static Grafo* _grafo=NULL;
static MatrizesPlanetRank* _rank=NULL;

bool Grafo_Carregado()
{
    return _grafo;
}
int Grafo_Vertices(){return _grafo->n_vertices;}

void CalcularPlanetRank()
{
    if(!_rank)
    {
        _rank = new MatrizesPlanetRank;
        _rank->nv = _grafo->n_vertices;
        _rank->na = _grafo->n_arestas;

        _rank->Grau = new int[_rank->nv];
        _rank->PlanetRank = new float*[_rank->na];
        _rank->ProbAleatoria = new float*[_rank->na];
        _rank->ProbPlaneta = new float*[_rank->na];

        for(int f=0; f<_rank->na; f++)
        {
            _rank->PlanetRank[f] = new float[_rank->nv];
            _rank->ProbAleatoria[f] = new float[_rank->nv];
            _rank->ProbPlaneta[f] = new float[_rank->nv];
        }

        //Determinando valores na matriz de grau
        int soma;
        for(int f=0; f<_rank->nv; f++)
        {
            soma=0;
            for(int g=0; g<_rank->na; g++)
                soma = soma+_grafo->matriz_inc[g][f];
            _rank->Grau[f] = soma;
        }

        //Determinando valores na matriz de probabilidade do planeta
        float proporcao;
        for(int f=0; f<_rank->nv; f++)
        {
            proporcao = (float)0.9/_rank->Grau[f];
            for(int g=0; g<_rank->na; g++)
                _rank->ProbPlaneta[g][f] = (float) _grafo->matriz_inc[g][f]* proporcao;
        }

        //Determinando valores na matriz de probabilidade aleatoria
        for(int f=0;f<_rank->nv;f++)
        {
            proporcao=(float)0.1/_rank->na;
            for(int g=0; g<_rank->na; g++)
                _rank->ProbAleatoria[g][f] = proporcao;
        }

        //Determinando valores na matriz planet rank
        for(int f=0;f<_rank->nv;f++)
        {
            for(int g=0; g<_rank->na; g++)
                _rank->PlanetRank[g][f] = _rank->ProbPlaneta[g][f] + _rank->ProbAleatoria[g][f];
        }
    }
}
bool PlanetRankCalculado()
{
    return _rank;
}
int PlanetRank(int planeta, float* chance)
{
    if(planeta < _rank->nv)
    {
        int res=0;
        float* temp = new float[_rank->nv];

        for(int d=0; d<_rank->nv; d++)
        {
            if(_grafo->matriz_adj[d][planeta])
                temp[d]=1;
            else
                temp[d]=0;
        }

        for(int e=0;e<_rank->na;e++)
        {
            if(_rank->PlanetRank[e][planeta]>0.1)
            {
                for(int f=0;f<_rank->nv;f++)
                    temp[f]+=_rank->PlanetRank[e][f];
            }
        }

        for(int g=1;g<_rank->nv;g++)
        {
            if(temp[g]>temp[res])
                res=g;
        }

        if(chance)
            *chance=temp[res]-1;
        delete [] temp;
        return res;
    }
    return -1;
}

void ImprimirMatrizPA()
{
    if(_rank)
    {
        for(int f=0; f<_rank->nv; f++)
            printf("%d\t", f);
        printf("\n");

        for(int f=0; f<_rank->nv; f++)
            printf("--------");
        printf("\n");

        for(int f=0; f<_rank->na; f++)
        {
            for(int g=0; g<_rank->nv; g++)
                printf("%.4f\t", _rank->ProbAleatoria[f][g]);
            printf("\n");
        }
        printf("\n");
    }
    else
        printf("Planet Rank nao calculado.\n");
}
void ImprimirMatrizPP()
{
    if(_rank)
    {
        for(int f=0; f<_rank->nv; f++)
            printf("%d\t", f);
        printf("\n");

        for(int f=0; f<_rank->nv; f++)
            printf("--------");
        printf("\n");

        for(int f=0; f<_rank->na; f++)
        {
            for(int g=0; g<_rank->nv; g++)
                printf("%.4f\t", _rank->ProbPlaneta[f][g]);
            printf("\n");
        }
        printf("\n");
    }
    else
        printf("Planet Rank nao calculado.\n");
}
void ImprimirMatrizPR()
{
    if(_rank)
    {
        for(int f=0; f<_rank->nv; f++)
            printf("%d\t", f);
        printf("\n");

        for(int f=0; f<_rank->nv; f++)
            printf("--------");
        printf("\n");

        for(int f=0; f<_rank->na; f++)
        {
            for(int g=0; g<_rank->nv; g++)
                printf("%.4f\t", _rank->PlanetRank[f][g]);
            printf("\n");
        }
        printf("\n");
    }
    else
        printf("Planet Rank nao calculado.\n");
}


int Grafo_GrauEntrada(int vertice)
{
    if(_grafo)
    {
        if(vertice>=_grafo->n_vertices)
            return -1;

        int c=0;
        for(int d=0; d<_grafo->n_vertices; d++)
        {
            if(_grafo->matriz_adj[d][vertice])
                c++;
        }
        return c;
    }
    return -1;
}

int Grafo_GrauSaida(int vertice)
{
    if(_grafo)
    {
        if(vertice>=_grafo->n_vertices)
            return -1;

        int c=0;
        for(int d=0; d<_grafo->n_vertices; d++)
        {
            if(_grafo->matriz_adj[vertice][d])
                c++;
        }
        return c;
    }
    return -1;
}
int Grafo_GrauIncidencia(int vertice)
{
    if(_grafo)
    {
        if(vertice>=_grafo->n_vertices)
            return -1;

        int c=0;
        for(int i=0; i<_grafo->n_arestas; i++)
            c=c+_grafo->matriz_inc[i][vertice];
        return c;
    }
    return -1;
}

bool Grafo_FortementeConectados()
{
    for(int f=0;f<_grafo->n_vertices;f++)
        for(int g=0;g<_grafo->n_vertices;g++)
        {
            if(_grafo->matriz_adj[f][g] != _grafo->matriz_adj[g][f])
                return false;
        }
    return true;
}

void Imprimir_ParesFConectados()
{
    for(int f=0;f<_grafo->n_vertices;f++)
        for(int g=0;g<_grafo->n_vertices;g++)
        {
            if(g>f)
                continue;

            if(_grafo->matriz_adj[f][g] == _grafo->matriz_adj[g][f])
                printf("%d %d\n", f, g);
        }
}

void CarregarGrafoBase(const char* arquivo)
{
    if(!_grafo)
        _grafo = CarregarArquivo(arquivo);
}

void DescarregarGrafoBase()
{
    if(_grafo)
    {
        delete _grafo;
        _grafo = NULL;
    }
    if(_rank)
    {
        if(_rank->Grau)
        {
            delete [] _rank->Grau;
            _rank->Grau=NULL;
        }

        if(_rank->PlanetRank)
        {
            for(int c=0; c<_rank->na; c++)
                delete [] _rank->PlanetRank[c];
            delete [] _rank->PlanetRank;
            _rank->PlanetRank=NULL;
        }

        if(_rank->ProbAleatoria)
        {
            for(int c=0; c<_rank->na; c++)
                delete [] _rank->ProbAleatoria[c];
            delete [] _rank->ProbAleatoria;
            _rank->ProbAleatoria=NULL;
        }

        if(_rank->ProbPlaneta)
        {
            for(int c=0; c<_rank->na; c++)
                delete [] _rank->ProbPlaneta[c];
            delete [] _rank->ProbPlaneta;
            _rank->ProbPlaneta=NULL;
        }

        delete _rank;
        _rank = NULL;
    }
}

int ContaCaracteres(int n)
{
    if(n==0)
        return 1;

    int c=0;
    while(true)
    {
        if(!n)break;

        c++;
        n=n/10;
    }
    return c;
}

void ImprimirMatrizAdj()
{
    if(_grafo)
    {
        int constante = ContaCaracteres(_grafo->n_vertices);

        for(int f=0; f<constante; f++)
            printf(" ");
        printf("| ");

        for(int h=0; h<_grafo->n_vertices; h++)
            printf("%d ", h);
        printf("\n");


        for(int l=0; l<constante; l++)
            printf("-");
        printf("--");
        for(int g=0; g<_grafo->n_vertices; g++)
        {
            for(int o=0; o<ContaCaracteres(g); o++)
                printf("-");
            printf("-");
        }
        printf("\n");

        for(int i=0; i<_grafo->n_vertices; i++)
        {
            printf("%d", i);

            for(int k=0; k<(constante-ContaCaracteres(i)); k++)
                printf(" ");
            printf("| ");

            for(int j=0; j<_grafo->n_vertices; j++)
            {
                printf("%d ", _grafo->matriz_adj[i][j]);

                for(int m=0; m<(ContaCaracteres(j)-1); m++)
                    printf(" ");
            }
            printf("\n");
        }
    }
    else
        printf("Grafo nao inicializado.\n");
}

void ImprimirMatrizInc()
{
    if(_grafo)
    {
        int constante = ContaCaracteres(_grafo->n_vertices);

        for(int f=0; f<_grafo->n_vertices; f++)
            printf("%d ", f);
        printf("\n");

        for(int f=0; f<_grafo->n_vertices; f++)
        {
            for(int g=0; g<ContaCaracteres(f); g++)
                printf("-");
            printf("-");
        }
        printf("\n");

        for(int f=0; f<_grafo->n_arestas; f++)
        {
            for(int g=0; g<_grafo->n_vertices; g++)
            {
                printf("%d ", _grafo->matriz_inc[f][g]);
                for(int m=0; m<(ContaCaracteres(g)-1); m++)
                    printf(" ");
            }
            printf("\n");
        }
        printf("\n");
    }
    else
        printf("Grafo nao inicializado.\n");
}

