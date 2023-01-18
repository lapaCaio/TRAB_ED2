#ifndef SAVE
#define SAVE

typedef struct musica Musicas;

typedef struct descritor Descritor;

//preenche a estrutura de músicas com todas as músicas 
void inserir_musicas_arquivo(Musicas* m);

//salva as músicas no arquivo "musicas.txt"
void salvar_musicas_arquivo(Musicas* m);

//preenche a lista de músicas com as músicas mais populares
void inserir_musicas_populares_arquivo(Musicas* m);

//salva as músicas no arquivo "musicas_populares.txt"
void salvar_musicas_populares_arquivo(Musicas* m, Musicas* saida);

//preenche a estrutura com todas as pessoas
void inserir_pessoas_arquivo(Descritor* d);

//salva os dados das pessoas no arquivo "pessoas.txt"
void salvar_pessoas(Descritor* d);

//salva os dados das pessoas no arquivo que será passado como parâmetro
void salvar_categoria(Descritor* d, int i);

#endif  //SAVE