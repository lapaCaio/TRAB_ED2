#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "salvar.h"
#include "funcoes.h"


void lerPessoasDoArquivo(Descritor* d){

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

void salvarPessoasNoArquivo(Descritor* d)
{

    FILE *arquivo_txt = fopen("arquivos/pessoas.txt", "w");

    for(NoPessoa* np = d->inicio; np != NULL; np = np->proximo){
        fprintf(arquivo_txt, "%d\t%s\t%s\t%d\t%d\t%d\n", np->pessoa.id, np->pessoa.nome, np->pessoa.sobrenome, np->pessoa.idade, np->pessoa.sexo, np->pessoa.tipo);
        fprintf(arquivo_txt, "\t%d\t%d\t%d\t%d\t%d\n", np->pessoa.musicas[0], np->pessoa.musicas[1], np->pessoa.musicas[2], np->pessoa.musicas[3], np->pessoa.musicas[4]);
    }

    fclose(arquivo_txt);
}

//-------------------------------------------------------------------------------------------------------------------------------

void salvarCategoria(Descritor* d, int i){
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

        for(NoPessoa* np = d->inicio; np != NULL; np = np->proximo){
            fprintf(arquivo_txt, "%s\t%s\t\n", np->pessoa.nome, np->pessoa.sobrenome);
        }

        fclose(arquivo_txt);
    }else{
        printf("A LISTA ESTA VAZIA!\n");
    }
}

void lerMusicasDoArquivo(ListaMusicas* lm, char* nomeArquivo){
    FILE* arquivo = fopen(nomeArquivo, "r");
    if(arquivo == NULL){
        printf("ERRO AO ABRIR ARQUIVO\n");
        return;
    }
    Musica novaMusica;
    while(fscanf(arquivo, "%d\t%[^\t]\t%[^\t]\t%d\n", &novaMusica.id, novaMusica.nome, novaMusica.autor, &novaMusica.vezes_selecionadas) != EOF){
        inserirMusica(lm, novaMusica);
        printf("\n >>> %d", novaMusica.vezes_selecionadas);
    }
    fclose(arquivo);
}

void salvarMusicasArquivo(ListaMusicas* lista, char* nomeArquivo){
    FILE* arquivo = fopen(nomeArquivo, "w");
    if(arquivo == NULL){
        printf("ERRO AO ABRIR O ARQUIVO\n");
        return;
    }
    ListaMusicas* atual = lista->proximo;
    while(atual != NULL){
        fprintf(arquivo, "%d\t%s\t%s\t%d\n", atual->m.id, atual->m.nome, atual->m.autor, atual->m.vezes_selecionadas);
        atual = atual->proximo;
    }
    fclose(arquivo);
}



