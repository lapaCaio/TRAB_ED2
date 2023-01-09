#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include <string.h>

//quantidade total de músicas
#define N 30  

int id_global = 1;

typedef struct musica{
    int codigo;
    int vezes_selecionada;
}Musica;

//----------> ESTRUTURAS <----------//

typedef struct pessoa {
    int id;

    char nome[255];
    int idade;
    char sexo;
    Musica* musicas[5];
    
    char tipo;  //o tipo será calculado...
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

//----------> FUNÇÕES AUXILIARES <----------//

void lb(){  //LIMPA BUFER
    setbuf(stdin, NULL);
}
void lt(){  //LIMPA TERMINAL
    system("cls");
    system("clear"); 
}
void linha(){
    printf("\n|------------------------------------------------------------------------------------------|");  
}

//----------> FUNÇÕES - TAD (PESSOA) <----------//

Pessoa le_pessoa(){
    Pessoa nova_pessoa;

    nova_pessoa.id = id_global;
    id_global++;


    lb();

    printf("\n NOME: ");
    scanf("%[^\n]", nova_pessoa.nome);
    lb();

    printf("\n IDADE: ");
    scanf("%d", nova_pessoa.idade);
    lb();

    printf("\n SEXO: ");
    scanf("%c", &nova_pessoa.sexo);
    lb();

    printf("\n MÚSICAS: ");
    for(int i = 0; i < 5; i++){
        printf("\n Digite o código da sua %d° música. ");
        printf("\n >>> ");
        scanf("%d", &nova_pessoa.musicas[i]->codigo);
        nova_pessoa.musicas[i]->codigo--;
        nova_pessoa.musicas[i]->vezes_selecionada++;
        lb();
    }
    
    if(nova_pessoa.sexo == "M" || nova_pessoa.sexo == "m"){
        if(nova_pessoa.idade <= 20){
            nova_pessoa.tipo = 1; //MULHERES com MENOS que 20 anos
        }else{
            nova_pessoa.tipo = 2;  //MULHERS com MAIS que 20 anos
        }
    }else{ 
        if(nova_pessoa.idade <= 20){
            nova_pessoa.tipo = 3;  //HOMENS com MENOS que 20 anos
        }else{
            nova_pessoa.tipo = 4;  //HOMENS com MAIS que 20 anos
        }
    }

    return nova_pessoa;
}

//função de alterar o nome retirada
//função de alterar curso retirada
//função de pegar curso retirada
//função de imprimir curso retirada

//----------> FUNÇÕES - DUPLAMENTE ENCADEADA (LISTA DE ALUNOS) <----------//

void inicializa_descritor(Descritor* d){
    d->tamanho = 0;
    d->inicio = d->final = NULL;
}

void inicializa_nopessoa(NoPessoa* p){
    p->anterior = p->proximo = NULL;
    p->pessoa = le_pessoa();
    for(int i = 0; i < 5; i++){
        p->pessoa.musicas[i]->vezes_selecionada = 0;
    }
}

//verifica se uma lista de pessoas está vázia
int lista_vazia(Descritor* d){  //MUDAR POR CAUSA DO DESCRITOR?
    return (d->inicio == d->final == NULL);
}


//função de buscar elemento retirada

void inserir_pessoa(Descritor* d){
    NoPessoa* novo_np = (NoPessoa*)malloc(sizeof(NoPessoa));

    inicializa_nopessoa(novo_np);

    if(lista_vazia(d)){  //insere na primeira posição da lista
        d->inicio = d->final = novo_np;
        d->tamanho++;
    }else{  //insere nos outros locais da lista
        d->final->proximo = novo_np;
        novo_np->anterior = d->final;
        d->final = novo_np;      
        d->tamanho++;
    }
    
}


void bubble_sort(int arr[], int n) {
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        int temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }
}

void imprime_musicas_populares(Descritor* d){
    Musica lista_pupulares[N];

    for(int i = 0; i < N; i++){
        lista_pupulares[i].codigo = -1;
        lista_pupulares[i].vezes_selecionada = 0;
    }

    int temp = 0;
    for(NoPessoa* np = d->inicio; np != d->final; np = np->proximo){
        for(int i = 0; i < 5; i++){
            if(lista_pupulares[np->pessoa.musicas[i]->codigo].codigo == -1  ){
                lista_pupulares[np->pessoa.musicas[i]->codigo] = //problema a ser resolvido aqui 
            }
                lista_pupulares[np->pessoa.musicas[i]->codigo] = ;
        }
        np->pessoa.musicas[]
    }
}


void imprime_alunos(ListaDeAlunos **lda){  //NÃO PRECISO MEXER EM NADA AQUI...

    lt();

    linha();

    printf("\n LISTA DE ALUNOS");

    linha();

    if(!lda_vazia(&(*lda))){

        printf("\n");

        for(ListaDeAlunos* p = *lda; p != NULL; p = p->proximo){

            imprimeAluno(&p->aluno);

        }
        
        printf("\n");

    }else{

        lt();

        linha();

        printf("\n A LISTA DE ALUNOS ESTÁ VAZIA!");
        printf("\n POR FAVOR INSIRA UM ALUNO NA LISTA ANTES DE TENTAR IMPRIMI-LA!");

    }
}


