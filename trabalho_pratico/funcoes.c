#include <stdio.h>
#include <stdlib.h>

#include "funcoes.h"
#include "salvar.h"

#define N 30  

int id_global = 1;

typedef struct musica Musicas;

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

//----------> FUNÇÕES - TAD (PESSOA) <----------//

Pessoa le_pessoa(Musicas* m){
    Pessoa nova_pessoa;

    nova_pessoa.id = id_global;
    atualiza_id_global();


    lb();

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
    scanf("%d %d %d %d %d", 
    &nova_pessoa.musicas[0], 
    &nova_pessoa.musicas[1], 
    &nova_pessoa.musicas[2], 
    &nova_pessoa.musicas[3], 
    &nova_pessoa.musicas[4]);

    for(int i = 0; i < 5; i++){
        for(int j = 0; j < N; j++){
            if(m[j].id == nova_pessoa.musicas[i]){
                m[j].vezes_selecionadas++;
            }
        }
    }

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

int lista_vazia(Descritor* d){
    return (d->inicio == NULL && d->final == NULL);
}

void inserir_pessoa(Descritor* d, Musicas* m){
    NoPessoa* novo_np = (NoPessoa*)malloc(sizeof(NoPessoa));

    novo_np->anterior = novo_np->proximo = NULL;
    novo_np->pessoa = le_pessoa(m);

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
            }
        }
    }else{
        printf("\n ERROR: LISTA DE ENTREVISTADOS VAZIA!");
    }
}

void listar_musicas(Musicas* m){
    lt();
    printf("\n TODAS AS MÚSICAS:");
    for(int i = 0; i < N; i++){
        printf("\n [%d] %s - %s", m[i].id, m[i].nome, m[i].autor);
    }
}

void listar_musicas_populares(Musicas* m)
{

    FILE *arquivo_txt = fopen("musicas_populares.txt", "r");
    rewind(arquivo_txt);

    Musicas temp;
    int i = 0;

    lt();
    printf("\n MÚSICAS POPULARES:");

    while (fscanf(arquivo_txt,"%d\t%[^\t]\t%[^\t]\t%d\n", &temp.id, temp.nome, temp.autor, &temp.vezes_selecionadas) != EOF){
        printf("\n [%d] %s - %s : %d", temp.id, temp.nome, temp.autor, temp.vezes_selecionadas);
    }

    fclose(arquivo_txt);
}

void atualiza_id_global(){
    id_global++;
}

void shellSortMusica(Musicas* m, int tam) {
    int espaco = tam / 2;
    while (espaco > 0) {
        for (int i = espaco; i < tam; i++) {
            Musicas temp = m[i];
            int j = i;
            while (j >= espaco && m[j - espaco].vezes_selecionadas > temp.vezes_selecionadas) {
                m[j] = m[j - espaco];
                j -= espaco;
            }
            m[j] = temp;
        }
        espaco /= 2;
    }

    salvar_musicas_populares_arquivo(m, m);
}

