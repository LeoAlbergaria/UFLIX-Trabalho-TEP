#ifndef Filmes_h
#define Filmes_h

typedef struct filmes Filmes;

/**
 * @brief Le e armazena os filmes do arquivo de filmes
 * @param qtdFilmes Quantidade de filmes na lista
 * @return Filmes lista de filmes
 */
Filmes* salvarFilmes(int *qtdFilmes);

/**
 * @brief Lista os filmes da struct de filmes
 * @param usuario struct usuario
 * @param filmes struct filmes
 * @param qtdFilmes quantidade de filmes da lista
 * @param verbosidade opcao de verbosidade
 */
void listarFilmes(Usuario *usuario, Filmes *filmes, int qtdFilmes, int verbosidade);

/**
 * @brief Le os metadados de um filme
 * @param filme struct filme
 * @param num numero do filme
 * @param linha char auxiliar para ler as linhas do arquivo
 */
void lerMetadados(Filmes *filme, int num, char *linha);

/**
 * @brief Imprime os metadados de um filme selecionado
 * @param usuario struct usuario
 * @param filme struct filme
 * @param num numero do filme
 * @param verbosidade opcao de verbosidade
 */
void imprimirMetadadosFilme(Filmes *filme, int num, Usuario *usuario, int verbosidade);

/**
 * @brief Assiste o filme selecionado
 * @param filme struct filme
 * @param num numero do filme
 * @param usuario struct usuario
 * @param verbosidade opcao de verbosidade
 */
void assistirFilme(Filmes *filme, int num, Usuario *usuario, int verbosidade);

/**
 * @brief Procura filmes na lista de filmes
 * @param filmes struct filmes
 * @param usuario struct usuario
 * @param titulo titulo dos filmes
 * @param qtdFilmes quantidade de filmes da lista
 * @param verbosidade opcao de verbosidade
 */
void procurarFilme(Filmes *filmes, Usuario *usuario, char *titulo, int qtdFilmes, int verbosidade);

/**
 * @brief Libera memoria atribuida ao armazenamento dos filmes e seus dados
 * @param filmes struct filmes
 * @param qtd quantidade de filmes
 */
void destroiFilmes(Filmes *filmes, int qtd);

#endif