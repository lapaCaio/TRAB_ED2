#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include <string.h>

//quantidade total de músicas
#define N 30  

int id_global = 1;

typedef struct musica{
    int id;
    char nome[30];
    char autor[30];
    int vezes_selecionadas;
}Musicas;

//criar um vetor de 30 espaços com os códigos, nomes e vezes que a musica foi selecionada, inicializar tudo com zero e fodas...


//----------> ESTRUTURAS <----------//

typedef struct pessoa {
    int id;

    char nome[255];
    int idade;
    int sexo;
    int musicas[5];  //ALTERAR AQUI...
    
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

Pessoa le_pessoa(Musicas* m){
    Pessoa nova_pessoa;

    nova_pessoa.id = id_global;
    id_global++;


    lb();

    printf("\n NOME: ");
    scanf("%[^\n]", nova_pessoa.nome);
    lb();

    printf("\n IDADE: ");
    scanf("%d", &nova_pessoa.idade);
    lb();

    printf("\n SEXO: ");
    printf("\n\t [0] > MASCULINO");
    printf("\n\t [1] > FEMININO");
    printf("\n >>> ");
    scanf("%d", &nova_pessoa.sexo);
    lb();
    
    printf("\n MÚSICAS: ");
    printf("\n Digite o código das músicas separadas por espaço (Ex.: 12 3 22 8 7).");
    printf("\n >>> ");
    scanf("%d %d %d %d %d", &nova_pessoa.musicas[0], &
    nova_pessoa.musicas[1], &
    nova_pessoa.musicas[2], &
    nova_pessoa.musicas[3], &
    nova_pessoa.musicas[4]);



    
    if(nova_pessoa.sexo == 1){  //o 1 representa o sexo feminino
        if(nova_pessoa.idade <= 20){
            nova_pessoa.tipo = 1; //MULHERES com MENOS que 20 anos
        }else{
            nova_pessoa.tipo = 2;  //MULHERS com MAIS que 20 anos
        }
    }else{ //por outro lado o 0 representa o sexo masculino
        if(nova_pessoa.sexo <= 20){
            nova_pessoa.tipo = 3;  //HOMENS com MENOS que 20 anos
        }else{
            nova_pessoa.tipo = 4;  //HOMENS com MAIS que 20 anos
        }
    }

    return nova_pessoa;
}

//----------> FUNÇÕES - DUPLAMENTE ENCADEADA (LISTA DE ALUNOS) <----------//

void inicializa_descritor(Descritor* d){
    d->tamanho = 0;
    d->inicio = d->final = NULL; 
}

void inicializa_nopessoa(NoPessoa* p){
    p->anterior = p->proximo = NULL;
    p->pessoa = le_pessoa();
}

//verifica se uma lista de pessoas está vázia
int lista_vazia(Descritor* d){  //MUDAR POR CAUSA DO DESCRITOR?
    return (d->inicio == NULL && d->final == NULL);
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

void imprime_geral(Descritor* d){
    if(!lista_vazia(d)){
        for(NoPessoa* np = d->inicio; np != NULL; np = np->proximo){
            printf("\n ID: %d", np->pessoa.id);
            printf("\n NOME: %s", np->pessoa.nome);

            if(np->pessoa.sexo == 0){
                printf("\n SEXO: Masculino");
            }else{
                printf("\n SEXO: Feminino");
            }
            printf("\n TIPO: %d", np->pessoa.tipo);
            printf("\n MÚSICAS: ");  
            for(int i = 0; i < 5; i++){
                printf("\n\tCod.: %d", np->pessoa.musicas[i]);
                //printf("\n\tVezes selecionada: %d", np->pessoa.musicas[i]->vezes_selecionada);
            }
        }
    }else{
        printf("\n A LISTA DE ENTREVISTADOS ESTÁ VAZIA! POR FAVOR INSIRA ALGUM PARA QUE POSSAMOS MOSTRA-LO AQUI!");
    }
}

void listar_populares(Descritor* d, Musicas* m){

    
    for(NoPessoa* np = d->inicio; np != NULL; np = np->proximo){  //percorre a lista de pessoas 
        for(int i = 0; i < 5; i++){  //dentro de cada pessoa, percorre os 5 id's ecolhidos
            for(int j = 0; j < N; j++){  //percorre dentro da lista de musicas de tamanho 30
                if(m[j].id == np->pessoa.musicas[i]){  //encontra a posição correspondente ao id de cada musica da pessoa
                    m[j].vezes_selecionadas++;  //adicionda a vez que a música foi selecionada
                }
            }
        }
    }
}

int main(int argc, char** argv){
    setlocale(LC_ALL, "");

//-----> VARIÁVEIS PRINCIPAIS <------//
    Descritor* d = (Descritor*)malloc(sizeof(Descritor));
    inicializa_descritor(d);

    Musicas m[N];

//-----> VARIÁVEIS SECUNDÁRIAS <-----//

    int escolha;
    bool condicao = true;

    //VARIÁVEIS RETIRADAS
    //int id_buscado, id_buscado_2;
    //char curso_buscado[255];

    //inserir_dados_arquivo(&ldp);



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

            printf("\n OPÇÃO NÚMERO 0 SELECIONADA!");
            inserir_pessoa(d);

            break;

        case 1:  //ALTERA OS DADOS DE UM ALUNO
            
            //alterar_dados(&ldp);
            printf("\n OPÇÃO NÚMERO 1 SELECIONADA!");
            imprime_geral(d);

            break;

        case 2:  //REMOVE OS DADOS DE UM ALUNO
                
            //remover_aluno(&ldp);
            
            printf("\n OPÇÃO NÚMERO 2 SELECIONADA!");

            break;
            
        case 3:

            lt();

            //salvar_dados_arquivo(&ldp);
            
            printf("\n PROGRAMA ENCERRADO!");

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