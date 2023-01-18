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

    Descritor* homens_abaixo = (Descritor*)malloc(sizeof(Descritor));
    inicializa_descritor(homens_abaixo);
    Descritor* homens_acima = (Descritor*)malloc(sizeof(Descritor));
    inicializa_descritor(homens_acima);
    
    Descritor* mulheres_abaixo = (Descritor*)malloc(sizeof(Descritor));
    inicializa_descritor(mulheres_abaixo);
    Descritor* mulheres_acima = (Descritor*)malloc(sizeof(Descritor));
    inicializa_descritor(mulheres_acima);
    

//-----> VARIÁVEIS SECUNDÁRIAS <-----//

    int escolha;
    bool condicao = true;

    inserir_musicas_arquivo(musicas);
    inserir_musicas_populares_arquivo(musicas_populares);
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
            separa_categorias(d, homens_abaixo, homens_acima, mulheres_abaixo, mulheres_acima);
            
            imprime_categoria(homens_abaixo);
            linha();
            imprime_categoria(homens_acima);
            linha();
            imprime_categoria(mulheres_abaixo);
            linha();
            imprime_categoria(mulheres_acima);

            break;
            
        case 3:

            lt();

            salvar_musicas_arquivo(musicas);
            salvar_musicas_populares_arquivo(musicas, musicas_populares);
            salvar_pessoas(d);

            salvar_categoria(homens_abaixo, 1);
            salvar_categoria(homens_acima, 2);
            salvar_categoria(mulheres_abaixo, 3);
            salvar_categoria(mulheres_acima, 4);
            
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