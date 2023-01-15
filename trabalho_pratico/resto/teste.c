#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct musica{
    int id;
    char nome[30];
    char autor[30];
    int vezes_selecionadas;
}Musicas;


void shellSortMusica(Musicas* msc, int n) {
    int gap = n / 2;
    while (gap > 0) {
        for (int i = gap; i < n; i++) {
            Musicas temp = msc[i];
            int j = i;
            while (j >= gap && msc[j - gap].vezes_selecionadas > temp.vezes_selecionadas) {
                msc[j] = msc[j - gap];
                j -= gap;
            }
            msc[j] = temp;
        }
        gap /= 2;
    }
}

int main(){
    Musicas msc[30];
    
    
    return EXIT_SUCCESS;
}