#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include <string.h>

#include "funcoes.h"
#include "salvar.h"

#define N 30

void shellsort(Musicas *m, int tamanho ) {
    int i, j, h;
    Musicas auxiliar;

    h = 1;

    while (h < tamanho){
        h = h*3+1;
    }
        
    while ( h > 1 ) {
        h = (h-1)/3;
        for ( i = h; i < tamanho; i++ ) {
            auxiliar = m[i];
            j = i-h;
            while  ( j >= 0 && auxiliar.vezes_selecionadas > m[j].vezes_selecionadas ) {
                m[j+h] = m[j];
                j = j - h;
            }
            if ( j != (i-h)) 
                m[j+h] = auxiliar;
        }

    }
}

int main(int argc, char** argv){
    setlocale(LC_ALL, "portuguese");

    //lista de todos os entrevistados
    Descritor* d = (Descritor*)malloc(sizeof(Descritor));
    inicializa_descritor(d);

    //lista com todas as músicas
    Musicas lista_musicas[N];
    inicializar_musicas(lista_musicas);

    //lista com apenas as músicas mais populares
    Musicas lista_musicas_populares[N];
    inicializar_musicas(lista_musicas_populares);

    //lista com as músicas mais populares na categoria: homens com menos que 20 anos
    Musicas lista_homens_acima[N];
    inicializar_musicas(lista_homens_acima);

    //lista com as músicas mais populares na categoria: homens com mais de 20 anos
    Musicas lista_homens_abaixo[N];
    inicializar_musicas(lista_homens_abaixo);

    //lista com as músicas mais populares na categoria: mulheres com menos de 20 anos
    Musicas lista_mulheres_acima[N];
    inicializar_musicas(lista_mulheres_acima);

    //lista com as músicas mais populares na categoria: mulheres com mais de 20 anos
    Musicas lista_mulheres_abaixo[N];
    inicializar_musicas(lista_mulheres_abaixo);

    //lista com os entrevistados que são homens com menos que 20 anos
    Descritor* homens_abaixo = (Descritor*)malloc(sizeof(Descritor));
    inicializa_descritor(homens_abaixo);

    //lista com os entrevistados que são homens com mais de 20 anos
    Descritor* homens_acima = (Descritor*)malloc(sizeof(Descritor));
    inicializa_descritor(homens_acima);

    //lista com os entrevistados que são mulheres com menos de 20 anos
    Descritor* mulheres_abaixo = (Descritor*)malloc(sizeof(Descritor));
    inicializa_descritor(mulheres_abaixo);

    //lista com os entrevistados que são mulheres com mais de 20 anos
    Descritor* mulheres_acima = (Descritor*)malloc(sizeof(Descritor));
    inicializa_descritor(mulheres_acima);

    int escolha;
    bool condicao = true;

    ler_pessoas_do_arquivo(d);

    ler_musicas_do_arquivo(lista_musicas, "arquivos/musicas.txt");
    ler_musicas_do_arquivo(lista_musicas_populares, "arquivos/musicas.txt");

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
            salvar_pessoas_no_arquivo(d);
            
            break;

        case 1: 
            printf("\n OPÇÃO SELECIONADA: LISTAR MÚSICAS MAIS POPULARES");
            linha();

            atualiza_musicas(d, lista_musicas_populares);
            shellsort(lista_musicas_populares, N);
            salvar_musicas_no_arquivo(lista_musicas_populares, "arquivos/musicas_populares.txt");

            listar_musicas(lista_musicas_populares);
            atualiza_musicas(d, lista_musicas);

            break;

        case 2:  
                
            printf("\n OPÇÃO SELECIONADA: LISTAR ENTREVISTADOS POR CATEGORIA");

            //separar as pessoas em suas categorias
            separa_categorias(d, homens_abaixo, homens_acima, mulheres_abaixo, mulheres_acima);
            
            //atualizar a lista de cada música
            atualiza_musicas(homens_abaixo, lista_homens_abaixo);
            atualiza_musicas(homens_acima, lista_homens_acima);
            atualiza_musicas(mulheres_abaixo, lista_mulheres_abaixo);
            atualiza_musicas(mulheres_acima, lista_mulheres_acima);

            //coloca as mais populares no inicio da lista
            shellsort(lista_homens_abaixo, N);
            shellsort(lista_homens_acima, N);
            shellsort(lista_mulheres_abaixo, N);
            shellsort(lista_mulheres_acima, N);

            //salva as pessoas em seu respectivo arquivo
            salvar_categoria(homens_abaixo, lista_homens_abaixo, 1);
            salvar_categoria(homens_acima, lista_homens_acima, 2);
            salvar_categoria(mulheres_abaixo, lista_mulheres_abaixo, 3);
            salvar_categoria(mulheres_acima, lista_mulheres_acima, 4);


            
            printf("\n HOMENS ABAIXO DE 20 ANOS DE IDADE: ");
            imprime_categoria(homens_abaixo);
            linha();
            
            printf("\n HOMENS ACIMA DE 20 ANOS DE IDADE: ");
            imprime_categoria(homens_acima);
            linha();
            
            printf("\n MULHERES ABAIXO DE 20 ANOS DE IDADE: ");
            imprime_categoria(mulheres_abaixo);
            linha();
            
            printf("\n MULHERES ACIMA DE 20 ANOS DE IDADE: ");
            imprime_categoria(mulheres_acima);
            linha();

            break;
        
        case 3:

            lt();

            salvar_pessoas_no_arquivo(d);
            salvar_musicas_no_arquivo(lista_musicas, "arquivos/musicas.txt");

            listar_musicas(lista_musicas_populares);
            salvar_musicas_no_arquivo(lista_musicas_populares, "arquivos/musicas_populares.txt");
            
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