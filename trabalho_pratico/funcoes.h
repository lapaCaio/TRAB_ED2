#ifndef FUNCS
#define FUNCS

//estrutura para guardas as informações de cada música
typedef struct musica{
    int id;
    char nome[30];
    char autor[30];
    int vezes_selecionadas;
}Musica;

typedef struct lista_de_musicas{
    Musica m;
    struct lista_de_musicas* proximo;
}ListaMusicas;

//estrutura para guardar as informações de cada pessoa
typedef struct pessoa {
    int id;
    char nome[255];
    char sobrenome[255];
    int idade;
    int sexo;
    int musicas[5];
    char tipo;
}Pessoa;

//nó simples da lista de pessoas entrevistadas
typedef struct nopessoa {
    Pessoa pessoa;
    struct nopessoa* proximo;
    struct nopessoa* anterior;
}NoPessoa;

//estrutura criada para guardar informações básicas sobre a lista de pessoas
typedef struct descritor {
    NoPessoa* inicio;
    NoPessoa* final;
    int tamanho;
}Descritor;

//limpa o buffer
void lb();

//limpa a tela
void lt();

//cria uma linha(usada para organização das informações no terminal)
void linha();

//acrescenta +1 no id global
void atualiza_id_global();

// coleta todas as informações de uma pessoa entrevistada
Pessoa le_pessoa(ListaMusicas* lm);

//preenche o descritor com as informações básicas
void inicializa_descritor(Descritor* d);

//verifica se a lista está vazia
int lista_vazia(Descritor* d);

//insere uma pessoa na lista, com suas informações
void inserir_pessoa(Descritor* d, ListaMusicas* lm);

//remove uma pessoa da lista, com suas informações
void remover_pessoa(Descritor* d, int id);

//imprime a lista de todas as pessoas
void imprime_pessoas(Descritor* d);

//inicializa  lista de músicas com suas iformações básicas
ListaMusicas* inicializarListaMusicas();

//verifica se a lista de músicas está vazia
int estaVazia(ListaMusicas* lm);

//insere uma música na lista de músicas
void inserirMusica(ListaMusicas* lm, Musica novaMusica);

//imprime uma lista de todas as músicas
void listar_musicas(ListaMusicas* lm);

//separa as músicas favoritas de uma lista para outra
void separar_favoritas(ListaMusicas* lm, ListaMusicas* saida);

//separa as pessoas em quatro categorias distintas
void separa_categorias(Descritor* todos, Descritor* d1, Descritor* d2, Descritor* d3, Descritor* d4);

//imprime todas as pessoas da categoria selecionada
void imprime_categoria(Descritor* d);

//troca o valor das vezes_selecionadas de todas as músicas para zero
void resetMusicas(ListaMusicas* lm);

//atualiza as informações das listas de músicas
void atualiza_musicas(Descritor* d,  ListaMusicas* lm);

//função que retorna o tamanho de uma lista de músicas
int tamanhoListaMusica(ListaMusicas* lm);

//função que ordena a lista de músicas com base nas vezes_selecionadas 
void shellSortListaMusica(ListaMusicas* lm);
#endif  //FUNCS