#include <stdio.h>
#include "base.h"

enum ComandoMenu
{
    CMENU_DESCONHECIDO = 0,

    CMENU_CARREGAR = 1u<<0,
    CMENU_SAIR = 1u<<1,

    CMENU_ESPECIFICAR = 1u<<2,
    CMENU_GALAXIAP = 1u<<3,
    CMENU_GALAXIAM = 1u<<4,
    CMENU_GALAXIAG = 1u<<5,

    CMENU_GRAU = 1u<<6,
    CMENU_CICLOS = 1u<<7,
    CMENU_CAMINHOS = 1u<<8,
    CMENU_CONECTADOS = 1u<<9,
    CMENU_PLANET_RANK = 1u<<10,
    CMENU_DESCARREGAR = 1u<<11,
    CMENU_IMPRIMIR_MAT_ADJ = 1u<<12,
    CMENU_IMPRIMIR_MAT_INC = 1u<<13,

    CMENU_TODOS = 1u<<14,
    CMENU_GRAU_INDEGREE = 1u<<15,
    CMENU_GRAU_OUTDEGREE = 1u<<16,
    CMENU_GRAU_INCIDENCIA = 1u<<17,

    CMENU_VERIF_FCONECTADOS = 1u<<18,
    CMENU_IMPRIMIR_PARESF = 1u<<19,

    CMENU_PR_IMPRIMIR_MAT_PROBPLANETA = 1u<<20,
    CMENU_PR_IMPRIMIR_MAT_PROBALEATORIA = 1u<<21,
    CMENU_PR_IMPRIMIR_MAT_PLANETRANK = 1u<<22,
};

ComandoMenu MenuInicial()
{
    printf( "1->Carregar grafo.\n"
            "2->Sair.\n");

    int r;
    scanf("%d", &r);

    switch(r)
    {
    case 1:
        return CMENU_CARREGAR;
    case 2:
        return CMENU_SAIR;
    }
    return CMENU_DESCONHECIDO;
}

int MenuCarregar()
{
    printf( "1->Especificar endereco de arquivo.\n"
            "2->Carregar " ARQUIVO_GALAXIA_MENOR ".\n"
            "3->Carregar " ARQUIVO_GALAXIA_MEDIA ".\n"
            "4->Carregar " ARQUIVO_GALAXIA_GRANDE ".\n");

    int r;
    scanf("%d", &r);
    switch(r)
    {
    case 1:
        return CMENU_ESPECIFICAR;
    case 2:
        return CMENU_GALAXIAP;
    case 3:
        return CMENU_GALAXIAM;
    case 4:
        return CMENU_GALAXIAG;
    }
    return CMENU_DESCONHECIDO;
}

int MenuGrafo()
{
    printf( "1->Determinar grau.\n"
            "2->Determinar ciclos entre planetas.\n"
            "3->Determinar caminhos mais curtos entre planetas.\n"
            "4->Determinar se os planetas estao fortemente conectados.\n"
            "5->Planet Rank.\n"
            "6->Descarregar grafo.\n"
            "7->Imprimir matriz de adjacencias.\n"
            "8->Imprimir matriz de incidencias.\n"
            "9->Sair.\n");

    int r;
    scanf("%d", &r);

    switch(r)
    {
    case 1:
        return CMENU_GRAU;
    case 2:
        return CMENU_CICLOS;
    case 3:
        return CMENU_CAMINHOS;
    case 4:
        return CMENU_CONECTADOS;
    case 5:
        return CMENU_PLANET_RANK;
    case 6:
        return CMENU_DESCARREGAR;
    case 7:
        return CMENU_IMPRIMIR_MAT_ADJ;
    case 8:
        return CMENU_IMPRIMIR_MAT_INC;
    case 9:
        return CMENU_SAIR;
    }
    return CMENU_DESCONHECIDO;
}

