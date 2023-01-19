#ifndef SAVE
#define SAVE

typedef struct musica Musicas;

typedef struct lista_de_musicas ListaMusicas;

typedef struct descritor Descritor;

//preenche a estrutura com todas as pessoas
void lerPessoasDoArquivo(Descritor* d);

//salva os dados das pessoas no arquivo "pessoas.txt"
void salvarPessoasNoArquivo(Descritor* d);

//salva os dados das pessoas no arquivo que será passado como parâmetro
void salvarCategoria(Descritor* d, int i);

//le do arquivo todas a músicas e preenche a lista com elas
void lerMusicasDoArquivo(ListaMusicas* lm, char* nomeArquivo);

//salva as músicas em um arquivo
void salvarMusicasArquivo(ListaMusicas* lm, char* nomeArquivo);

#endif  //SAVE