#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include <string.h>

//quantidade total de músicas
#define N 30  

int id_global = 1;

//----------> ESTRUTURAS <----------//

typedef struct pessoa {
    int id;

    char nome[255];
    int idade;
    char sexo;
    char* musicas[5];
    
    char tipo;  //o tipo será calculado...
}Pessoa;

typedef struct listadepessoas {
    Pessoa pessoa;
    struct listadepessoas* proximo;
    struct listadepessoas* anterior;
}ListaDePessoas;

typedef struct descritor {
    ListaDePessoas* inicio;
    ListaDePessoas* final;
    int tamanho;
}Descritor;

//----------> FUNÇÕES AUXILIARES <----------//

void lb(){  //LIMPA BUFER
    setbuf(stdin, NULL);
}
void lt(){  //LIMPA TERMINAL
    system("cls");
    system("clear"); 
}
void linha(){
    printf("\n|------------------------------------------------------------------------------------------|");  
}

//----------> FUNÇÕES - TAD (PESSOA) <----------//

Pessoa* le_pessoa(){
    Pessoa* nova_pessoa = (Pessoa*)malloc(sizeof(Pessoa));

    nova_pessoa->id = id_global;
    id_global++;


    lb();
    printf("\n NOME: ");
    scanf("%[^\n]", nova_pessoa->nome);
    lb();
    printf("\n IDADE: ");
    scanf("%d", nova_pessoa->idade);
    lb();
    printf("\n SEXO: ");
    scanf("%c", &nova_pessoa->sexo);
    lb();
    printf("\n MÚSICAS: ");
    printf("\n Digite o código das suas 5 músicas favoritas separadas por espaço. Ex.: 1 28 13 17 8");
    printf("\n >>> ");
    scanf("%d %d %d %d %d", &nova_pessoa->musicas[0], &nova_pessoa->musicas[1], &nova_pessoa->musicas[2], &nova_pessoa->musicas[3], &nova_pessoa->musicas[4]);
    lb();

    if(nova_pessoa->sexo == "M" || nova_pessoa->sexo == "m"){
        if(nova_pessoa->idade <= 20){
            nova_pessoa->tipo = 1; //MULHERES com MENOS que 20 anos
        }else{
            nova_pessoa->tipo = 2;  //MULHERS com MAIS que 20 anos
        }
    }else{ 
        if(nova_pessoa->idade <= 20){
            nova_pessoa->tipo = 3;  //HOMENS com MENOS que 20 anos
        }else{
            nova_pessoa->tipo = 4;  //HOMENS com MAIS que 20 anos
        }
    }


    return nova_pessoa;
}

//função de alterar o nome retirada
//função de alterar curso retirada
//função de pegar curso retirada
//função de imprimir curso retirada

//----------> FUNÇÕES - DUPLAMENTE ENCADEADA (LISTA DE ALUNOS) <----------//


//inicializa uma lista de pessoas
ListaDePessoas* cria_ldp(){  //MUDAR POR CAUSA DO DESCRITOR
    return NULL;
}

//verifica se uma lista de pessoas está vázia
int ldp_vazia(ListaDePessoas** lda){  //MUDAR POR CAUSA DO DESCRITOR
    return (*lda == NULL);
}


//função de buscar elemento retirada


void inserir_aluno(ListaDePessoas** ldp){  //MUDAR POR CAUSA DO DESCRITOR

lt();

    linha();

    printf("\n INSERIR NOVO ALUNO");

    linha();

    printf("\n");

    ListaDePessoas* novo_entrevistado = malloc(sizeof(ListaDePessoas));
    ListaDePessoas* p;

    if(novo_entrevistado){

        novo_entrevistado->pessoa = *le_pessoa();

        lt();
        
        if(*ldp == NULL){  //INSERE O PRIMEIRO ELEMENTO DA LISTA
            
            novo_entrevistado->proximo = novo_entrevistado->anterior = NULL;
            *ldp = novo_entrevistado;

        }
        /*              
        else if(strcmp(n->aluno.nome, (*ldp)->aluno.nome) < 0){  //INSERE ANTES DO PRIMEIRO ELEMENTO
            
            n->proximo = *ldp;
            n->anterior = NULL;
            (*ldp)->anterior = n;
            *ldp = n;

        }*/
        else{  //INSERE DEPOIS DO PRIMEIRO ELEMENTO...

            if(strcmp(n->aluno.nome, p->aluno.nome) < 0){ //INSERE ANTES DE P
                
                n->proximo = p;
                n->anterior = p->anterior;                        
                p->anterior->proximo = n;                        
                p->anterior = n;
                
            }else{  //INSERE DEPOIS DE P

                n->proximo = p->proximo;
                n->anterior = p;
                p->proximo = n;

            }
            
        }
    }else{

        printf("\nOPS! ALGO DEU ERRADO AQUI, DESCULPE-NOS PELO TRANSTORNO... T-T");

    }
}

