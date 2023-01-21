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

    Musicas* lista_musicas;
    inicializar_musicas(lista_musicas);
    Musicas* lista_musicas_populares;
    inicializar_musicas(lista_musicas_populares);

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

    ler_pessoas_do_arquivo(d);
    ler_musicas_do_arquivo(lista_musicas, "arquivos/musicas.txt");

//-----> O RESTO DA MAIN <-----//
    while(condicao){
        escolha = 0;

        linha();
        printf("\n ESCOLHA A OPÇÃO DESEJADA: ");
        linha();
        printf("\n 0 - ADICIONAR NOVO ENTREVISTADO");
        printf("\n 1 - LISTAR MÚSICAS MAIS POPULARES");
        printf("\n 2 - LISTAR ENTREVISTADOS POR CATEGORIA");
        printf("\n 3 - SAIR");
        linha();
        printf("\n >>> ");
        scanf("%d", &escolha);
        lb();

        switch (escolha)
        {
        case 0:  //INSERE UMA PESSOA(ENTREVISTADO)
            printf("\n OPÇÃO SELECIONADA: ADICIONAR NOVO ENTREVISTADO");
            inserir_pessoa(d, le_pessoa(lista_musicas));

            //atualiza_musicas(d, musicas);
            
            break;

        case 1: 
            printf("\n OPÇÃO SELECIONADA: LISTAR MÚSICAS MAIS POPULARES");
            
            separar_populares(lista_musicas, lista_musicas_populares);
            //listar_musicas(lista_musicas_populares);

            atualiza_musicas(d, lista_musicas);

            break;

        case 2:  
                
            printf("\n OPÇÃO SELECIONADA: LISTAR ENTREVISTADOS POR CATEGORIA");
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

            salvar_pessoas_no_arquivo(d);
            salvar_musicas_no_arquivo(lista_musicas, "arquivos/musicas.txt");
            salvar_musicas_no_arquivo(lista_musicas_populares, "arquivos/musicas_populares.txt");

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