#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "funcoes.h"
#include "salvar.h"

#define N 30  

int id_global = 1;

typedef struct musica Musicas;

typedef struct lista_de_musicas ListaMusicas;

//----------> ESTRUTURAS <----------//

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

Pessoa le_pessoa(ListaMusicas* lm){  //OK
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
    listar_musicas(lm);
    linha();
    printf("\n Digite o código das músicas separadas por espaço (Ex.: 12 3 22 8 7).");
    printf("\n >>> ");
    scanf("%d %d %d %d %d", 
    &nova_pessoa.musicas[0], 
    &nova_pessoa.musicas[1], 
    &nova_pessoa.musicas[2], 
    &nova_pessoa.musicas[3], 
    &nova_pessoa.musicas[4]);

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

void inserir_pessoa(Descritor* d, ListaMusicas* lm){  //OK
    NoPessoa* novo_np = (NoPessoa*)malloc(sizeof(NoPessoa));

    novo_np->anterior = novo_np->proximo = NULL;
    novo_np->pessoa = le_pessoa(lm);

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

void remover_pessoa(Descritor* d, int id) {
    NoPessoa* atual = d->inicio;

    while (atual != NULL) {
        if (atual->pessoa.id == id) {
            if (atual == d->inicio) {
                d->inicio = atual->proximo;
                d->inicio->anterior = NULL;
            } else if (atual == d->final) {
                d->final = atual->anterior;
                d->final->proximo = NULL;
            } else {
                atual->anterior->proximo = atual->proximo;
                atual->proximo->anterior = atual->anterior;
            }
            free(atual);
            d->tamanho--;
            return;
        }
        atual = atual->proximo;
    }
    printf("NAO FOI ENCONTRADA UMA PESSOA COM O ID ESPECIFICADO!\n");
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

ListaMusicas* inicializarListaMusicas(){
    ListaMusicas* novoNo = (ListaMusicas*)malloc(sizeof(ListaMusicas));
    novoNo->proximo = NULL;
    return novoNo;
}

int estaVazia(ListaMusicas* lm){
    return lm->proximo == NULL;
}

void inserirMusica(ListaMusicas* lm, Musica novaMusica){
    ListaMusicas* novoNo = inicializarListaMusicas();
    novoNo->m = novaMusica;
    if(estaVazia(lm)){
        lm->proximo = novoNo;
    }else{
        ListaMusicas* atual = lm->proximo;
        while(atual->proximo != NULL){
            atual = atual->proximo;
        }
        atual->proximo = novoNo;
    }
}

void listar_musicas(ListaMusicas* lm){  //OK
    //lt();
    printf("\n TODAS AS MÚSICAS:");

    for(ListaMusicas* atual = lm->proximo; atual != NULL; atual = atual->proximo){
        printf("\n [%d] %s - %s - %d", atual->m.id, atual->m.nome, atual->m.autor, atual->m.vezes_selecionadas);
    }
}

void separar_favoritas(ListaMusicas* lm, ListaMusicas* saida){
    for(ListaMusicas* atual = lm->proximo; atual != NULL && atual->m.vezes_selecionadas != 0; atual = atual->proximo){
        inserirMusica(saida, atual->m);
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
        NoPessoa* novo_np = (NoPessoa*)malloc(sizeof(NoPessoa));
        if(novo_np == NULL) {
            printf("\n ERRO AO ALOCAR MEMORIA!");
            return;
        }
        novo_np->anterior = novo_np->proximo = NULL;
        novo_np->pessoa = np->pessoa;

        if(lista_vazia(temp)){ 
            temp->inicio = temp->final = novo_np;
            temp->tamanho++;
        }else{
            temp->final->proximo = novo_np;
            novo_np->anterior = temp->final;
            temp->final = novo_np;      
            temp->tamanho++;
        }
    }
}

void imprime_categoria(Descritor* d){
    if(!lista_vazia(d)){
        for(NoPessoa* np = d->inicio; np != NULL; np = np->proximo){
            printf("\nNOME: %s %s", np->pessoa.nome, np->pessoa.sobrenome);
        }    
    }else{
        printf("\n A CATEGORIA ESTÁ VAZIA!");
    }
}

void resetMusicas(ListaMusicas* lm) {
    ListaMusicas* atual = lm;
    while (atual != NULL) {
        atual->m.vezes_selecionadas = 0;
        atual = atual->proximo;
    }
}

void atualiza_musicas(Descritor* d,  ListaMusicas* lm){
    //reinicia o valor das vezes_selecionadas para zero
    resetMusicas(lm);

    //coletando as informações das músicas a partir da lista total de pessoas
    ListaMusicas* atual = lm;
    for(NoPessoa* np = d->inicio; np != NULL; np = np->proximo){
        for(int i = 0; i < 5; i++){
            while(atual != NULL){
                if(atual->m.id == np->pessoa.musicas[i]){
                    atual->m.vezes_selecionadas++;
                }
                atual = atual->proximo;
            }
        }
    }
}


int tamanhoListaMusica(ListaMusicas* lm) {
    int tamanho = 0;
    ListaMusicas* atual = lm->proximo;
    while (atual != NULL) {
        tamanho++;
        atual = atual->proximo;
    }
    return tamanho;
}

//ENTENDER O FUNCIONAMENTO DO SHELLSORT...
void shellSortListaMusica(ListaMusicas* lm) {
    if (lm == NULL) {
        printf("\n lm é nulo");
        return;
    }
    ListaMusicas* atual = lm;
    printf("\n atual recebe lm");
    int h, i, j;
    Musica temp;
    int tam = tamanhoListaMusica(lm);
    printf("\n tam recebe o retorno da função (%d)", tam);

    for (h = tam/2; h > 0; h /= 2) {
        printf("\n h: %d", h);
        for (i = h; i < tam; i++) {
            printf("\n i: %d", i);
            atual = lm->proximo;  //recebe o proximo
            printf("\n atual recebe lm dnv");
            printf("\n %d - %s - %d", atual->m.id, atual->m.nome, atual->m.vezes_selecionadas);
            for (j = i - h; j >= 0; j -= h) {
                printf("\n j: %d", j);
                for (int k = 0; k < j; k++) {
                    printf("\n k: %d", k);
                    atual = atual->proximo;
                    printf("\n atual recebe atual->proximo");
                }
                printf("\n entrando no if");
                if (atual->m.vezes_selecionadas >= atual->proximo->m.vezes_selecionadas) {
                    temp = atual->m;
                    printf("\n temp recebe atual->m");
                    atual->m = atual->proximo->m;
                    printf("\n atual->m recebe proximo->m");
                    atual->proximo->m = temp;
                    printf("\natual->proximo recebe temp (atual->m)");
                    listar_musicas(lm);
                }
            }
        }
    }
}





