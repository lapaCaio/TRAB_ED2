#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "salvar.h"
#include "funcoes.h"

#define N 30

typedef struct descritor Descritor;

typedef struct musica Musicas;

typedef struct nopessoa NoPessoa;


void ler_pessoas_do_arquivo(Descritor* d){

    FILE *arquivo_txt = fopen("arquivos/pessoas.txt", "r");
    rewind(arquivo_txt);

    Pessoa temp;
    int i = 0;

    while (fscanf(arquivo_txt,"%d\t%[^\t]\t%[^\t]\t%d\t%d\t%d\n", &temp.id, temp.nome, temp.sobrenome, &temp.idade, &temp.sexo, &temp.tipo) != EOF){
        
        fscanf(arquivo_txt,"\t%d\t%d\t%d\t%d\t%d\n", &temp.musicas[0], &temp.musicas[1], &temp.musicas[2], &temp.musicas[3], &temp.musicas[4]);
        
        inserir_pessoa(d, temp);
        atualiza_id_global();

        i++;
    }

    fclose(arquivo_txt);
}

void salvar_pessoas_no_arquivo(Descritor* d){

    FILE *arquivo_txt = fopen("arquivos/pessoas.txt", "w");

    for(NoPessoa* np = d->inicio; np != NULL; np = np->proximo){
        fprintf(arquivo_txt, "%d\t%s\t%s\t%d\t%d\t%d\n", np->pessoa.id, np->pessoa.nome, np->pessoa.sobrenome, np->pessoa.idade, np->pessoa.sexo, np->pessoa.tipo);
        fprintf(arquivo_txt, "\t%d\t%d\t%d\t%d\t%d\n", np->pessoa.musicas[0], np->pessoa.musicas[1], np->pessoa.musicas[2], np->pessoa.musicas[3], np->pessoa.musicas[4]);
    }

    fclose(arquivo_txt);
}

//-------------------------------------------------------------------------------------------------------------------------------

void salvar_categoria(Descritor* d, Musicas* m, int i){
    char* nome_arquivo;
    if(!lista_vazia(d)){
        if(i == 1){
            nome_arquivo = "categorias/homens_abaixo.txt"; 
        }else if(i == 2){
            nome_arquivo = "categorias/homens_acima.txt"; 
        }else if(i == 3){
            nome_arquivo = "categorias/mulheres_abaixo.txt"; 
        }else if(i == 4){
            nome_arquivo = "categorias/mulheres_acima.txt"; 
        }else{
            printf("\n VALOR INFORMADO É INVÁLIDO!");
            return;
        }

        FILE *arquivo_txt = fopen(nome_arquivo, "w");
    
        if(arquivo_txt == NULL) {
            printf("ERRO AO ABRIR O ARQUIVO: %s\n",nome_arquivo);
            return;
        }

        rewind(arquivo_txt);

        for(NoPessoa* np = d->inicio; np != NULL; np = np->proximo){
            for(int i = 0; i < 3; i++){
                if(np->pessoa.musicas[0] == m[i].id){
                    fprintf(arquivo_txt, "%s\t%s\t\n", np->pessoa.nome, np->pessoa.sobrenome);
                    i = 3;
                }
            }
        }

        fclose(arquivo_txt);
    }
}

void ler_musicas_do_arquivo(Musicas* m, char* nomeArquivo){
    FILE* arquivo = fopen(nomeArquivo, "r");
    if(arquivo == NULL){
        printf("ERRO AO ABRIR ARQUIVO\n");
        return;
    }
    Musicas nova_musica;
    int i = 0;
    while(fscanf(arquivo, "%d\t%[^\t]\t%[^\t]\t%d\n", &nova_musica.id, nova_musica.nome, nova_musica.autor, &nova_musica.vezes_selecionadas) != EOF){
        m[i] = nova_musica;
        i++;
    }
    fclose(arquivo);
}

void salvar_musicas_no_arquivo(Musicas* m, char* nomeArquivo){
    FILE* arquivo = fopen(nomeArquivo, "w");
    if(arquivo == NULL){
        printf("ERRO AO ABRIR O ARQUIVO\n");
        return;
    }

    if(esta_ordenada(m)){
        for(int i = 0; i < N; i++){
            if(m[i].vezes_selecionadas == 0){
                continue;
            }else{
                fprintf(arquivo, "%d\t%s\t%s\t%d\n", m[i].id, m[i].nome, m[i].autor, m[i].vezes_selecionadas);
            }        
        }
    }else{
        for(int i = 0; i < N; i++){
            fprintf(arquivo, "%d\t%s\t%s\t%d\n", m[i].id, m[i].nome, m[i].autor, m[i].vezes_selecionadas);
        }
    }

    fclose(arquivo);
}



