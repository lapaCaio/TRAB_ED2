typedef struct musica{
    int id;
    char nome[30];
    char autor[30];
    int vezes_selecionadas;
}Musicas;

void listar_musicas(Musicas* m){  //OK
    //lt();
    printf("\n TODAS AS MÚSICAS:");

    for(int i = 0; i < 30; i++){
        printf("\n [%d] %s - %s - %d", m[i].id, m[i].nome, m[i].autor, m[i].vezes_selecionadas);
    }
}

int main(){
    Musicas m[30];

}