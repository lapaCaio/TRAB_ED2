#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include <string.h>

#include "funcoes.h"
#include "salvar.h"

#define N 30

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

    separa_categorias(d, homens_abaixo, homens_acima, mulheres_abaixo, mulheres_acima);

    atualiza_musicas(homens_abaixo, lista_homens_abaixo);
    atualiza_musicas(homens_acima, lista_homens_acima);
    atualiza_musicas(homens_acima, lista_homens_acima);
    atualiza_musicas(mulheres_abaixo, lista_mulheres_abaixo);
    atualiza_musicas(mulheres_acima, lista_mulheres_acima);

    shellsort(lista_homens_abaixo);
    shellsort(lista_homens_acima);
    shellsort(lista_mulheres_abaixo);
    shellsort(lista_mulheres_acima);

    salvar_categoria(homens_abaixo, lista_homens_abaixo, 1);
    salvar_categoria(homens_acima, lista_homens_acima, 2);
    salvar_categoria(mulheres_abaixo, lista_mulheres_abaixo, 3);
    salvar_categoria(mulheres_acima, lista_mulheres_acima, 4);
    

    //listar_musicas(lista_musicas_populares);

    while(condicao){
        escolha = 0;

        linha();
        printf("\n ESCOLHA A OPCAO DESEJADA: ");
        linha();
        printf("\n [1] - ADICIONAR NOVO ENTREVISTADO");
        printf("\n [2] - LISTAR MUSICAS MAIS POPULARES");
        printf("\n [3] - LISTAR ENTREVISTADOS POR CATEGORIA");
        printf("\n [4] - LISTAR TODAS AS MUSICAS");
        printf("\n [5] - LISTAR TODAS AS PESSOAS");
        printf("\n [0] - SAIR");
        linha();
        printf("\n >>> ");
        scanf("%d", &escolha);
        lb();

        switch (escolha)
        {
        case 0:  
            lt();

            salvar_pessoas_no_arquivo(d);

            shellsort(lista_musicas_populares);

            salvar_musicas_no_arquivo(lista_musicas_populares, "arquivos/musicas_populares.txt");

            atualiza_musicas(d, lista_musicas);
            salvar_musicas_no_arquivo(lista_musicas, "arquivos/musicas.txt");
            

            libera_Descritor(d);

            libera_Descritor(homens_abaixo);
            libera_Descritor(homens_acima);

            libera_Descritor(mulheres_abaixo);
            libera_Descritor(mulheres_acima);

            linha();
            printf("\n PROGRAMA ENCERRADO!");
            linha();

            condicao = false;
            
            break;

        case 1: 
        //INSERE UMA PESSOA(ENTREVISTADO)
            printf("\n OPCAO SELECIONADA:\n ADICIONAR NOVO ENTREVISTADO");
            linha();

            inserir_pessoa(d, le_pessoa(lista_musicas));
            salvar_pessoas_no_arquivo(d);
            atualiza_musicas(d, lista_musicas);

            separa_categorias(d, homens_abaixo, homens_acima, mulheres_abaixo, mulheres_acima);

            listar_pessoas(homens_acima);
            linha();
            linha();
            separa_categorias(d, homens_abaixo, homens_acima, mulheres_abaixo, mulheres_acima);
            listar_pessoas(homens_acima);

            atualiza_musicas(homens_abaixo, lista_homens_abaixo);
            atualiza_musicas(homens_acima, lista_homens_acima);
            atualiza_musicas(mulheres_abaixo, lista_mulheres_abaixo);
            atualiza_musicas(mulheres_acima, lista_mulheres_acima);

    
            shellsort(lista_homens_abaixo);
            shellsort(lista_homens_acima);
            shellsort(lista_mulheres_abaixo);
            shellsort(lista_mulheres_acima);

            salvar_categoria(homens_abaixo, lista_homens_abaixo, 1);
            salvar_categoria(homens_acima, lista_homens_acima, 2);
            salvar_categoria(mulheres_abaixo, lista_mulheres_abaixo, 3);
            salvar_categoria(mulheres_acima, lista_mulheres_acima, 4);

            break;

        case 2:  
            printf("\n OPCAO SELECIONADA:\n LISTAR MÚSICAS MAIS POPULARES");
            linha();

            atualiza_musicas(d, lista_musicas_populares);
            shellsort(lista_musicas_populares);

            salvar_musicas_no_arquivo(lista_musicas_populares, "arquivos/musicas_populares.txt");
            listar_musicas(lista_musicas_populares);
            atualiza_musicas(d, lista_musicas);

            break;
        
        case 3:
            lt();
            printf("\n OPCAO SELECIONADA:\n LISTAR ENTREVISTADOS POR CATEGORIA");

            // printf("\nteste");
            // listar_musicas(lista_homens_acima);


            bool sub_condicao = true;
            int sub_escolha;

            while(sub_condicao){
                sub_escolha = 0;

                linha();
                printf("\n ESCOLHA EM QUAL CATEGORIA DESEJA MOSTRAR \n AS PESSOAS E SUAS MUSICAS FAVORITAS: ");
                linha();
                printf("\n [1] - HOMENS ABAIXO DE 20 ANOS");
                printf("\n [2] - HOMENS ACIMA DE 20 ANOS");
                printf("\n [3] - MULHERES ABAIXO DE 20 ANOS");
                printf("\n [4] - MULHERES ACIMA DE 20 ANOS");
                printf("\n [0] - VOLTAR");
                linha();
                printf("\n >>> ");
                scanf("%d", &sub_escolha);
                lb();
                lt();

                switch (sub_escolha)
                {
                    case 0:
                        sub_condicao = false;
                        break;
                    case 1:

                        printf("\n HOMENS ABAIXO DE 20 ANOS DE IDADE: ");
                        imprime_categoria(homens_abaixo);
                        linha();
                        printf("\n MUSICAS MAIS POPULARES DA CATEGORIA:");
                        if(esta_ordenada(lista_homens_abaixo)){
                            listar_musicas(lista_homens_abaixo);
                        }else{
                            printf("\n A LISTA DE MASICAS ESTA VAZIA!");
                        }

                        break;
                    case 2:

                        printf("\n HOMENS ACIMA DE 20 ANOS DE IDADE: ");
                        imprime_categoria(homens_acima);
                        linha();
                        printf("\n MUSICAS MAIS POPULARES DA CATEGORIA:");
                        if(esta_ordenada(lista_homens_acima)){
                            listar_musicas(lista_homens_acima);
                        }else{
                            printf("\n A LISTA DE MUSICAS ESTA VAZIA!");
                        }
                        
                        break;
                    case 3:

                        printf("\n MULHERES ABAIXO DE 20 ANOS DE IDADE: ");
                        imprime_categoria(mulheres_abaixo);
                        linha();
                        printf("\n MUSICAS MAIS POPULARES DA CATEGORIA:");
                        if(esta_ordenada(lista_mulheres_abaixo)){
                            listar_musicas(lista_mulheres_abaixo);
                        }else{
                            printf("\n A LISTA DE MUSICAS ESTA VAZIA!");
                        }       
                        break;
                    case 4:

                        printf("\n MULHERES ACIMA DE 20 ANOS DE IDADE: ");
                        imprime_categoria(mulheres_acima);
                        linha();
                        printf("\n MUSICAS MAIS POPULARES DA CATEGORIA:");
                        if(esta_ordenada(lista_mulheres_acima)){
                            listar_musicas(lista_mulheres_acima);
                        }else{
                            printf("\n A LISTA DE MUSICAS ESTÁ VAZIA!");
                        } 

                        break;
                    default:

                        lb();
                        lt();
                        linha();
                        printf("\n O VALOR QUE VOCÊ DIGITOU NAO CORRESPONDE A NENHUMA OPCAO,");
                        printf("\n POR FAVOR DIGITE UM NUMERO ENTRE 0 E 4, CORRESPONDENDE COM A OPCAO QUE DESEJA!");
                        linha();

                        continue;
                }
            }

            break;
        case 4:

            lt();
            linha();
            printf("\n OPCAO SELECIONADA: LISTAR TODAS AS MUSICAS");
            linha();
            atualiza_musicas(d, lista_musicas);
            listar_musicas(lista_musicas);

            break;
        case 5:

            lt();
            linha();
            printf("\n OPCAO SELECIONADA: LISTAR TODAS AS PESSOAS");
            linha();
            listar_pessoas(d);

            break;
        default:

            lb();
            lt();
            linha();
            printf("\n O VALOR QUE VOCÊ DIGITOU NÃO CORRESPONDE A NENHUMA OPCAO,");
            printf("\n POR FAVOR DIGITE UM NUMERO ENTRE 0 E 4, CORRESPONDENDE COM A OPCAO QUE DESEJA!");
            linha();

            continue;
        }
    }

    return EXIT_SUCCESS;
}