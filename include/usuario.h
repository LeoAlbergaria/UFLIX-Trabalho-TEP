#ifndef Usuario_h
#define Usuario_h

typedef struct usuario Usuario;

/**
 * @brief Verifica se o nome e a senha pertencem a um usuario valido
 * @param nome nome usuario
 * @param senha senha usuario
 * @param verbosidade verbosidade
 * @return int TRUE se for um usuario valido e FALSE caso nao for
 */
int verificaUsuario(char *nome, char *senha, int verbosidade);

/**
 * @brief Cria um novo usuario com os dados do usuario que possui o ID id 
 * @param id identificador de usuario
 * @return Usuario um usuario criado
 */
Usuario* criaUsuario(int id);

/**
 * @brief Verifica se o nome e a senha pertence a um usuario valido
 * @param nome nome usuario
 * @param senha senha usuario
 * @param senha2 confirmacao da senha usuario
 * @param verbosidade verbosidade
 * @return int TRUE se nao pertence a um usuario valido e FALSE caso pertenca
 */
int validaCadastro(char *nome, char *senha, char *senha2, int verbosidade);

/**
 * @brief Adiciona no final do arquivo de usuario um novo usuario
 * @param nome nome usuario
 * @param senha senha usuario
 */
void cadastraUsuario(char *nome, char *senha);

/**
 * @brief Da free nas variaveis alocadas para o usario
 * @param usuario struct usuario
 */
void destroiUsuario(Usuario *usuario);

/**
 * @brief Torna um usuario inativo no arquivo de usuarios
 * @param usuario struct usuario
 */
void excluirUsuario(Usuario *usuario);

/**
 * @brief Adiciona um historico a struct usuario 
 * @param usuario struct usuario
 * @param verbosidade verbosidade
 */
void criaHistoricoUsuario(Usuario *usuario, int verbosidade);

/**
 * @brief Chama a funcao de ordenacao de historico do TAD historico
 * @param usuario struct usuario
 * @param verbosidade verbosidade
 */
void historicoOrdenado(Usuario *usuario,int verbosidade);

/**
 * @brief um getter para obter o id do usuario
 * @param usuario struct usuario
 * @return id do usuario
 */
int retornaId(Usuario *usuario);

/**
 * @brief um getter para obter a quantidade de filmes no historico do usuario
 * @param usuario struct usuario
 * @return quantidade de filmes visto pelo usuario
 */
int retornaQtdFilme(Usuario *usuario);

/**
 * @brief um getter para obter o nome do usuario
 * @param usuario struct usuario
 * @return nome do usuario
 */
char* retornaNome(Usuario *usuario);

/**
 * @brief um setter para alterar a quantidade de filmes vista pelo usuario
 * @param usuario struct usuario
 */
void setterQtdFilme(Usuario *usuario, int qtd);

#endif