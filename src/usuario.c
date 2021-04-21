#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/usuario.h"
#include "../include/filmes.h"
#include "../include/historico.h"
#include "../include/menu.h"

struct usuario{
  char *nome;
  int id;
  int qtdFilmes;
  Historico *historico;
};

int verificaUsuario(char *nome, char *senha, int verbosidade)
{
  if(verbosidade)
    system("clear");
  FILE *arquivoUsuarios = fopen("data/usuarios.csv","r");
  if (arquivoUsuarios == NULL)
  {
    printf("Problemas na abertura do arquivo\n");
    exit(1);
  }
  char linha[50];
  char idAux[5];
  char nomeAux[20];
  char senhaAux[20];
  char usuarioValido[2];
  int usuarioInativo = 0;

  while(fgets(linha, 50, arquivoUsuarios))
  {
    strcpy(idAux, strtok(linha, ","));
    strcpy(nomeAux, strtok(NULL, ","));
    strcpy(senhaAux, strtok(NULL, ","));
    strcpy(usuarioValido, strtok(NULL, "\n"));
    if(strcmp(nome, nomeAux) == 0)
    {
      if(usuarioValido[0] == '0')
      {
        usuarioInativo = 1;
      }
      else{
        if(strcmp(senha, senhaAux) == 0)
        {
          fclose(arquivoUsuarios);
          return atoi(idAux);
        }
        else
        {
          fclose(arquivoUsuarios);
          printf("Senha incorreta.\n");
          return 0;
        }
      }
    }
  }
  if(usuarioInativo)
    printf("Usuario inativo\n");
  else
    printf("Usuario nao cadastado.\n");
  fclose(arquivoUsuarios);
  return 0;
}

Usuario* criaUsuario(int id)
{
  Usuario* usuario = (Usuario*)malloc(sizeof(Usuario));

  FILE *arquivoUsuarios = fopen("data/usuarios.csv","r");
  if (arquivoUsuarios == NULL)
  {
    printf("Problemas na abertura do arquivo\n");
    exit(1);
  }

  char linha[50];
  char idAux[5];
  char nomeAux[20];

  while(fgets(linha, 50, arquivoUsuarios))
  {
    strcpy(idAux, strtok(linha, ","));
    strcpy(nomeAux, strtok(NULL, ","));
    if(atoi(idAux) == id)
    {
      usuario->nome = strdup(nomeAux);
      break;
    }
  }
  fclose(arquivoUsuarios);

  usuario->id = id;
  usuario->qtdFilmes = 0;
  usuario->historico = criaHistorico();
  return usuario;
}

int validaCadastro(char *nome, char *senha, char *senha2, int verbosidade)
{
  if(verbosidade)
    system("clear");

  FILE *arquivoUsuarios = fopen("data/usuarios.csv","r");
  if (arquivoUsuarios == NULL)
  {
    printf("Problemas na abertura do arquivo\n");
    exit(1);
  }
  
  char linha[50];
  char idAux[5];
  char nomeAux[20];
  char senhaAux[20];
  char usuarioValido[2];

  while(fgets(linha, 50, arquivoUsuarios))
  {
    strcpy(idAux, strtok(linha, ","));
    strcpy(nomeAux, strtok(NULL, ","));
    strcpy(senhaAux, strtok(NULL, ","));
    strcpy(usuarioValido, strtok(NULL, "\n"));
    if(strcmp(nome, nomeAux) == 0)
    {
      if(atoi(usuarioValido))
      {
        printf("Usuario ja cadastrado.\n");
        fclose(arquivoUsuarios);
        return 0;
      }
    }
  }

  int tamanhoSenha = strlen(senha);
  for(int i = 0; i < tamanhoSenha;i++)
  {
    if(isalpha(senha[i]) == 0 && isalnum(senha[i]) == 0)
    {
      printf("Senha fora do padrao.\n");
      fclose(arquivoUsuarios);
      return 0;
    }
  }

  if(strcmp(senha, senha2) != 0)
  {
    printf("Senha incorreta.\n");
    fclose(arquivoUsuarios);
    return 0;
  }

  fclose(arquivoUsuarios);
  return 1;
}

void cadastraUsuario(char *nome, char *senha)
{
  FILE *arquivoUsuarios = fopen("data/usuarios.csv","r+");
  if (arquivoUsuarios == NULL)
  {
    printf("Problemas na abertura do arquivo\n");
    exit(1);
  }

  char linha[50];
  int qtdLinhas = 0;

  while(fgets(linha, 50, arquivoUsuarios))
  {
    qtdLinhas++;
  }
  fprintf(arquivoUsuarios,"%d,%s,%s,1\n",qtdLinhas+1, nome, senha);
  fclose(arquivoUsuarios);
}

void destroiUsuario(Usuario *usuario)
{
  free(usuario->nome);
  free(usuario->historico);
  free(usuario);
}

void excluirUsuario(Usuario *usuario)
{
  FILE *arquivoUsuarios = fopen("data/usuarios.csv","r+");
  char linha[50];
  char idAux[10];
  while(fgets(linha, 50, arquivoUsuarios))
  {
    strcpy(idAux, strtok(linha, ","));
    if(atoi(idAux) == usuario->id)
    {
      fseek(arquivoUsuarios, -2, SEEK_CUR);
      fputc('0',arquivoUsuarios);
    }
  }
  fclose(arquivoUsuarios);
}

void criaHistoricoUsuario(Usuario *usuario, int verbosidade)
{
  if(verbosidade)
    system("clear");
  usuario->historico = adicionaHistoricoUsuario(usuario->historico,usuario);
  historicoOrdenado(usuario,verbosidade);
  destroiHistorico(usuario->historico, usuario->qtdFilmes);
  usuario->qtdFilmes = 0;
}

void historicoOrdenado(Usuario *usuario, int verbosidade)
{
  char opcao;
  int voltar;
  if(verbosidade)
    printf("Digite D para ordenar por (D)ata ou N para ordenar por (N)ota!!!\n");
  getchar();
  scanf("%c", &opcao);
  getchar();
  if(verbosidade)
  {
    system("clear");
    printf("Usuario: %s\nMeu historico:\n", usuario->nome);
  }
  imprimirHistoricoOrdenado(usuario->historico, usuario->qtdFilmes, opcao);
  if(verbosidade)
    printf("0 - Voltar\n");
  scanf("%d", &voltar);
}

int retornaQtdFilme(Usuario *usuario)
{
  return usuario->qtdFilmes;
}

int retornaId(Usuario *usuario)
{
  return usuario->id;
}

char* retornaNome(Usuario *usuario)
{
  return usuario->nome;
}

void setterQtdFilme(Usuario *usuario, int qtd)
{
  usuario->qtdFilmes = qtd;
}