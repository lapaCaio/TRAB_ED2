#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include <string.h>

#include "funcoes.h"
#include "salvar.h"

#define N 30

int main(int argc, char** argv){
    setlocale(LC_ALL, "");

//-----> VARIÁVEIS PRINCIPAIS <------//
    Descritor* d = (Descritor*)malloc(sizeof(Descritor));
    inicializa_descritor(d);

    Musicas musicas[N];
    Musicas musicas_populares[N];

//-----> VARIÁVEIS SECUNDÁRIAS <-----//

    int escolha;
    bool condicao = true;

    //inserir_musicas_arquivo(musicas);
    //inserir_musicas_populares_arquivo(musicas_populares);
    inserir_pessoas_arquivo(d);

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
           
            inserir_musicas_arquivo(musicas);
            inserir_musicas_populares_arquivo(musicas_populares);

            printf("\n OPÇÃO SELECIONADA : ADICIONAR NOVO ENTREVISTADO");
            inserir_pessoa(d, musicas);

            salvar_musicas_arquivo(musicas);
            salvar_musicas_populares_arquivo(musicas, musicas_populares);
            
            break;

        case 1: 
            
            inserir_musicas_arquivo(musicas);
            inserir_musicas_populares_arquivo(musicas_populares);

            //shellSortMusica(musicas_populares, d->tamanho);

            printf("\n OPÇÃO SELECIONADA: LISTAR MÚSICAS MAIS POPULARES");
            listar_musicas_populares(musicas_populares);

            salvar_musicas_arquivo(musicas);
            salvar_musicas_populares_arquivo(musicas, musicas_populares);

            break;

        case 2:  
                
            printf("\n OPÇÃO NÚMERO 2 SELECIONADA!");
            listar_musicas(musicas);

            break;
            
        case 3:

            lt();

            salvar_musicas_arquivo(musicas);
            salvar_musicas_populares_arquivo(musicas, musicas_populares);
            salvar_pessoas(d);
            
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