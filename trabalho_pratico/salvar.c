#include <stdlib.h>
#include <stdio.h>

typedef struct musica{
    int id;
    char nome[30];
    char autor[30];
    int vezes_selecionadas;
}Musicas;

/*
void inserir_dados_arquivo(ListaDeAlunos **lda)
{

    // lt();

    printf("\n");

    FILE *arquivo_txt = fopen("musicas.txt", "r");
    rewind(arquivo_txt);

    Aluno *aluno_novo = (Aluno *)malloc(sizeof(Aluno));

    while (fscanf(arquivo_txt, "%[^\t]\t%d\t%[^\n]\n\t", aluno_novo->nome, &aluno_novo->id, aluno_novo->curso) != EOF)
    {

        atualiza_id_global(aluno_novo->id);

        aluno_novo->prox_amg = NULL;

        ListaDeAlunos *n = malloc(sizeof(ListaDeAlunos));
        ListaDeAlunos *p;

        int id_temp;

        while (fscanf(arquivo_txt, "%d ", &id_temp) == 1)
        {
            No *novo_amigo = malloc(sizeof(No));

            novo_amigo->id = id_temp;
            novo_amigo->prox = aluno_novo->prox_amg;
            aluno_novo->prox_amg = novo_amigo;
        }

        if (n)
        {

            n->aluno = *aluno_novo;

            // lt();

            if (*lda == NULL)
            { // INSERÇÃO EM PRIMEIRO NA LISTA

                n->proximo = n->anterior = NULL;
                *lda = n;
            }
            else if (strcmp(n->aluno.nome, (*lda)->aluno.nome) < 0)
            { // INSERÇÃO NO INÍCIO DA LISTA

                n->proximo = *lda;
                n->anterior = NULL;
                (*lda)->anterior = n;
                *lda = n;
            }
            else
            { // INSERÇÃO COM VÁRIOS VALORES EM ORDEM DECRESCENTE

                for (p = *lda; p->proximo != NULL && strcmp(n->aluno.nome, p->aluno.nome) > 0; p = p->proximo)
                    ;

                if (strcmp(n->aluno.nome, p->aluno.nome) < 0)
                {

                    n->proximo = p;
                    n->anterior = p->anterior;
                    p->anterior->proximo = n;
                    p->anterior = n;
                }
                else
                {

                    n->proximo = p->proximo;
                    n->anterior = p;
                    p->proximo = n;
                }
            }
        }
        else
        {

            printf("\nOPS! ALGO DEU ERRADO AQUI, DESCULPE-NOS PELO TRANSTORNO... T-T");
        }
    }

    fclose(arquivo_txt);
}
*/


void salvar_dados_arquivo(Musicas* m)
{

    //lt();

    //linha();

    printf("\n");

    FILE *arquivo_txt = fopen("musicas.txt", "w");

    m->id = 0;
    m->vezes_selecionadas = 0;
    printf("\nNome: ");
    scanf("%[^\n]", m->nome);
    setbuf(stdin, NULL);
    printf("\nAutor: ");
    scanf("%[^\n]", m->autor);

    for(int i = 0; i < 30; i++){
        m->id++;
        fprintf(arquivo_txt, "%d\t%s\t%s\t%d\n\t", (i + 1), m->nome, m->autor, m->vezes_selecionadas);
    }

    /*
    for (ListaDeAlunos *p = *lda; p != NULL; p = p->proximo)
    {

        fprintf(arquivo_txt, "%s\t%d\t%s\n\t", p->aluno.nome, p->aluno.id, p->aluno.curso);

        for (No *n = p->aluno.prox_amg; n != NULL; n = n->prox)
        {
            fprintf(arquivo_txt, "%d ", n->id);
        }

        fprintf(arquivo_txt, "\n");
    }

    */
    fclose(arquivo_txt);
}

int main(){

    Musicas* m = (Musicas*)malloc(sizeof(Musicas));

    salvar_dados_arquivo(m);
    

    return EXIT_SUCCESS;
}