int MenuGrau()
{
    int c;
    printf( "1->Grau de incidencia de um planeta.\n"
            "2->Grau de incidencia de todos planetas.\n"
            "3->Grau de entrada de um planeta.\n"
            "4->Grau de entrada de todos planetas.\n"
            "5->Grau de saida de um planeta.\n"
            "6->Grau de saida de todos planetas.\n"
            "7->Voltar.\n");

    scanf("%d", &c);

    switch(c)
    {
    case 1:
        return CMENU_GRAU_INCIDENCIA | CMENU_ESPECIFICAR;
    case 2:
        return CMENU_GRAU_INCIDENCIA | CMENU_TODOS;
    case 3:
        return CMENU_GRAU_INDEGREE | CMENU_ESPECIFICAR;
    case 4:
        return CMENU_GRAU_INDEGREE | CMENU_TODOS;
    case 5:
        return CMENU_GRAU_OUTDEGREE | CMENU_ESPECIFICAR;
    case 6:
        return CMENU_GRAU_OUTDEGREE | CMENU_TODOS;
    case 7:
        return CMENU_SAIR;
    }
    return CMENU_DESCONHECIDO;
}

void ResolverGrau(int comando)
{
    int v, grau;

    if(comando & CMENU_ESPECIFICAR)
    {
        comando = comando & ~(CMENU_ESPECIFICAR);
        switch(comando)
        {
        case CMENU_GRAU_INDEGREE:
            printf("Insira o numero do planeta/vertice: ");
            scanf("%d", &v);
            grau = Grafo_GrauEntrada(v);
            if(grau>-1)
                printf("O planeta %d tem um grau de entrada de %d.\n", v, grau);
            else
                printf("Planeta nao encontrado.\n");

            break;

        case CMENU_GRAU_OUTDEGREE:
            printf("Insira o numero do planeta/vertice: ");
            scanf("%d", &v);
            grau = Grafo_GrauSaida(v);
            if(grau>-1)
                printf("O planeta %d tem um grau de saida de %d.\n", v, grau);
            else
                printf("Planeta nao encontrado.\n");

            break;

        case CMENU_GRAU_INCIDENCIA:
            printf("Insira o numero do planeta/vertice: ");
            scanf("%d", &v);
            grau = Grafo_GrauIncidencia(v);
            if(grau>-1)
                printf("O planeta %d tem um grau de %d.\n", v, grau);
            else
                printf("Planeta nao encontrado.\n");
            break;
        }
    }
    else if(comando & CMENU_TODOS)
    {
        comando = comando & ~(CMENU_TODOS);
        switch(comando)
        {
        case CMENU_GRAU_INDEGREE:
            v=0;
            grau=Grafo_GrauEntrada(v);

            printf("PLANETA\tGRAU DE ENTRADA\n");
            while(grau>-1)
            {
                printf("%d\t%d\n", v, grau);
                v++;
                grau=Grafo_GrauEntrada(v);
            }
            break;

        case CMENU_GRAU_OUTDEGREE:
            v=0;
            grau=Grafo_GrauEntrada(v);

            printf("PLANETA\tGRAU DE SAIDA\n");
            while(grau>-1)
            {
                printf("%d\t%d\n", v, grau);
                v++;
                grau=Grafo_GrauSaida(v);
            }
            break;

        case CMENU_GRAU_INCIDENCIA:
            v=0;
            grau=Grafo_GrauEntrada(v);

            printf("PLANETA\tGRAU DE INCIDENCIA\n");
            while(grau>-1)
            {
                printf("%d\t%d\n", v, grau);
                v++;
                grau=Grafo_GrauIncidencia(v);
            }
            break;
        }
    }
}

ComandoMenu MenuCiclo()
{
    printf("Nao implementado.\n");
    return CMENU_DESCONHECIDO;
}
ComandoMenu MenuCaminho()
{
    printf("Nao implementado.\n");
    return CMENU_DESCONHECIDO;
}

