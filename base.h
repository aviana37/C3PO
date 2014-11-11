#ifndef BASE_H_INCLUDED
#define BASE_H_INCLUDED

/*André Viana Sena de Souza - 25037
**Projeto e Análise de Algoritmos - ECO027
**Projeto #3 - C3PO - 10/11/2014
**Arquivo: base.h
**Descrição: Define os protótipos de métodos e estruturas utilizados na manipulação do tipo Grafo.
*/

/** \file base.h
    \brief Base operacional do C3PO.
    \details Dispõe de diversos métodos, e recursos estáticos para efetuação dos itens especificados no projeto.

    \def ARQUIVO_GALAXIA_MENOR Macro correspondente ao endereço do arquivo.
    \def ARQUIVO_GALAXIA_MEDIA Macro correspondente ao endereço do arquivo.
    \def ARQUIVO_GALAXIA_GRANDE Macro correspondente ao endereço do arquivo.

    \enum TipoPercurso
    \brief Tipo de percurso.
    \details Utilizado na variável estática _percursoAtual, que armazena o último percurso realizado no grafo.

    \struct MatrizesPlanetRank
    \brief Container para as matrizes utilizadadas durante o cálculo do Planet Rank.
    \details Não possui construtor ou destrutor, recursos são desalocados manualmente através do método DescarregarGrafoBase().

    \var Matrizes::PlanetRank::Grau
    Vetor que armazena o grau de cada vértice do grafo. Seu tamanho é Matrizes::PlanetRank::nv.
    \var Matrizes::PlanetRank::ProbPlaneta
    Matriz de float que armazena a probabilidade dos planetas.
    \var Matrizes::PlanetRank::ProbAleatoria
    Matriz de float que armazena a probabilidade aleatória.
    \var Matrizes::PlanetRank::PlanetRank
    Matriz de float que armazena o resultado da soma de Matrizes::PlanetRank::ProbPlaneta e Matrizes::PlanetRank::ProbAleatoria.
    \var Matrizes::PlanetRank::nv
    Número de vértices do grafo.
    \var Matrizes::PlanetRank::na
    Número de arestas do grafo.

    \fn void Grafo_FazerPercursoProfundidade();
    \brief Chama o método PercursoProfundidade do grafo.

    \fn void Grafo_FazerPercursoLargura();
    \brief Chama o método PercursoLargura do grafo.

    \fn bool Grafo_Carregado();
    \brief Avalia se o ponteiro _grafo é nulo.
    \return TRUE se o grafo está carregado. FALSE se não.

    \fn bool Grafo_Aciclico();
    \brief Acessa a variável aciclico no grafo.
    \return FALSE se o grafo possuir um ou mais ciclos. FALSE se não.

    \fn int Grafo_Vertices();
    \brief Acessa a variável n_vertices no grafo.
    \return Retorna a quantidade de vértices do grafo atual.

    \fn TipoPercurso Grafo_PercursoAtual();
    \brief Acessa a variável estática _percursoAtual;
    \return Retorna o valor da variável _percursoAtual.

    \fn void ImprimirVertices();
    \brief Imprime os valores internos dos vértices de acordo com o último percurso realizado.

    \fn void CalcularPlanetRank();
    \brief Calcula o Planet Rank. Deve ser chamada antes de PlanetRank(int, float);
    \details Instancia o struct interno com as MatrizesPlanetRank.

    \fn bool PlanetRankCalculado();
    \brief Avalia se o ponteiro _rank é nulo.
    \return TRUE se a variável _rank for instanciada. FALSE se ela apontar para NULL.

    \fn int PlanetRank(int planeta, float* chance=NULL);
    \brief Lê as matrizes internas para gerar o resultado.
    \return Retorna o Planet Rank do planeta especifado ou -1 caso ele esteja fora do escopo dos vértices.
    \param planeta O planeta especificado.
    \param chance Caso esse ponteiro não seja nulo, lhe será atribuído o valor da chance total do planeta.

    \fn void ImprimirMatrizPA();
    \brief Imprime a matriz de probabilidade aleatória.
    \fn void ImprimirMatrizPP();
    \brief Imprime a matriz de probabilidade do planeta.
    \fn void ImprimirMatrizPR();
    \brief Imprime a matriz de probabilidade Planet Rank.

    \fn int Grafo_GrauEntrada(int vertice);
    \brief Avalia o grau de entrada de um vértice através da matriz de adjacências.
    \fn int Grafo_GrauSaida(int vertice);
    \brief Avalia o grau de saída de um vértice através da matriz de adjacências.
    \fn int Grafo_GrauIncidencia(int vertice);
    \brief Avalia o grau de incidência (ou grau total) de um vértice através da matriz de incidencia.

    \fn void Grafo_DeterminarCaminho(int inicio, int fim);
    \brief Realiza percurso em largura a partir do vértice início e inicia a recursão em Grafo_ImprimirCaminho().
    \fn void Grafo_ImprimirCaminho(int inicio, int atual);
    \brief Método recursivo utilizado para imprimir um possível caminho já determinado por Grafo_DeterminarCaminho().

    \fn bool Grafo_Direcionado();
    \brief Itera pelos vértices e arestas do grafo. Essencial para Grafo_ComponentesFortementeConectados().
    \return TRUE se o grafo atual for direcionado. FALSE se não.

    \fn int* Grafo_ComponentesFortementeConectados(int* n_componentes);
    \brief Após realizar um percurso por profundidade, avalia se e quais componentes do grafo são fortemente conectados.
    \return Retorna um vetor de vertices que deve ser desalocado manualmente ou NULL caso o grafo não seja fortemente conectado.
    \param n_componentes Recebe a quantidade de componentes que estão armazenados no vetor retornado.
    \fn void Imprimir_ParesFConectados();
    \brief Itera pela matriz de adjacências imprimindo todas as arestas fortemente conectadas.

    \fn void CarregarGrafoBase(const char* arquivo);
    \brief Chama a função CarregarArquivo() e atribui o seu retorno à variável estática _grafo;
    \fn void DescarregarGrafoBase();
    \brief Desaloca todos os componentes e variáveis estáticas.

    \fn int ContaCaracteres(int n);
    \brief Utilizada nas funções ImprimirMatrizAdj() e ImprimirMatrizInc().
    \return Retorna a quantidade de caracteres necessarios para imprimir o valor n.

    \fn void ImprimirMatrizAdj();
    \brief Imprime a matriz de adjacências do grafo atual.
    \fn void ImprimirMatrizInc();
    \brief Imprime a matriz de incidência do grafo atual.
*/


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
