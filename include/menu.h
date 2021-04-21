#ifndef Menu_h
#define Menu_h

/**
 * @brief Imprime opcoes menu de Login
 */
void imprimeMenuLogin();

/**
 * @brief Imprime opcoes menu principal
 */
void imprimeMenuPrincipal();

/**
 * @brief Imprime opcoes menu perfil
 */
void imprimeMenuPerfil();

/**
 * @brief Chama o menu login
 * @param verbosidade opcao de verbosidade
 * @return Caso possuir um usuario valido retorna seu id, caso contrario retorna FALSE
 */
int menuLogin(int verbosidade);

/**
 * @brief Chama o menu principal
 * @param usuario struct usuario
 * @param filmes struct filmes
 * @param verbosidade opcao de verbosidade
 * @return um inteiro com a opcao desejada de acesso
 */
int menuPrincipal(Usuario *usuario,Filmes *filmes, int verbosidade);

/**
 * @brief Chama o menu perfil
 * @param usuario struct usuario
 * @param verbosidade opcao de verbosidade
 * @return um inteiro com a opcao desejada de acesso
 */
int menuPerfil(Usuario *usuario, int verbosidade);

#endif