int MenuConexao()
{
    int c;
    printf( "1->Verificar se grafo possui componentes fortemente conectados.\n"
            "2->Imprimir pares fortemente conectados.\n"
            "3->Voltar\n");
    scanf("%d", &c);

    switch(c)
    {
    case 1:
        return CMENU_VERIF_FCONECTADOS;
    case 2:
        return CMENU_IMPRIMIR_PARESF;
    case 3:
        return CMENU_SAIR;
    }
    return CMENU_DESCONHECIDO;
}
void ResolverConexao(int comando)
{
    switch(comando)
    {
    case CMENU_VERIF_FCONECTADOS:
        printf("O grafo possui %d vertices ", Grafo_Vertices());
        if(!Grafo_FortementeConectados())
            printf("nao ");
        printf("fortemente conectados.\n");
    break;
    case CMENU_IMPRIMIR_PARESF:
        printf("Pares fortemente conectados:\n");
        Imprimir_ParesFConectados();
    break;
    }
}


int MenuRank()
{
    int c;
    printf( "1->Planetas antecessores mais provaveis de todos planetas.\n"
            "2->Planetas antecessores mais provaveis de um planeta especifico.\n"
            "3->Imprimir matriz de probabilidade do planeta.\n"
            "4->Imprimir matriz de probabilidade aleatoria.\n"
            "5->Imprimir matriz Planet Rank.\n"
            "6->Voltar.\n");

    scanf("%d", &c);
    switch(c)
    {
    case 1:
        return CMENU_TODOS;
    case 2:
        return CMENU_ESPECIFICAR;
    case 3:
        return CMENU_PR_IMPRIMIR_MAT_PROBPLANETA;
    case 4:
        return CMENU_PR_IMPRIMIR_MAT_PROBALEATORIA;
    case 5:
        return CMENU_PR_IMPRIMIR_MAT_PLANETRANK;
    case 6:
        return CMENU_SAIR;
    default:
        return CMENU_DESCONHECIDO;
    }
}

void ResolverRank(int comando)
{
    int v, rank;
    float pct;

    switch(comando)
    {
    case CMENU_TODOS:
        v=0;
        rank=PlanetRank(v, &pct);
        printf("PLANETA\tANT\t%%\n");
        while(rank>-1)
        {
            printf("%d\t%d%.3f\n", v, rank, pct);
            v++;
            rank=PlanetRank(v, &pct);
        }
        break;
    case CMENU_ESPECIFICAR:
        printf("Insira o numero do planeta/vertice: ");
        scanf("%d", &v);
        rank=PlanetRank(v, &pct);
        if(rank>-1)
            printf("O planeta antecessor mais provavel de %d em uma viagem espacial e %d, com %.3f%%.\n", v, rank, pct);
        else
            printf("Planeta nao encontrado.\n");
        break;

    case CMENU_PR_IMPRIMIR_MAT_PROBPLANETA:
        printf("MATRIZ DE PROBABILIDADE DO PLANETA\n\n");
        ImprimirMatrizPP();
        break;
    case CMENU_PR_IMPRIMIR_MAT_PROBALEATORIA:
        printf("MATRIZ DE PROBABILIDADE ALEATORIA\n\n");
        ImprimirMatrizPA();
        break;
    case CMENU_PR_IMPRIMIR_MAT_PLANETRANK:
        printf("MATRIZ PLANET RANK\n\n");
        ImprimirMatrizPR();
        break;
    }

}

