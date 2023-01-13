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

    Musicas lista_populares[N];

//-----> VARIÁVEIS SECUNDÁRIAS <-----//

    int escolha;
    bool condicao = true;

    //VARIÁVEIS RETIRADAS
    //int id_buscado, id_buscado_2;
    //char curso_buscado[255];

    inserir_musicas_arquivo(lista_populares);



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

            printf("\n OPÇÃO NÚMERO 0 SELECIONADA!");
            inserir_pessoa(d, lista_populares);

            break;

        case 1:  //ALTERA OS DADOS DE UM ALUNO
            
            //alterar_dados(&ldp);
            printf("\n OPÇÃO NÚMERO 1 SELECIONADA!");
            imprime_geral(d);

            break;

        case 2:  //REMOVE OS DADOS DE UM ALUNO
                
            //remover_aluno(&ldp);
            
            printf("\n OPÇÃO NÚMERO 2 SELECIONADA!");

            break;
            
        case 3:

            lt();

            salvar_musicas_arquivo(lista_populares);
            
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