void alterar_dados(ListaDeAlunos** lda){  //TROCAR NOMES DE VARÁVEIS AQUI

    int id_buscado;

    lt();

    linha();

    printf("\n ALTERAR DADOS DE UM ALUNO");

    linha();

    id_buscado = 0;

    printf("\n ID DO ALUNO: ");
    scanf("%d", &id_buscado);
    lb();

    if(!lda_vazia(&(*lda))){

        ListaDeAlunos* w;

        for(w = *lda; w->proximo != NULL && w->aluno.id != id_buscado; w = w->proximo);

        if(w->aluno.id == id_buscado){

            lb();
            alterarNome(&w->aluno);
            lb();
            alterarCurso(&w->aluno);
            lb();

        }else{

            printf("\n ALUNO NÃO ENCONTRADO!");

        }

        ListaDeAlunos* n = malloc(sizeof(ListaDeAlunos));
        ListaDeAlunos* p;

        if(n){

            n->aluno = w->aluno;

            //-------> REMOÇÃO DA CÓPIA DO ALUNO DA LISTA <-----------------------------

            ListaDeAlunos* z = buscar_elemento(&(*lda), id_buscado);

            if(*lda == z){

                *lda = z->proximo;

            }else{

                z->anterior->proximo = z->proximo;

            }
            if(z->proximo != NULL){

                z->proximo->anterior = z->anterior;
                free(z);

            }

            //-------> INSERÇÃO DO ALUNO COM DADOS TROCADOS NO LUGAR CORRETO DA LISTA <-----------------------------

            if(*lda == NULL){  //INSERÇÃO EM PRIMEIRO NA LISTA ESTÁ OK
                
                n->proximo = n->anterior = NULL;
                *lda = n;

            }else if(strcmp(n->aluno.nome, (*lda)->aluno.nome) < 0){  //INSERÇÃO NO INÍCIO DA LISTA ESTÁ OK

                n->proximo = *lda;
                n->anterior = NULL;
                (*lda)->anterior = n;
                *lda = n;

            }else{  //INSERÇÃO COM VÁRIOS VALORES EM ORDEM DECRESCENTE FUNCIONANDO PERFEITAMENTE... fedcba...

                for(p = *lda; p->proximo != NULL && strcmp(n->aluno.nome, p->aluno.nome) > 0; p = p->proximo);

                if(strcmp(n->aluno.nome, p->aluno.nome) < 0){ //se n vem antes de P

                    n->proximo = p;
                    n->anterior = p->anterior;                        
                    p->anterior->proximo = n;                        
                    p->anterior = n;

                }else{

                    n->proximo = p->proximo;
                    n->anterior = p;
                    p->proximo = n;

                }
            }

        }else{

            printf("\n ESTAMOS COM ALGUM PROBLEMA! T-T");
            printf("\n NÃO SERÁ POSSÍVEL ADICIONAR UM ALUNO!");

        }

    }else{

        lt();
        printf("\n A LISTA DE ALUNOS ESTÁ VAZIA!");
        printf("\n POR FAVOR INSIRA UM ALUNO ANTES DE TENTAR ALTERAR OS DADOS!");

    }
}

