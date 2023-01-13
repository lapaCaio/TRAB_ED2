#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int soma(int a, int b){
    return a + b;
}

typedef struct no {
    int valor;
    struct no* proximo;
}No;

int main(){
    int a;
    int  b = 20;
    
    printf("\n >>> %d", &b);
    return EXIT_SUCCESS;
}