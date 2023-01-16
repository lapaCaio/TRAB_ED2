#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "salvar.h"
#include "funcoes.h"

void inserir_musicas_arquivo(Musicas* m)
{

    FILE *arquivo_txt = fopen("arquivos/musicas.txt", "r");
    rewind(arquivo_txt);

    Musicas temp;
    int i = 0;

    while (fscanf(arquivo_txt,"%d\t%[^\t]\t%[^\t]\t%d\n", &temp.id, temp.nome, temp.autor, &temp.vezes_selecionadas) != EOF){
        m[i].id = temp.id;
        strcpy(m[i].nome, temp.nome);
        strcpy(m[i].autor, temp.autor);
        m[i].vezes_selecionadas = temp.vezes_selecionadas;
        i++;
    }

    fclose(arquivo_txt);
}

void salvar_musicas_arquivo(Musicas* m)
{

    FILE *arquivo_txt = fopen("arquivos/musicas.txt", "w");

    for(int i = 0; i < 30; i++){
        fprintf(arquivo_txt, "%d\t%s\t%s\t%d\n", m[i].id, m[i].nome, m[i].autor, m[i].vezes_selecionadas);
    }

    fclose(arquivo_txt);
}


void inserir_musicas_populares_arquivo(Musicas* m)
{

    FILE *arquivo_txt = fopen("arquivos/musicas_populares.txt", "r");
    rewind(arquivo_txt);

    Musicas temp;
    int i = 0;

    while (fscanf(arquivo_txt,"%d\t%[^\t]\t%[^\t]\t%d\n", &temp.id, temp.nome, temp.autor, &temp.vezes_selecionadas) != EOF){
        m[i].id = temp.id;
        strcpy(m[i].nome, temp.nome);
        strcpy(m[i].autor, temp.autor);
        m[i].vezes_selecionadas = temp.vezes_selecionadas;
        i++;
    }

    fclose(arquivo_txt);
}

void salvar_musicas_populares_arquivo(Musicas* m, Musicas* saida)
{

    FILE *arquivo_txt = fopen("arquivos/musicas_populares.txt", "w");

    for(int i = 0; i < 30; i++){
        if(m[i].vezes_selecionadas > 0){
            fprintf(arquivo_txt, "%d\t%s\t%s\t%d\n", m[i].id, m[i].nome, m[i].autor, m[i].vezes_selecionadas);
        }
    }

    fclose(arquivo_txt);
}

void inserir_pessoas_arquivo(Descritor* d){

    FILE *arquivo_txt = fopen("arquivos/pessoas.txt", "r");
    rewind(arquivo_txt);

    Pessoa temp;
    int i = 0;

    while (fscanf(arquivo_txt,"%d\t%[^\t]\t%[^\t]\t%d\t%d\t%d\n", &temp.id, temp.nome, temp.sobrenome, &temp.idade, &temp.sexo, &temp.tipo) != EOF){
        
        fscanf(arquivo_txt,"\t%d\t%d\t%d\t%d\t%d\n", &temp.musicas[0], &temp.musicas[1], &temp.musicas[2], &temp.musicas[3], &temp.musicas[4]);
        
        atualiza_id_global();
    
        NoPessoa* novo_np = (NoPessoa*)malloc(sizeof(NoPessoa));
        
        novo_np->anterior = novo_np->proximo = NULL;
        novo_np->pessoa = temp;

        if(lista_vazia(d)){  //insere na primeira posição da lista
            d->inicio = d->final = novo_np;
            d->tamanho++;
        }else{  //insere nos outros locais da lista
            d->final->proximo = novo_np;
            novo_np->anterior = d->final;
            d->final = novo_np;      
            d->tamanho++;
        }
        i++;
    }

    fclose(arquivo_txt);
}

void salvar_pessoas(Descritor* d)
{

    FILE *arquivo_txt = fopen("arquivos/pessoas.txt", "w");

    for(NoPessoa* np = d->inicio; np != NULL; np = np->proximo){
        fprintf(arquivo_txt, "%d\t%s\t%s\t%d\t%d\t%d\n", np->pessoa.id, np->pessoa.nome, np->pessoa.sobrenome, np->pessoa.idade, np->pessoa.sexo, np->pessoa.tipo);
        fprintf(arquivo_txt, "\t%d\t%d\t%d\t%d\t%d\n", np->pessoa.musicas[0], np->pessoa.musicas[1], np->pessoa.musicas[2], np->pessoa.musicas[3], np->pessoa.musicas[4]);
    }

    fclose(arquivo_txt);
}


