#ifndef BASE_H_INCLUDED
#define BASE_H_INCLUDED

#include "grafo.h"

#define ARQUIVO_GALAXIA_MENOR   "universo/galaxiamenor.txt"
#define ARQUIVO_GALAXIA_MEDIA   "universo/galaxiamedia.txt"
#define ARQUIVO_GALAXIA_GRANDE  "universo/galaxiagrande.txt"

struct MatrizesPlanetRank
{
    int* Grau;
    float** ProbPlaneta;
    float** ProbAleatoria;
    float** PlanetRank;

    int nv, na;
};

bool Grafo_Carregado();
int Grafo_Vertices();

void CalcularPlanetRank();
bool PlanetRankCalculado();
int PlanetRank(int planeta, float* chance=NULL);
void ImprimirMatrizPA();
void ImprimirMatrizPP();
void ImprimirMatrizPR();

int Grafo_GrauEntrada(int vertice);
int Grafo_GrauSaida(int vertice);
int Grafo_GrauIncidencia(int vertice);

bool Grafo_FortementeConectados();
void Imprimir_ParesFConectados();

void CarregarGrafoBase(const char* arquivo);
void DescarregarGrafoBase();

int ContaCaracteres(int n);
void ImprimirMatrizAdj();
void ImprimirMatrizInc();

#endif // BASE_H_INCLUDED