void remover_aluno(ListaDeAlunos** lda){  //NÃO PRECISO MUDAR NADA AQUI

    int id_buscado;

    lt();
        
    linha();
    
    printf("\n REMOVER UM ALUNO");

    linha();

    if(!lda_vazia(&(*lda))){

        id_buscado = 0;

        printf("\n ID DO ALUNO: ");
        scanf("%d", &id_buscado);
        lb();

        ListaDeAlunos* p = buscar_elemento(&(*lda), id_buscado);

        if (p){

            if(*lda == p){ // REMOVE O PRIMEIRO ALUNO

                *lda = p->proximo;

            }else{ // REMOVE ULTIMO ALUNO

                p->anterior->proximo = p->proximo;

            }

            if(p->proximo != NULL){ // REMOVE ALUNO NO MEIO

                p->proximo->anterior = p->anterior;
                
            }

        }else{

            printf("\n O ALUNO NÃO ENCONTRADO! ");

        }

        free(p);

        for(ListaDeAlunos* p = *lda; p != NULL; p = p->proximo){  //PERCORRE TODA A DUPLAMENTE ENCADEADA
            
            if(p->aluno.prox_amg){  //SE A MINHA SIMPLESMENTE ENCADEADA EXISTIR, ELA SERÁ PERCORRIDA

                remove_relacao(&p->aluno.prox_amg, id_buscado); 

            }else{

                printf("\n QUE TRISTE, ESSE ALUNO NÃO TEM AMIGOS... T-T");

            }
        }
    
    }else{

        lt();

        linha();

        printf("\n A LISTA DE ALUNOS ESTÁ VAZIA!");
        printf("\n POR FAVOR INSIRA UM ALUNO ANTES DE TENTAR REMOVÊ-LO!");

    }
}


void imprime_alunos(ListaDeAlunos **lda){  //NÃO PRECISO MEXER EM NADA AQUI...

    lt();

    linha();

    printf("\n LISTA DE ALUNOS");

    linha();

    if(!lda_vazia(&(*lda))){

        printf("\n");

        for(ListaDeAlunos* p = *lda; p != NULL; p = p->proximo){

            imprimeAluno(&p->aluno);

        }
        
        printf("\n");

    }else{

        lt();

        linha();

        printf("\n A LISTA DE ALUNOS ESTÁ VAZIA!");
        printf("\n POR FAVOR INSIRA UM ALUNO NA LISTA ANTES DE TENTAR IMPRIMI-LA!");

    }
}

void criar_relacao(ListaDeAlunos **lda){  //NÃO PRECISO MEXER EM NADA AQUI...

    int id_buscado, id_buscado_2;

    lt();

    linha();

    printf("\n CRIAR RELAÇÃO DE AMIZADE");

    linha();

    if(!lda_vazia(&(*lda))){
        
        printf("\n ID DO PRIMEIRO ALUNO: ");
        scanf("%d", &id_buscado);
        lb();
        printf("\n ID DO SEGUNDO ALUNO: ");
        scanf("%d", &id_buscado_2);
        lb();

        ListaDeAlunos* busca_amigo_01 = buscar_elemento(&(*lda), id_buscado);  //FUNCIONANDO PERFEITAMENTE
        ListaDeAlunos* busca_amigo_02 = buscar_elemento(&(*lda), id_buscado_2);  //FUNCIONANDO PERFEITAMENTE

        insere_relacao(&busca_amigo_01->aluno.prox_amg, id_buscado_2);
        insere_relacao(&busca_amigo_02->aluno.prox_amg, id_buscado);

    }else{

        lt();

        printf("\n A LISTA DE ALUNOS ESTÁ VAZIA!");
        printf("\n POR FAVOR INSIRA PELO MENOS DOIS ALUNO ANTES DE TENTAR CRIAR UMA RELAÇÃO DE AMIZADE!");

    }
}

void remover_relacao(ListaDeAlunos** lda){  //NÃO PRECISO MEXER EM NADA AQUI...

    int id_buscado, id_buscado_2;

    lt();

    linha();

    printf("\n REMOVER RELAÇÃO DE AMIZADE: ");

    linha();

    if(!lda_vazia(&(*lda))){
        
        printf("\n ID DO PRIMEIRO ALUNO: ");
        scanf("%d", &id_buscado);
        lb();
        printf("\n ID DO SEGUNDO ALUNO: ");
        scanf("%d", &id_buscado_2);
        lb();

        ListaDeAlunos* busca_amigo_01 = buscar_elemento(&(*lda), id_buscado);  
        ListaDeAlunos* busca_amigo_02 = buscar_elemento(&(*lda), id_buscado_2);

        remove_relacao(&busca_amigo_01->aluno.prox_amg, id_buscado_2);
        remove_relacao(&busca_amigo_02->aluno.prox_amg, id_buscado);

    }else{

        lt();

        printf("\n NÃO TEM COMO ACABAR COM UMA AMIZADE SE ELA NÃO EXISTE!");

    }
}

