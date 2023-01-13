#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "salvar.h"
#include "funcoes.h"

void inserir_musicas_arquivo(Musicas* m)
{

    lt();

    printf("\n");

    FILE *arquivo_txt = fopen("musicas.txt", "r");
    rewind(arquivo_txt);

    Musicas temp;
    int i = 0;

    while (fscanf(arquivo_txt,"%d\t%[^\t]\t%[^\t]\t%d\n", &temp.id, temp.nome, temp.autor, &temp.vezes_selecionadas) != EOF){
        m[i].id = temp.id;
        strcpy(m[i].nome, temp.nome);
        strcpy(m[i].autor, temp.autor);
        m[i].vezes_selecionadas = temp.vezes_selecionadas;
        
        printf("\n id: %d", m[i].id);
        printf("\n nome: %s", m[i].nome);
        printf("\n vs: %d", m[i].vezes_selecionadas);
        printf("\n autor: %s", m[i].autor);
        printf("\n------------ %d", i);

        i++;
    }

    fclose(arquivo_txt);
}



void salvar_musicas_arquivo(Musicas* m)
{

    lt();

    linha();

    printf("\n");

    FILE *arquivo_txt = fopen("musicas.txt", "w");

    for(int i = 0; i < 30; i++){
        fprintf(arquivo_txt, "%d\t%s\t%s\t%d\n", m[i].id, m[i].nome, m[i].autor, m[i].vezes_selecionadas);
    }

    fclose(arquivo_txt);
}
