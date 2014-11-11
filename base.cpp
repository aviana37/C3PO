#include "base.h"

/*André Viana Sena de Souza - 25037
**Projeto e Análise de Algoritmos - ECO027
**Projeto #3 - C3PO - 10/11/2014
**Arquivo: base.cpp
**Descrição: Implementação dos métodos definidos em base.h.
*/

/** \file base.cpp
    \brief Implementações de base.h e seus recursos estáticos.

    \var _grafo
    Ponteiro interno de um objeto Grafo, para uso dos métodos da base.
    \var _rank
    Ponteiro para um objeto MatrizesPlanetRank.
    \var _percursoAtual
    Aponta para o último percurso realizado. Atualizado pelos métodos Grafo_FazerPercursoProfundidade()
     e Grafo_FazerPercursoLargura().
*/

static Grafo* _grafo=NULL;
static MatrizesPlanetRank* _rank=NULL;
static TipoPercurso _percursoAtual=PERCURSO_NENHUM;

void Grafo_FazerPercursoProfundidade()
{
    if(_grafo)
    {
        _grafo->PercursoProfundidade();
        _percursoAtual=PERCURSO_PROFUNDIDADE;
    }
}

bool Grafo_Aciclico()
{
    return _grafo->aciclico;
}
bool Grafo_Carregado()
{
    return _grafo;
}
int Grafo_Vertices()
{
    return _grafo->n_vertices;
}
TipoPercurso Grafo_PercursoAtual()
{
    return _percursoAtual;
}
void ImprimirVertices()
{
    switch(_percursoAtual)
    {
    case PERCURSO_NENHUM:
        printf("Nenhum percurso realizado.\n");
        return;
    case PERCURSO_LARGURA:
        printf("Percurso largura:\n");
        break;
    case PERCURSO_PROFUNDIDADE:
        printf("Percurso profundidade:\n");
        break;
    }

    for(int c=0; c<_grafo->n_vertices; c++)
    {
        printf("v-%d\tant-%d\tdesc-%d\tterm-%d\tcor-%d\n",
               c, _grafo->vertices[c].ant, _grafo->vertices[c].descoberta,
               _grafo->vertices[c].termino, _grafo->vertices[c].cor);
    }
}

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
        for(int f=0; f<_rank->nv; f++)
        {
            proporcao=(float)0.1/_rank->na;
            for(int g=0; g<_rank->na; g++)
                _rank->ProbAleatoria[g][f] = proporcao;
        }

        //Determinando valores na matriz planet rank
        for(int f=0; f<_rank->nv; f++)
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

        for(int e=0; e<_rank->na; e++)
        {
            if(_rank->PlanetRank[e][planeta]>0.1)
            {
                for(int f=0; f<_rank->nv; f++)
                    temp[f]+=_rank->PlanetRank[e][f];
            }
        }

        for(int g=1; g<_rank->nv; g++)
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

void Grafo_ImprimirCaminho(int inicio, int atual)
{
    if(inicio==atual)
        printf("%d.\n", atual);
    else if(_grafo->vertices[atual].ant == -1)
        printf("%d->X.\nNao existe um caminho a partir de %d a %d.\n", atual, atual, inicio);
    else
    {
        printf("%d->", atual);
        Grafo_ImprimirCaminho(inicio, _grafo->vertices[atual].ant);
    }
}
void Grafo_DeterminarCaminho(int inicio, int fim)
{
    _grafo->PercursoLargura(inicio);
    Grafo_ImprimirCaminho(inicio, fim);
}

bool Grafo_Direcionado()
{
    int c=0;
    for(int f=0; f<_grafo->n_vertices; f++)
        for(int g=0; g<_grafo->n_vertices; g++)
        {
            if(_grafo->matriz_adj[f][g] != _grafo->matriz_adj[g][f])
                c++;
        }
    if(!c || c==_grafo->n_vertices*_grafo->n_vertices)
        return true;
    return false;
}

int* Grafo_ComponentesFortementeConectados(int* n_componentes)
{
    int componentes, adj, comp_atual;
    int* ret;

    componentes = _grafo->PercursoProfundidade();

    if(!Grafo_Direcionado())
    {
        if(componentes>1)
            return NULL;
    }

    ret=new int[componentes];
    Grafo* gt=new Grafo(0,NULL,0);
    gt->n_vertices = _grafo->n_vertices;
    gt->vertices=new Grafo::Vertice[_grafo->n_vertices];

    for(int c=0; c<_grafo->n_vertices; c++)
    {
        _grafo->vertices[c].ProximoVerticeAdj(NULL);

        while(_grafo->vertices[c].ProximoVerticeAdj(&adj))
            gt->vertices[adj].AdicionarVerticeAdj(c);
    }

    int atual;
    for(int c=0; c<gt->n_vertices; c++)
        gt->vertices[c].cor = Grafo::Vertice::BRANCO;

    comp_atual=0;
    while(true)
    {
        atual=0;
        while(true)
        {
            if(gt->vertices[atual].cor == Grafo::Vertice::BRANCO)
                break;

            if(atual>=gt->n_vertices)
            {
                atual=-1;
                break;
            }
            atual++;
        }

        if(atual==-1)
            break;

        for(int c=0; c<_grafo->n_vertices; c++)
        {
            if(gt->vertices[c].cor == Grafo::Vertice::BRANCO)
            {
                if(_grafo->vertices[c].termino > _grafo->vertices[atual].termino)
                    atual = c;
            }
        }

        if(comp_atual>=componentes)
        {
            delete [] ret;
            return NULL;
        }

        ret[comp_atual]=atual;
        comp_atual++;

        gt->_Profundidade_R(atual);
    }

    if(n_componentes)
        *n_componentes=comp_atual;
    delete gt;
    return ret;
}

void Imprimir_ParesFConectados()
{
    for(int f=0; f<_grafo->n_vertices; f++)
        for(int g=0; g<_grafo->n_vertices; g++)
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

