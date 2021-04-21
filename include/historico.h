#ifndef Historico_h
#define Historico_h

typedef struct historico Historico;

/**
 * @brief Cria um historico para um usuario valido
 * @return Historico o historico de um usuario
 */
Historico* criaHistorico();

/**
 * @brief Le o arquivo historico e salva o historico de um usuario em sua respectiva struct
 * @param historico struct historico 
 * @param usuario struct usuario
 * @return Historico o historico preenchido de um usuario
 */
Historico* adicionaHistoricoUsuario(Historico *historico, Usuario *usuario);

/**
 * @brief Adiciona os filmes assistidos ao historico de um usuario valido
 * @param titulo titulo do filme
 * @param nota nota atribuida ao filme
 * @param data  data que o filme foi assistido
 * @param usuario struct usuario 
 */
void colocarFilmeHistorico(char* titulo, float nota, char* data, Usuario *usuario);

/**
 * @brief Imprime o historico de um usuario de forma ordenada
 * @param historico struct historico 
 * @param qtdFilmes quantidade de filmes vistos pelo usuario
 * @param opcao para escolher a forma de ordenacao 
 */
void imprimirHistoricoOrdenado(Historico *historico,int qtdFilmes, char opcao);

/**
 * @brief Ordena o historico de um usuario por nota
 * @param historico struct historico
 * @param qtdFilmes quantidade de filmes assistidos
 */
void ordenaHistoricoNota(Historico *historico,int qtdFilmes);

/**
 * @brief Ordena o historico de um usuario por data
 * @param historico struct historico
 * @param qtdFilmes quantidade de filmes assistidos
 */
void ordenaHistoricoData(Historico *historico,int qtdFilmes);


/**
 * @brief Faz a troca das variaveis de dois historicos
 * @param historico struct historico
 * @param i numero do historico j
 * @param i numero do historico i
 */
void trocaVariaveisHistorico(Historico *historico, int i, int j);

/**
 * @brief Libera memoria atribuida ao historico
 * @param historico struct historico
 * @param qtdFilmes quantidade de filmes assistidos
 */
void destroiHistorico(Historico *historico, int qtdFilmes);

#endif