void inserir_dados_arquivo(ListaDeAlunos **lda)
{

    // lt();

    printf("\n");

    FILE *arquivo_txt = fopen("entradas.txt", "r");
    rewind(arquivo_txt);

    Aluno *aluno_novo = (Aluno *)malloc(sizeof(Aluno));

    while (fscanf(arquivo_txt, "%[^\t]\t%d\t%[^\n]\n\t", aluno_novo->nome, &aluno_novo->id, aluno_novo->curso) != EOF)
    {

        atualiza_id_global(aluno_novo->id);

        aluno_novo->prox_amg = NULL;

        ListaDeAlunos *n = malloc(sizeof(ListaDeAlunos));
        ListaDeAlunos *p;

        int id_temp;

        while (fscanf(arquivo_txt, "%d ", &id_temp) == 1)
        {
            No *novo_amigo = malloc(sizeof(No));

            novo_amigo->id = id_temp;
            novo_amigo->prox = aluno_novo->prox_amg;
            aluno_novo->prox_amg = novo_amigo;
        }

        if (n)
        {

            n->aluno = *aluno_novo;

            // lt();

            if (*lda == NULL)
            { // INSERÇÃO EM PRIMEIRO NA LISTA

                n->proximo = n->anterior = NULL;
                *lda = n;
            }
            else if (strcmp(n->aluno.nome, (*lda)->aluno.nome) < 0)
            { // INSERÇÃO NO INÍCIO DA LISTA

                n->proximo = *lda;
                n->anterior = NULL;
                (*lda)->anterior = n;
                *lda = n;
            }
            else
            { // INSERÇÃO COM VÁRIOS VALORES EM ORDEM DECRESCENTE

                for (p = *lda; p->proximo != NULL && strcmp(n->aluno.nome, p->aluno.nome) > 0; p = p->proximo)
                    ;

                if (strcmp(n->aluno.nome, p->aluno.nome) < 0)
                {

                    n->proximo = p;
                    n->anterior = p->anterior;
                    p->anterior->proximo = n;
                    p->anterior = n;
                }
                else
                {

                    n->proximo = p->proximo;
                    n->anterior = p;
                    p->proximo = n;
                }
            }
        }
        else
        {

            printf("\nOPS! ALGO DEU ERRADO AQUI, DESCULPE-NOS PELO TRANSTORNO... T-T");
        }
    }

    fclose(arquivo_txt);
}


void salvar_dados_arquivo(ListaDeAlunos **lda)
{

    lt();

    linha();

    printf("\n");

    FILE *arquivo_txt = fopen("entradas.txt", "w");

    for (ListaDeAlunos *p = *lda; p != NULL; p = p->proximo)
    {

        fprintf(arquivo_txt, "%s\t%d\t%s\n\t", p->aluno.nome, p->aluno.id, p->aluno.curso);

        for (No *n = p->aluno.prox_amg; n != NULL; n = n->prox)
        {
            fprintf(arquivo_txt, "%d ", n->id);
        }

        fprintf(arquivo_txt, "\n");
    }

    fclose(arquivo_txt);
}

int main(int argc, char** argv){
    setlocale(LC_ALL, "");

//-----> VARIÁVEIS PRINCIPAIS <------//
    Descritor* d;
    inicializa_descritor(d);


//-----> VARIÁVEIS SECUNDÁRIAS <-----//

    int escolha;
    bool condicao = true;

    //VARIÁVEIS RETIRADAS
    //int id_buscado, id_buscado_2;
    //char curso_buscado[255];

    inserir_dados_arquivo(&ldp);



//-----> O RESTO DA MAIN <-----//
    while(condicao){
        escolha = 0;

        linha();
        printf("\n ESCOLHA A OPÇÃO DESEJADA: ");
        linha();
        printf("\n 0 - ADICIONAR NOVO ENTREVISTADO");
        printf("\n 1 - LISTAR MÚSICAS MAIS POPULARES");
        printf("\n 2 - MÚSICAS MAIS POPULARES POR CATEGORIA");
        printf("\n 3 - SAIR");
        linha();
        printf("\n >>> ");
        scanf("%d", &escolha);
        lb();

        switch (escolha)
        {
        case 0:  //INSERE UMA PESSOA(ENTREVISTADO)

            inserir_pessoa(d);

            break;

        case 1:  //ALTERA OS DADOS DE UM ALUNO
            
            alterar_dados(&ldp);

            break;

        case 2:  //REMOVE OS DADOS DE UM ALUNO
                
            remover_aluno(&ldp);

            break;
            
        case 3:  //IMPRIME A LISTA DOS ALUNOS NA TELA

            imprime_alunos(&ldp);

            break;

        case 4:

            lt();

            salvar_dados_arquivo(&ldp);

            linha();

            condicao = false;

            break;

        default:

            lb();
            lt();
            linha();
            printf("\n O VALOR QUE VOCÊ DIGITOU NÃO CORRESPONDE A NENHUMA OPÇÃO,");
            printf("\n POR FAVOR DIGITE UM NÚMERO ENTRE 0 E 4, CORRESPONDENDE COM A OPÇÃO QUE DESEJA!");
            linha();

            continue;
        }
    }

    return EXIT_SUCCESS;
}