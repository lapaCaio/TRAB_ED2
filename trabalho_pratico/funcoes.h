#ifndef FUNCS
#define FUNCS


typedef struct musica{
    int id;
    char nome[30];
    char autor[30];
    int vezes_selecionadas;
}Musicas;

typedef struct pessoa {
    int id;
    char nome[255];
    int idade;
    int sexo;
    int musicas[5];
    char tipo;
}Pessoa;

typedef struct nopessoa {
    Pessoa pessoa;
    struct nopessoa* proximo;
    struct nopessoa* anterior;
}NoPessoa;

typedef struct descritor {
    NoPessoa* inicio;
    NoPessoa* final;
    int tamanho;
}Descritor;

void lb();
void lt();
void linha();

Pessoa le_pessoa(Musicas* m);

void inicializa_descritor(Descritor* d);
int lista_vazia(Descritor* d);
void imprime_geral(Descritor* d);
void listar_populares(Descritor* d, Musicas* m);

void inicializa_nopessoa(NoPessoa* p, Musicas* m);

void inserir_pessoa(Descritor* d, Musicas* m);

#endif  //FUNCS