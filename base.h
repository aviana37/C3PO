#ifndef BASE_H_INCLUDED
#define BASE_H_INCLUDED

#include "grafo.h"

#define ARQUIVO_GALAXIA_MENOR   "universo/galaxiamenor.txt"
#define ARQUIVO_GALAXIA_MEDIA   "universo/galaxiamedia.txt"
#define ARQUIVO_GALAXIA_GRANDE  "universo/galaxiagrande.txt"

enum TipoPercurso
{
    PERCURSO_NENHUM,
    PERCURSO_LARGURA,
    PERCURSO_PROFUNDIDADE,
};

struct MatrizesPlanetRank
{
    int* Grau;
    float** ProbPlaneta;
    float** ProbAleatoria;
    float** PlanetRank;

    int nv, na;
};

void Grafo_FazerPercursoProfundidade();
void Grafo_FazerPercursoLargura();

bool Grafo_Carregado();
bool Grafo_Aciclico();
int Grafo_Vertices();
TipoPercurso Grafo_PercursoAtual();
void ImprimirVertices();

void CalcularPlanetRank();
bool PlanetRankCalculado();
int PlanetRank(int planeta, float* chance=NULL);
void ImprimirMatrizPA();
void ImprimirMatrizPP();
void ImprimirMatrizPR();

int Grafo_GrauEntrada(int vertice);
int Grafo_GrauSaida(int vertice);
int Grafo_GrauIncidencia(int vertice);

void Grafo_DeterminarCaminho(int inicio, int fim);
void Grafo_ImprimirCaminho(int inicio, int atual);

bool Grafo_Direcionado();
int* Grafo_ComponentesFortementeConectados(int* n_componentes);
void Imprimir_ParesFConectados();

void CarregarGrafoBase(const char* arquivo);
void DescarregarGrafoBase();

int ContaCaracteres(int n);
void ImprimirMatrizAdj();
void ImprimirMatrizInc();

#endif // BASE_H_INCLUDED
