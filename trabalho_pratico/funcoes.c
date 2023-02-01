#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "funcoes.h"
#include "salvar.h"

#define N 30  

int id_global = 1;

//----------> ESTRUTURAS <----------//

typedef struct musica Musicas;

typedef struct pessoa Pessoa;

typedef struct nopessoa NoPessoa;

typedef struct descritor Descritor;

void lb(){  //LIMPA BUFER
    setbuf(stdin, NULL);
}
void lt(){  //LIMPA TERMINAL
    system("cls");
    system("clear"); 
}
void linha(){
    printf("\n|-----------------------------------------------|");  
}

void atualiza_id_global(){
    id_global++;
}

Pessoa le_pessoa(Musicas* m){  //OK
    Pessoa nova_pessoa;

    nova_pessoa.id = id_global;
    atualiza_id_global();
    
    bool condicao = true;
    while(condicao){
        lb();
        printf("\n NOME: ");
        scanf("%[^\n]", nova_pessoa.nome);
        lb();
        //verifica se o nome foi digitado
        if(strlen(nova_pessoa.nome) == 0){
            printf("\n ERRO: O NOME NÃO PODE SER VAZIO. \n");
            linha();
        }else{
            condicao = false;
        }
    }
    
    condicao = true;
    while(condicao){
        lb();
        printf("\n SOBRENOME: ");
        scanf("%[^\n]", nova_pessoa.sobrenome);
        lb();
        //verifica se o sobrenome foi digitado
        if(strlen(nova_pessoa.sobrenome) == 0){
            printf("\n ERRO: O SOBRENOME NÃO PODE SER VAZIO. \n");
            linha();
        }else{
            condicao = false;
        }
    }
    
    condicao = true;
    while(condicao){
        printf("\n IDADE: ");
        scanf("%d", &nova_pessoa.idade);
        lb();
        //verifica se a idade é um número inteiro positivo e está dentro do intervalo esperado
        if(nova_pessoa.idade <= 0 || nova_pessoa.idade > 110){
            printf("\n ERRO: A IDADE DEVE SER UM NÚMERO INTEIRO DE 0 A 110. \n");
        }else{
            condicao = false;
        }
    }
    
    condicao = true;
    while(condicao){
        printf("\n SEXO: ");
        printf("\n\t [0] > MASCULINO");
        printf("\n\t [1] > FEMININO");
        printf("\n >>> ");
        scanf("%d", &nova_pessoa.sexo);
        lb();
        //verifica se o sexo é 0 (masculino) ou 1 (feminino)
        if(nova_pessoa.sexo != 0 && nova_pessoa.sexo != 1){
            printf("\n ERRO: O SEXO DEVE SER 0 (MASCULINO) OU 1 (FEMININO).\n");
        }else{
            condicao = false;
        }
    }
    
    condicao = true;
    while(condicao){
        linha();
        listar_musicas(m);
        linha();
        printf("\n Digite o código das músicas separadas por espaço (Ex.: 12 3 22 8 7).");
        printf("\n >>> ");
        scanf("%d %d %d %d %d", &nova_pessoa.musicas[0], &nova_pessoa.musicas[1], &nova_pessoa.musicas[2], &nova_pessoa.musicas[3], &nova_pessoa.musicas[4]);

        //verifica se os códigos das músicas existem na lista de músicas fornecida
        for(int i=0; i<5; i++){
            int existe = 0;
            for(int j = 0; j < N; j++){
                if(nova_pessoa.musicas[i] == m[j].id){
                    existe = 1;
                }
            }
            if(!existe){
                printf("\n ERRO: UM DOS CODIGOS INFORMADOS NAO EXISTE. \n");
                continue;
            }else{
                condicao = false;
            }
        }
        //verifica se não há códigos de músicas duplicados
        for(int i = 0; i < 5; i++){
            for(int j = i+1; j < 5; j++){
                if(nova_pessoa.musicas[i] == nova_pessoa.musicas[j]){
                    printf("\n ERRO: O CÓDIGO DE MÚSICA %d FOI DIGITADO MAIS DE UMA VEZ. \n", nova_pessoa.musicas[i]);
                }else{
                    condicao = false;
                }
            }
        }
    }

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

void inicializa_descritor(Descritor* d){  
    d->tamanho = 0;
    d->inicio = d->final = NULL; 
}

int lista_vazia(Descritor* d){  
    return (d->inicio == NULL && d->final == NULL);
}

void inserir_pessoa(Descritor* d, Pessoa p){  
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

void imprime_pessoas(Descritor* d){  
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
    for (int i = 0; i < N; i++) {
        m[i].id = i + 1;
        // strcpy(m[i].nome, "");
        // strcpy(m[i].autor, "");
        m[i].vezes_selecionadas = 0;
    }
}

void listar_musicas(Musicas* m){  
    //lt();
    printf("\n TODAS AS MÚSICAS:");

    if(esta_ordenada(m)){
        for(int i = 0; i < N; i++){
            if(m[i].vezes_selecionadas == 0){
                continue;
            }else{
                printf("\n [%d] %s - %s - %d", m[i].id, m[i].nome, m[i].autor, m[i].vezes_selecionadas);
            }        
        }
    }else{
        for(int i = 0; i < N; i++){
            printf("\n [%d] %s - %s - %d", m[i].id, m[i].nome, m[i].autor, m[i].vezes_selecionadas);
        }
    }

    
}

int esta_ordenada(Musicas* m){
    int i = 0;
    int j = 1;

    while(i < N){
        if(m[i].id != j){
            return 1;
        }
        i++;
        j++;
    }
    return 0;
}

void separa_categorias(Descritor* all, Descritor* d1, Descritor* d2, Descritor* d3, Descritor* d4) {
    //limpa as listas d1, d2, d3 e d4
    limpa_lista(d1);
    limpa_lista(d2);
    limpa_lista(d3);
    limpa_lista(d4);

    NoPessoa* atual = all->inicio;
    while (atual != NULL) {
        //verifica o tipo da pessoa atual
        int tipo = atual->pessoa.tipo;
        //seleciona a lista de destino de acordo com o tipo
        Descritor* destino;
        switch (tipo) {
            case 1: destino = d1; break;
            case 2: destino = d2; break;
            case 3: destino = d3; break;
            case 4: destino = d4; break;
            default: destino = NULL; break;
        }
        //se a lista de destino foi selecionada, insere a pessoa na lista
        if (destino != NULL) {
            inserePessoa(destino, atual->pessoa);
        }
        //avança para o próximo nó da lista all
        atual = atual->proximo;
    }
}




void imprime_categoria(Descritor* d){  //ADICIONAR DETALHES SOBRE A CATEGORIA QUE ESTÁ SENDO IMPRIMIDA NA TELA
    if(!lista_vazia(d)){
        for(NoPessoa* np = d->inicio; np != NULL; np = np->proximo){
            printf("\nNOME: %s %s", np->pessoa.nome, np->pessoa.sobrenome);
        }    
    }else{
        printf("\n A CATEGORIA ESTA VAZIA!");
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

void shellsort(Musicas *m) {
    int i, j, h;
    Musicas auxiliar;

    h = 1;

    while (h < N){
        h = h*3+1;
    }
        
    while ( h > 1 ) {
        h = (h-1)/3;
        for ( i = h; i < N; i++ ) {
            auxiliar = m[i];
            j = i-h;
            while  ( j >= 0 && auxiliar.vezes_selecionadas > m[j].vezes_selecionadas ) {
                m[j+h] = m[j];
                j = j - h;
            }
            if ( j != (i-h)){
                m[j+h] = auxiliar;
            }       
        }
    }
}

void listar_pessoas(Descritor* d){
    for(NoPessoa* np = d->inicio; np != NULL; np = np->proximo){
        printf("\n ID: %d", np->pessoa.id);
        printf("\n\tNOME COMPLETO: %s %s", np->pessoa.nome, np->pessoa.sobrenome);
        printf("\n\tIDADE: %d", np->pessoa.idade);
        if(np->pessoa.sexo == 0){
            printf("\n\tSEXO: Masculino");
        }else{
            printf("\n\tSEXO: Feminino");
        }
        printf("\n\tMUSICAS: ");
        for(int i = 0; i < 5; i++){
            printf(" %d", np->pessoa.musicas[i]);
        }
    }
}

void limpa_lista(Descritor* d) {
    NoPessoa* atual = d->inicio;
    while (atual != NULL) {
        NoPessoa* proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    d->inicio = NULL;
    d->final = NULL;
    d->tamanho = 0;
}

void inserePessoa(Descritor* d, Pessoa p) {
    NoPessoa* novoNo = (NoPessoa*) malloc(sizeof(NoPessoa));
    novoNo->pessoa = p;
    novoNo->proximo = NULL;
    if (d->inicio == NULL) {
        d->inicio = novoNo;
    } else {
        d->final->proximo = novoNo;
    }
    d->final = novoNo;
    d->tamanho++;
}

void libera_NoPessoa(NoPessoa* np) {
    if(np != NULL) {
        libera_NoPessoa(np->proximo);
        free(np);
    }
}

void libera_Descritor(Descritor* d) {
    if(d != NULL) {
        libera_NoPessoa(d->inicio);
        free(d);
    }
}