int main()
{
    int c;
    bool trava;

    printf("Bem-vindo ao C3PO!\n"
           "Por favor, selecione uma das opcoes abaixo:\n\n");

    while(true)
    {
        if(!Grafo_Carregado())
        {
            c=MenuInicial();
            if(c==CMENU_SAIR)
                break;
            else if(c==CMENU_DESCONHECIDO)
                printf("Valor nao reconhecido. Tente novamente.\n\n");
            else
            {
                c=MenuCarregar();
                switch(c)
                {
                case CMENU_ESPECIFICAR:
                    char arquivo[128];
                    printf("Insira o endereco do arquivo a ser lido: ");
                    scanf("%s", arquivo);
                    CarregarGrafoBase(arquivo);

                    if(Grafo_Carregado())
                        printf("Grafo em \"%s\" carregado com sucesso.\n\n", arquivo);
                    else
                        printf("Arquivo nao pode ser carregado.\n\n");
                    break;

                case CMENU_GALAXIAP:
                    CarregarGrafoBase(ARQUIVO_GALAXIA_MENOR);
                    if(Grafo_Carregado())
                        printf("Grafo em \"%s\" carregado com sucesso.\n\n", ARQUIVO_GALAXIA_MENOR);
                    else
                        printf("Arquivo nao pode ser carregado.\n\n");
                    break;

                case CMENU_GALAXIAM:
                    CarregarGrafoBase(ARQUIVO_GALAXIA_MEDIA);
                    if(Grafo_Carregado())
                        printf("Grafo em \"%s\" carregado com sucesso.\n\n", ARQUIVO_GALAXIA_MEDIA);
                    else
                        printf("Arquivo nao pode ser carregado.\n\n");
                    break;

                case CMENU_GALAXIAG:
                    CarregarGrafoBase(ARQUIVO_GALAXIA_GRANDE);
                    if(Grafo_Carregado())
                        printf("Grafo em \"%s\" carregado com sucesso.\n\n", ARQUIVO_GALAXIA_GRANDE);
                    else
                        printf("Arquivo nao pode ser carregado.\n\n");
                    break;
                }
            }
        }
        else
        {
            c=MenuGrafo();
            if(c==CMENU_SAIR)
                break;
            else if(c==CMENU_DESCONHECIDO)
                printf("Valor nao reconhecido. Tente novamente.\n\n");
            else
            {
                switch(c)
                {
                case CMENU_GRAU:
                    trava = true;
                    while(trava)
                    {
                        c=MenuGrau();
                        printf("\n");

                        if(c==CMENU_DESCONHECIDO)
                            printf("Valor nao reconhecido. Tente novamente.\n\n");
                        else if(c==CMENU_SAIR)
                            trava=false;
                        else
                            ResolverGrau(c);

                        printf("\n");
                    }
                    break;
                case CMENU_CICLOS:
                    MenuCiclo();
                    printf("\n");
                    break;
                case CMENU_CAMINHOS:
                    MenuCaminho();
                    printf("\n");
                    break;
                case CMENU_CONECTADOS:
                    trava=true;
                    while(trava)
                    {
                        c=MenuConexao();
                        printf("\n");

                        if(c==CMENU_DESCONHECIDO)
                            printf("Valor nao reconhecido. Tente novamente.\n\n");
                        else if(c==CMENU_SAIR)
                            trava=false;
                        else
                            ResolverConexao(c);

                        printf("\n");
                    }
                    break;
                case CMENU_PLANET_RANK:
                    if(!PlanetRankCalculado())
                    {
                        printf("Calculando Planet Rank. Isso pode demorar um pouco. ");
                        CalcularPlanetRank();
                        printf("Pronto.\n\n");
                    }
                    trava=true;
                    while(trava)
                    {
                        c=MenuRank();
                        printf("\n");
                        if(c==CMENU_DESCONHECIDO)
                            printf("Valor nao reconhecido. Tente novamente.\n\n");
                        else if(c==CMENU_SAIR)
                            trava=false;
                        else
                            ResolverRank(c);
                        printf("\n");
                    }

                    break;

                case CMENU_DESCARREGAR:
                    DescarregarGrafoBase();
                    printf("\nPronto.\n\n");
                    break;

                case CMENU_IMPRIMIR_MAT_ADJ:
                    printf("\nMATRIZ DE ADJACENCIA\n\n");
                    ImprimirMatrizAdj();
                    printf("\n");
                    break;

                case CMENU_IMPRIMIR_MAT_INC:
                    printf("\nMATRIZ DE INCIDENCIA\n\n");
                    ImprimirMatrizInc();
                    printf("\n");
                    break;
                }
            }
        }
    }

    printf("\nDescarregando recursos alocados. ");
    DescarregarGrafoBase();
    printf("Pronto.\nQue a Forca esteja com voce...\n");

    return 0;
}
