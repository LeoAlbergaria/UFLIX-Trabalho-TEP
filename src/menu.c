#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/usuario.h"
#include "../include/filmes.h"
#include "../include/historico.h"
#include "../include/menu.h"

void imprimeMenuLogin()
{
    printf("1 - Login\n2 - Cadastrar\n3 - Sair\n");
}

void imprimeMenuPrincipal()
{
    printf("1 - Listar Filmes\n2 - Meu perfil\n3 - Procurar Filme\n4 - Sair\n");
}

void imprimeMenuPerfil()
{
    printf("1 - Historico\n2 - Excluir conta\n3 - Voltar\n");
}

int menuLogin(int verbosidade)
{
    char operacao[3];
    char nome[20], senha[20], senha2[20];
    while(1)
    {
        if(verbosidade)
            imprimeMenuLogin();
        scanf("%s", operacao);
        switch(atoi(operacao)){
            case 1:
                //Login
                if(verbosidade)
                {
                    system("clear");
                    printf("Usuário:");
                }
                scanf("%s", nome);
                if(verbosidade)
                    printf("Senha:");
                scanf("%s", senha);
                int idUsuarioValido;
                idUsuarioValido = verificaUsuario(nome, senha, verbosidade);
                if(idUsuarioValido)
                {
                    return idUsuarioValido;
                }
                break;

            case 2:
                //Cadastro 
                if(verbosidade)
                {
                    system("clear");
                    printf("Usuário:");
                }
                scanf("%s", nome);
                if(verbosidade)
                    printf("Senha:");
                scanf("%s", senha);
                if(verbosidade)
                    printf("Senha:");
                scanf("%s", senha2);
                if(validaCadastro(nome,senha,senha2, verbosidade))
                    cadastraUsuario(nome, senha);
                break;

            case 3:
                if(verbosidade)
                    system("clear");
                return 0;
        }

    }
}

int menuPrincipal(Usuario* usuario,Filmes* filmes, int verbosidade)
{
    char operacao[3];
    while(1)
    {
        int qtdFilmes;
        if(filmes == NULL)
        {
            qtdFilmes= 0;
            filmes = salvarFilmes(&qtdFilmes);
        }
        if(verbosidade)
            imprimeMenuPrincipal();
        scanf("%s", operacao);
        char titulo[100];

        switch(atoi(operacao)){
            case 1:
                listarFilmes(usuario,filmes, qtdFilmes, verbosidade);
                break;

            case 2:
                destroiFilmes(filmes, qtdFilmes);
                filmes = NULL;
                return 3;
                break;
                
            case 3:
                if(verbosidade)
                {
                    system("clear");
                    printf("Nome do Filme: ");
                }
                scanf("%s", titulo);
                if(verbosidade)
                    system("clear");
                procurarFilme(filmes, usuario, titulo, qtdFilmes, verbosidade);
                break;

            case 4:
                destroiFilmes(filmes, qtdFilmes);
                filmes = NULL;
                if(verbosidade)
                    system("clear");
                return 1;
                break;
        }
    }
}

int menuPerfil(Usuario *usuario, int verbosidade)
{
    char operacao[3];
    while(1)
    {
        if(verbosidade)
        {
            system("clear");
            imprimeMenuPerfil();
        }
        scanf("%s", operacao);
        char titulo[100];

        switch(atoi(operacao)){
            case 1:
                criaHistoricoUsuario(usuario,verbosidade);
                break;

            case 2:
                excluirUsuario(usuario);
                if(verbosidade)
                {
                    system("clear");
                    printf("Conta excluida\n");
                }
                return 1;
                break;
                
            case 3:
                if(verbosidade)
                    system("clear");
                return 2;
                break;
        }
    }
}
