#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/usuario.h"
#include "../include/filmes.h"
#include "../include/historico.h"
#include "../include/menu.h"

struct filmes{
  char *titulo;
  int id;
  int ano;
  int duracao;
  float nota;
  char *descricao;
};

Filmes* salvarFilmes(int *qtdFilmes)
{
    FILE *arquivoFilmes = fopen("data/filmes-grande.csv","r");
    if (arquivoFilmes == NULL)
    {
        printf("Problemas na abertura do arquivo\n");
        exit(1);
    }
    char linha[300];
    Filmes *filmes = (Filmes*)malloc(sizeof(Filmes));

    while(fgets(linha, 300, arquivoFilmes))
    {
        *qtdFilmes += 1;
        filmes = (Filmes*)realloc(filmes, (*qtdFilmes) * sizeof(Filmes));
        lerMetadados(filmes, (*qtdFilmes - 1) , linha);
    }
    fclose(arquivoFilmes);
    return filmes;
}

void listarFilmes(Usuario *usuario, Filmes *filmes, int qtdFilmes, int verbosidade)
{
    char opcao[10];
    if(verbosidade)
        system("clear");
    for(int i = 0; i < qtdFilmes; i++)
    {
        printf("%d - %s\n", i+1, filmes[i].titulo);

        if((i+1)%10 == 0 && i!= 0)
        {
            getchar();
            if(verbosidade)
                printf("M - mais filmes\n0 - Voltar");
            scanf("%s", opcao);
            if(opcao[0] >= '1' && opcao[0] <= '9')
            {
                imprimirMetadadosFilme(filmes, atoi(opcao) - 1, usuario, verbosidade);
                i -= 10;
            }
            if(opcao[0] == '0')
            {
                if(verbosidade)
                    system("clear");
                break;
            }
            if(verbosidade)
                system("clear");
        }
    }
    if(opcao[0] != '0')
        printf("Fim de filmes disponiveis\n");
}

void lerMetadados(Filmes *filme, int num, char *linha)
{
    char stringAux[200];
    filme[num].id = num;
    strcpy(stringAux, strtok(linha, ","));
    filme[num].titulo = strdup(stringAux);
    strcpy(stringAux, strtok(NULL, ","));
    filme[num].ano = atoi(stringAux);
    strcpy(stringAux, strtok(NULL, ","));
    filme[num].duracao = atoi(stringAux);
    strcpy(stringAux, strtok(NULL, ","));
    filme[num].nota = atof(stringAux);
    strcpy(stringAux, strtok(NULL, "\n"));
    if(stringAux[0] == '\"')
        strcpy(stringAux, strtok(stringAux, "\""));
    filme[num].descricao = strdup(stringAux);
}

void imprimirMetadadosFilme(Filmes *filme, int num, Usuario *usuario, int verbosidade)
{
    char opcao[3];
    if(verbosidade)
        system("clear");
    printf("Titulo: %s\n", filme[num].titulo);
    printf("Ano: %d\n", filme[num].ano);
    printf("Duração: %d minutos\n", filme[num].duracao);
    printf("Avaliação: %.1f\n", filme[num].nota);
    printf("Descrição: %s\n", filme[num].descricao);
    if(verbosidade)
    {
        printf("\n1- Assistir\n2- Voltar \n");
    }
    while(opcao[0] != '2' && opcao[0] != '1')
        scanf("%s", opcao);
    if(opcao[0] == '1')
        assistirFilme(filme, num, usuario, verbosidade);
}

void assistirFilme(Filmes *filme, int num, Usuario *usuario, int verbosidade)
{
    if(verbosidade)
    {
        system("clear");
        printf("O que achou de %s? De uma nota entre 0 e 10:\n", filme[num].titulo);
    }
    float nota;
    scanf("%f", &nota);
    char data[12];
    if(verbosidade)
        printf("Data:");
    scanf("%s", data);
    colocarFilmeHistorico(filme[num].titulo, nota, data, usuario);
}

void procurarFilme(Filmes *filmes, Usuario* usuario,  char *titulo, int qtdFilmes, int verbosidade)
{
    char *comparador;
    int opcao = -1;

    //transforma toda string em minusculo
    for(int i = 0; i < strlen(titulo); i++)
    {
        if(titulo[i] >= 'A' && titulo[i] <= 'Z')
        {   
            titulo[i] = tolower(titulo[i]);
        }
    }
    while(opcao)
    {
        for(int i = 0; i < qtdFilmes; i++)
        {
            char tituloFilmesAux[100] = "";
            //transforma toda string em minusculo
            for(int j = 0; j < strlen(filmes[i].titulo); j++)
            {
                if(filmes[i].titulo[j] >= 'A' && filmes[i].titulo[j] <= 'Z')
                {   
                    tituloFilmesAux[j] = tolower(filmes[i].titulo[j]);
                }
                else
                {
                    tituloFilmesAux[j] = filmes[i].titulo[j];
                }
            }

            comparador = strstr(tituloFilmesAux, titulo);
            if(comparador != NULL)
            {
                printf("%d - %s\n",filmes[i].id, filmes[i].titulo);
            }
        }
        if(verbosidade)
            printf("0 - Voltar\n");
        scanf("%d", &opcao);
        if(opcao != 0)
            imprimirMetadadosFilme(filmes, opcao, usuario, verbosidade);
        else
        {
            if(verbosidade)
                system("clear");
            break;
        }
        if(verbosidade)
            system("clear");
    }
}

void destroiFilmes(Filmes *filmes, int qtd)
{
    for(int j = 0; j < qtd; j++)
    {
        free(filmes[j].titulo);
        free(filmes[j].descricao);
    }
    free(filmes);
}
