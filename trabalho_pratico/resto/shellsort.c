#include <stdio.h>
#include <stdlib.h>

void shellsort(int array[], int n) {
  int intervalo, i, j, temp;

  // Encontra o intervalo inicial
  intervalo = n / 2;
  while (intervalo > 0) {
    for (i = intervalo; i < n; i++) {
      j = i;
      temp = array[i];
      while (j >= intervalo && array[j - intervalo] > temp) {
        array[j] = array[j - intervalo];
        j = j - intervalo;
      }
      array[j] = temp;
    }
    intervalo = intervalo / 2;
  }
}

int main(int argc, char** argv){

    int array[] = {5, 3, 8, 4, 9, 1, 6, 2, 7};
    int n = 9;

    shellsort(array, n);



    return EXIT_SUCCESS;
}