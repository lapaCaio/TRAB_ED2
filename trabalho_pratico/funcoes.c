#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "funcoes.h"
#include "salvar.h"

#define N 30  

int id_global = 1;

//----------> ESTRUTURAS <----------//

typedef struct musica Musicas;

typedef struct pessoa Pessoa;

typedef struct nopessoa NoPessoa;

typedef struct descritor Descritor;

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

void atualiza_id_global(){
    id_global++;
}

//----------> FUNÇÕES - TAD (PESSOA) <----------//

Pessoa le_pessoa(Musicas* m){  //OK
    Pessoa nova_pessoa;

    nova_pessoa.id = id_global;
    atualiza_id_global();

    printf("\n NOME: ");
    scanf("%[^\n]", nova_pessoa.nome);
    lb();

    printf("\n SOBRENOME: ");
    scanf("%[^\n]", nova_pessoa.sobrenome);
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
    
    linha();
    listar_musicas(m);
    linha();
    printf("\n Digite o código das músicas separadas por espaço (Ex.: 12 3 22 8 7).");
    printf("\n >>> ");
    scanf("%d %d %d %d %d", &nova_pessoa.musicas[0], &nova_pessoa.musicas[1], &nova_pessoa.musicas[2], &nova_pessoa.musicas[3], &nova_pessoa.musicas[4]);

    if(nova_pessoa.sexo == 0){  //o 1 representa o sexo feminino
        if(nova_pessoa.idade <= 20){
            nova_pessoa.tipo = 1; //HOMENS com MENOS que 20 anos
        }else{
            nova_pessoa.tipo = 2;  //HOMENS com MAIS que 20 anos
        }
    }else{ //por outro lado o 0 representa o sexo masculino
        if(nova_pessoa.idade <= 20){
            nova_pessoa.tipo = 3;  //MULHERES com MENOS que 20 anos
        }else{
            nova_pessoa.tipo = 4;  //MULHERES com MAIS que 20 anos
        }
    }

    return nova_pessoa;
}

//----------> FUNÇÕES - DUPLAMENTE ENCADEADA (LISTA DE ALUNOS) <----------//

void inicializa_descritor(Descritor* d){  //OK
    d->tamanho = 0;
    d->inicio = d->final = NULL; 
}

int lista_vazia(Descritor* d){  //OK
    return (d->inicio == NULL && d->final == NULL);
}

void inserir_pessoa(Descritor* d, Pessoa p){  //OK
    NoPessoa* novo_np = (NoPessoa*)malloc(sizeof(NoPessoa));

    novo_np->proximo = NULL;
    novo_np->pessoa = p;

    if(lista_vazia(d)){  //insere na primeira posição da lista
        d->inicio = d->final = novo_np;
        d->tamanho++;
    }else{  //insere nos outros locais da lista
        d->final->proximo = novo_np;
        d->final = novo_np;      
        d->tamanho++;
    }
}

void imprime_pessoas(Descritor* d){  //OK
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
            }
        }
    }else{
        printf("\n ERROR: LISTA DE ENTREVISTADOS VAZIA!");
    }
}

void inicializar_musicas(Musicas* m){
    for(int i = 0; i < N; i++){
        m[i].vezes_selecionadas = 0;
    }
}

void listar_musicas(Musicas* m){  //OK
    //lt();
    printf("\n TODAS AS MÚSICAS:");

    for(int i = 0; i < N; i++){
        printf("\n [%d] %s - %s - %d", m->id, m->nome, m->autor, m->vezes_selecionadas);
    }
}

void separar_populares(Musicas* entrada, Musicas* saida){
    inicializar_musicas(saida);
    int j = 0;
    for(int i = 0; i < N; i++){
        if(entrada[i].vezes_selecionadas > 0){
            saida[j] = entrada[i];
            j++;
        }
    }
}

void separa_categorias(Descritor* todos, Descritor* d1, Descritor* d2, Descritor* d3, Descritor* d4){
    if(lista_vazia(todos)){ 
        printf("\n A LISTA DE ENTREVISTADOS ESTA VAZIA!");
        return;
    }
    for(NoPessoa* np = todos->inicio; np != NULL; np = np->proximo){
        Descritor* temp;
        if(np->pessoa.tipo == 1){ //HOMEM ABAIXO
            temp = d1;
        }else if(np->pessoa.tipo == 2){  //HOMEM ACIMA
            temp = d2;
        }else if(np->pessoa.tipo == 3){  //MULHER ABAIXO
            temp = d3;
        }else if(np->pessoa.tipo == 4){  //MULHER ACIMA
            temp = d4;
        }else{
            printf("\n ALGO DEU ERRADO!");
            return;
        }
        inserir_pessoa(temp, np->pessoa);
    }
}

void imprime_categoria(Descritor* d){  //ADICIONAR DETALHES SOBRE A CATEGORIA QUE ESTÁ SENDO IMPRIMIDA NA TELA
    if(!lista_vazia(d)){
        for(NoPessoa* np = d->inicio; np != NULL; np = np->proximo){
            printf("\nNOME: %s %s", np->pessoa.nome, np->pessoa.sobrenome);
        }    
    }else{
        printf("\n A CATEGORIA ESTÁ VAZIA!");
    }
}

void atualiza_musicas(Descritor* d,  Musicas* m){
    //reinicia o valor das vezes_selecionadas para zero
    inicializar_musicas(m);

    //coletando as informações das músicas a partir da lista total de pessoas
    for(NoPessoa* np = d->inicio; np != NULL; np = np->proximo){
        for(int i = 0; i < 5; i++){
            for(int j = 0; j < N; j++){
                if(m[j].id == np->pessoa.musicas[i]){
                    m[j].vezes_selecionadas++;
                }
            }
        }
    }
}






