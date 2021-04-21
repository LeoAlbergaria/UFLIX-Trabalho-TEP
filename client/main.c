#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/usuario.h"
#include "../include/filmes.h"
#include "../include/menu.h"

int main(int argc, char *argv[])
{
  int verbosidade;
  if(argc > 1)
  {
    verbosidade = atoi(argv[1]);
    if(verbosidade != 0 && verbosidade != 1)
    {
      printf("Digite uma verbosidade valida!!!");
      exit(1);
    }
  }
  else
    verbosidade = 1;

  int menu = 1, idUsuario;
  Usuario* usuario = NULL;
  Filmes* filmes = NULL;

  while(menu != 0)
  {
    switch (menu)
    {
    case 1:
      idUsuario = menuLogin(verbosidade);
      if(idUsuario)
        menu = 2;
      else
        menu = 0;
      break;

    case 2:
      if(usuario == NULL)
        usuario = criaUsuario(idUsuario);
      menu = menuPrincipal(usuario, filmes, verbosidade);
      if(menu == 1)
      {
        destroiUsuario(usuario);
        usuario = NULL;
      }
      break;

    case 3:
      menu = menuPerfil(usuario, verbosidade);
      if(menu == 1)
      {
        destroiUsuario(usuario);
        usuario = NULL;
      }
      break;
    }
  }
  return 0;
}