void imprimir_relacao(ListaDeAlunos** lda){  //NÃO PRECISO MUDAR NADA AQUI...

    int id_buscado;

    lt();

    linha();

    printf("\n IMPRIMIR RELAÇÕES DE AMIZADE");

    linha();

    id_buscado = 0;

    printf("\n ID DO ALUNO: ");
    scanf("%d", &id_buscado);  
    lb();

    ListaDeAlunos* elo_buscado = buscar_elemento(&(*lda), id_buscado); //ACHA O ALUNO BUSCADO E SALVA NA VARIÁVEL

    if(elo_buscado){

        ListaDeAlunos* rel_amizade;

        int contador = 0;

        printf("\n AMIGOS DE %s", elo_buscado->aluno.nome);

        for(No* n = elo_buscado->aluno.prox_amg; n != NULL; n = n->prox){
            if(buscar_elemento(&(*lda), n->id)){

                rel_amizade = buscar_elemento(&(*lda), n->id);
                ++contador;

                printf("\n %d) %s", contador, rel_amizade->aluno.nome);
            }else{
                continue;
            }
        }

        if(elo_buscado->aluno.prox_amg == NULL){
            printf("\n QUE TRISTE! O ALUNO SELECIONADO NÃO TEM AMIGOS. T-T\n");
        }
    }else{
        printf("\n O ALUNO BUSCADO NÃO FOI ENCONTRADO, ADICIONE ALGUM ALUNO ANTES DE FAZER ALGUMA BUSCA!");
    }

   

}

void alunos_por_curso(ListaDeAlunos** lda){  //NÃO PRECISO  MUDAR NADA AQUI...

char curso_buscado[255];

lt();

    linha();

    printf("\n IMPRIMIR ALUNOS POR CURSO");

    linha();

    if(!lda_vazia(&(*lda))){

        printf("\n NOME DO CURSO: ");
        scanf("%[^\n]", curso_buscado);
        lb();

        char curso;
        int contador = 0;

        for(ListaDeAlunos* p = *lda; p != NULL; p = p->proximo){

            if(strcmp(curso_buscado, retornaCurso(&p->aluno)) == 0){

                imprimeAluno(&p->aluno);
                contador++;
            }
        }

        if(contador != 0){
            printf("\n CURSO NÃO ENCONTRADO NO SISTEMA!");
        }

    }else{

        lt();

        printf("\n A LISTA DE ALUNOS ESTÁ VAZIA!");
        printf("\n POR FAVOR INSIRA PELO MENOS UM ALUNO ANTES DE TENTAR IMPRIMIR A LISTA DO CURSO!");

    }

}

void inserir_dados_arquivo(ListaDeAlunos **lda)
{

    // lt();

    printf("\n");

    FILE *arquivo_txt = fopen("entradas.txt", "r");
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


void salvar_dados_arquivo(ListaDeAlunos **lda)
{

    lt();

    linha();

    printf("\n");

    FILE *arquivo_txt = fopen("entradas.txt", "w");

    for (ListaDeAlunos *p = *lda; p != NULL; p = p->proximo)
    {

        fprintf(arquivo_txt, "%s\t%d\t%s\n\t", p->aluno.nome, p->aluno.id, p->aluno.curso);

        for (No *n = p->aluno.prox_amg; n != NULL; n = n->prox)
        {
            fprintf(arquivo_txt, "%d ", n->id);
        }

        fprintf(arquivo_txt, "\n");
    }

    fclose(arquivo_txt);
}

int main(int argc, char** argv){
    setlocale(LC_ALL, "");

//-----> VARIÁVEIS PRINCIPAIS <------//
    ListaDePessoas* ldp;
    ldp = cria_ldp();


//-----> VARIÁVEIS SECUNDÁRIAS <-----//

    int escolha;
    bool condicao = true;

    //VARIÁVEIS RETIRADAS
    //int id_buscado, id_buscado_2;
    //char curso_buscado[255];

    inserir_dados_arquivo(&ldp);



//-----> O RESTO DA MAIN <-----//
    while(condicao){
        escolha = 0;

        linha();
        printf("\n ESCOLHA A OPÇÃO DESEJADA: ");
        linha();
        printf("\n 0 - ADICIONAR NOVO INTREVISTADO");
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

            inserir_aluno(&ldp);

            break;

        case 1:  //ALTERA OS DADOS DE UM ALUNO
            
            alterar_dados(&ldp);

            break;

        case 2:  //REMOVE OS DADOS DE UM ALUNO
                
            remover_aluno(&ldp);

            break;
            
        case 3:  //IMPRIME A LISTA DOS ALUNOS NA TELA

            imprime_alunos(&ldp);

            break;

        case 4:

            lt();

            salvar_dados_arquivo(&ldp);

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