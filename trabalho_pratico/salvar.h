#ifndef SAVE
#define SAVE

typedef struct descritor Descritor;

typedef struct musica Musicas;

//preenche a estrutura com todas as pessoas
void ler_pessoas_do_arquivo(Descritor* d);

//salva os dados das pessoas no arquivo "pessoas.txt"
void salvar_pessoas_no_arquivo(Descritor* d);

//salva os dados das pessoas no arquivo que será passado como parâmetro
void salvar_categoria(Descritor* d, int i);

//le do arquivo todas a músicas e preenche a lista com elas
void ler_musicas_do_arquivo(Musicas* m, char* nomeArquivo);

//salva as músicas em um arquivo
void salvar_musicas_no_arquivo(Musicas* m, char* nomeArquivo);

#endif  //SAVE