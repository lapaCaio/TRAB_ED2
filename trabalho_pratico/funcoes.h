#ifndef FUNCS
#define FUNCS

//estrutura para guardas as informações de cada música
typedef struct musica{
    int id;
    char nome[30];
    char autor[30];
    int vezes_selecionadas;
}Musicas;

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

// coleta todas as informações de uma pessoa entrevistada
Pessoa le_pessoa(Musicas* m);

//preenche o descritor com as informações básicas
void inicializa_descritor(Descritor* d);

//verifica se a lista está vazia
int lista_vazia(Descritor* d);

//imprime todas as informações coletadas das pessoas entrevistadas
void imprime_geral(Descritor* d);

//lista as músicas populares
void listar_populares(Descritor* d, Musicas* m);

//adiciona uma nova pessoa na lista de pessoas entrevistadas
void inserir_pessoa(Descritor* d, Musicas* m);

//lista todas a músicas
void listar_musicas(Musicas* m);

//lista as músicas populares
void listar_musicas_populares(Musicas* m);

//acrescenta +1 no id global
void atualiza_id_global();

//algoritmo de ordenação por diminuição de incremento
void shellSortMusica(Musicas* m, int tam);

#endif  //FUNCS