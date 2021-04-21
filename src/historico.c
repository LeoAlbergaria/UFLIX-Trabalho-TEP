#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/usuario.h"
#include "../include/filmes.h"
#include "../include/historico.h"
#include "../include/menu.h"

struct historico
{
  char *titulo;
  char *data;
  float nota;
};

Historico* criaHistorico()
{
  Historico *historico = (Historico*)malloc(sizeof(Historico));
  return historico;
}

Historico* adicionaHistoricoUsuario(Historico *historico,Usuario *usuario)
{
  FILE *arquivoHistorico = fopen("data/historico.csv","r+");
  if (arquivoHistorico == NULL)
  {
      printf("Problemas na abertura do arquivo\n");
      exit(1);
  }

  char linha[300];
  char idAux[10];
  char tituloAux[100];
  char dataAux[20];
  char notaAux[20];
  while(fgets(linha, 300, arquivoHistorico))
  {
    strcpy(idAux, strtok(linha, ","));
    if(atoi(idAux) == retornaId(usuario))
    {
      setterQtdFilme(usuario, retornaQtdFilme(usuario) + 1);
      historico = (Historico*)realloc(historico,retornaQtdFilme(usuario) * sizeof(Historico));
      strcpy(tituloAux, strtok(NULL, ","));
      strcpy(dataAux, strtok(NULL, ","));
      strcpy(notaAux, strtok(NULL, ","));
      historico[retornaQtdFilme(usuario)- 1].titulo = strdup(tituloAux);
      historico[retornaQtdFilme(usuario)- 1].data = strdup(dataAux);
      historico[retornaQtdFilme(usuario)- 1].nota = atof(notaAux);
    }
  }
  fclose(arquivoHistorico);
  return historico;
}

void colocarFilmeHistorico(char* titulo, float nota, char* data, Usuario *usuario)
{
  FILE *arquivoHistorico = fopen("data/historico.csv","a");
  if (arquivoHistorico == NULL)
  {
      printf("Problemas na abertura do arquivo\n");
      exit(1);
  }

  fprintf(arquivoHistorico,"%d,%s,%s,%.1f\n", retornaId(usuario), titulo, data, nota);

  fclose(arquivoHistorico);
}

void imprimirHistoricoOrdenado(Historico *historico,int qtdFilmes, char opcao)
{
  if(opcao == 'D' || opcao == 'd')
    ordenaHistoricoData(historico, qtdFilmes);
  else
    if(opcao == 'N' || opcao == 'n')
      ordenaHistoricoNota(historico, qtdFilmes);
  for(int i = 0; i < qtdFilmes; i++)
  {
    if(historico[i].nota != -1)
      printf("%s - %s: %.1f\n", historico[i].data, historico[i].titulo, historico[i].nota);
    else
      printf("%s - %s: Sem avaliacao\n", historico[i].data, historico[i].titulo);
  }
}

void destroiHistorico(Historico *historico, int qtdFilmes)
{
  for(int i = 0; i < qtdFilmes;i++)
  {
    free(historico[i].data);
    free(historico[i].titulo);
  }
}

void ordenaHistoricoNota(Historico *historico,int qtdFilmes)
{
  // bubblesort
  for (int i = 0; i < qtdFilmes ; i++)
  {
    for (int j = i; j < qtdFilmes; j++)
    {
      if (historico[i].nota < historico[j].nota)
      {
        trocaVariaveisHistorico(historico, i, j);
      }
    }
  }
}

void ordenaHistoricoData(Historico *historico,int qtdFilmes)
{
  // bubblesort
  int dia1, mes1, ano1, dia2, mes2, ano2;
  for (int i = 0; i < qtdFilmes ; i++)
  {
    for (int j = i; j < qtdFilmes; j++)
    {
      sscanf(historico[i].data, "%2d/%2d/%4d", &dia1, &mes1, &ano1);
      sscanf(historico[j].data, "%2d/%2d/%4d", &dia2, &mes2, &ano2);
      if (ano1 <= ano2)
      {
        if(ano1 < ano2)
          trocaVariaveisHistorico(historico, i, j);
        else
        {
          if (mes1 <= mes2)
          {
            if(mes1 < mes2)
              trocaVariaveisHistorico(historico, i, j);
            else
            {
              if(dia1 < dia2)
                trocaVariaveisHistorico(historico, i, j);
            }
          }
        }
      }
    }
  }
}

void trocaVariaveisHistorico(Historico *historico, int i, int j)
{
  float auxNota = historico[i].nota;
  historico[i].nota = historico[j].nota;
  historico[j].nota = auxNota;
  char auxTitulo1[150];
  char auxTitulo2[150];

  strcpy(auxTitulo1,historico[i].titulo);
  strcpy(auxTitulo2,historico[j].titulo);
  free(historico[i].titulo);
  free(historico[j].titulo);
  historico[j].titulo = strdup(auxTitulo2);
  historico[i].titulo = strdup(auxTitulo1);

  char auxData[20];
  strcpy(auxData,historico[i].data);
  strcpy(historico[i].data,historico[j].data);
  strcpy(historico[j].data,auxData);
}