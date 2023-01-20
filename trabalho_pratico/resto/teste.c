#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct musica{
    int id;
    char nome[30];
    char autor[30];
    int vezes_selecionadas;
}Musica;

typedef struct lista_de_musicas{
    Musica m;
    struct lista_de_musicas* proximo;
}ListaMusicas;

typedef struct pessoa {
    int id;
    char nome[255];
    char sobrenome[255];
    int idade;
    int sexo;
    int musicas[5];
    char tipo;
}Pessoa;

typedef struct nopessoa {
    Pessoa pessoa;
    struct nopessoa* proximo;
    struct nopessoa* anterior;
}NoPessoa;

typedef struct descritor {
    NoPessoa* inicio;
    NoPessoa* final;
    int tamanho;
}Descritor;

int main(){
    ListaMusicas* lm = (ListaMusicas*)malloc(sizeof(ListaMusicas));
      
    return EXIT_SUCCESS;
}

int tamanhoListaMusica(ListaMusicas* lm) {
    int tamanho = 0;
    ListaMusicas* atual = lm;
    while (atual != NULL) {
        tamanho++;
        atual = atual->proximo;
    }
    return tamanho;
}
void shellSortListaMusica(ListaMusicas* lm) {
    if (lm == NULL) {
        return;
    }
    ListaMusicas* atual = lm;
    int h, i, j;
    Musica temp;
    int tam = tamanhoListaMusica(lm);

    for (h = tam/2; h > 0; h /= 2) {
        for (i = h; i < tam; i++) {
            atual = lm;
            for (j = i - h; j >= 0; j -= h) {
                for (int k = 0; k < j; k++) {
                    atual = atual->proximo;
                }
                if (atual->m.vezes_selecionadas >= atual->proximo->m.vezes_selecionadas) {
                    temp = atual->m;
                    atual->m = atual->proximo->m;
                    atual->proximo->m = temp;
                }
            }
        }
    }
}


